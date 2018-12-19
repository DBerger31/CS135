/* Author: Daniel Berger
Course: CSCI-136
Instructor: Genady Maryash
Assignment: 7.15

Write a function int* read_data(int& size)
that reads data from cin until the user terminates input by entering Q.
The function should set the size reference parameter to the number of numeric inputs.
Return a pointer to an array on the free store. That array should have exactly size elements.
Of course, you won’t know at the outset how many elements the user will enter. Start with an array of 10 elements,
and double the size whenever the array fills up. At the end, allocate an array of the correct size and copy all inputs into it.
Be sure to delete any intermediate arrays.
*/

#include <iostream>

using namespace std;

int* read_data(int& size)
{
   int* original = new int[size]; // declares the original array as a pointer
   int* other = new int[size];
   int count = 0;
   char value;

   for (int i = 0; i < size; i++) // set every value of both arrays to equal 0
   {
      original[i] = 0;
      other[i] = 0;
   }

   while (cin >> value)
   {
      if (value == 'q') // if the user enters q; break out of the while loop
      {
         break;
      }
      count++; // increase the count
      for (int i = 0; i < size; i++)
      {
         original[i] = value; // serts each value to each input
      }
      if (count >= size)
      {
         size = size * 2;
      }
   }

   for (int i = 0; i < size; i++)
   {
      other[i] = original[i]; // copys every value of thhe original into other
   }
   delete[] original; // delete the memory of the original array
   original = other; // sets the adress of the orginal to the adress of other?????

   for (int i = 0; i < size; i++)
   {
      cout << original[i] << endl;
   }
}

int main()
{
   int size = 10;
   read_data(size);
}
