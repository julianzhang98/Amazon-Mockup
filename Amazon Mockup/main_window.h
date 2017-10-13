#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QRadioButton>   
#include <QComboBox> 
#include <QStringList>
#include <string>
#include <QFileDialog>
#include <QFont>
#include <QMessageBox>

#include "mydatastore.h"
#include "msort.h"


class MainWindow : public QWidget
{
    Q_OBJECT

public:

    struct alpha {
        bool operator()(Product * lhs, Product * rhs) {
            string str1 = lhs->getName();
            string str2 = rhs->getName();
            return (str1.compare(str2) < 0);
        }
    };


    struct rating {
        bool operator()(const Product * lhs, const Product * rhs) {  
            return (lhs->getRating() > rhs->getRating());
        }
    };

    struct date {
    	bool operator()(const Review * lhs, const Review * rhs) {
    		string str1 = lhs->date;
            string str2 = rhs->date;
    		return (str1.compare(str2) > 0);
    	}
    };


    struct suggest {
        bool operator()(const std::pair<std::string, double> lhs, const std::pair<std::string, double> rhs) {
            if (lhs.second > rhs.second) {
                return true;
            } else if (lhs.second == rhs.second) {
                return ((lhs.first).compare(rhs.first) < 0);
            }
            return false;
        } 
    };

    MainWindow(MyDataStore * ds);
    ~MainWindow();

private slots:

	void displayProductsAnd();
	void displayProductsOr();
	void displayProductInfo();

    void sortProductsAlpha();
    void sortProductsRating();
    //void switchUserList();
    //void switchUserText();

    void addToCart();
    void openCartWindow();
    void removeFromCart();
    void buyItems();

    void addNewReview();
    void resetReviewFields();
    void saveProgram();
    //void quitProgram();

    void switchCurrentUser();


    void loginUser();
    void quitProgram();
    void createNewUser();

    void openSuggestionWindow();
    void closeSuggestionWindow();

private:

	// other functions
	void displayProducts(int option);
	void sortProducts(int option);
    void refreshCart();
    void sortReviews();



    void loginComplete(string username);
    void clearLoginFields();
    unsigned int hash(string p);





    // font for headers

    QFont headerFont;

    QLabel * userHeader;
    QLabel * searchHeader;
    QLabel * reviewHeader;
    QLabel * addReviewHeader;
    QLabel * saveQuitHeader;

    QVBoxLayout * divider;
    QLabel * dividerLabel;


    MyDataStore * ds; // data storage method
    Msort * sorter; // sorting method
    QHBoxLayout * finalLayout; // final layout


    QWidget * cartWindow;
    QHBoxLayout * cartLayout;



    // Search Items
    QLabel * searchPrompt;
    QLineEdit * searchWords;
    QPushButton * andOption;
    QPushButton * orOption;
    QPushButton * alphaSort;
    QPushButton * ratingSort;
    QListWidget * searchResults;
    QHBoxLayout * searchOptions;
    QHBoxLayout * sortOptions;
    QVBoxLayout * searchLayout;



    // User Items
    QLabel * user;
    QLabel * currentUser;
    QHBoxLayout * userBox;
    QVBoxLayout * userLayout;
    QPushButton * switchUser;


    // Save Quit Optioins
    QPushButton * quit;
    QPushButton * save;
    QHBoxLayout * SQOptions;
    QLabel * SQPrompt;
    QLineEdit * file;



    // Cart Items
    QPushButton * addItem;
    QPushButton * viewCart;
    QHBoxLayout * productOptions;
    QVBoxLayout * productInfoLayout;
    QLabel * prodLab;
    QLabel * confirmAdd;


    QVBoxLayout * productLayout;


    // Review Items
    QVBoxLayout * reviewLayout;
    QListWidget * reviews;
    QVBoxLayout * addReviewLayout;
    QLabel * pleaseSelectItem;

    QRadioButton * star1;
    QRadioButton * star2;
    QRadioButton * star3;
    QRadioButton * star4;
    QRadioButton * star5;

    QHBoxLayout * fiveStarLayout;
    QLabel * fiveStarLabel;

    QHBoxLayout * dateLayout;

    QLabel * slash1;
    QLabel * slash2;

    QLineEdit * month;
    QLineEdit * day;
    QLineEdit * year;
    QLabel * dateLabel;

    QLabel * textPrompt;
    QTextEdit * reviewInput;
    QPushButton * submitReview;
    QPushButton * clearReview;

    QHBoxLayout * reviewButtons;



    // Cart Items
    QPushButton * removeItem;
    QPushButton * buyCart;
    QVBoxLayout * cartOptions;
    QLabel * cartLabel;
    QListWidget * cartItems;

    QWidget * loginWindow;
    QVBoxLayout * loginLayout;
    QHBoxLayout * usernameLayout;
    QHBoxLayout * passwordLayout;
    QHBoxLayout * buttonLayout;
    QLabel * userLabel;
    QLabel * passLabel;
    QLineEdit * userField;
    QLineEdit * passField;
    QLabel * mainLabel;
    QPushButton * login;
    QPushButton * quitLogin;
    QPushButton * newUser;





    QPushButton * recommend;
    QWidget * suggestionWindow;
    QVBoxLayout * suggestionLayout;
    QListWidget * suggestionResults;
    QPushButton * done;

    // ADD OTHER DATA MEMBERS HERE
    std::vector<Product*> productResults;
    std::string currentUsername;










};