#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>

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
    auto clean_word = [](string s)
    {
	string::size_type fno_pos{s.find_first_not_of("\"'(")};
	s = s.substr(fno_pos);
	string::size_type lno_pos{s.find_last_not_of("!?;,:.\"')")};
	s = s.substr(0, lno_pos+1);
	string::size_type rf_pos{s.rfind("'s")};
	s = s.substr(0, rf_pos);
	cout << s << endl;
	return s;
    };

    transform(potential_words.begin(), potential_words.end(), back_inserter(cleaned_words), clean_word);
    
    
    // Keep only valid words : only letters and hyphens, no leading, trailing or consecutive hyphens, no less than 3 characters

    // -a   : Sort alphabetically (ascending), format by left-aligned word, right-aligned frequency
    // -f   : Sort by decreasing frequency,    format by right-aligned word, right-aligned frequency
    // -o N : Sort by occurence in the file, with newlines to prevent lines getting bigger than N

      if (strcmp(argv[2], "-o") != 0)
    {
	map<string, int> m;
	
    }
    return 0;
}

