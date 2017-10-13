#include "movie.h"
#include "util.h"
#include <sstream>
using namespace std;

Movie::Movie(const string category, const string name, double price, int qty, string genre, string rating)
		: Product(category, name, price, qty), genre_(genre), rating_(rating)
{
}

/**
 * Returns the appropriate keywords that this product should be associated with
 */
set<string> Movie::keywords() const {
	string temp = name_ + " " + genre_;
	return parseStringToWords(temp);
}

/**
 * Returns a string to display the product info for hits of the search
 */
string Movie::displayString() const {
	stringstream ss;
	ss << "\n" << price_ << " " << qty_ << " left.";
	return (name_ + "\nGenre: " + genre_ + " Rating: " + rating_ + ss.str());
}

/**
 * Outputs the product info in the database format
 */
void Movie::dump(std::ostream& os) const {
	os << category_ << endl;
	os << name_ << endl;
	os << price_ << endl;
	os << qty_ << endl;
	os << genre_ << endl;
	os << rating_ << endl;
}
