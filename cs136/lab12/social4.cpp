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
   bool following[MAX_USERS][MAX_USERS]; // Friendship matrix
   //follwing[id1][id2] == true when id1 is following id2
   static const int MAX_POSTS = 100;
   int numPosts; // number of posts
   Post posts[MAX_POSTS]; //array of all the posts

public:

   // Constructor, makes an empty network (numUsers = 0)
   Network();
   // Attempts to sign up a new user with specified username and displayname
   // return true if the operation was successful, otherwise return false
   bool addUser(string usrn, string dspn);
   // Make 'usrn1' follow 'usrn2' (if both usernames are in the network).
   // return true if success (if both usernames exist), otherwise return false
   bool follow (string usrn1, string usrn2);
   // Print Dot file (graphical representation of the network)
   void printDot();
   bool writePost(string usrn, string msg); // add a new post
   bool printTimeline(string usrn); // prints user's timeline
};

Network::Network() : numUsers (0), numPosts(0) {
   for (int i = 0; i < MAX_USERS; i++) {
      for (int j = 0; j < MAX_USERS; j++) {
         following[i][j] = false;
      }
   }
}

bool Network:: addUser (string usrn, string dspn) {
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

bool Network:: follow (string usrn1, string usrn2) {
   if ((findID(usrn1) != -1) && (findID(usrn2) != -1)) { // if both usernames exist
      following[findID(usrn1)][findID(usrn2)] = true;
      return true;
   }
   else {
      return false;}
}

void Network:: printDot() {
   cout << "digraph {" << endl;
   for (int i = 0; i < MAX_USERS; i++) {
      if (profiles[i].getUsername() != "") {
         cout << "   \"@" + profiles[i].getUsername() + "\""<< endl;
      }
   }

   for (int i = 0; i < MAX_USERS; i++) {
      for (int j = 0; j < MAX_USERS; j++) {
         if (following[i][j]) { // if true
            cout << "   \"@" + profiles[i].getUsername() + "\" -> \"@" + profiles[j].getUsername() + "\"" << endl;
         }
      }
   }
   cout << "}" << endl;
}

bool Network:: writePost (string usrn, string msg) {
   
}

struct Post {
   string username;
   string message;
};

int main() {
    Network nw;
    // add three users
    nw.addUser("mario", "Mario");
    nw.addUser("luigi", "Luigi");
    nw.addUser("yoshi", "Yoshi");

    // make them follow each other
    nw.follow("mario", "luigi");
    nw.follow("mario", "yoshi");
    nw.follow("luigi", "mario");
    nw.follow("luigi", "yoshi");
    nw.follow("yoshi", "mario");
    nw.follow("yoshi", "luigi");

    // add a user who does not follow others
    nw.addUser("wario", "Wario");

    // add clone users who follow @mario
    for(int i = 2; i < 6; i++) {
        string usrn = "mario" + to_string(i);
        string dspn = "Mario " + to_string(i);
        nw.addUser(usrn, dspn);
        nw.follow(usrn, "mario");
    }
    // additionally, make @mario2 follow @luigi
    nw.follow("mario2", "luigi");

    nw.printDot();
}
