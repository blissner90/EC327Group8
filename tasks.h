#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
using namespace std;

// test
// function to convert user inputted time to time_t structure

// all inputs will be strings     scin == strings

// testing getting time value from user
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
    struct tm * timeinfo;
    /* get current timeinfo and modify it to the user's choice */
    time(&rawtime);
    timeinfo = localtime ( &rawtime );
    timeinfo->tm_year = atoi(year -1900);
    timeinfo->tm_mon = atoi(month - 1);
    timeinfo->tm_mday = atoi(day);
    timeinfo->tm_hour = atoi(hour);
    timeinfo->tm_min = atoi(min);

  /* call mktime: timeinfo->tm_wday will be set */

    time_t converted;
    converted = mktime (timeinfo);
    return converted;
}

//





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
  scin >> taskName; // give the name of the task

  scin >> expectedLength;  // how long you expect it to take in minutes
  expectedLength = stoi(expectedLength); // turn string into integer
      
  scin >> userdeadline;  // user inputs a string in a certain format; ex: 12:45:07

  deadlineTime = user_totime(userdeadline);  //string to time_t variable


  remainingTime = deadlineTime - currentTime; // once user clicks the checkbox the remaining time should be calculated


  expectedLength = expectedLength * 60; //user gives time in minutes conversion to seconds
  pointsAwarded = 100; // base amount of points awarded



}
