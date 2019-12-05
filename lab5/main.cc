#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    bool syntax_error{false};
    if (argc <= 1)
    {
	syntax_error = true;
	cout << "Error: No arguments given." << endl;
	return 1;
    }
    else if (argc <= 2)
    {
	syntax_error = true;
	cout << "Error: Second argument missing." << endl;
	return 2;
    }
    else if ((argv[3] != "-a") && (argv[3] != "-f") && (argv[3] != "-o"))
    {
	syntax_error = true;
	cout << "Error: Invalid second argument." << endl;
	return 3;
    }
    else if (((argv[3] != "-o") && (argc > 3))
	     || ((argv[3] == "-o") && (argc > 4)))
    {
	syntax_error = true;
	cout << "Error: Too many arguments." << endl;
	return 4;
    }

    if (syntax_error)
    {
	cout << "Usage: ./a.out FILE [-a] [-f] [-o N]" << endl;
    }
    
    // Get filename from command-line arguments

    // Open file with filename (handle errors)

    // Put all potential words in a container ( >> string is good)

    // Clean words : leading, trailing, 's

    // Keep only valid words : only letters and hyphens, no leading, trailing or consecutive hyphens, no less than 3 characters

    // -a   : Sort alphabetically (ascending), format by left-aligned word, right-aligned frequency
    // -f   : Sort by decreasing frequency,    format by right-aligned word, right-aligned frequency
    // -o N : Sort by occurence in the file, with newlines to prevent lines getting bigger than N
    return 0;
}
