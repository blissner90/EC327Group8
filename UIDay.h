#ifndef UIDAY_H
#define UIDAY_H

// creation of default individual day planner
int loadDefaultDayPlanner(Profile& userInformation, 
		vector<vector<Task>>& taskInformation, string day);

// creation of post-it themed individual day planner
int loadPostItDayPlanner(Profile& userInformation, 
		vector<vector<Task>>& taskInformation, string day);

// creation of dark themed individual day planner
int loadDarkDayPlanner(Profile& userInformation, 
		vector<vector<Task>>& taskInformation, string day);

#endif