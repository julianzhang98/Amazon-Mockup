

#include "main_window.h"
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;


#include <iostream>

MainWindow::MainWindow(MyDataStore * database) {
	ds = database;

	sorter = new Msort();

	// Title
	setWindowTitle("Amazon");


	headerFont.setBold(true);
    headerFont.setPointSize(15);

    userHeader = new QLabel("User Options and Information");
    searchHeader = new QLabel("\nProduct Search and Results");
    reviewHeader = new QLabel("Customer Reviews for Selected Product");
    addReviewHeader = new QLabel("\nAdd a Review for the Selected Product Below");
    saveQuitHeader = new QLabel("\nSave and Quit Options");

    userHeader->setFont(headerFont);
    searchHeader->setFont(headerFont);
    reviewHeader->setFont(headerFont);
    addReviewHeader->setFont(headerFont);
    saveQuitHeader->setFont(headerFont);

    divider = new QVBoxLayout();
    dividerLabel = new QLabel("     ");
    divider->addWidget(dividerLabel);


	// Main Layout
	finalLayout = new QHBoxLayout();

	cartWindow = new QWidget();
	cartWindow->setWindowTitle("Cart");
	cartLayout = new QHBoxLayout();


	// SEARCH LAYOUT
	searchPrompt = new QLabel("Enter Search Words Below:");
	searchWords = new QLineEdit();
	andOption = new QPushButton("AND Search");//new QRadioButton("AND search", this);
  	orOption = new QPushButton("OR Search");//new QRadioButton("OR search", this);

	searchResults = new QListWidget();
	alphaSort = new QPushButton("Sort Alphabetically");
	ratingSort = new QPushButton("Sort by Ratings");

	searchOptions = new QHBoxLayout();
	searchOptions->addWidget(andOption);
	searchOptions->addWidget(orOption);
	sortOptions = new QHBoxLayout;
	sortOptions->addWidget(alphaSort);
	sortOptions->addWidget(ratingSort);

	searchLayout = new QVBoxLayout();
	searchLayout->addWidget(searchHeader);
	searchLayout->addWidget(searchPrompt);
	searchLayout->addWidget(searchWords);
	searchLayout->addLayout(searchOptions);
	//searchLayout->addWidget(enterSearch);
	searchLayout->addWidget(searchResults);
	searchLayout->addLayout(sortOptions);

	//connect(enterSearch, SIGNAL(clicked()), this, SLOT(displayProducts()));
	connect(andOption, SIGNAL(clicked()), this, SLOT(displayProductsAnd()));
	connect(orOption, SIGNAL(clicked()), this, SLOT(displayProductsOr()));

	connect(alphaSort, SIGNAL(clicked()), this, SLOT(sortProductsAlpha()));
	connect(ratingSort, SIGNAL(clicked()), this, SLOT(sortProductsRating()));
	connect(searchResults, SIGNAL(itemSelectionChanged()), this, SLOT(displayProductInfo()));



	// SUGGESTIONS

	recommend = new QPushButton("Product Recommendations");
    suggestionWindow = new QWidget();
    suggestionWindow->setWindowTitle("Suggestions");
    suggestionLayout = new QVBoxLayout();
    suggestionResults = new QListWidget();
	done = new QPushButton("Done");

	suggestionLayout->addWidget(suggestionResults);
	suggestionLayout->addWidget(done);
	suggestionWindow->setLayout(suggestionLayout);

	connect(recommend, SIGNAL(clicked()), this, SLOT(openSuggestionWindow()));
	connect(done, SIGNAL(clicked()), this, SLOT(closeSuggestionWindow()));


	// USER 
	user = new QLabel("Current User: ");
	currentUser = new QLabel("");
	//userPrompt = new QLabel("Find Existing User or Enter Username:");
	//enterUser = new QLineEdit();
	//knownUsers = new QComboBox();
	//confirmUserText = new QPushButton("Switch Users");
	//confirmUserList = new QPushButton("Switch Users");
	//invalidUsername = new QLabel("");

	userBox = new QHBoxLayout();
	//userOptions1 = new QHBoxLayout();
	//userOptions2 = new QHBoxLayout();
	userBox->addWidget(user);
	userBox->addWidget(currentUser);
	//userOptions1->addWidget(knownUsers);
	//userOptions1->addWidget(confirmUserList);
	//userOptions2->addWidget(enterUser);
	//userOptions2->addWidget(confirmUserText);

	userLayout = new QVBoxLayout();
	userLayout->addWidget(userHeader);
	//userLayout->addLayout(userBox);
	//userLayout->addWidget(userPrompt);
	//userLayout->addLayout(userOptions1);
	//userLayout->addLayout(userOptions2);
	//userLayout->addWidget(invalidUsername);
	switchUser = new QPushButton("Logout And Switch User");
	userLayout->addLayout(userBox);
	userLayout->addWidget(switchUser);
	userLayout->addWidget(recommend);

	connect(switchUser, SIGNAL(clicked()), this, SLOT(switchCurrentUser()));

	save = new QPushButton("SAVE");
	quit = new QPushButton("QUIT");


	SQPrompt = new QLabel("Enter filename to save the curent database as.\n(QUIT will auto-save if filename is entered)");
	file = new QLineEdit();

	SQOptions = new QHBoxLayout();
	SQOptions->addWidget(save);
	SQOptions->addWidget(quit);

	//userLayout->addWidget(SQPrompt);

	//userLayout->addWidget(file);

	//userLayout->addLayout(SQOptions);
	// USER COMPLETE

	//connect(confirmUserText, SIGNAL(clicked()), this, SLOT(switchUserText()));
	//connect(confirmUserList, SIGNAL(clicked()), this, SLOT(switchUserList()));

	connect(quit, SIGNAL(clicked()), this, SLOT(quitProgram()));
	connect(save, SIGNAL(clicked()), this, SLOT(saveProgram()));
/*
	map<string,User*> tempUserMap = ds->getUsers();
	for (map<string,User*>::const_iterator umit = tempUserMap.begin(); umit != tempUserMap.end(); ++umit) {
		// loop through and fill in the list box
		knownUsers->addItem(QString::fromStdString(umit->first));
	}
	currentUser->setText(QString::fromStdString((tempUserMap.begin())->first));
	currentUsername = (tempUserMap.begin())->first;

*/



	// PRODUCTINFOLAYOUT

	addItem = new QPushButton("Add To Cart");
	viewCart = new QPushButton("View Cart");

	productOptions = new QHBoxLayout();
	productInfoLayout = new QVBoxLayout();
	productOptions->addWidget(addItem);
	productOptions->addWidget(viewCart);
	prodLab = new QLabel();
	confirmAdd = new QLabel();
	
	productInfoLayout->addWidget(prodLab);
	productInfoLayout->addWidget(confirmAdd);
	productInfoLayout->addLayout(productOptions);

	connect(addItem, SIGNAL(clicked()), this, SLOT(addToCart()));
	connect(viewCart, SIGNAL(clicked()), this, SLOT(openCartWindow()));

	productLayout = new QVBoxLayout();
	productLayout->addLayout(searchLayout);
	productLayout->addLayout(productInfoLayout);
	




	// FOR CART WINDOW
	removeItem = new QPushButton("Remove Item");
	buyCart = new QPushButton("Buy Items In Cart");
	cartLabel = new QLabel("");
	cartItems = new QListWidget();

	cartOptions = new QVBoxLayout();
	cartOptions->addWidget(cartLabel);
	cartOptions->addWidget(removeItem);
	cartOptions->addWidget(buyCart);

	cartLayout->addWidget(cartItems);
	cartLayout->addLayout(cartOptions);

	connect(removeItem, SIGNAL(clicked()), this, SLOT(removeFromCart()));
	connect(buyCart, SIGNAL(clicked()), this, SLOT(buyItems()));





	// REVIEWS
	reviewLayout = new QVBoxLayout();
	
	reviews = new QListWidget();
	reviews->setSelectionMode(QAbstractItemView::NoSelection);
	

	reviewLayout->addWidget(reviewHeader);
	reviewLayout->addWidget(reviews);




	// FOR ADDING REVIEWS
	addReviewLayout = new QVBoxLayout();
    
    pleaseSelectItem = new QLabel(); // "You Have Not Selected an Item to Review.\nPlease Select an Item to Review."

    fiveStarLabel = new QLabel("Rank the product from 1-5 stars:");
    star1 = new QRadioButton("1", this);
    star2 = new QRadioButton("2", this);
    star3 = new QRadioButton("3", this);
    star4 = new QRadioButton("4", this);
    star5 = new QRadioButton("5", this);

    fiveStarLayout = new QHBoxLayout();
    fiveStarLayout->addWidget(star1);
    fiveStarLayout->addWidget(star2);
    fiveStarLayout->addWidget(star3);
    fiveStarLayout->addWidget(star4);
    fiveStarLayout->addWidget(star5);

	QLabel * dateLabel = new QLabel("Enter Date in MM/DD/YYYY Format:");
    QLabel * slash1 = new QLabel("/");
    QLabel * slash2 = new QLabel("/");
    month = new QLineEdit();
    day = new QLineEdit();
    year = new QLineEdit();
    month->setMaxLength(2);
    day->setMaxLength(2);
    year->setMaxLength(4);
    month->setFixedWidth(25);
    day->setFixedWidth(25);
    year->setFixedWidth(50);


    dateLayout = new QHBoxLayout();
    dateLayout->addWidget(dateLabel);
    dateLayout->addWidget(month);
    dateLayout->addWidget(slash1);
    dateLayout->addWidget(day);
    dateLayout->addWidget(slash2);
    dateLayout->addWidget(year);

	textPrompt = new QLabel("Enter Your Review Below:");
    reviewInput = new QTextEdit();
    submitReview = new QPushButton("Submit Review");
    clearReview = new QPushButton("Clear Review");

    reviewButtons = new QHBoxLayout;
    reviewButtons->addWidget(clearReview);
    reviewButtons->addWidget(submitReview);

    addReviewLayout->addWidget(addReviewHeader);
    addReviewLayout->addWidget(pleaseSelectItem);
    addReviewLayout->addWidget(fiveStarLabel);
    addReviewLayout->addLayout(fiveStarLayout);
    addReviewLayout->addLayout(dateLayout);
    addReviewLayout->addWidget(textPrompt);
    addReviewLayout->addWidget(reviewInput);
    addReviewLayout->addLayout(reviewButtons);

    connect(submitReview, SIGNAL(clicked()), this, SLOT(addNewReview()));
    connect(clearReview, SIGNAL(clicked()), this, SLOT(resetReviewFields()));



    reviewLayout->addLayout(addReviewLayout);

    userLayout->addLayout(productLayout);



    userLayout->addWidget(saveQuitHeader);
    userLayout->addWidget(SQPrompt);
	userLayout->addWidget(file);
    userLayout->addLayout(SQOptions);



	// ADD EVERYTHING TO FINAL LAYOUT

	finalLayout->addLayout(userLayout);
	finalLayout->addLayout(divider);
	finalLayout->addLayout(reviewLayout);
	//finalLayout->addLayout(addReviewLayout);
	//finalLayout->addLayout(userLayout);
	cartWindow->setLayout(cartLayout);
	setLayout(finalLayout);


	// login window

	loginWindow = new QWidget();

	userLabel = new QLabel("Username: ");
	passLabel = new QLabel("Password: ");
	userField = new QLineEdit();
	passField = new QLineEdit();
	passField->setEchoMode(QLineEdit::Password); // don't show password

	mainLabel = new QLabel("Please Login");
	login = new QPushButton("Login");
	quitLogin = new QPushButton("Quit");
	newUser = new QPushButton("Create New User");

	loginLayout = new QVBoxLayout();
	usernameLayout = new QHBoxLayout();
	passwordLayout = new QHBoxLayout();
	buttonLayout = new QHBoxLayout();

	usernameLayout->addWidget(userLabel);
	usernameLayout->addWidget(userField);
	passwordLayout->addWidget(passLabel);
	passwordLayout->addWidget(passField);
	buttonLayout->addWidget(login);
	buttonLayout->addWidget(quitLogin);
	buttonLayout->addWidget(newUser);

	loginLayout->addWidget(mainLabel);
	loginLayout->addLayout(usernameLayout);
	loginLayout->addLayout(passwordLayout);
	loginLayout->addLayout(buttonLayout);


	loginWindow->setWindowTitle("Please Login");
	loginWindow->setLayout(loginLayout);

	connect(login, SIGNAL(clicked()), this, SLOT(loginUser()));
	connect(quitLogin, SIGNAL(clicked()), this, SLOT(quitProgram()));
	connect(newUser, SIGNAL(clicked()), this, SLOT(createNewUser()));

	switchCurrentUser();


}

MainWindow::~MainWindow() {
	delete sorter;
}

// CONSTRUCTOR AND DESTRUCTOR ENDS ////////////////////////////////////////////////////////////
// CONSTRUCTOR AND DESTRUCTOR ENDS ////////////////////////////////////////////////////////////
// CONSTRUCTOR AND DESTRUCTOR ENDS ////////////////////////////////////////////////////////////
// CONSTRUCTOR AND DESTRUCTOR ENDS ////////////////////////////////////////////////////////////
// CONSTRUCTOR AND DESTRUCTOR ENDS ////////////////////////////////////////////////////////////
// CONSTRUCTOR AND DESTRUCTOR ENDS ////////////////////////////////////////////////////////////
// CONSTRUCTOR AND DESTRUCTOR ENDS ////////////////////////////////////////////////////////////
// CONSTRUCTOR AND DESTRUCTOR ENDS ////////////////////////////////////////////////////////////
// CONSTRUCTOR AND DESTRUCTOR ENDS ////////////////////////////////////////////////////////////
// CONSTRUCTOR AND DESTRUCTOR ENDS ////////////////////////////////////////////////////////////


void MainWindow::switchCurrentUser() {
	loginWindow->show();
	suggestionWindow->hide(); // just in case it's open
	cartWindow->hide(); // just in case it's open
	hide();
}

void MainWindow::displayProductsAnd() { displayProducts(0); }
void MainWindow::displayProductsOr() { displayProducts(1); }
void MainWindow::displayProducts(int option) {
	// 0 for and and 1 for or

	// if no text or no and/or option selected
	if (searchWords->text().isEmpty()) {
		return;
	}

	// first clear the list
	searchResults->clear();

	// then take the words in the text box and search for the products
	string words = searchWords->text().toStdString();
	string temp;
	stringstream ss(words);
	vector<string> keywords;
	while(ss >> temp) {
		temp = convToLower(temp);
		keywords.push_back(temp);
    }
  
    productResults = ds->search(keywords, option);

    // insert the products into the listbox
    for (unsigned int i = 0; i < productResults.size(); i++) {
    	stringstream ss1;
    	temp = productResults[i]->getName();
    	double price = productResults[i]->getPrice();
    	ss1 << temp << "  - - -  " << price;
    	temp = ss1.str();
		searchResults->addItem(QString::fromStdString(temp));
    }

    // reset the other things
    searchWords->setText("");
	confirmAdd->setText("");
	displayProductInfo();
}

void MainWindow::sortProductsAlpha() { sortProducts(0); }
void MainWindow::sortProductsRating() { sortProducts(1); }
void MainWindow::sortProducts(int option) {
	// 0 is for alpha and 1 is for rating

	if (searchResults->count() == 0) { // if there are no results to sort
		return;
	}

	if (option == 0) {
		alpha comp;
		sorter->mergeSort(productResults, comp);
	}
	else if (option == 1) { 
		rating comp;
		sorter->mergeSort(productResults, comp);
	}

	searchResults->clear();
	for (unsigned int i = 0; i < productResults.size(); i++) {
    	stringstream ss1;
    	string temp = productResults[i]->getName();
    	double price = productResults[i]->getPrice();
    	ss1 << temp << "  - - -  " << price;
    	temp = ss1.str();
		searchResults->addItem(QString::fromStdString(temp));
    }
    displayProductInfo();
}
/*
void MainWindow::switchUserText() {
	if (enterUser->text().isEmpty()) { // if no name entered
		return;
	}
	QString username = enterUser->text(); // get the name
	enterUser->setText(QString::fromStdString("")); // reset the blank
	if ((ds->getUsers()).find(username.toStdString()) == ds->getUsers().end()) { // if user does not exist
		invalidUsername->setText("Please Enter a Valid Username");
		return;
	}
	invalidUsername->setText(""); // remove the invalid username message
	currentUser->setText(username); // update Label on UI
	currentUsername = username.toStdString(); // change string data member

	refreshCart();
}

void MainWindow::switchUserList() {
	QString username = knownUsers->currentText(); // get username
	currentUser->setText(username); // update Label on UI
	currentUsername = username.toStdString(); // change string data member
	invalidUsername->setText(""); // remove the invalid username message if it exists
	refreshCart();
}
*/
void MainWindow::displayProductInfo() { // shows product description and product reviews

	if (searchResults->selectedItems().isEmpty()) {
		reviews->clear();
		prodLab->setText("");
		return;
	}

	int index = searchResults->currentRow(); // finds the selected item index

	//sortReviews();

	string description = "Category: " + productResults[index]->getCategory() + "\n-----------------------\n";
	description += productResults[index]->displayString();
	

	double avgrating = productResults[index]->getRating();
	stringstream ss;
	ss << avgrating;

	description += ("     Average Rating: " + ss.str());

	prodLab->setText(QString::fromStdString(description)); // update product description label

	map<string,vector<Review*> >::iterator it = (ds->getReviews()).find(productResults[index]->getName());
	
	reviews->clear();

	if (it != (ds->getReviews()).end()) {
		string temp;
		for (unsigned int i = 0; i < (it->second).size(); i++) {
			stringstream ss; // used to turn rating into string
			ss << (it->second)[i]->rating;


    		temp = "Review for: " + (it->second)[i]->prodName + "\nBy User: " + (it->second)[i]->username + "\n";
			temp += ("Rating: " + ss.str() + "               Review Date: " + (it->second)[i]->date + "\n");
			temp += ("\"" + (it->second)[i]->reviewText + "\"\n");

   			reviews->addItem(QString::fromStdString(temp));



		}
	}

	sortReviews();

}

void MainWindow::addToCart() {
	
	if (searchResults->selectedItems().isEmpty()) { // if no item is selected
		return;
	}

	int index = searchResults->currentRow(); // finds index of selected item
	ds->addToCart(currentUsername, productResults, index+1); // add to cart

	string confirmation = "Added " + productResults[index]->getName() + " to cart!"; // confirmation message
	confirmAdd->setText(QString::fromStdString(confirmation)); // update confirmation label
	refreshCart();

}

void MainWindow::openCartWindow() {
	refreshCart();
	cartLabel->setText("");
	cartWindow->show();
}

void MainWindow::refreshCart() {

	User * thisUser = ((ds->getUsers()).find(currentUsername))->second;
	vector<Product*> thisCart = ((ds->getCarts()).find(thisUser))->second;

	cartItems->clear(); // remove everything first

	string temp;
	for (unsigned int i = 0; i < thisCart.size(); i++) {
    	stringstream ss;
    	temp = thisCart[i]->getName();
    	double price = thisCart[i]->getPrice();
    	ss << temp << "  - - -  " << price;
    	temp = ss.str();
		cartItems->addItem(QString::fromStdString(temp));
    }

}

void MainWindow::removeFromCart() {

	if (cartItems->selectedItems().isEmpty()) { // if there is no item to remove
		cartLabel->setText("No Item Selected for Removal");
		return;
	}
	int index = cartItems->currentRow(); // finds index of selected item

	ds->removeFromCart(currentUsername, index);

	cartLabel->setText("Item Removed");	
	refreshCart();

}
void MainWindow::buyItems() {

	ds->buyCart(currentUsername);
	cartLabel->setText("Transaction Complete:\n\nYou bought everything that\ncould have been bought.");
	displayProductInfo(); // refreshes quantity
	refreshCart();

}

void MainWindow::sortReviews() {

	if (reviews->count() == 0) { // if there are no reviews to sort
		return;
	}

	int index = searchResults->currentRow();
    map<string,vector<Review*> >::iterator it = (ds->getReviews()).find(productResults[index]->getName());

	date comp;
	sorter->mergeSort(it->second, comp);


	// once reviews are sorted reprint them

	reviews->clear();

	
	string temp;
	for (unsigned int i = 0; i < (it->second).size(); i++) {
		stringstream ss; // used to turn rating into string
		ss << (it->second)[i]->rating;


    	temp = "Review for: " + (it->second)[i]->prodName + "\nBy User: " + (it->second)[i]->username + "\n";
		temp += ("Rating: " + ss.str() + "               Review Date: " + (it->second)[i]->date + "\n");
		temp += ("\"" + (it->second)[i]->reviewText + "\"\n");

   		reviews->addItem(QString::fromStdString(temp));

	}
}

void MainWindow::saveProgram() {
	if (file->text().isEmpty()) {
		return;
	}

	string filename = file->text().toStdString();
	ofstream ofile(filename.c_str());
	ds->dump(ofile);
	ofile.close();



	file->setText("");
}
void MainWindow::quitProgram() {
	// if filename line not empty then save
	if (!(file->text().isEmpty())) {
		saveProgram();
	}

	//ds->dumpSuggestions();

	ofstream ofile("rec.txt");
	map<string, User*> usernames = ds->getUsers();

	for (map<string, User*>::const_iterator it = usernames.begin(); it != usernames.end(); ++it) {
		string currentUser = it->first;
		ofile << currentUser << endl;

		vector<pair<string, double> > suggestions = ds->makeSuggestion(currentUser);
		
		if (suggestions.size() == 0) {
			continue; // if there are no suggestions
		}
		
		suggest comp;
		sorter->mergeSort(suggestions, comp);

		for (unsigned int i = 0; i < suggestions.size(); i++) {
			ofile << setprecision(2) << fixed << suggestions[i].second << " " << suggestions[i].first << endl;
		}

	}

	ofile.close();

	//continue quitting...
	suggestionWindow->close();
	loginWindow->close();
	cartWindow->close();
	close();
}



void MainWindow::addNewReview() {


	// check if item is selected

	if (searchResults->selectedItems().isEmpty()) {
		pleaseSelectItem->setText("You Have Not Selected an Item to Review.\nPlease Select an Item in the Search Results.");
		return;
	}

	int r;
	if (star1->isChecked()) {
		r=1;
	} else if (star2->isChecked()) {
		r=2;
	} else if (star3->isChecked()) {
		r=3;
	} else if (star4->isChecked()) {
		r=4;
	} else if (star5->isChecked()) {
		r=5;
	} else {
		pleaseSelectItem->setText("Please select a rating from 1-5.");
		return;
	}


	if (month->text().length() != 2 || day->text().length() != 2 || year->text().length() != 4) {
		pleaseSelectItem->setText("Please Enter a Valid Date.");
		return;
	}

	stringstream ss;
	ss << year->text().toStdString() << " " << month->text().toStdString() << " " << day->text().toStdString();

	int x,y,z;
	ss >> x >> y >> z;
	if (x < 2016 || x > 2030 || y < 1 || y > 12 || z < 1 || z > 31) {
		pleaseSelectItem->setText("Please Enter a Valid Date.");
		return;
	}

	string d = year->text().toStdString() + "-" + month->text().toStdString() + "-" + day->text().toStdString();


	if (reviewInput->toPlainText().isEmpty()) {
		pleaseSelectItem->setText("Please Enter a Description.");
		return;
	}
	string t = reviewInput->toPlainText().toStdString();



	int index = searchResults->currentRow(); // finds the selected item index to get productname
	Review * temp = new Review(productResults[index]->getName(),r,currentUsername,d,t);

	ds->addReview(temp);


	displayProductInfo();
	sortReviews();

	resetReviewFields();

}


void MainWindow::resetReviewFields() { // only if user switches or if review is submitted
	pleaseSelectItem->setText("");

	reviewInput->clear();
	month->setText("");
	day->setText("");
	year->setText("");

	star1->setAutoExclusive(false);
	star1->setChecked(false);
	star1->setAutoExclusive(true);
	star2->setAutoExclusive(false);
	star2->setChecked(false);
	star2->setAutoExclusive(true);
	star3->setAutoExclusive(false);
	star3->setChecked(false);
	star3->setAutoExclusive(true);
	star4->setAutoExclusive(false);
	star4->setChecked(false);
	star4->setAutoExclusive(true);
	star5->setAutoExclusive(false);
	star5->setChecked(false);
	star5->setAutoExclusive(true);

}


























unsigned int MainWindow::hash(string p) {

	unsigned long long result = 0;
	unsigned int n = p.length();

	for (unsigned int i = 0; i < n; i++) {
		unsigned long long power = pow(128, n-(i+1));
		result += ((int)p[i] * power);
	}

	// convert it to base 65521
	unsigned int w[4];
	for (int i = 0; i < 4; i++) {
		w[i] = result % 65521;
		result /= 65521;
	}

	unsigned int final;
	final = (45912 * w[3] + 35511 * w[2] + 65169 * w[1] + 4625 * w[0]) % 65521;
	return final;

}

void MainWindow::createNewUser() {

	if (userField->text().isEmpty() || passField->text().isEmpty()) {
		QMessageBox errmsg;
		errmsg.setWindowTitle("Error");
		errmsg.setText("Please Enter a Username and a Password");
		errmsg.exec();
		clearLoginFields();
		return;
	}

	QString username = userField->text();
	QString password = passField->text();
	clearLoginFields();

	string p = password.toStdString();

	if (p.length() > 8) {
		QMessageBox errmsg;
		errmsg.setWindowTitle("Error");
		errmsg.setText("The Password Must Have Fewer Than 8 Characters");
		errmsg.exec();
		return;
	}

	unsigned int hashcode = hash(p);

	map<std::string, User*>::iterator it = ds->getUsers().find(username.toStdString());
	if (it != ds->getUsers().end()) {
		// then this user exists and you cannot create a user

		QMessageBox errmsg;
		errmsg.setWindowTitle("Error");
		errmsg.setText("This Username Already Exists");
		errmsg.exec();
		return;

	}
	User * newUser = new User(username.toStdString(), 100, 0, hashcode);
	ds->addUser(newUser);
	
	QMessageBox succmsg;
	succmsg.setWindowTitle("Success!");
	succmsg.setText("You Have Successfully Created a New User Account!");
	succmsg.exec();
	
	loginComplete(username.toStdString());

}

void MainWindow::clearLoginFields() {
	userField->setText("");
	passField->setText("");

}

void MainWindow::loginComplete(string u) {

	currentUser->setText(QString::fromStdString(u)); // update Label on UI
	currentUsername = u;
	refreshCart();

	clearLoginFields();
	loginWindow->hide();
	show();

}

void MainWindow::loginUser() {

	if (userField->text().isEmpty() || passField->text().isEmpty()) {
		QMessageBox errmsg;
		errmsg.setWindowTitle("Error");
		errmsg.setText("Please Enter a Username and a Password");
		errmsg.exec();
		clearLoginFields();
		return;
	}

	QString username = userField->text();
	QString password = passField->text();
	clearLoginFields();

	if (password.toStdString().length() > 8) {
		QMessageBox errmsg;
		errmsg.setWindowTitle("Error");
		errmsg.setText("The Password Does Not Match the Username\n(Hint: Must be 8 characters or fewer)");
		errmsg.exec();
		return;
	}
	unsigned int hashcode = hash(password.toStdString());

	map<std::string, User*>::iterator it = ds->getUsers().find(username.toStdString());
	if (it == ds->getUsers().end()) {
		// invalid username because user does not exist
		QMessageBox errmsg;
		errmsg.setWindowTitle("Error");
		errmsg.setText("This User Does Not Exist");
		errmsg.exec();
		return;
	}

	if (hashcode == (it->second)->getHashcode()) {
		loginComplete(username.toStdString());
	} else {
		QMessageBox errmsg;
		errmsg.setWindowTitle("Error");
		errmsg.setText("The Password Does Not Match the Username");
		errmsg.exec();
	}
	
}

void MainWindow::openSuggestionWindow() {

	suggestionResults->clear();

	vector<pair<string, double> > suggestions = ds->makeSuggestion(currentUsername);

	if (suggestions.size() == 0) {
		QMessageBox msg;
		msg.setWindowTitle("Sorry");
		msg.setText("No recommendations available");
		msg.exec();
		return;
	}

	suggest comp;
	sorter->mergeSort(suggestions, comp);

	for (unsigned int i = 0; i < suggestions.size(); i++) {
		stringstream ss;
		ss << setprecision(2) << fixed << suggestions[i].second << " " << suggestions[i].first;
		suggestionResults->addItem(QString::fromStdString(ss.str()));
	}

	suggestionWindow->show();

}
void MainWindow::closeSuggestionWindow() {
	suggestionWindow->hide();
}