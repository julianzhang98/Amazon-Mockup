#include "book.h"
#include "util.h"
#include <sstream>
using namespace std;

Book::Book(const string category, const string name, double price, int qty, string isbn, string author)
		: Product(category, name, price, qty), isbn_(isbn), author_(author)
{
}


/**
 * Returns the appropriate keywords that this product should be associated with
 */
set<string> Book::keywords() const {
	string temp = name_ + " " + author_;
	set<string> words = parseStringToWords(temp);
	words.insert(isbn_);
	return words;
}

/**
 * Returns a string to display the product info for hits of the search
 */
string Book::displayString() const {
	stringstream ss;
	ss << "\n" << price_ << " " << qty_ << " left.";
	return (name_ + "\nAuthor: " + author_ + " ISBN: " + isbn_ + ss.str());
}

/**
 * Outputs the product info in the database format
 */
void Book::dump(std::ostream& os) const {
	os << category_ << endl;
	os << name_ << endl;
	os << price_ << endl;
	os << qty_ << endl;
	os << isbn_ << endl;
	os << author_ << endl;
}
