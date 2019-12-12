#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cctype>

using namespace std;

int main(int argc, char* argv[])
{
    // Get filename from command-line arguments
    
    bool syntax_error{false};
    int return_code{};
    if (argc <= 1)
    {
	syntax_error = true;
	cout << "Error: No arguments given." << endl;
	return_code = 1;
    }
    else if (argc <= 2)
    {
	syntax_error = true;
	cout << "Error: Second argument missing." << endl;
	return_code = 2;
    }
    else if ((strcmp(argv[2], "-a") != 0)
	     && (strcmp(argv[2], "-f") != 0)
	     && (strcmp(argv[2], "-o") != 0))
    {
	syntax_error = true;
	cout << "Error: Invalid second argument." << endl;
	return_code = 3;
    }
    else if (((strcmp(argv[2], "-o") != 0) && (argc > 3))
	     || ((strcmp(argv[2], "-o") == 0) && (argc > 4)))
    {
	syntax_error = true;
	cout << "Error: Too many arguments." << endl;
	return_code = 4;
    }

    if (syntax_error)
    {
	cout << "Usage: ./a.out FILE [-a] [-f] [-o N]" << endl;
	return return_code;
    }
    
    int line_size{};
    if (strcmp(argv[2], "-o") == 0)
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
	    cout << "N must be an integer" << endl;
	    cout << "Usage: ./a.out FILE [-a] [-f] [-o N]" << endl;
	}
	catch(out_of_range& e)
	{
	    cout << "N must be a not-so-big strictly positive integer" << endl;
	    cout << "Usage: ./a.out FILE [-a] [-f] [-o N]" << endl;
	}
    }
       
    // Open file with filename (handle errors)

    string filename{argv[1]};
    ifstream ifs{filename};

    if (!ifs.is_open())
    {
	cout << "Error: Could not open file." << endl;
	return 5;
    }
    
    // Put all potential words in a container ( >> string is good)
  
    vector<string> potential_words{istream_iterator<string>(ifs), istream_iterator<string>()};
    
    // Clean words : leading, trailing, 's
    vector<string> cleaned_words{};
    auto cleaning = [](string s)
    {
	string::size_type fno_pos{s.find_first_not_of("\"'(")};
	s = s.substr(fno_pos);
	string::size_type lno_pos{s.find_last_not_of("!?;,:.\"')")};
	s = s.substr(0, lno_pos+1);
	if ((s.size() >= 2) && (s.substr(s.size() - 2) == "'s"))
	{
	    s = s.substr(0, s.size() - 2);
	}
	return s;
    };

    transform(potential_words.begin(), potential_words.end(), back_inserter(cleaned_words), cleaning);
    
    
    // Keep only valid words : only letters and hyphens, no leading, trailing or consecutive hyphens, no less than 3 characters
    vector<string> valid_words{};
    auto is_valid = [](string s)
    {
	bool valid{true};
	if (s.size() < 3)
	{
	    valid = false;
	}
	else if (s.find_first_not_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM-") != string::npos)
	{
	    valid = false;
	}
	else if (s.find_first_of("--") != string::npos)
	{
	    valid = false;
	}
	else if (s.front() == '-' || s.back() == '-')
	{
	    valid = false;
	}
	return valid;
    };
    copy_if(cleaned_words.begin(), cleaned_words.end(), back_inserter(valid_words), is_valid);

    auto str_lower = [](string s)
    {
	string result{s};
	transform(s.begin(), s.end(), result.begin(), [](char c) { return tolower(c); });
	return result;
    };
    transform(valid_words.begin(), valid_words.end(), valid_words.begin(), str_lower);
    
    // -a   : Sort alphabetically (ascending), format by left-aligned word, right-aligned frequency
    // -f   : Sort by decreasing frequency,    format by right-aligned word, right-aligned frequency
    // -o N : Sort by occurence in the file, with newlines to prevent lines getting bigger than N

    if (strcmp(argv[2], "-o") != 0)
    {
	map<string, int> m;
	auto add_to_m = [&m](string s)
	{
	    m[s]++;
	};
	for_each(valid_words.begin(), valid_words.end(), add_to_m);

	vector<pair<string, int>> vect{};
	copy(m.begin(), m.end(), back_inserter(vect));

	auto compare = [](pair<string, int> const& l, pair<string, int> const& r)
	{
	    return l.second > r.second;
	};
	sort(vect.begin(), vect.end(), compare);	    
	

	
	auto print = [](pair<string, int> x)
	{
	    cout << x.first << ':' << x.second << endl;
	};
	
	for_each(vect.begin(), vect.end(), print);
	cout << endl;
	for_each(m.begin(), m.end(), print);
	
    }
    return 0;
}

