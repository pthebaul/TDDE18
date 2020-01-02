#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;

//TODO: Complementary work needed, your main function should be pretty clean.
//Divide your program in multiple functions, each having one use.

//TODO: Complementary work neded, iterating through the entire alphabet for each character
//is far too inefficient. Use the library cctype which you have included.

// We took care of both concerns, we also added a syntax check

vector<string> every_potential_words_in_file(string & filename)
{
    // Opening file and handling eventual errors
    ifstream ifs{filename};

    if (!ifs.is_open())
    {
        cerr << "Error: Could not open file." << endl;
        throw invalid_argument("invalid filename");
    }

    // Getting every words from file
    return vector<string>(istream_iterator<string>(ifs), istream_iterator<string>());
}

void cleaning_words(vector<string> & vect)
{
    auto cleaning = [](string s)
        {
            string::size_type fno_pos{s.find_first_not_of("\"'(")};
            if (fno_pos == string::npos)
            {
                fno_pos = s.size();
            }
	    
            string::size_type lno_pos{s.find_last_not_of("!?;,:.\"')")};
	    
            s = s.substr(fno_pos, lno_pos+1);
	    
            if ((s.size() >= 2) && (s.substr(s.size() - 2) == "'s"))
            {
                s = s.substr(0, s.size() - 2);
            }
	    
            return s;
        };
    transform(vect.begin(), vect.end(), vect.begin(), cleaning);
}


void remove_invalid_words(vector<string> & vect)
{
    auto invalid_char = [](char c)
	{
	    return !isalpha(c) && (c != '-');
	};
    auto is_invalid = [&invalid_char](string s)
        {
            return (s.size() < 3)
            || any_of(s.begin(), s.end(), invalid_char)
            || (s.front() == '-') || (s.back() == '-')
            || (s.find("--") != string::npos);
        };
    
    // remove_if does not remove elements but shift them, so we have to erase them
    vect.erase(remove_if(vect.begin(), vect.end(), is_invalid), vect.end());
}

void put_words_in_lowercase(vector<string> & vect)
{
    auto str_lower = [](string s)
        {
            string result{s};
            transform(s.begin(), s.end(), result.begin(), [](char c) { return tolower(c); });
            return result;
        };
    transform(vect.begin(), vect.end(), vect.begin(), str_lower);
}

string::size_type length_of_longest_word(vector<string> & vect)
{
    auto compare_by_length = [](string const& l, string const& r)
	{
	    return l.size() < r.size();
	};
    return (*max_element(vect.begin(), vect.end(), compare_by_length)).size();
}

map<string, int> generate_frequency_map(vector<string> const& vect)
{
    map<string, int> result;
    auto add_to_result = [&result](string s)
	{
	    result[s]++;
	};
    for_each(vect.begin(), vect.end(), add_to_result);
    return result;
}

int length_of_largest_value(map<string, int> const& map)
{
    pair<string, int> last_pair{*(--map.end())};
    int largest_value{last_pair.second};
    return 1 + static_cast<int>(log(largest_value)/log(10));
}

void print_alphabetically(map<string, int> const& word_frequency_map, string::size_type const max_word_length)
{
    // Calculating the length of the largest frequency
    int max_number_length{length_of_largest_value(word_frequency_map)};
    
    // Formatting according to requirements
    auto format = [max_word_length, max_number_length](pair<string, int> const& l)
	{
	    ostringstream oss{};
	    oss << left << setw(max_word_length) << l.first;
	    oss << "  ";
	    oss << right << setw(max_number_length) << l.second;
	    oss << endl;

	    return oss.str();
	};
    transform(word_frequency_map.begin(), word_frequency_map.end(), ostream_iterator<string>(cout), format);
}

void print_by_frequency(map<string, int> const& word_frequency_map, string::size_type const max_word_length)
{
    // Calculating the length of the largest frequency
    int max_number_length{length_of_largest_value(word_frequency_map)};
    
    // Putting every word/frequency pair in a vector
    vector<pair<string, int>> word_frequency_vect{word_frequency_map.begin(), word_frequency_map.end()};

    // Sorting the vector by frequency
    auto compare_by_frequency = [](pair<string, int> const& l, pair<string, int> const& r)
	{
	    return l.second > r.second;
	};
    sort(word_frequency_vect.begin(), word_frequency_vect.end(), compare_by_frequency);

    // Formatting according to requirements
    auto format = [max_word_length, max_number_length](pair<string, int> const& l)
	{
	    ostringstream oss{};
	    oss << right;
	    oss << setw(max_word_length) << l.first;
	    oss << "  ";
	    oss << setw(max_number_length) << l.second;
	    oss << endl;

	    return oss.str();
	};
    transform(word_frequency_vect.begin(), word_frequency_vect.end(), ostream_iterator<string>(cout), format);
}

void print_in_original_order(vector<string> const& vect, string::size_type const line_size)
{
    string::size_type char_count{0};
    auto format = [&char_count, line_size](string s)
	{
	    // If printing the word would exceed the limit
	    if ((char_count + 1 + s.size()) >= line_size)
	    {
		cout << endl;
		char_count = 0;
	    }
	    // Else if it is not the first word
	    else if (char_count > 0)
	    {
		cout << " ";
		char_count++;
	    }
	    cout << s;
	    char_count += s.size();
	};
    for_each(vect.begin(), vect.end(), format);
    cout << endl;
}

int main(int argc, char* argv[])
{
    // Handling command-line arguments

    string filename{""};
    char option;
    try
    {
        if (argc <= 2)
        {
            cerr << "Error: Not enough arguments." << endl;
            throw 1;
        }
        else
        {
            filename = argv[1];
            option = argv[2][1];

            if ((argv[2][0] != '-') || ((option != 'a') && (option != 'f') && (option != 'o')))
            {
                cerr << "Error: Invalid second argument." << endl;
                throw 2;
            }
	    else if ((option == 'o') && (argc < 4))
	    {
		cerr << "Error: Not enough arguments." << endl;
		throw 1;
	    }
            else if (((option != 'o') && (argc > 3)) || (argc > 4))
            {
                cerr << "Error: Too many arguments." << endl;
                throw 3;
            }
        }
    }
    catch (int const& error_code)
    {
        cerr << "Usage: " << argv[0] << " FILE [-a] [-f] [-o N]" << endl;
        return error_code;
    }

    string::size_type line_size{0};
    if (option == 'o')
    {
        try
        {
            line_size = stoi(argv[3]);
            if (line_size <= 0)
            {
                throw out_of_range("Negative or equal to zero");
            }
        }
        catch(invalid_argument& e)
        {
            cerr << "Error: N must be an integer" << endl;
            return 4;
        }
        catch(out_of_range& e)
        {
            cerr << "Error: N must be a not-so-big strictly positive integer" << endl;
            return 5;
        }
    }
    
    // Putting all potential words in a vector
    vector<string> words;
    try
    {
	words = every_potential_words_in_file(filename);
    }
    catch (invalid_argument const& e)
    {
	return 6;
    }

    // Cleaning words : leading chars, trailing chars, trailing 's
    cleaning_words(words);


    // Keeping only valid words : no less than 3 characters, only letters and hyphens, no leading, trailing or consecutive hyphens
    remove_invalid_words(words);

    // Putting valid words in lowercase
    put_words_in_lowercase(words);

    // -a   : Sort alphabetically (ascending), format by left-aligned word, right-aligned frequency
    // -f   : Sort by decreasing frequency,    format by right-aligned word, right-aligned frequency
    // -o N : Keep the original order, with newlines to prevent lines getting bigger than N chars
    if (words.empty())
    {
        cerr << "Warning: No valid words found" << endl;
    }
    else
    {
        // Finding the length of the longest word
	string::size_type max_word_length{length_of_longest_word(words)};

        if (option != 'o')
        {
            // Counting occurences of words by putting them in a map
            map<string, int> word_frequency_map{generate_frequency_map(words)};
	    
            if (option == 'a')
            {
		print_alphabetically(word_frequency_map, max_word_length);
            }
            else
            {
		print_by_frequency(word_frequency_map, max_word_length);
            }
        }
        else
        {
            if (max_word_length >= line_size)
            {
                cerr << "Error: There is a words longer than " << line_size << " characters" << endl;
                return 7;
            }

	    print_in_original_order(words, line_size);
        }
    }
    return 0;
}
