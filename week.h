#include <iostream>
#include <string>
#include "tasks.h"
#include "days.h"
#include <vector>

using namespace std;


class Week {    
    public:
      // 0 to 6, where 0 is Monday and 6 is Sunday
      vector< vector < Task> > taskbyDay;


      //Constructor
      Week();

      //Methods
      string getTaskName();
      float getTaskCountdown();


    private:

};

Week::Week(){
  // just intialzing the week, this acts as more of a holder for now
}

// get the name of the task
Week::getTaskName(){
  string theName;
  int day = ; // mon = 0, tues = 1
  int taskNum = ; // 1st task = 0, 2nd task = 1,.. 5th task = 4
  theName =taskbyDay.at(day).at(taskNum).taskName;   //call the taskname
  return theName;
}

Week::getTaskCountdown(){
  float theTimer;
  int day = ; // mon = 0, tues = 1
  int taskNum = ; // 1st task = 0, 2nd task = 1,.. 5th task = 4
  theTimer =taskbyDay.at(day).at(taskNum).countdownTime();   //call remaining time
  return theTimer;
}