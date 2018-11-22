/* Author: Daniel Berger
Course: CSCI-136
Instructor: Genady Maryash
Assignment: Lab11
recursions
*/

#include <iostream>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;

void printRange(int left, int right) // prints a range of numbers
{
   if (left > right)
   {
      return;
   }
   cout << left << " ";
   printRange(left + 1, right);
}

int sumRange(int left, int right) // prints the sum of the range
{
   if (left > right) // if the left bound is greater then right exit
   {
      return 0; // exit
   }
   return left + sumRange(left + 1, right); // continues to add the numbers recursively
}

int sumArray(int *arr, int size)
{
   if (size == 1)
   {
      return arr[0];
   }
   else
   {
      return arr[size - 1] + sumArray(arr, size - 1);
   }
}

bool isAlphanumeric(string s)
{
   if (s == "")
   {
      return true;
   }
   else
   {
      if(isalnum(s.substr(0, s.length() - 1 ) && isAlphanumeric(s.substr(0, s.length() - 1 )))
      {
         return true;
      }
      else {return false;}
   }
}

int main()
{
   //printRange(-2, 10);
   //cout << "the total is" << sumRange(-2, 10);

   /*
   int size = 10;
   int *arr = new int[size]; // allocate array dynamically
   arr[0] = 12;
   arr[1] = 17;
   arr[2] = -5;
   arr[3] = 3;
   arr[4] = 7;
   arr[5] = -15;
   arr[6] = 27;
   arr[7] = 5;
   arr[8] = 13;
   arr[9] = -21;

   int sum1 = sumArray(arr, size); // Add all elements
   cout << "Sum is " << sum1 << endl;  // Sum is 43
   int sum2 = sumArray(arr, 5); // Add up first five elements
   cout << "Sum is " << sum2 << endl;  // Sum is 34
   delete[] arr;         // deallocate it
   */

   cout << isAlphanumeric("ABCD") << endl;        // true (1)
   cout << isAlphanumeric("Abcd1234xyz") << endl; // true (1)
   cout << isAlphanumeric("KLMN 8-7-6") << endl;  // false (0)

}
