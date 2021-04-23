#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
#include <chrono>
#include <cstring>
#include <stdio.h>
//will need to include the Profile class and button class?

using namespace std;

class Task{
    
    public:
        string taskName;
        string userdeadlinedate;
        string userdeadlinetime;
        bool complete = false;
        bool pointsgiven = false; //check if the points have already been given
        int pointsAwarded;
        int totalPointsAwarded;
    //Methods
        Task();
        void taskStatus();
        void renameTask();
        void newdeadLine();
        void setTask();

    private:

};


//basic constructor of task class
Task::Task(){
  pointsAwarded = 50; // base amount of points awarded
 
}

//name the class and give the deadlines
void Task::setTask(){
  cin >> userdeadlinedate;   // Year-Month-Day -> 2021-4-18
  if(userdeadlinedate.size() > 10){
    cin >> userdeadlinedate;
    }
  cin >> userdeadlinetime;    // Hour:Minute -> 12:45
    if(userdeadlinetime.size() > 5){
    cin >> userdeadlinetime;
    }

  deadlineTime = user_totime(userdeadlinedate, userdeadlinetime);  //string to time_t variable

}

//call the User class to update user points
void Task::updateUserPoints(){
    if(complete == true  && pointsgiven == false){
      totalPointsAwarded = pointsAwarded;
      //Add points to user Profile class, use userprofile points as nameholder for now
      userprofilePoints = userprofilePoints + totalPointsAwarded;
    }
    //sets points given as true, so this task will no longer give more points even if clicked and unclicked again
    pointsgiven = true;
}

//upon clicking the box to checkoff task, this will update task status to complete and give user points
void Task::taskStatus(){
  complete = true;
  updateUserPoints();
}

void Task::renameTask(){
  cin >> taskName;
}

void Task::newdeadLine(){
  cin >> userdeadlinedate; // user inputs a string in a certain format; example: Year-Month-Day -> 2021-4-18
  cin >> userdeadlinetime; // user inputs the string in a certain format; example: Hour:Minute -> 12:45
    
  deadlineTime = user_totime(userdeadlinedate, userdeadlinetime);
}

