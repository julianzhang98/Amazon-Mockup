#include "mydatastore.h"
#include <cmath>
#include <fstream>
using namespace std;

/**
 * Adds a product to the data store
 */


MyDataStore::~MyDataStore() {

	// deallocate the users and products and reviews that were dynamically allocated earlier
	set<Product*>::const_iterator p_it;
	map<string,User*>::const_iterator u_it;
	map<string,vector<Review*> >::const_iterator r_it;

	for (p_it = products_.begin(); p_it != products_.end(); ++p_it) {
		delete *(p_it);
	}
	for (u_it = usernames_.begin(); u_it != usernames_.end(); ++u_it) {
		delete u_it->second;
	}

	//map<string,vector<Review*> > reviews_;
	for (r_it = reviews_.begin(); r_it != reviews_.end(); ++r_it) {
		//for (unsigned int i = (r_it->second).size()-1; i >= 0; i--) {
		for (unsigned int i = 0; i < (r_it->second).size(); i++) {
			delete (r_it->second)[i];
		}
	}



}

void MyDataStore::addProduct(Product* p) {
	products_.insert(p);

	set<string> words = p->keywords(); // set of keywords belonging to that product

	for (set<string>::const_iterator it = words.begin(); it != words.end(); ++it) {
		map<string,set<Product*> >::iterator mit = keyWordMap_.find(*it);
		if (mit == keyWordMap_.end()) { 
			// if the keywordmap does not have this keyword yet
			set<Product*> temp;
			temp.insert(p);
			keyWordMap_.insert(make_pair(*it, temp));
		} else {
			// if the keywordmap has this keyword already
			(mit->second).insert(p); // might need a * idk yet [?]

		}
	}
}

/**
 * Adds a user to the data store
 */
void MyDataStore::addUser(User* u) {

	vector<Product*> cart; // empty cart (vector because FIFO)
	users_.insert(make_pair(u, cart)); // might deallocate? [?] probably not though
	usernames_.insert(make_pair(u->getName(), u));

}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
vector<Product*> MyDataStore::search(vector<string>& terms, int type) {

	set<Product*> finalSet; // this is the set that we are making

	if (type == 0) {

		finalSet = products_; // if it's intersection, start with all the products

		for (unsigned int i = 0; i < terms.size(); i++) { // goes through all the search terms
			map<string,set<Product*> >::iterator it = keyWordMap_.find(terms[i]); // terms[i] is a string
			if (it != keyWordMap_.end()) { // if the search term matches a keyword
				// all the products with that keyword are in (it->second), which is a set of product*s

				finalSet = setIntersection(finalSet, (it->second));

			} else { // if an element is not a keyword it automatically returns an empty set
				set<Product*> empty;
				finalSet = empty;
			}	
		}
	} else {

		for (unsigned int i = 0; i < terms.size(); i++) { // goes through all the search terms
			map<string,set<Product*> >::iterator it = keyWordMap_.find(terms[i]); // terms[i] is a string

			if (it != keyWordMap_.end()) { // if the search term matches a keyword
				// all the products with that keyword are in (it->second), which is a set of product*s
				finalSet = setUnion(finalSet, (it->second));
			}	
		}
	}

	vector<Product*> hits;
	for (set<Product*>::const_iterator it = finalSet.begin(); it != finalSet.end(); ++it) {
		hits.push_back(*it); // copies the set into a vector
	}
	return hits;

}

/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(ostream& ofile) {


	ofile << "<products>" << endl;

	set<Product*>::const_iterator p_it;
	for (p_it = products_.begin(); p_it != products_.end(); ++p_it) {
		(*p_it)->dump(ofile); // for the products
	}

	ofile << "</products>" << endl << "<users>" << endl;

	map<string,User*>::const_iterator u_it;
	for (u_it = usernames_.begin(); u_it != usernames_.end(); ++u_it) {
		(u_it->second)->dump(ofile); // for the users
	}

	ofile << "</users>" << endl << "<reviews>" << endl;

	map<string,vector<Review*> >::const_iterator r_it;
	for (r_it = reviews_.begin(); r_it != reviews_.end(); ++r_it) {
		for (unsigned int i = 0; i < (r_it->second).size(); i++) {
			Review * temp = (r_it->second)[i];
			ofile << temp->prodName << endl;
			ofile << temp->rating << " " << temp->username << " " << temp->date << " " << temp->reviewText << endl;
		}
	}


	ofile << "</reviews>" << endl;

}

void MyDataStore::addToCart(string u, vector<Product*> hits, int index) {

	if ((unsigned int)index > hits.size() || index < 1) {
		cout << "Invalid request" << endl; // if index out of bounds
		return;
	} 
	Product* p = hits[index-1];

	map<string,User*>::iterator userNamedU = usernames_.find(u);
	User* user_u = userNamedU->second;
	if (userNamedU == usernames_.end()) {
		cout << "Invalid request" << endl; // if invalid username
		return;
	}

	map<User*,vector<Product*> >::iterator it = users_.find(user_u);
	(it->second).push_back(p);
}

void MyDataStore::removeFromCart(string u, int index) {
	map<User*,vector<Product*> >::iterator it = users_.find((usernames_.find(u))->second);

	for (unsigned int i = index; i < (it->second).size()-1; i++) {
		(it->second)[i] = (it->second)[i+1];
	}
	(it->second).pop_back();
}

void MyDataStore::viewCart(string u) {
	map<string,User*>::iterator userNamedU = usernames_.find(u);

	if (userNamedU == usernames_.end()) {
		cout << "Invalid username" << endl;
		return;
	}
	User* user_u = userNamedU->second;

	map<User*,vector<Product*> >::iterator it = users_.find(user_u);
	displayCart(it->second); // prints the cart

}

void MyDataStore::displayCart(vector<Product*>& cart) { // prints the cart
    int resultNo = 1;
    for(vector<Product*>::iterator it = cart.begin(); it != cart.end(); ++it) {
        cout << "Item " << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}

void MyDataStore::buyCart(string u) {
	map<string,User*>::iterator userNamedU = usernames_.find(u);
	User* user_u = userNamedU->second;

	if (userNamedU == usernames_.end()) {
		cout << "Invalid username" << endl;
		return;
	}

	map<User*,vector<Product*> >::iterator it = users_.find(user_u);


	// (it->first) is the user pointer
	// (it->second) is the cart vector

	User* person = it->first;
	vector<Product*> cart = it->second;

	vector<int> itemsNotRemoved;


	for (unsigned int i = 0; i < cart.size(); i++) {
		double bal = person->getBalance();
		double price = cart[i]->getPrice();
		int stock = cart[i]->getQty();

		if (bal >= price && stock > 0) {
			person->deductAmount(price); // deduct price from balance
			cart[i]->subtractQty(1); // subtract 1 from stock
		} else {
			itemsNotRemoved.push_back(i);
		}

	}

	vector<Product*> updatedCart;
	for (unsigned int i = 0; i < itemsNotRemoved.size(); i++) {
		updatedCart.push_back(cart[itemsNotRemoved[i]]);
	}

	it->second = updatedCart;

}

void MyDataStore::addReview(Review* r) {
	map<string,vector<Review*> >::iterator it = reviews_.find(r->prodName);
	if (it == reviews_.end()) {
		vector<Review*> temp;
		temp.push_back(r);
		reviews_.insert(make_pair(r->prodName, temp));
		assignProductRatings(); // do average ratings every time a review is inserted.
		return;
	}
	(it->second).push_back(r);
	assignProductRatings(); // do average ratings every time a review is inserted.
}

void MyDataStore::assignProductRatings() {

	for (set<Product*>::const_iterator sit = products_.begin(); sit != products_.end(); ++sit) {
		string productName = (*sit)->getName();
		map<string,vector<Review*> >::iterator it = reviews_.find(productName);

		// if no reviews exist yet
		if (it == reviews_.end()) {
			(*sit)->setRating(0);
		} else {
			double temp = 0;
			for (unsigned int j = 0; j < (it->second).size(); j++) {
				temp += (it->second)[j]->rating; 
			}
			temp /= (int)(it->second.size());
			(*sit)->setRating(temp);
		}

	}

}

map<string,User*>& MyDataStore::getUsers() {
	return usernames_;
}

set<Product*>& MyDataStore::getProducts() {
	return products_;
}

map<User*,vector<Product*> >& MyDataStore::getCarts() {
	return users_;
}

map<string,vector<Review*> >& MyDataStore::getReviews() {
	return reviews_;
}


double MyDataStore::calculateBasicSimilarities(User * u1, User * u2) {

	// can we use the setIntersection?
	set<Product*> p_u1;
	set<Product*> p_u2;

	// go through reviews
	for (set<Product*>::const_iterator it = products_.begin(); it != products_.end(); ++it) {
		map<string, vector<Review*> >::iterator mit = reviews_.find((*it)->getName());

		if(mit == reviews_.end()) { // this product has no reviews yet
			continue;
		}


		for (unsigned int i = 0; i < (mit->second).size(); i++) {
			if ((mit->second)[i]->username == u1->getName()) {
				p_u1.insert(*it);
			} else if ((mit->second)[i]->username == u2->getName()) {
				p_u2.insert(*it);
			}
		}
	}

	set<Product*> intersection = setIntersection(p_u1, p_u2);

	int reviewed = intersection.size(); // If there are no products in common
	if (reviewed == 0) {
		return 1;
	}


	double score1 = 0;
	double score2 = 0;

	double averageSum = 0;

	for (set<Product*>::const_iterator it = intersection.begin(); it != intersection.end(); ++it) {
		map<string, vector<Review*> >::iterator mit = reviews_.find((*it)->getName());
		for (unsigned int i = 0; i < (mit->second).size(); i++) {
			if ((mit->second)[i]->username == u1->getName()) {
				score1 = (mit->second)[i]->rating;
			} else if ((mit->second)[i]->username == u2->getName()) {
				score2 = (mit->second)[i]->rating;
			}
		}

		// once I have the two scores
		double diffOver4 = abs(score1-score2) / 4.0;
		averageSum += diffOver4;
	}

	double average = averageSum / (double)reviewed;
	return average;
}

map<string, double> MyDataStore::calculateRefinedSimilarities(User * source) {

	less<double> param1;
	hash<string> param2;
	equal_to<string> param3;
	Heap<string, equal_to<string>, less<double>, hash<string> > myheap(2, param1, param2, param3);

	map<string, double> lockedIn; // will be returned
	set<string> notLockedIn;

	lockedIn.insert(make_pair(source->getName(), 0));


	for (map<string, User*>::const_iterator it = usernames_.begin(); it != usernames_.end(); ++it) {

		string thisName = it->first;
		User * thisUser = it->second;

		if (thisUser == source) {
			continue; // we don't need to add this to heap
		}

		double distance = calculateBasicSimilarities(source, thisUser);
		myheap.push(distance, thisName);

		notLockedIn.insert(thisName);
		lockedIn.insert(make_pair(thisName, distance)); // push users into map
	}

	// NOW ALL THE USERS ARE IN THE HEAP EXCEPT FOR THE SOURCE

	while (myheap.empty() == false) {

		string curr = myheap.top(); // top element
		notLockedIn.erase(curr); // since you're visiting it you lock it in
		myheap.pop(); // remove the top element


		User * user1 = (usernames_.find(curr))->second;
		User * user2; // declare the users to be compared

		for (set<string>::const_iterator it = notLockedIn.begin(); it != notLockedIn.end(); ++it) {
			// goes through all the nodes that have not been locked in
			
			user2 = (usernames_.find(*it))->second;	

			double currDist = (lockedIn.find(*it))->second; // current distance from source
			double newDist = (lockedIn.find(curr))->second + calculateBasicSimilarities(user1, user2);
		
			if (newDist < currDist) {
				// update the distance for *it
				map<string, double>::iterator mit = lockedIn.find(*it);
				mit->second = newDist;

				myheap.decreaseKey(newDist, *it);
			}
		}
	}

	return lockedIn;
}


vector<pair<string, double> > MyDataStore::makeSuggestion(string currentUser) {
	
	vector<pair<string, double> > suggestions;

	User * thisUser = (usernames_.find(currentUser))->second;

	map<string, double> similarities = calculateRefinedSimilarities(thisUser);


	
	// CONCLUSION: Dijkstra's works perfectly

	// test map
	for (map<string, double>::const_iterator aaa = similarities.begin(); aaa != similarities.end(); ++aaa) {
		cout << aaa->first << " " << aaa->second << endl;
	}



	// go through each product
	for (set<Product*>::const_iterator pit = products_.begin(); pit != products_.end(); ++pit) {

		bool currentUserReviewedThis = false;
		// for 2 users A and B, score for a product is 
		map<string, vector<Review*> >::iterator rit = reviews_.find((*pit)->getName());

		if (rit == reviews_.end()) {
			// this product has been reviewed by nobody
			
			// [!] WAIT FOR PIAZZA RESPONSE -- update: don't add non-reviewed products
			//suggestions.push_back(make_pair((*pit)->getName(), 0));
			
			continue;
		}

		for (unsigned int i = 0; i < (rit->second).size(); i++) {
			if ((rit->second)[i]->username == currentUser) {
				currentUserReviewedThis = true;
			}
		}

		if (currentUserReviewedThis) {
			continue;
		}

		// now that we have made sure the current user has not reviewed this
		// and that this product does have reviews

		double R_of_P = 0; // R(P)
		double W = 0;


		for (unsigned int i = 0; i < (rit->second).size(); i++) {
			// go over all the reviews

			string otherUser = (rit->second)[i]->username;

			double r = (rit->second)[i]->rating;
			double s = (similarities.find(otherUser))->second;

			R_of_P += ((1-s)*(r));
			W += (1-s);
		}

		double overall = 0;
		if (W != 0 && R_of_P != 0) {
			overall = R_of_P / W;
		}

		suggestions.push_back(make_pair((*pit)->getName(), overall));
		
	}

	return suggestions;
}
