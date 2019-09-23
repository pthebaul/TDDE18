#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
  int integer;
  
  cout << "Enter one integer: " << flush;
  cin >> integer;
  cout << "You entered the number: " << integer << endl;

  cin.ignore(1000, '\n');
  cout << endl;

  cout << "Enter four integers: " << flush;
  cin >> integer;
  cout << "You entered the numbers: " << integer << flush;
  cin >> integer;
  cout <<  " " << integer << flush;
  cin >> integer;
  cout << " " << integer << flush;
  cin >> integer;
  cout << " " << integer << endl;

  cin.ignore(1000, '\n');
  cout << endl;

  double real;
  
  cout << "Enter one integer and one real number: " << flush;
  cin >> integer;
  cin >> real;
  cout << fixed << setprecision(3) << right;
  cout << "The real is: " << setw(11) << real << endl;
  cout << "The integer is: " << setw(8) << integer << endl;
  
  cin.ignore(1000, '\n');
  cout << endl;

  cout << "Enter one real and one integer: " << flush;
  cin >> real;
  cin >> integer;
  cout << "The real is: " << setfill('.') << setw(11) << real << endl;
  cout << "The integer is: " << setw(8) << integer << endl;
  
  cin.ignore(1000, '\n');
  cout << endl;

  char letter;
  
  cout << "Enter a character: " << flush;
  cin >> letter;
  cout << "You entered: " << letter << endl;

  cin.ignore(1000, '\n');
  cout << endl;

  string word;
  
  cout << "Enter a word: " << flush;
  cin >> word;
  cout << "The word '" << word << "' has " <<
	  word.size() << " character(s)." << endl;

  cin.ignore(1000, '\n');
  cout << endl;

  cout << "Enter an integer and a word: " << flush;
  cin >> integer;
  cin >> word;
  cout << "You entered ´" << integer << "´ and ´" << word << "´." << endl;

  cin.ignore(1000, '\n');
  cout << endl;

  cout << "Enter a character and a word: " << flush;
  cin >> letter;
  cin >> word;
  cout << "You entered the string \"" << word <<
	  "\" and the character ´" << letter << "´." << endl;

  cin.ignore(1000, '\n');
  cout << endl;
  
  cout << "Enter a word and a real: " << flush;
  cin >> word;
  cin >> real;
  cout << "You entered \"" << word << "\" and \"" << real << "\"." << endl;

  cin.ignore(1000, '\n');
  cout << endl;

  cout << "Enter a text-line: " << flush;
  getline(cin, word);
  cout << "You entered: \"" << word << "\"" << endl;

  cout << endl;

  cout << "Enter a second line of text: " << flush;
  getline(cin, word);
  cout << "You entered: ´" << word << "\"" << endl;

  cout << endl;

  cout << "Enter three words: " << flush;
  cin >> word;
  cout << "You entered: ´" << word << flush;
  cin >> word;
  cout << " " << word << flush;
  cin >> word;
  cout << " " << word << "´" << endl;
  return 0;
}

