#ifndef UIMAIN_H
#define UIMAIN_H

// creation of default main planner page
int loadDefaultMainPlanner(Profile& userInformation, vector<vector<Task>>& taskInformation);

// creation of post-it themed main planner page
int loadPostItMainPlanner(Profile& userInformation, vector<vector<Task>>& taskInformation);

// creation of dark themed main planner page
int loadDarkMainPlanner(Profile& userInformation, vector<vector<Task>>& taskInformation);

#endif