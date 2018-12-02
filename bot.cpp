
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
int Coord2D[MAX_ROWS][MAX_COLS]; // creates a global two dimensional array

bool GatherLumber = true; // true until 300 lumber is reached
bool FirstFencePlaced = false;
bool Walk = true;

/*class Coord2D
{
public:
   int r;
   int c;
};*/

bool isEmpty(Dwarf & dwarf, int r, int c) // checks if that square alone contains a tree
{
   if (dwarf.look(r, c) == EMPTY)
   {
      return true;
   }
   else { return false;}
}

bool isFence(Dwarf & dwarf, int r, int c) // checks if that square alone contains a tree
{
   if (dwarf.look(r, c) == FENCE)
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

   int closest_row = 0;
   int closest_col = 0;
   double sd = 9999;

   for (int i = 0; i < ROWS; i++)
   {
      for (int j = 0; j < COLS; j++)
      {
         double d = sqrt(pow((r - i),2) + pow((c - j),2));
         if (isNextToATree(dwarf, i, j) && isEmpty(dwarf, i, j)) // starting from coordinates (0,0)... checks if adjacent to tree
         {
            if (d < sd) // so if the lcoation is next to a tree set the location equal to closest row (will keep going till we find the closest tree)
            {
               sd = d;
               closest_row = i;
               closest_col = j;
            }
         }
      }
   }
   log << "Walk to " << closest_row << " " << closest_col << endl;
   dwarf.start_walk(closest_row, closest_col);
}

void CreateMap(Dwarf &dwarf, std::ostream &log)
{
   for (int i = 0; i < ROWS; i++)
   {
      for (int j = 0; j < COLS; j++)
      {
         if (dwarf.look(i, j) == FENCE)
         {
            Coord2D[i][j] = FENCE;
         }
         else if (dwarf.look(i, j) == APPLE_TREE)
         {
            Coord2D[i][j] = APPLE_TREE;
         }
         else if (dwarf.look(i, j) == PINE_TREE)
         {
            Coord2D[i][j] = PINE_TREE;
         }
         else if (dwarf.look(i, j) == DWARF)
         {
            Coord2D[i][j] = DWARF;
         }
         else if (dwarf.look(i, j) == EMPTY)
         {
            Coord2D[i][j] = EMPTY;
         }
      }
   }
}

void SendDwarfCloseToFence(Dwarf & dwarf, std::ostream &log)
{
   if (dwarf.name() && Walk == true)
   {
      for (int i = 0; i < ROWS; i++)
      {
         if (Walk == false)
         {
            break;
         }
         for (int j = 0; j < COLS; j++)
         {
            if (Coord2D[i][j] == FENCE)
            {
               if ((Coord2D[i - 1][j] == EMPTY) && (Coord2D[i - 2][j] == EMPTY))
               {
                  dwarf.start_walk(i - 2, j);
                  log << " walked ";
                  Walk = false;
                  break;
               }
               else if ((Coord2D[i + 1][j] == EMPTY) && (Coord2D[i + 2][j] == EMPTY))
               {
                  dwarf.start_walk(i + 2, j);
                  log << " walked ";
                  Walk = false;
                  break;
               }
               else if ((Coord2D[i][j - 1] == EMPTY) && (Coord2D[i - 2][j] == EMPTY))
               {
                  dwarf.start_walk(i, j - 2);
                  log << " walked ";
                  Walk = false;
                  break;
               }
               else if ((Coord2D[i][j + 1] == EMPTY) && (Coord2D[i - 2][j] == EMPTY))
               {
                  dwarf.start_walk(i, j + 2);
                  log << " walked ";
                  Walk = false;
                  break;
               }
            }
         }
      }
   }
   CreateMap(dwarf,log);
}

//dwarve 0 builds one fence as a starting point
void firstFence(Dwarf & dwarf, int r, int c, std::ostream &log)
{
   if (dwarf.name() == 0)
   {
      if (isEmpty(dwarf, r, c+1)) {
         dwarf.start_build(EAST);
         log << "Constructing first Fence 1" << endl;
      }
      else if (isEmpty(dwarf, r, c-1)) {
         dwarf.start_build(WEST);
         log << "Constructing first Fence 2" << endl;
      }
      else if (isEmpty(dwarf, r+1, c)) {
         dwarf.start_build(SOUTH);
         log << "Constructing first Fence 3" << endl;
      }
      else if (isEmpty(dwarf, r-1, c)) {
         dwarf.start_build(NORTH);
         log << "Constructing first Fence" << endl;
      }
      FirstFencePlaced = true;
      log << "done with the first func" << endl;
   }
   //CreateMap(dwarf, log); // creates a map after the first fence has been built
}


void ReadMap(Dwarf &dwarf, std::ostream &log)
{
   for (int i = 0; i < ROWS; i++)
   {
      for (int j = 0; j < COLS; j++)
      {
         if (Coord2D[i][j] == FENCE)
         {
            log << "THE LOCATION " << i << " ," << j << " CONTAINS FENCE" << endl;
         }
         else if (Coord2D[i][j] == APPLE_TREE)
         {
            log << "THE LOCATION " << i << " ," << j << " CONTAINS APPLE TREE" << endl;
         }
         else if (Coord2D[i][j] == EMPTY)
         {
            log << "THE LOCATION " << i << " ," << j << " CONTAINS EMPTY" << endl;
         }
      }
   }
}

void BuildFence(Dwarf & dwarf, std::ostream &log)
{
   int r = dwarf.row();
   int c = dwarf.col();

   if (dwarf.name() && Walk == false)
   {
      for (int i = 0; i < ROWS; i++)
      {
         if (Walk == true)
         {
            break;
         }
         for (int j = 0; j < COLS; j++)
         {
            if (Coord2D[r - 2][c] == FENCE)
            {
               dwarf.start_build(NORTH);
               log << " built a fence 1" << endl;
               Walk = true;
               break;
            }
            else if (Coord2D[r + 2][c] == FENCE)
            {
               dwarf.start_build(SOUTH);
               log << " built a fence 2" << endl;
               Walk = true;
               break;
            }
            else if (Coord2D[r][c - 2] == FENCE)
            {
               dwarf.start_build(WEST);
               log << " built a fence 3" << endl;
               Walk = true;
               break;
            }
            else if (Coord2D[r][c + 2] == FENCE)
            {
               dwarf.start_build(EAST);
               log << " built a fence 4" << endl;
               Walk = true;
               break;
            }
         }
      }
   }
   CreateMap(dwarf,log);
}


/* onStart:

An Initialization procedure called at the start of the game.
You can use it to initialize certain global variables, or do
something else before the actual simulation starts.
rows: number of rows
Parameters:
    cols: number of columns
    num:  number of dwarfs
    log:  a cout-like log */

void onStart(int rows, int cols, int num, std::ostream &log) {
  log << "Start!" << endl; // Print a greeting message
  // Look if there is a tree on the right from the dwarf

  ROWS = rows; // Save values in global variables
  COLS = cols;
  NUM = num;


}

/* onAction:
A procedure called each time an idle dwarf is choosing
their next action.
    dwarf:   dwarf choosing an action
    Parameters:
    day:     day (1+)
    hours:   number of hours in 24-hour format (0-23)
    minutes: number of minutes (0-59)
    log:     a cout-like log  */

void onAction(Dwarf &dwarf, int day, int hours, int minutes, ostream &log) {
  // Get current position of the dwarf
  int r = dwarf.row();
  int c = dwarf.col();

  // Phase one of the game is cutting the trees to obtain enough lumber to start building a fence

  while(GatherLumber) // once our lumber is greater than 300 we stop chopping trees by all dwarves
  {
     if (dwarf.lumber() >= 300)
     {
        GatherLumber = false;
        //BuildFence(dwarf, r, c, log);
     }

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

  if (!FirstFencePlaced)
  {
     firstFence(dwarf, r, c, log);
     //FirstFencePlaced = true;
  }
  else if (Walk)
  {
     SendDwarfCloseToFence(dwarf, log);
  }
  else if (!Walk)
  {
     BuildFence(dwarf, log);
 }



  // now we should start building
  //firstFence(dwarf, r, c, log);
  //ReadMap(dwarf, log);
  return;

}
