#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
#include <chrono>
#include <cstring>
#include <stdio.h>
//will need to include the Profile class and button class?

using namespace std;




// all inputs will be strings     scin == strings

class Task{
    
    public:
        string taskName;
        string userdeadlinedate;
        string userdeadlinetime;
        string strexpectedLength;
        string strCountdown;
        time_t currentTime;
        time_t deadlineTime;
        time_t remainingTime;
        int expectedLength;
        bool complete = false;
        bool pointsgiven = false; //check if the points have already been given

    //Methods
        Task();
        void countdownTime();
        void updateUserPoints();
        void taskStatus(click event);
        time_t user_totime(string date, string time);
        void renameTask();
        void newdeadLine();

    private:
        int pointsAwarded;
        int totalPointsAwarded;

    //Methods
        int bonus_points(time_t timeleft);
};


//basic constructor of task class
Task::Task(){
  scin >> taskName; // give the name of the task

  scin >> strexpectedLength;  // string for how long you expect it to take in minutes
  expectedLength = stoi(strexpectedLength); // turn string into integer value that can be used
  expectedLength = expectedLength * 60; //user gives time in minutes, task converts to seconds for use in time_t structures
      
  scin >> userdeadlinedate; // user inputs a string in a certain format; example: Year-Month-Day -> 2021-4-18
  scin >> userdeadlinetime; // user inputs the string in a certain format; example: Hour:Minute -> 12:45
    
  deadlineTime = user_totime(userdeadlinedate, userdeadlinetime);  //string to time_t variable
  pointsAwarded = 100; // base amount of points awarded
 
}
//get how much time is left until the task deadline in terms of hours
Task::countdownTime(){
    float intCountdown;
    currentTime = time(NULL);
    remainingTime = deadlineTime - currentTime;
    // in terms of hours
    intCountdown = remainingTime/3600.0;
    strCountdown = to_string(intCountdown);
}

Task::updateUserPoints(){
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

//upon clicking the box to checkoff task, this will update task status to complete and give user points
Task::taskStatus(click event){
  complete = true;
  updateUserPoints();
}
//converts 2 user inputted strings into a time_t structure
Task::user_totime(string date, string time){
    char* year, *month, *day, *hour, *min;
    const char * dt = date.c_str();
    const char * tm = time.c_str();
    //cout<<dt<<endl;
    char * temp1 = strdup(dt);
    char * temp2 = strdup(tm);
    //cout<<temp<<endl;

    char * date1 = strtok_r(temp1, " ", &temp1);
    year = strtok_r(date1, "-", &date1);
    month = strtok_r(date1, "-", &date1);
    day = strtok_r(date1, "-", &date1);

    hour = strtok_r(temp2, ":", &temp2);
    min = strtok_r(temp2, ":", &temp2);

    time_t rawtime;
    struct tm * timeinfo = localtime( &rawtime );
    timeinfo->tm_year = atoi(year) - 1900;
    timeinfo->tm_mon = atoi(month) -1 ;
    timeinfo->tm_mday = atoi(day);
    timeinfo->tm_hour = atoi(hour)- 1;
    timeinfo->tm_min = atoi(min);

  //use mktime to convert tm to time_t variable

    time_t converted;
    converted = mktime (timeinfo);
    return converted;
}

Task::renameTask(){
  scin >> taskName;
}

Task::newdeadLine(){
  scin >> userdeadlinedate; // user inputs a string in a certain format; example: Year-Month-Day -> 2021-4-18
  scin >> userdeadlinetime; // user inputs the string in a certain format; example: Hour:Minute -> 12:45
    
  deadlineTime = user_totime(userdeadlinedate, userdeadlinetime);
}

Task::bonus_points(time_t timeleft){
  int bonus;
  double calculate;
  if (timeleft <= 0){
    bonus = 0;
  } else {
    calculate = timeleft/3600; // to get in terms of hours
    cout << calculate << "\n";
    for (int i = 0; i < calculate; i++){
      bonus = i * 5; //5 points per hour before assigned deadline, if less then an hour no baonus points
    }
  }

  return bonus;

}