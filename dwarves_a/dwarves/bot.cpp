
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "bot.h"

using namespace std;

const int MAX_ROWS = 40;
const int MAX_COLS = 40;
const int MAX_NUM = 10;

int ROWS;  // global variables
int COLS;
int NUM;

class Coord2D
{
public:
   int r;
   int c;
};

bool isTree(Dwarf & dwarf, int r, int c) // checks if that square alone contains a tree
{
   if (dwarf.look(r, c) == PINE_TREE || dwarf.look(r, c) == APPLE_TREE)
   {
      return true;
   }
   else { return false;}
}

bool isNextToATree(Dwarf & dwarf, int r, int c) {
   if (dwarf.look(r, c+1) == PINE_TREE || dwarf.look(r, c+1) == APPLE_TREE) {
      return true;
   }
   else if (dwarf.look(r, c-1) == PINE_TREE || dwarf.look(r, c-1) == APPLE_TREE) {
      return true;
   }
   else if (dwarf.look(r+1, c) == PINE_TREE || dwarf.look(r+1, c) == APPLE_TREE) {
      return true;
   }
   else if (dwarf.look(r-1, c) == PINE_TREE || dwarf.look(r-1, c) == APPLE_TREE) {
      return true;
   }
   else {return false;}
}

// pick a point in the array (map) and see how many trees there are adjacent
/*int NumberOfTreesAround(Dwarf & dwarf, int r, int c) {
   int count = 0;
   if (dwarf.look(r, c+1) == PINE_TREE || dwarf.look(r, c+1) == APPLE_TREE) {
      count++;
   }
   if (dwarf.look(r, c-1) == PINE_TREE || dwarf.look(r, c-1) == APPLE_TREE) {
      count++;
   }
   if (dwarf.look(r+1, c) == PINE_TREE || dwarf.look(r+1, c) == APPLE_TREE) {
      count++;
   }
   if (dwarf.look(r-1, c) == PINE_TREE || dwarf.look(r-1, c) == APPLE_TREE) {
      count++;
   }
   return count;
}
*/

void SendToClosestTree(Dwarf & dwarf, std::ostream &log) // send the dwarf to the closest tree
{
   int r = dwarf.row();
   int c = dwarf.col();

   int closest_row = 1000;
   int closest_col = 1000;

   for (int i = 0; i <= ROWS; i++)
   {
      for (int j = 0; j <= COLS; j++)
      {
         if ((isNextToATree(dwarf, i, j) == true) && isTree(dwarf, i, j) == false) // starting from coordinates (0,0)... checks if adjacent to tree
         {
            if ((abs(r - i) < closest_row) && abs(c - j) < closest_col) // so if the lcoation is next to a tree set the location equal to closest row (will keep going till we find the closest tree)
            {
               closest_row = i;
               closest_col = j;
            }
         }
      }
   }
   log << "Walk to " << closest_row << " " << closest_col << endl;
   dwarf.start_walk(closest_row, closest_col);
}

/* onStart:
An Initialization procedure called at the start of the game.
You can use it to initialize certain global variables, or do
something else before the actual simulation starts.
Parameters:
    rows: number of rows
    cols: number of columns
    num:  number of dwarfs
    log:  a cout-like log */

void onStart(int rows, int cols, int num, std::ostream &log) {
  log << "Start!" << endl; // Print a greeting message

  ROWS = rows; // Save values in global variables
  COLS = cols;
  NUM = num;


}

/* onAction:
A procedure called each time an idle dwarf is choosing
their next action.
Parameters:
    dwarf:   dwarf choosing an action
    day:     day (1+)
    hours:   number of hours in 24-hour format (0-23)
    minutes: number of minutes (0-59)
    log:     a cout-like log  */

void onAction(Dwarf &dwarf, int day, int hours, int minutes, ostream &log) {
  // Get current position of the dwarf
  int r = dwarf.row();
  int c = dwarf.col();

  // Look if there is a tree on the right from the dwarf
  if (dwarf.look(r, c+1) == PINE_TREE || dwarf.look(r, c+1) == APPLE_TREE) {
    // If there is a pine tree, chop it
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(EAST);
    return;
  }
  else if (dwarf.look(r, c-1) == PINE_TREE || dwarf.look(r, c-1) == APPLE_TREE) { // Look if there is a tree on the left from the dwarf
    // If there is a pine tree, chop it
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(WEST);
    return;
  }
  else if (dwarf.look(r+1, c) == PINE_TREE || dwarf.look(r+1, c) == APPLE_TREE) { // Look if there is a tree below the dwarf
    // If there is a pine tree, chop it
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(SOUTH);
    return;
  }
  else if (dwarf.look(r-1, c) == PINE_TREE || dwarf.look(r-1, c) == APPLE_TREE) { // Look if there is a tree above the dwarf
    // If there is a pine tree, chop it
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(NORTH);
    return;
  }
  else {
    SendToClosestTree(dwarf, log);
    return;
  }
}
