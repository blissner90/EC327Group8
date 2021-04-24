#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


//creates one task class that can be called again and again to update a tasks.txt file which stores task data

class Task{
    
    public:
        string taskName;
        string dueDate;
        bool complete = false;
        bool pointsgiven = false; //check if the points have already been given
        int pointsAwarded;
        string description;   //contains full desrcription of task
    //Methods
        Task();
        void taskStatus();
        void renameTask();
        void newDate();
        void setTask();
        void recordTask();
        void describeTask();

    private:

};


//basic constructor of task class
Task::Task(){
  pointsAwarded = 50; // base amount of points awarded
 
}

//set the due date of the week for the task, the user must input a day of the week otherwise it will keep asking for a valid input
void Task::setTask(){
  cin >> dueDate;
  while(true){
    if ( (dueDate == "Monday") || (dueDate == "Tuesday") || (dueDate == "Wednesday") || (dueDate == "Thursday") || (dueDate == "Friday") || (dueDate == "Saturday") || (dueDate == "Sunday") ){
      break;
    }
    cin >> dueDate;
  } 
    
}


//changes complete to true ( from 0 to a 1 in tasks.txt file)
void Task::taskStatus(){
  complete = true;
}

void Task::renameTask(){
  cin >> taskName;
  if (taskName.size() > 5){
    cin >> taskName;
  }
}

// change the data of a task, only works if you haven't already updated the tasks.txt textfile using recordTask function
void Task::newDate(){
  cin >> dueDate;
  while(true){
    if ( (dueDate == "Monday") || (dueDate == "Tuesday") || (dueDate == "Wednesday") || (dueDate == "Thursday") || (dueDate == "Friday") || (dueDate == "Saturday") || (dueDate == "Sunday") ){
      break;
    }
    cin >> dueDate;
  }
    

}

void Task::describeTask(){
  cin >> description;
}


//stores the task data in a textfile called tasks.txt, be sure to initialize a empty tasks.txt file if you don't have one already
void Task::recordTask(){
  ifstream taskRecords;
  string taskline;
  vector< string > taskinfo;
  taskRecords.open("tasks.txt");
  while (getline(taskRecords, taskline))
    taskinfo.push_back(taskline);
  taskRecords.close();

  ofstream newfile("tasks.txt");
  for (auto s : taskinfo) {
    newfile << s << "\n";
  }
  //order of the info given seperated by a double space
  newfile << dueDate << "  " << taskName << "  " << complete << "  " << pointsgiven << "  " << pointsAwarded << "\n";
  newfile << description << "\n";
  newfile.close();

}



//testing the  task class for functionality
//only uncommnent if you want to test the baretasks.h file alone
/*
int main(){
  Task testTask;
  testTask.renameTask();
  cout << "name set" <<"\n";
  testTask.describeTask();
  cout << "desribed" << "\n";
  testTask.setTask();
  cout << "date set" << "\n";
  testTask.recordTask();

  testTask.renameTask();
  cout << "name set" <<"\n";
  testTask.describeTask();
  testTask.setTask();
  cout << "date set" << "\n";
  testTask.taskStatus();
  testTask.recordTask();

  return 0;
}
*/
