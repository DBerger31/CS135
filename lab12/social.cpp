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
