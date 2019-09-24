#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
    double first_price;
    double last_price;
    double stride;
    int tax_percent;
    bool error;

    cout << fixed << setprecision(2) << endl;

    cout << "INPUT PART" << endl;
    cout << "==========" << endl;

    do
    {
	cout << "Enter first price: " << flush;
	cin >> first_price;
	cin.ignore(1000,'\n');

	error = (first_price < 0);
	if (error)
	{
	    cout << "ERROR: First price must be at least 0 (zero) EUR" << endl;
	}
    }
    while (error);

    do
    {
	cout << "Enter last price : " << flush;
	cin >> last_price;
	cin.ignore(1000,'\n');

	error = (last_price <= first_price);
	if (error)
	{
	    cout << "ERROR: Last price must be greater than first price" << endl;
	}
    }
    while (error);

    do
    {
	cout << "Enter stride     : " << flush;
	cin >> stride;
	cin.ignore(1000,'\n');

	error = ((stride >= (last_price - first_price)) or (stride <= 0));
	if (error)
	{
	    cout << "ERROR: Stride is too big, or is less or equal than 0" << endl;
	}
    }
    while (error);

    do
    {
	cout << "Enter tax percent: " << flush;
	cin >> tax_percent;
	cin.ignore(1000,'\n');

	error = ((tax_percent <= 0) or (tax_percent > 100));
	if (error)
	{
	    cout << "ERROR: Tax percent must be between 0 and 100" << endl;
	}
    }
    while (error);
      
    cout << endl;
			  
    cout << "TAX TABLE" << endl;
    cout << "=========" << endl;

    cout << right
	 << setw(12) << "Price"
	 << setw(17) << "Tax"
	 << setw(20) << "Price with tax" << endl;
    cout << setfill('-') << setw(49) << "" << setfill(' ') << endl;

    double current_price;
    double current_tax;
    for (int i{0}; i <= (last_price-first_price)/stride; ++i)
    {
	current_price = first_price + i*stride;
	current_tax = tax_percent*current_price/100;
	cout << setw(12) << current_price
	     << setw(17) << current_tax
	     << setw(20) << current_price + current_tax << endl;
    }

    cout << endl;
    return 0;
}
