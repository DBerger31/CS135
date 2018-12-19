/* Author: Daniel Berger
Course: CSCI-136
Instructor: Genady Maryash
Assignment: Lab10
time class and functions
*/

#include <iostream>
#include <string>
#include <cmath>

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

class TimeSlot {
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

void printTimeSlot(TimeSlot ts)
{
   printMovie(ts.movie);
   Time endtime;
   endtime = addMinutes(ts.startTime, ts.movie.duration);
   cout << "[starts at ";
   printTime(ts.startTime);
   cout << ", ends by ";
   printTime(endtime);
   cout << "]" << endl;
   //cout << "[starts at " << printTime(ts.startTime) << ", ends by " << printTime(endtime) << "]";
}

TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie)
{
   TimeSlot next;
   next.movie = nextMovie;
   next.startTime = addMinutes(ts.startTime, ts.movie.duration);
   return next;
}

bool timeOverlap(TimeSlot ts1, TimeSlot ts2)
{
   int start1 = minutesSinceMidnight(ts1.startTime); // start time in minutes
   int start2 = minutesSinceMidnight(ts2.startTime); // start time in minutes
   Time end1 = addMinutes(ts1.startTime, ts1.movie.duration); // end time in minutes
   Time end2 = addMinutes(ts2.startTime, ts2.movie.duration); // end time in minutes
   int end11 = minutesSinceMidnight(end1);
   int end22 = minutesSinceMidnight(end2);

   if (start1 == start2)
   {
      return true;
   }
   else if(start1 < start2)
   {
      if(end11 > start2)
      {
         return true;
      }
   }
   else if(start2 < start1)
   {
      if(end22 > start1)
      {
         return true;
      }
   }

   return false;
}

int main()
{
   //Time first;
   //Time second;
   //Time newtime;

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

   Movie movie1 = {"Black Panther", ACTION, 134};
   Movie movie2 = {"Dumb and Dumber", COMEDY, 100};
   Movie movie3 = {"50 shades of Gay", ROMANCE, 224};

   TimeSlot morning = {movie1, {11, 30}};
   TimeSlot day = {movie1, {12, 30}};
   TimeSlot noon = {movie2, {12, 00}};
   TimeSlot evening = {movie2, {17, 26}};
   TimeSlot night = {movie3, {19, 30}};

   printTimeSlot(morning);
   printTimeSlot(day);
   printTimeSlot(noon);
   printTimeSlot(evening);
   printTimeSlot(night);

   if (timeOverlap(morning, day) == true)
   {
      cout << "overlap";
   }
   else {cout << "u good";}

return 0;
}
