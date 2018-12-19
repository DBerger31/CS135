/* Author: Daniel Berger
Course: CSCI-136
Instructor: Genady Maryash
Assignment: Lab12
creating a simple social network
*/

#include <string>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <locale>

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

Network::Network() : numUsers (0) { }

bool Network:: addUser(string usrn, string dspn) {
   static int index = 0;
   if (index < MAX_USERS) {
      if ((usrn != "")) {
         for (int i = 0; i < usrn.length(); i ++) {
            if (!(isalnum(usrn[i]))) {
               return false;
            }
         }
         for (int i = 0; i < MAX_USERS; i++) {
            if (profiles[i].getUsername() == usrn) {
               return false;
            }
            else {
               profiles[index] = Profile(usrn, dspn);
               index++;
               return true;
            }
         }
      }
   }
   else { return false;}
}


int Network:: findID (string usrn) {
   for (int i = 0; i < MAX_USERS; i++) {
      if (profiles[i].getUsername() == usrn) {
         return i;
      }
   }
   return -1;
}


int main() {
  Network nw;
  cout << nw.addUser("mario", "Mario") << endl;     // true (1)
  cout << nw.addUser("luigi", "Luigi") << endl;     // true (1)

  cout << nw.addUser("mario", "Mario2") << endl;    // false (0)
  cout << nw.addUser("mario 2", "Mario2") << endl;  // false (0)
  cout << nw.addUser("mario-2", "Mario2") << endl;  // false (0)

  for(int i = 2; i < 20; i++)
      cout << nw.addUser("mario" + to_string(i),
                 "Mario" + to_string(i)) << endl;   // true (1)

  cout << nw.addUser("yoshi", "Yoshi") << endl;     // false (0)

  cout << "the user id is " << nw.findID("mario") << endl;
  cout << "the user id is " << nw.findID("luigi") << endl;

}
