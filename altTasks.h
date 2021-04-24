#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <time.h>
#include <cstring>
#include <stdio.h>

using namespace std;

class Task{
    
    public:
        string taskName;
        string userDate;
        string userTime;
        time_t currentTime;
        time_t deadlineTime;
        time_t remainingTime;
        bool complete = false;
        bool pointsgiven = false; //check if the points have already been given
        bool validInput; // check for validity of input
        int pointsAwarded;
        int totalPointsAwarded;

    //Methods
        Task();
        void countdownTime();
        void updateUserPoints();
        void taskStatus();
        time_t userDuetime(string userDate, string userTime);
        void nameTask();
        void newdeadLine();
        void setTask();
        void calctime();
        void properInput();

    private:
    //Methods
        int bonus_points(time_t timeleft);
};


//basic constructor of task class
Task::Task(){
  pointsAwarded = 50; // base amount of points awarded
 
}

//error checking of inputs, run calctime first before calling this
void Task::properInput(){
  // 604800 is time of 1 week
  if ( (currentTime % 259199 == 0) && (remainingTime < 604800)){
    validInput = true;
  }else{
    validInput = false;
  }
}

//give the deadline times
void Task::setTask(){
  cin >> userDate;   
  cin >> userTime;
}


//get how much time is left until the task deadline in terms of hours
void Task::countdownTime(){
    currentTime = time(NULL);
    remainingTime = deadlineTime - currentTime; 
}

//call the User class to update user points
/*void Task::updateUserPoints(){
    currentTime = time(NULL);
    remainingTime = deadlineTime - currentTime; 
    if(complete == true  && pointsgiven == false){
      totalPointsAwarded = pointsAwarded + bonuspoints(remainingTime);
      //Add points to user Profile class, use userprofile points as nameholder for now
      userprofilePoints = userprofilePoints + totalPointsAwarded;
    }
    //sets points given as true, so this task will no longer give more points even if clicked and unclicked again
    pointsgiven = true;
}
*/
// update complete status to true and give user points

/*
void Task::taskStatus(){
  complete = true;
  updateUserPoints();
}

*/
//call to name the task
void Task::nameTask(){
  cin >> taskName;
}

int Task::bonus_points(time_t timeleft){
  int bonus;
  double calculate;
  if (timeleft <= 0){
    bonus = 0;
  } else {
    calculate = timeleft/3600; // to get in terms of hours
    cout << calculate << "\n";
    for (int i = 0; i < calculate; i++){
      bonus = i * 5; //5 points per hour before assigned deadline, if less then an hour no bonus points
    }
  }

  return bonus;

}

void Task::calctime(){
  deadlineTime = userDuetime(userDate, userTime);
  remainingTime = deadlineTime - currentTime;
}

//converts 2 user inputted strings into a time_t structure
time_t Task::userDuetime(string date, string time){
  char* month, *day, *hour, *min;
  const char * dt = date.c_str();
  const char * tm = time.c_str();
  char * temp1 = strdup(dt);
  char * temp2 = strdup(tm);

  char * date1 = strtok_r(temp1, " ", &temp1);
  month = strtok_r(date1, "-", &date1);
  day = strtok_r(date1, "-", &date1);

  hour = strtok_r(temp2, ":", &temp2);
  min = strtok_r(temp2, ":", &temp2);

  struct tm t = {0};  // Initalize to all 0's
  t.tm_year = (2021 - 1900);  // This is year 2021 - 1900, hardcoded in
  t.tm_mon = (atoi(month) - 1);
  t.tm_mday = atoi(day);
  t.tm_hour = (atoi(hour) - 1);
  t.tm_min = atoi(min);
  //t.tm_sec = ;
  time_t deadline = mktime(&t); //gets the time_t variable we want

  return deadline;
}
