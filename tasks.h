#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
using namespace std;


// function to convert user inputted time to time_t structure

time_t user_totime(string givendeadline){
  int yyyy, month, day, hh, mm, ss;

  struct tm when = {0};

  sscanf(givendeadline, "%d-%d-%d %d:%d:%d", &yyy, &month, &day, &hh, &mm, &ss)

  when.tm_year = (yyyy - 1900);
  when.tm_mon = month;
  when.tm_mday = day;
  when.tm_hour = hh;
  when.tm_min = mm;
  when.tm_sec = ss;


  time_t converted;
  converted = mktime(&when);
  return converted;
}



class Task{
    
    public:
        string taskName;
        string userdeadline; 
        time_t currentTime;
        time_t deadlineTime;
        time_t remainingTime;
        int expectedLength;
        bool complete = false;

    private:
        int pointsAwarded; // user shouldn't be able to determine thier own point gain

};

Task::Task(){
  cin >> taskName; // give the name of the task

  cin >> expectedLength  // how long you expect it to take in minutes

  cin >> userdeadline;  // user inputs a string in a certain format; ex: 12:45:07

  deadlineTime = user_totime(userdeadline);  //string to time_t variable


  remainingTime = deadlineTime - currentTime; // once user clicks the checkbox the remaining time should be calculated


  expectedLength = expectedLength * 60; //user gives time in minutes conversion to seconds
  pointsAwarded = 100; // base amount of points awarded



}
