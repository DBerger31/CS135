/* Author: Daniel Berger
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Project 2
uses a pronunciation dictionary for finding words with similar pronunciation.
*/


#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;

void splitOnSpace(string s, string & before, string & after)
{
  // reset strings
  before = "";
  after = "";
  // accumulate before space
  int i = 0;
  while (i < s.size() && not isspace(s[i])) { before += s[i]; i++; }
  // skip the space
  i++;
  // accumulate after space
  while (i < s.size()) { after += s[i]; i++; }
}

void Convert(string& str) // converts lower case to upper and checks for illegal characters
{
string temp;
for (int i = 0; i < str.length(); i++)
   {
      if (97 <= int(str[i]) && int(str[i]) <= 122)
      {
         temp += int(str[i]) - 32;
      }
      else if (int(str[i]) == 39)
      {
         temp += int(str[i]);
      }
      else if (65 <= int(str[i]) && int(str[i]) <= 90)
      {
         temp += int(str[i]);
      }
      else {temp = "$$$$$";}
   }
   str = temp;
}

string findPrononce(string word, string data)
{
   bool found = false;
   string before;
   string after;
   string pronunciation;
   ifstream fin("cmudict.0.7a"); // creates a input file stream named fin
   if (fin.fail()) // if there is no file named fin or if the file name is wrong
   {
   cerr << "File cannot be opened for reading." << endl;
   exit(1); //exit the file if it failed
   }
   while (getline(fin, data)) // while we are reading the file
   {
      splitOnSpace(data, before, after);
      if (word == before)
      {

         cout << "Pronunciation: " << after << endl;
         //splitOnSpace(after, newbefore, pronunciation);
         pronunciation = after;
         found = true;
         break;
      }
   }
   if (!found)
   {
      cout << "NOT FOUND";
      exit(1);
   }
   return pronunciation;
}

void findIdentical(string word, string pronunciation, string data)
{
   string before;
   string after;
   ifstream fin("cmudict.0.7a"); // creates a input file stream named fin
   if (fin.fail()) // if there is no file named fin or if the file name is wrong
   {
   cerr << "File cannot be opened for reading." << endl;
   exit(1); //exit the file if it failed
   }
   cout << "\nIdentical: ";
   while (getline(fin, data)) // while we are reading the file // to find word with identical pronunciation
   {
      splitOnSpace(data, before, after);
      if (pronunciation == after && before != word)
      {
         cout << before << " ";
      }
   }
}

int find_spaces(string str, string ch) // finds the number of spaces in a string
{
   int spaces = 0;
   for(int i = 0; i <= str.length(); i++)
   {
      if (str.substr(i, 1) == ch)
      {
         spaces++;
      }
   }
   return spaces;
}

void ReplacePhoneme(string pronunciation, string data) //gives me a word with one replaced phoneme
{
   string before;
   string after;
   string pro_before;
   string pro_after;
   string compare_before;
   string compare_after;
   ifstream fin("cmudict.0.7a"); // creates a input file stream named fin
   if (fin.fail()) // if there is no file named fin or if the file name is wrong
   {
   cerr << "File cannot be opened for reading." << endl;
   exit(1); //exit the file if it failed
   }
   cout << "\nReplace Phoneme: ";
   while(getline(fin, data))
   {
      int count = 0;
      splitOnSpace(data, before, after);
      Convert(before); // this will convert before into a garbage string if there are illegal characters present
      if(before == "$$$$$") // before is a garbage string continue to the next line (restart while loop)
      {
         continue;
      }
      string after_temp = after;
      string pro_temp = pronunciation;
      int ogspaces = find_spaces(pro_temp," ");
      int targetspaces = find_spaces(after_temp, " ");
      if(ogspaces == targetspaces)
         while(pro_temp != "")
         {
            splitOnSpace(pro_temp, pro_before, pro_temp);
            splitOnSpace(after_temp, compare_before, after_temp);
            if(pro_before != compare_before)
            {
               count++;
            }
            if(count > 1)
            {
               break;
            }
         }
         if (count == 1 )
         {
            cout << before << " ";
         }
   }
}

void AddPhoneme(string pronunciation, string data) //gives me a word with one added phoneme
{
   string before;
   string after;
   string pro_before;
   string pro_after;
   string compare_before;
   string compare_after;
   ifstream fin("cmudict.0.7a"); // creates a input file stream named fin
   if (fin.fail()) // if there is no file named fin or if the file name is wrong
   {
   cerr << "File cannot be opened for reading." << endl;
   exit(1); //exit the file if it failed
   }
   cout << "\nAdd Phoneme: ";
   while(getline(fin, data))
   {
      int count = 0;
      splitOnSpace(data, before, after);
      Convert(before); // this will convert before into a garbage string if there are illegal characters present
      if(before == "$$$$$") // before is a garbage string continue to the next line (restart while loop)
      {
         continue;
      }
      string after_temp = after;
      string pro_temp = pronunciation;
      int ogspaces = find_spaces(pro_temp," ");
      int targetspaces = find_spaces(after_temp, " ");
      if(ogspaces + 1 == targetspaces)
      {
         while(after_temp != "")
         {
            splitOnSpace(pro_temp, pro_before, pro_temp);
            splitOnSpace(after_temp, compare_before, after_temp);
            if(pro_before != compare_before)
            {
               count++;
               splitOnSpace(after_temp, compare_before, after_temp);
               if(pro_before != compare_before)
               {
                  count++;
                  break;
               }
            }
            if(count > 1)
            {
               break;
            }
         }
      }
      if (count == 1 )
      {
         cout << before << " ";
      }

   }
}

void RemovePhoneme(string pronunciation, string data) //gives me a word with one removed phoneme
{
   string before;
   string after;
   string pro_before;
   string pro_after;
   string compare_before;
   string compare_after;
   ifstream fin("cmudict.0.7a"); // creates a input file stream named fin
   if (fin.fail()) // if there is no file named fin or if the file name is wrong
   {
   cerr << "File cannot be opened for reading." << endl;
   exit(1); //exit the file if it failed
   }
   cout << "\nRemove Phoneme: ";
   while(getline(fin, data))
   {
      int count = 0;
      splitOnSpace(data, before, after);
      Convert(before); // this will convert before into a garbage string if there are illegal characters present
      if(before == "$$$$$") // before is a garbage string continue to the next line (restart while loop)
      {
         continue;
      }
      string after_temp = after;
      string pro_temp = pronunciation;
      int ogspaces = find_spaces(pro_temp," ");
      int targetspaces = find_spaces(after_temp, " ");
      if(ogspaces - 1 == targetspaces)
      {
         while(pro_temp != "")
         {
            splitOnSpace(pro_temp, pro_before, pro_temp);
            splitOnSpace(after_temp, compare_before, after_temp);
            if(pro_before != compare_before)
            {
               count++;
               splitOnSpace(pro_temp, pro_before, pro_temp);
               if(pro_before != compare_before)
               {
                  count++;
                  break;
               }
            }
            if(count > 1)
            {
               break;
            }
         }
      }
      if (count == 1 )
      {
         cout << before << " ";
      }

   }
}

int main() // executes the prior functions
{
   string data;
   string word;
   string before = "";
   string after = "";
   string pronunciation;

   cout << "Enter a word: ";
   cin >> word;
   Convert(word);
   pronunciation = findPrononce(word, data);
   findIdentical(word, pronunciation, data);
   ReplacePhoneme(pronunciation, data);
   AddPhoneme(pronunciation, data);
   RemovePhoneme(pronunciation,data);

}
