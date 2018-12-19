/* Author: Daniel Berger
Course: CSCI-136
Instructor: Genady Maryash
Assignment: 8.2/8.3
open file.txt and average the numbers
*/


#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <cctype>

using namespace std;

int main()
{
   int count = 0;
   double num, sum, avg;
   string filename;

   cout << "Enter file name:  ";
   cin >> filename;
   ifstream fin(filename); // alternative way in chap 8.1
   while(fin >> num)
   {
      sum += num;
      count++;
   }
   avg = sum/count;
   cout << "the average is: " << avg;

   fin.close();

return 0;
}
