#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "util.h"
#include "heap.h"
#include <map>

class MyDataStore : public DataStore {


public:

	~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);


    // ADDED IN HW5
    void addReview(Review* r);

    // below here is for menu functions

    void addToCart(std::string u, std::vector<Product*> hits, int index);
    void removeFromCart(std::string u, int index);
    void viewCart(std::string u);
    void buyCart(std::string u);
    void displayCart(std::vector<Product*>& cart);

    void assignProductRatings();

    std::map<std::string,User*>& getUsers();
    std::set<Product*>& getProducts();
    std::map<User*,std::vector<Product*> >& getCarts();
    std::map<std::string,std::vector<Review*> >& getReviews();


    double calculateBasicSimilarities(User * u1, User * u2);
    std::map<std::string, double> calculateRefinedSimilarities(User * source);
    std::vector<std::pair<std::string, double> > makeSuggestion(std::string currentUser);
    
private:

	std::map<std::string,User*> usernames_;
	std::map<User*,std::vector<Product*> > users_; // map of each user to their cart
	std::set<Product*> products_;
	std::map<std::string,std::set<Product*> > keyWordMap_;


	// ADDED IN HW5
	std::map<std::string,std::vector<Review*> > reviews_;
};

#endif