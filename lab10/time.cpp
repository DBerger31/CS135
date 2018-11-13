/* Author: Daniel Berger
Course: CSCI-136
Instructor: Genady Maryash
Assignment: Lab10
time class and functions
*/

#include <iostream>
#include <string>

using namespace std;

class Time {
public:
    int h;
    int m;
};

void printTime(Time time)
{
    cout << time.h << ":" << time.m;
}

int minutesSinceMidnight(Time time) // returns the minutes away from midnight
{
   return time.h * 60 + time.m;
}

int minutesUntil(Time earlier, Time later) // returns the difference in minutes between the two times
{
   return minutesSinceMidnight(later) - minutesSinceMidnight(earlier);
}

Time addMinutes(Time time0, int min) // this can be optimized better by rounding down
{
   Time time1;
   if(min < 60)
   {
      time1.h = time0.h;
      time1.m = time0.m + min;
   }
   else
   {
      time1.h = time0.h + ((min) - (min % 60)) / 60;
      time1.m = time0.m + min % 60;
   }

   if(time1.m >= 60)
   {
      time1.m = time1.m % 60;
      time1.h = time1.h + 1; // why cant it be time1.h++ ?????
   }
   return time1;
}

enum Genre {ACTION, COMEDY, DRAMA, ROMANCE, THRILLER};

class Movie {
public:
   string title;
   Genre genre; // only one genre per movie
   int duration; // in minutes
};

class Timeslot {
public:
   Movie movie; // What movie
   Time startTime; // when the movie starts
};

void printMovie(Movie mv){
    string g;
    switch (mv.genre) {
        case ACTION   : g = "ACTION"; break;
        case COMEDY   : g = "COMEDY"; break;
        case DRAMA    : g = "DRAMA";  break;
        case ROMANCE  : g = "ROMANCE"; break;
        case THRILLER : g = "THRILLER"; break;
    }
    cout << mv.title << " " << g << " (" << mv.duration << " min)";
}

void PrintTimeslot(Timeslot ts)
{
   printMovie(ts.movie);
   Time endtime;
   endtime = addMinutes(ts.startTime, ts.movie.duration);
   cout << "[starts at ";
   printTime(ts.startTime);
   cout << ", ends by ";
   printTime(endtime);
   cout << "]";
   //cout << "[starts at " << printTime(ts.startTime) << ", ends by " << printTime(endtime) << "]";
}

int main()
{
   Time first;
   Time second;
   Time newtime;

   /*cout << "Enter a first time: " << endl;
   cin >> first.h >> first.m; // input time on one line hours and minutes are seperated by spaces
   cout << "Enter a second time: " << endl;
   cin >> second.h >> second.m; // input time on one line hours and minutes are seperated by spaces

   cout << "The first time is : " << minutesSinceMidnight(first) << " minutes from midnight" << endl;
   cout << "The second time is : " << minutesSinceMidnight(second) << " minutes from midnight" << endl;

   cout << "The interval between them is : " << minutesUntil(first, second) << " minutes";*/
   //printTime(first);
   //printTime(second);

   //newtime = addMinutes({8,10}, 75);
   //printTime(newtime);

   Movie one = {"Black Panther", ACTION, 134};
   Movie two = {"Dumb and Dumber", COMEDY, 100};
   Movie three = {"50 shades of Gay", ROMANCE, 224};

   Timeslot morning = {one, {11, 30}};
   Timeslot day = {one, {2, 30}};
   Timeslot noon = {two, {12, 00}};
   Timeslot evening = {two, {17, 26}};
   Timeslot night = {three, {19, 30}};

   PrintTimeslot(morning);
}
