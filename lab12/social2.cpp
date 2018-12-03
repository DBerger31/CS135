/* Author: Daniel Berger
Course: CSCI-136
Instructor: Genady Maryash
Assignment: Lab12
creating a simple social network
*/

#include <string>
#include <iostream>

using namespace std;

class Profile {
private:
   string displayname;
   string username;

public:
   // Profile constructor for a user (initializing
   // private variables username=usrn, displayname =dspn)
   Profile(string usrn, string dspn);
   //default profile constructor
   Profile();
   //return username
   string getUsername();
   // return name in the format: "displayname (@username)"
   string getFullName();
   // changes displayname
   void setDisplayName(string dspn);
};

Profile::Profile() : username(""), displayname("") { }

Profile::Profile(string usrn, string dpsn) {
   username = usrn;
   displayname = dpsn;
}

string Profile::getUsername() { // Do I need to use the P:: thing?
   return username;
}

string Profile::getFullName() {
   return displayname + " (@" + username + ")";
}

void Profile::setDisplayName(string dspn) {
   displayname = dspn;
}

class Network {
private:
   static const int MAX_USERS = 20; // max number of user profiles
   Profile profiles[MAX_USERS]; //user profiles array : ID -> Profile
   int numUsers; // number of registered users
   //returns user ID (index in the profiles array) by their username or -1 if username not found
   int findID (string usrn);

public:

   // Constructor, makes an empty network (numUsers = 0)
   Network();
   // Attempts to sign up a new user with specified username and displayname
   // return true if the operation was successful, otherwise return false
   bool addUser(string usrn, string dspn);
};

Network::Network() : numUsers = 0 { }

bool Network:: addUser(string usrn, string dspn) {
   if ()
}


int main() {
    Profile p1("marco", "Marco");
    cout << p1.getUsername() << endl; // marco
    cout << p1.getFullName() << endl; // Marco (@marco)

    p1.setDisplayName("Marco Rossi");
    cout << p1.getUsername() << endl; // marco
    cout << p1.getFullName() << endl; // Marco Rossi (@marco)

    Profile p2("tarma1", "Tarma Roving");
    cout << p2.getUsername() << endl; // tarma1
    cout << p2.getFullName() << endl; // Tarma Roving (@tarma1)
}
