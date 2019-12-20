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

// Opening file and handling eventual errors
    ifstream ifs{filename};

    if (!ifs.is_open())
    {
        cerr << "Error: Could not open file." << endl;
        return 6;
    }

// Putting all potential words in a vector
    vector<string> words{istream_iterator<string>(ifs), istream_iterator<string>()};


// Cleaning words : leading chars, trailing chars, trailing 's
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
    transform(words.begin(), words.end(), words.begin(), cleaning);


// Keeping only valid words : no less than 3 characters, only letters and hyphens, no leading, trailing or consecutive hyphens
    auto is_invalid = [](string s)
        {
            return (s.size() < 3)
            || (s.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-") != string::npos)
            || (s.front() == '-') || (s.back() == '-')
            || (s.find("--") != string::npos);
        };

    // remove_if does not remove elements but shift them, so we have to erase them
    words.erase(remove_if(words.begin(), words.end(), is_invalid), words.end());

// Putting valid words in lowercase
    auto str_lower = [](string s)
        {
            string result{s};
            transform(s.begin(), s.end(), result.begin(), [](char c) { return tolower(c); });
            return result;
        };
    transform(words.begin(), words.end(), words.begin(), str_lower);

// -a   : Sort alphabetically (ascending), format by left-aligned word, right-aligned frequency
// -f   : Sort by decreasing frequency,    format by right-aligned word, right-aligned frequency
// -o N : Keep the original order, with newlines to prevent lines getting bigger than N chars
    if (words.empty())
    {
        cerr << "Warning: No valid words found" << endl;
    }
    else
    {
        // Finding the longest word
        auto compare_by_length = [](string const& l, string const& r)
            {
                return l.size() < r.size();
            };
        string::size_type longest_word_length{(*max_element(words.begin(), words.end(), compare_by_length)).size()};

        if (option != 'o')
        {
            // Counting occurences of words by putting them in a map
            map<string, int> word_frequency_map;
            auto add_to_word_frequency_map = [&word_frequency_map](string s)
                {
                    word_frequency_map[s]++;
                };
            for_each(words.begin(), words.end(), add_to_word_frequency_map);

            // Calculating the length of the biggest number

            int longest_number_length{1 + static_cast<int>(log((--word_frequency_map.end())->second)/log(10))};
            if (option == 'a')
            {
                // Formatting according to requirements
                auto format = [longest_word_length, longest_number_length](pair<string, int> const& l)
                    {
                        ostringstream oss{};
                        oss << left << setw(longest_word_length) << l.first;
                        oss << "  ";
                        oss << right << setw(longest_number_length) << l.second;
                        oss << endl;

                        return oss.str();
                    };
                transform(word_frequency_map.begin(), word_frequency_map.end(), ostream_iterator<string>(cout), format);
            }
            else
            {
                // Putting every word/frequency pair in a vector
                vector<pair<string, int>> word_frequency_vect{word_frequency_map.begin(), word_frequency_map.end()};

                // Sorting the vector by frequency
                auto compare_by_frequency = [](pair<string, int> const& l, pair<string, int> const& r)
                    {
                        return l.second > r.second;
                    };
                sort(word_frequency_vect.begin(), word_frequency_vect.end(), compare_by_frequency);

                // Formatting according to requirements
                auto format = [longest_word_length, longest_number_length](pair<string, int> const& l)
                    {
                        ostringstream oss{};
                        oss << right;
                        oss << setw(longest_word_length) << l.first;
                        oss << "  ";
                        oss << setw(longest_number_length) << l.second;
                        oss << endl;

                        return oss.str();
                    };
                transform(word_frequency_vect.begin(), word_frequency_vect.end(), ostream_iterator<string>(cout), format);
            }
        }
        else
        {
            if (longest_word_length >= line_size)
            {
                cerr << "Error: There is a words longer than " << line_size << " characters" << endl;
                return 7;
            }

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
            for_each(words.begin(), words.end(), format);
            cout << endl;
        }
    }
    return 0;
}
