// Copyright 2021 Matthew Collins matcoll@bu.edu
// Copyright 2021 Benjamin Lissner blissner@bu.edu
// Copyright 2021 Tiffany Lukmantara tiffaluk@bu.edu
// Copyright 2021 Juan Luis Ugarte jugarte@bu.edu

// Tasks class to store task information within the OnTrack application

#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
#include <chrono>
#include <cstring>
#include <stdio.h>

using std::string;

class Task{
    
    public:
        string taskName;
        string description;
        int dueDate;
        int dueTime;
        int AmPm;
        int dueInSec;
        bool complete;
        int pointsgiven;
    
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