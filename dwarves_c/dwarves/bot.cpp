
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


bool GatherLumber = true; // true until 300 lumber is reached
bool FirstFencePlaced = false;
bool Walk = true;
//bool center = true;

// declaration of all functions
bool isFence(Dwarf & dwarf, int r, int c);
bool isEmpty(Dwarf & dwarf, int r, int c);
bool isNextToFence(Dwarf & dwarf, int r, int c);
bool isNextToATree(Dwarf & dwarf, int r, int c);
void SendToClosestTree(Dwarf & dwarf, std::ostream &log);
void SendDwarfCloseToFence(Dwarf & dwarf, std::ostream &log);
void firstFence(Dwarf & dwarf, int r, int c, std::ostream &log);
void BuildFence(Dwarf & dwarf, std::ostream &log);
void FindClosestFence(Dwarf & dwarf, int & r_fence, int & c_fence ,std::ostream &log);
void FindClosestApple(Dwarf & dwarf, int & r_apple, int & c_apple ,std::ostream &log);

// end of all declaration
bool AreTherePumpkins(Dwarf & dwarf, int r, int c) { // CHECKS IF THERE ANY PUMPKINS ON THE BOARD
   int count = 0;
   for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
         if (dwarf.look(i, j) == PUMPKIN)
         {
            count++;
         }
      }
   }
   if (count == 0) {
      return false;
   }
   else { return true; }
}

bool isPumpkin(Dwarf & dwarf, int r, int c) // checks if tthe sqaure contains a PUMPKIN
{
   if (dwarf.look(r, c) == PUMPKIN)
   {
      return true;
   }
   else { return false;}
}

bool isApple(Dwarf & dwarf, int r, int c) // checks if tthe sqaure contains an apple tree
{
   if (dwarf.look(r, c) == APPLE_TREE)
   {
      return true;
   }
   else { return false;}
}

bool isFence(Dwarf & dwarf, int r, int c) // checks if tthe sqaure contains a fence
{
   if (dwarf.look(r, c) == FENCE)
   {
      return true;
   }
   else { return false;}
}

bool isEmpty(Dwarf & dwarf, int r, int c) // checks if the square is empty
{
   if (dwarf.look(r, c) == EMPTY)
   {
      return true;
   }
   else { return false;}
}

bool isNextToEmpty(Dwarf & dwarf, int r, int c) // checks if there is a sqaure next to a fence(or anything else) that is empty
{
   if (dwarf.look(r, c+1) == EMPTY) {
      return true;
   }
   else if (dwarf.look(r, c-1) == EMPTY) {
      return true;
   }
   else if (dwarf.look(r+1, c) == EMPTY) {
      return true;
   }
   else if (dwarf.look(r-1, c) == EMPTY) {
      return true;
   }
   else {return false;}
}
bool isNextToAnyTree(Dwarf & dwarf, int r, int c) {
   if (dwarf.look(r, c+1) == PINE_TREE || dwarf.look(r, c+1) == APPLE_TREE) {
      return true;
   }
   else if (dwarf.look(r, c-1) == PINE_TREE || dwarf.look(r, c+1) == APPLE_TREE) {
      return true;
   }
   else if (dwarf.look(r+1, c) == PINE_TREE || dwarf.look(r, c+1) == APPLE_TREE) {
      return true;
   }
   else if (dwarf.look(r-1, c) == PINE_TREE || dwarf.look(r, c+1) == APPLE_TREE) {
      return true;
   }
   else {return false;}
}


bool isNextToATree(Dwarf & dwarf, int r, int c) { // checks if the square is next to a pine tree
   if (dwarf.look(r, c+1) == PINE_TREE) {
      return true;
   }
   else if (dwarf.look(r, c-1) == PINE_TREE) {
      return true;
   }
   else if (dwarf.look(r+1, c) == PINE_TREE) {
      return true;
   }
   else if (dwarf.look(r-1, c) == PINE_TREE) {
      return true;
   }
   else {return false;}
}

bool isNextToAppleTree(Dwarf & dwarf, int r, int c) { // checks if the square is next to a apple tree
   if (dwarf.look(r, c+1) == APPLE_TREE) {
      return true;
   }
   else if (dwarf.look(r, c-1) == APPLE_TREE) {
      return true;
   }
   else if (dwarf.look(r+1, c) == APPLE_TREE) {
      return true;
   }
   else if (dwarf.look(r-1, c) == APPLE_TREE) {
      return true;
   }
   else {return false;}
}

bool isNextToPumpkin(Dwarf & dwarf, int r, int c) { // checks if the square is next to a apple tree
   if (dwarf.look(r, c+1) == PUMPKIN) {
      return true;
   }
   else if (dwarf.look(r, c-1) == PUMPKIN) {
      return true;
   }
   else if (dwarf.look(r+1, c) == PUMPKIN) {
      return true;
   }
   else if (dwarf.look(r-1, c) == PUMPKIN) {
      return true;
   }
   else {return false;}
}

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

void firstFence(Dwarf & dwarf, int r, int c, std::ostream &log) // dwarf 0 will builds the first fence wherever he is when the dwarves stop collecting lumber
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
         log << "Constructing first Fence 4" << endl;
      }
      FirstFencePlaced = true;
      log << "Placed the first fence!" << endl;
   }
}

void FindClosestFence(Dwarf & dwarf, int & r_fence, int & c_fence ,std::ostream &log) {

   int r = dwarf.row();
   int c = dwarf.col();

   double distance_so_far = 9999;
   //log << "the row fence is" << r_fence << endl;
   //log << "the col fence is " << c_fence << endl;
   for (int i = 0; i < ROWS; i++)
   {
      for (int j = 0; j < COLS; j++)
      {
         double d = sqrt(pow((r - i),2) + pow((c - j),2));
         if ((isFence(dwarf, i, j)) && (isNextToEmpty(dwarf, i, j))) // starting from coordinates (0,0)... checks if adjacent to tree
         {
            if (d < distance_so_far) // so if the lcoation is next to a tree set the location equal to closest row (will keep going till we find the closest tree)
            {
               distance_so_far = d;
               r_fence = i; // stores the row of the fence
               c_fence = j; // stores the row of the fence
               //log << "the distance so far is " << d << endl;
               log << "The row of the fence is  " << r_fence << endl;
               log << "The col of the fence is  " << c_fence << endl;
            }
         }
      }
   }
}

void SendDwarfCloseToFence(Dwarf & dwarf, int r_fence, int c_fence ,std::ostream &log) {
   if (isEmpty(dwarf, r_fence - 2, c_fence))
   {
      log << "Walk to (1) " << r_fence - 2 << " " << c_fence << endl;
      dwarf.start_walk(r_fence - 2, c_fence);
      return;
   }
   else if (isEmpty(dwarf, r_fence + 2, c_fence))
   {
      log << "Walk to (2) " << r_fence + 2 << " " << c_fence << endl;
      log << r_fence << " " << c_fence;
      dwarf.start_walk(r_fence + 2, c_fence);
      return;
   }
   else if (isEmpty(dwarf, r_fence, c_fence - 2))
   {
      log << "Walk to (3) " << r_fence << " " << c_fence - 2 << endl;
      dwarf.start_walk(r_fence, c_fence - 2);
      return;
   }
   else if (isEmpty(dwarf, r_fence, c_fence + 2))
   {
      log << "Walk to (4) " << r_fence << " " << c_fence + 2 << endl;
      dwarf.start_walk(r_fence, c_fence + 2);
      return;
   }
   else { return; }
}

void BuildFence(Dwarf & dwarf, std::ostream &log) {
   int r = dwarf.row();
   int c = dwarf.col();

   //static int fence_count = 1;

   if ((dwarf.look(r - 2, c) == FENCE) && (dwarf.look(r - 1, c) == EMPTY))
   {
      log << " Constructing NORTH fence" << endl;
      dwarf.start_build(NORTH);
   }
   else if ((dwarf.look(r + 2, c) == FENCE) && (dwarf.look(r + 1, c) == EMPTY))
   {
      log << " Constructing SOUTH fee" << endl;
      dwarf.start_build(SOUTH);
   }
   else if ((dwarf.look(r, c - 2) == FENCE) && (dwarf.look(r, c - 1) == EMPTY))
   {
      log << " Constructing WEST fence" << endl;
      dwarf.start_build(WEST);
   }
   else if ((dwarf.look(r, c + 2) == FENCE) && (dwarf.look(r, c + 1) == EMPTY))
   {
      log << " Constructing EAST fence" << endl;
      dwarf.start_build(EAST);
   }
   else { return; } // if there is no dwarf in a viable build location
}

void Build(Dwarf & dwarf, std::ostream &log) { // just builds in all directions
   int r = dwarf.row();
   int c = dwarf.col();

   //static int fence_count = 1;

   if ((dwarf.look(r - 1, c) == EMPTY))
   {
      log << " Constructing NORTH fence" << endl;
      dwarf.start_build(NORTH);
   }
   else if ((dwarf.look(r + 1, c) == EMPTY))
   {
      log << " Constructing SOUTH fee" << endl;
      dwarf.start_build(SOUTH);
   }
   else if ((dwarf.look(r, c - 1) == EMPTY))
   {
      log << " Constructing WEST fence" << endl;
      dwarf.start_build(WEST);
   }
   else if ((dwarf.look(r, c + 1) == EMPTY))
   {
      log << " Constructing EAST fence" << endl;
      dwarf.start_build(EAST);
   }
   else { return; } // if there is no dwarf in a viable build location
}

void PickApple(Dwarf & dwarf, std::ostream &log) {
   int r = dwarf.row();
   int c = dwarf.col();

   //static int fence_count = 1;

   if ((dwarf.look(r - 1, c) == APPLE_TREE))
   {
      log << " Picking Apple NORTH " << endl;
      dwarf.start_pick(NORTH);
   }
   else if ((dwarf.look(r + 1, c) == APPLE_TREE))
   {
      log << " Picking Apple SOUTH " << endl;
      dwarf.start_pick(SOUTH);
   }
   else if ((dwarf.look(r, c - 1) == APPLE_TREE))
   {
      log << " Picking Apple WEST " << endl;
      dwarf.start_pick(WEST);
   }
   else if ((dwarf.look(r, c + 1) == APPLE_TREE))
   {
      log << " Picking Apple EAST " << endl;
      dwarf.start_pick(EAST);
   }
   else { return; } // if there is no dwarf in a viable build location
}

void PickPumpkin(Dwarf & dwarf, std::ostream &log) {
   int r = dwarf.row();
   int c = dwarf.col();

   //static int fence_count = 1;

   if ((dwarf.look(r - 1, c) == PUMPKIN))
   {
      log << " Picking PUMPKIN NORTH " << endl;
      dwarf.start_pick(NORTH);
   }
   else if ((dwarf.look(r + 1, c) == PUMPKIN))
   {
      log << " Picking PUMPKIN SOUTH " << endl;
      dwarf.start_pick(SOUTH);
   }
   else if ((dwarf.look(r, c - 1) == PUMPKIN))
   {
      log << " Picking PUMPKIN WEST " << endl;
      dwarf.start_pick(WEST);
   }
   else if ((dwarf.look(r, c + 1) == PUMPKIN))
   {
      log << " Picking PUMPKIN EAST " << endl;
      dwarf.start_pick(EAST);
   }
   else { return; } // if there is no dwarf in a viable build location
}

void FindClosestApple(Dwarf & dwarf, int & r_apple, int & c_apple ,std::ostream &log) {
   int r = dwarf.row();
   int c = dwarf.col();

   double distance_so_far = 9999;
   //log << "the row fence is" << r_fence << endl;
   //log << "the col fence is " << c_fence << endl;
   for (int i = 0; i < ROWS; i++)
   {
      for (int j = 0; j < COLS; j++)
      {
         double d = sqrt(pow((r - i),2) + pow((c - j),2));
         if ((isApple(dwarf, i, j)) && (isNextToEmpty(dwarf, i, j))) // is that square an apple tree and is the space next to it empty
         {
            if (d < distance_so_far) // so if the lcoation is next to a tree set the location equal to closest row (will keep going till we find the closest tree)
            {
               distance_so_far = d;
               r_apple = i; // stores the row of the apple
               c_apple = j; // stores the row of the apple
            }
         }
      }
   }
}

void FindClosestPumpkin(Dwarf & dwarf, int & r_pumpkin, int & c_pumpkin ,std::ostream &log) {
   int r = dwarf.row();
   int c = dwarf.col();

   double distance_so_far = 9999;
   //log << "the row fence is" << r_fence << endl;
   //log << "the col fence is " << c_fence << endl;
   for (int i = 0; i < ROWS; i++)
   {
      for (int j = 0; j < COLS; j++)
      {
         double d = sqrt(pow((r - i),2) + pow((c - j),2));
         if ((isPumpkin(dwarf, i, j)) && (isNextToEmpty(dwarf, i, j))) // is that square an apple tree and is the space next to it empty
         {
            if (d < distance_so_far) // so if the lcoation is next to a tree set the location equal to closest row (will keep going till we find the closest tree)
            {
               distance_so_far = d;
               r_pumpkin = i; // stores the row of the pumpkin
               c_pumpkin = j; // stores the row of the pumpkin
            }
         }
      }
   }
}

void SendDwarfCloseToPumpkin(Dwarf & dwarf, int r_pumpkin, int c_pumpkin ,std::ostream &log) {
   FindClosestPumpkin(dwarf, r_pumpkin, c_pumpkin ,log);
   if (isEmpty(dwarf, r_pumpkin - 1, c_pumpkin))
   {
      log << "Walk to (1) " << r_pumpkin - 1 << " " << c_pumpkin << endl;
      dwarf.start_walk(r_pumpkin - 1, c_pumpkin);
      return;
   }
   else if (isEmpty(dwarf, r_pumpkin + 1, c_pumpkin))
   {
      log << "Walk to (2) " << r_pumpkin + 1 << " " << c_pumpkin << endl;
      log << r_pumpkin << " " << c_pumpkin;
      dwarf.start_walk(r_pumpkin + 1, c_pumpkin);
      return;
   }
   else if (isEmpty(dwarf, r_pumpkin, c_pumpkin - 1))
   {
      log << "Walk to (3) " << r_pumpkin << " " << c_pumpkin - 1 << endl;
      dwarf.start_walk(r_pumpkin, c_pumpkin - 1);
      return;
   }
   else if (isEmpty(dwarf, r_pumpkin, c_pumpkin + 2))
   {
      log << "Walk to (4) " << r_pumpkin << " " << c_pumpkin + 1 << endl;
      dwarf.start_walk(r_pumpkin, c_pumpkin + 1);
      return;
   }
   else { return; }
}

void SendDwarfCloseToApple(Dwarf & dwarf, int r_apple, int c_apple ,std::ostream &log) {
   FindClosestApple(dwarf, r_apple, c_apple ,log);
   if (isEmpty(dwarf, r_apple - 1, c_apple))
   {
      log << "Walk to (1) " << r_apple - 1 << " " << c_apple << endl;
      dwarf.start_walk(r_apple - 1, c_apple);
      return;
   }
   else if (isEmpty(dwarf, r_apple + 1, c_apple))
   {
      log << "Walk to (2) " << r_apple + 1 << " " << c_apple << endl;
      log << r_apple << " " << c_apple;
      dwarf.start_walk(r_apple + 1, c_apple);
      return;
   }
   else if (isEmpty(dwarf, r_apple, c_apple - 1))
   {
      log << "Walk to (3) " << r_apple << " " << c_apple - 1 << endl;
      dwarf.start_walk(r_apple, c_apple - 1);
      return;
   }
   else if (isEmpty(dwarf, r_apple, c_apple + 2))
   {
      log << "Walk to (4) " << r_apple << " " << c_apple + 1 << endl;
      dwarf.start_walk(r_apple, c_apple + 1);
      return;
   }
   else { return; }
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

  int r_fence = 0;
  int c_fence = 0;

  int r_apple = 0;
  int c_apple = 0;

  int r_pumpkin = 0;
  int c_pumpkin = 0;



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


  // On day seven we are going to cut the rest of the trees builf 30 fences plus box themselves in
  if (day == 7 && hours > 7) {
     //if (there are no pine trees left) {
        //while (dwarf.lumber() <)
     //}

     if (dwarf.look(r, c+1) == PINE_TREE || dwarf.look(r, c+1) == APPLE_TREE || dwarf.look(r, c + 1) == FENCE) {
      // If there is a pine tree, chop it
      log << "Found a tree -- chop" << endl;
      dwarf.start_chop(EAST);
      return;
     }
     else if (dwarf.look(r, c-1) == PINE_TREE || dwarf.look(r, c-1) == APPLE_TREE || dwarf.look(r, c - 1) == FENCE) { // Look if there is a tree on the left from the dwarf
      // If there is a pine tree, chop it
      log << "Found a tree -- chop" << endl;
      dwarf.start_chop(WEST);
      return;
     }
     else if (dwarf.look(r+1, c) == PINE_TREE || dwarf.look(r+1, c) == APPLE_TREE || dwarf.look(r + 1, c) == FENCE) { // Look if there is a tree below the dwarf
      // If there is a pine tree, chop it
      log << "Found a tree -- chop" << endl;
      dwarf.start_chop(SOUTH);
      return;
     }
     else if (dwarf.look(r-1, c) == PINE_TREE || dwarf.look(r-1, c) == APPLE_TREE || dwarf.look(r - 1, c) == FENCE) { // Look if there is a tree above the dwarf
      // If there is a pine tree, chop it
      log << "Found a tree -- chop" << endl;
      dwarf.start_chop(NORTH);
      return;
     }
      else {
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
               if (isNextToAnyTree(dwarf, i, j) && isEmpty(dwarf, i, j)) // starting from coordinates (0,0)... checks if adjacent to tree
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
  }

  // for the first day start sending the dwarves to apples and build and pick
  if (day < 2) {
     if (!isNextToAppleTree(dwarf, r, c)) {
       SendDwarfCloseToApple(dwarf, r_apple, c_apple ,log);
     }
     else if (isNextToAppleTree(dwarf, r, c)) {
       Build(dwarf, log);
       PickApple(dwarf, log);
     }
  }


  // if it is not the first day
  else if (day >= 2) {
     if (dwarf.name() == 1) { // dwarf 1 will
        if (hours >= 7 && hours <= 21) { // during the day time
           if (AreTherePumpkins(dwarf, r, c) == true) { // if there still pumpkins on the board
              if (!isNextToPumpkin(dwarf, r, c)) {
                // if there is a fence cut it so it cna go out and pick pumpkins
                if (dwarf.look(r - 1, c) == FENCE) { // cut a north fence
                   dwarf.start_chop(NORTH);
                }
                else if (dwarf.look(r + 1, c) == FENCE) { //
                   dwarf.start_chop(SOUTH);
                }
                else if (dwarf.look(r , c - 1) == FENCE) { //
                   dwarf.start_chop(WEST);
                }
                else if (dwarf.look(r, c + 1) == FENCE) { //
                   dwarf.start_chop(EAST);
                }
                else {
                   SendDwarfCloseToPumpkin(dwarf, r_pumpkin, c_pumpkin, log); // go the closest pumpkin
                }
              }
              else if (isNextToPumpkin(dwarf,r,c)) { // and pick it
                PickPumpkin(dwarf, log);
              }
           }
           else { // if there are no pumkins left go to an apple tree build and pick
             if (!isNextToAppleTree(dwarf, r, c)) {
                SendDwarfCloseToApple(dwarf, r_apple, c_apple ,log);
             }
             else if (isNextToAppleTree(dwarf, r, c)) {
                Build(dwarf, log);
                PickApple(dwarf, log);
             }
           }
        }
     }
     // still for after day 1
     else if (dwarf.name() != 1) { // all other dwarfs will remain next to an apple tree and pick
        if (!isNextToAppleTree(dwarf, r, c)) {
          SendDwarfCloseToApple(dwarf, r_apple, c_apple ,log);
        }
        else if (isNextToAppleTree(dwarf, r, c)) {
          Build(dwarf, log);
          PickApple(dwarf, log);
        }
     }
  }
  // soo what i need to do is at in the day time i need to send
  // 1 -4 other dwarfs to collect pumpkins
  // and clsoe to night time again they need to go back to the apple tree
  // build and then Pick
  // then on the last day they can all build a structure


  return;

}
