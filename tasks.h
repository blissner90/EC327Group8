#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
#include <chrono>
#include <cstring>
#include <stdio.h>
// //will need to include the Profile class and button class?

using std::string;

// using namespace std;

// // all inputs will be strings     scin == strings

class Task{
    
    public:
        string taskName;
        string description;
        int dueDate;
        int dueTime;
        int AmPm;
        int dueInSec;
        bool complete;
        int pointsgiven; //check if the points have already been given

    //Methods
        Task();
        void countdownTime();
        void updateUserPoints();
        // void taskStatus(click event);
        time_t user_totime(string date, string time);
        void renameTask();
        void newdeadLine();
        void setTask();

    private:
        int pointsAwarded;
        int totalPointsAwarded;

    //Methods
        int bonus_points(time_t timeleft);


//basic constructor of task class
public:
    
Task(string inTaskName, string inDescription, int inDueDate, int inDueTime, int inAmPm){
  this->taskName = inTaskName; // give the name of the task
  this->description = inDescription;
  this->dueDate = inDueDate;
  this->dueTime = inDueTime;
  this->AmPm = inAmPm;
  this->dueInSec = (dueDate * 86400) + (3600 * (dueTime + (12 * AmPm)));
  this->complete = false;
  this->pointsgiven = 0;

    }

Task(string inTaskName, string inDescription, int inDueDate, int inDueTime, int inAmPm, bool inComplete, int inPointsGiven){
  this->taskName = inTaskName; // give the name of the task
  this->description = inDescription;
  this->dueDate = inDueDate;
  this->dueTime = inDueTime;
  this->AmPm = inAmPm;
  this->dueInSec = (dueDate * 86400) + (3600 * (dueTime + (12 * AmPm)));
  this->complete = inComplete;
  this->pointsgiven = inPointsGiven;
    }
};

// //name the class and give the deadlines
// void Task::setTask(){
//   cin >> userdeadlinedate;   // Year-Month-Day -> 2021-4-18
//   cin >> userdeadlinetime;    // Hour:Minute -> 12:45

//   deadlineTime = user_totime(userdeadlinedate, userdeadlinetime);  //string to time_t variable

// }


// //get how much time is left until the task deadline in terms of hours
// void Task::countdownTime(){
//     float intCountdown;
//     currentTime = time(NULL);
//     remainingTime = deadlineTime - currentTime;
//     // in terms of hours
//     intCountdown = remainingTime/3600.0;
//     strCountdown = to_string(intCountdown);
// }

// //call the User class to update user points
// void Task::updateUserPoints(){
//     currentTime = time(NULL);
//     remainingTime = deadlineTime - currentTime; 
//     if(complete == true  && pointsgiven == false){
//       totalPointsAwarded = pointsAwarded + bonuspoints(remainingTime);
//       //Add points to user Profile class, use userprofile points as nameholder for now
//       userprofilePoints = userprofilePoints + totalPointsAwarded;
//     }
//     //sets points given as true, so this task will no longer give more points even if clicked and unclicked again
//     pointsgiven = true;
// }

// //upon clicking the box to checkoff task, this will update task status to complete and give user points
// void Task::taskStatus(){
//   complete = true;
//   updateUserPoints();
// }
// //converts 2 user inputted strings into a time_t structure
// time_t Task::user_totime(string date, string time){
//     char* year, *month, *day, *hour, *min;
//     const char * dt = date.c_str();
//     const char * tm = time.c_str();
//     //cout<<dt<<endl;
//     char * temp1 = strdup(dt);
//     char * temp2 = strdup(tm);
//     //cout<<temp<<endl;

//     char * date1 = strtok_r(temp1, " ", &temp1);
//     year = strtok_r(date1, "-", &date1);
//     month = strtok_r(date1, "-", &date1);
//     day = strtok_r(date1, "-", &date1);

//     hour = strtok_r(temp2, ":", &temp2);
//     min = strtok_r(temp2, ":", &temp2);

//     time_t rawtime;
//     struct tm * timeinfo = localtime( &rawtime );
//     timeinfo->tm_year = atoi(year) - 1900;
//     timeinfo->tm_mon = atoi(month) -1 ;
//     timeinfo->tm_mday = atoi(day);
//     timeinfo->tm_hour = atoi(hour)- 1;
//     timeinfo->tm_min = atoi(min);

//   //use mktime to convert tm to time_t variable

//     time_t converted;
//     converted = mktime (timeinfo);
//     return converted;
// }

// void Task::renameTask(){
//   cin >> taskName;
// }

// void Task::newdeadLine(){
//   cin >> userdeadlinedate; // user inputs a string in a certain format; example: Year-Month-Day -> 2021-4-18
//   cin >> userdeadlinetime; // user inputs the string in a certain format; example: Hour:Minute -> 12:45
    
//   deadlineTime = user_totime(userdeadlinedate, userdeadlinetime);
// }

// int Task::bonus_points(time_t timeleft){
//   int bonus;
//   double calculate;
//   if (timeleft <= 0){
//     bonus = 0;
//   } else {
//     calculate = timeleft/3600; // to get in terms of hours
//     cout << calculate << "\n";
//     for (int i = 0; i < calculate; i++){
//       bonus = i * 5; //5 points per hour before assigned deadline, if less then an hour no baonus points
//     }
//   }

//   return bonus;

// }