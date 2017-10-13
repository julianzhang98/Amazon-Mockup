#include "clothing.h"
#include "util.h"
#include <sstream>
using namespace std;

Clothing::Clothing(const string category, const string name, double price, int qty, string size, string brand)
		: Product(category, name, price, qty), size_(size), brand_(brand)
{
}

/**
 * Returns the appropriate keywords that this product should be associated with
 */
set<string> Clothing::keywords() const {
	string temp = name_ + " " + brand_;
	return parseStringToWords(temp);
}

/**
 * Returns a string to display the product info for hits of the search
 */
string Clothing::displayString() const {
	stringstream ss;
	ss << "\n" << price_ << " " << qty_ << " left.";
	return (name_ + "\nSize: " + size_ + " Brand: " + brand_ + ss.str());
}

/**
 * Outputs the product info in the database format
 */
void Clothing::dump(std::ostream& os) const {
	os << category_ << endl;
	os << name_ << endl;
	os << price_ << endl;
	os << qty_ << endl;
	os << size_ << endl;
	os << brand_ << endl;
}
