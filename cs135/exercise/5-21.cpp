/* Author: Daniel Berger
Course: CSCI-136
Instructor: Genady Maryash
Assignment: 5.21

Write a recursive function
string reverse(string str)
that computes the reverse of a string. For example, reverse("flow") should return "wolf".
Hint: Reverse the substring starting at the second character, then add the first character at the end.
For example, to reverse "flow", first reverse "low" to "wol", then add the "f" at the end.

*/

#include <iostream>
#include <string>

using namespace std;

string reverse (string str)
{
   if (str == "")
   {
      return "";
   }
   return reverse(str.substr(1 ,str.length())) + str[0];
}

int main()
{
   cout << reverse("flow");
}
