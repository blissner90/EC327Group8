#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
using namespace std;

// test
// function to convert user inputted time to time_t structure
time_t user_totime(string date, string time){
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

  // mktime till convert tm to time_t variable

    time_t converted;
    converted = mktime (timeinfo);
    return converted;
}

// all inputs will be strings     scin == strings

class Task{
    
    public:
        string taskName;
        string userdeadlinedate;
        string userdeadlinetime;
        string strexpectedLength;
        time_t currentTime;
        time_t deadlineTime;
        time_t remainingTime;
        int expectedLength;
        bool complete = false;
        bool pointsgiven = false; //check if the points have already been given

    private:
        int pointsAwarded; // user shouldn't be able to determine thier own point gain

};

Task::Task(){
  scin >> taskName; // give the name of the task

  scin >> strexpectedLength;  // string for how long you expect it to take in minutes
  expectedLength = stoi(expectedLength); // turn string into integer value that can be used
  expectedLength = expectedLength * 60; //user gives time in minutes, task converts to seconds for use in time_t structures
      
  scin >> userdeadlinedate; // user inputs a string in a certain format; example: Year-Month-Day -> 2021-4-18
  scin >> userdeadlinetime; // user inputs the string in a certain format; example: Hour:Minute -> 12:45
    
  deadlineTime = user_totime(userdeadlinedate, userdeadlinetime);  //string to time_t variable


  remainingTime = deadlineTime - currentTime; // once user clicks the checkbox the remaining time should be calculated

  pointsAwarded = 100; // base amount of points awarded



}
