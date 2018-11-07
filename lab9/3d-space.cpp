/* Author: Daniel Berger
Course: CSCI-136
Instructor: Genady Maryash
Assignment: Lab9
function that receives coordinates if a point passed as a pointer and computes the distance from the origin to the point
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Coord3D {
public:
   double x;
   double y;
   double z;
}; // a class(or structure) consisting of 3 coordinates x y and z

double length(Coord3D *p)
{
   double total_sq, length;
   total_sq = pow(p->x, 2) + pow(p->y, 2) + pow(p->z, 2); // p is a pointer, access a class member by having p point to x,y,z
   length = sqrt(total_sq);

   return length;
}

Coord3D * fartherFromOrigin(Coord3D *p1, Coord3D *p2) // takes two coordinates and returns the one further from orgigin
{
   if (length(p1) > length(p2))
   {
      return p1;
   }
   else { return p2; }
}

void move(Coord3D *ppos, Coord3D *pvel, double dt)
{
   ppos->x = ppos->x + pvel->x * dt; // points to the x in the class
   ppos->y = ppos->y + pvel->y * dt; // points to the y in the class
   ppos->z = ppos->z + pvel->z * dt; // points to the z in the class
}

Coord3D* createCoord3D(double x, double y, double z)
{
   Coord3D *p = new Coord3D; // dynamically creates memory for the pointer

   p->x = x; // points to the x in the class
   p->y = y; // points to the y in the class
   p->z = z; // points to the z in the class

   return p;
}

void deleteCoord3D(Coord3D *p)
{
   delete p; // deletes the address
}

int main()
{
   //Coord3D pointP = {10, 20, 30};
   //cout << length(&pointP) << endl; // what happens if I remove the '&' ????

   /*
   Coord3D pointP = {10, 20, 30};
   Coord3D pointQ = {-20, 21, -22};

   cout << "Address of P: " << &pointP << endl;
   cout << "Address of Q: " << &pointQ << endl;

   Coord3D * ans = fartherFromOrigin(&pointP, &pointQ);
   cout << "ans = " << ans << endl; // prints which point is farther
   */

   /*
   Coord3D pos = {0, 0, 100.0};
   Coord3D vel = {1, -5, 0.2};

   move(&pos, &vel, 2.0); // object changes position
   cout << pos.x << " " << pos.y << " " << pos.z << endl;
   */

   double x, y, z;
   cout << "Enter position: ";
   cin >> x >> y >> z;
   Coord3D *ppos = createCoord3D(x,y,z);

   cout << "Enter velocity: ";
   cin >> x >> y >> z;
   Coord3D *pvel = createCoord3D(x,y,z);

   move(ppos, pvel, 10.0);

   cout << "Coordinates after 10 seconds: " << (*ppos).x << " " << (*ppos).y << " " << (*ppos).z << endl;

   deleteCoord3D(ppos); // deleting the adress of the coordinates
   deleteCoord3D(pvel);
}
