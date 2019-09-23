#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
    int word_count{0};
    int char_count{0};
    string shortest_word{""};
    string longest_word{""};
    ifstream ifs{"data.txt"};
    string word;
    while (ifs >> word)
    {
	word_count++;
	char_count += word.size();
	if ((shortest_word == "") and (longest_word == ""))
	{
	    shortest_word = word;
	    longest_word = word;
	}
	else
	{
	    if (word.size() < shortest_word.size())
	    {
		shortest_word = word;
	    }
	    if (word.size() > longest_word.size())
	    {
		longest_word = word;
	    }
	}
    }

  
    cout << "There are " << word_count << " words in the file." << endl;
    cout << "The shortest word was \"" << shortest_word <<
	"\" with " << shortest_word.size() << " character(s)." << endl;
    cout << "The longest word was \"" << longest_word <<
	"\" with " << longest_word.size() << " character(s)." << endl;
    cout << "The average length was " <<
	static_cast<double>(char_count) / word_count << " character(s)." << endl;
    return 0;
}

