#include "user.h"
using namespace std;

User::User() : name_("unknown"), balance_(0.0), type_(1)
{

}
User::User(std::string name, double balance, int type, unsigned int hashcode) :
    name_(name), balance_(balance), type_(type), hashcode_(hashcode)
{

}

User::~User()
{

}

unsigned int User::getHashcode() const
{
	return hashcode_;
}

std::string User::getName() const
{
    return name_;
}

double User::getBalance() const
{
    return balance_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

void User::dump(std::ostream& os)
{
    os << name_ << " "  << balance_ << " " << type_ << " " << hashcode_ << endl;
}
