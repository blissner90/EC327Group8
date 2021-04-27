#ifndef UIOTHERCONTROL_H
#define UIOTHERCONTROL_H

// loads added task to planner and place it accordingly based on deadline
int loadAddTask(Profile& userInformation, vector<vector<Task>>& allTaskData);

// loads set up screen if first time user
int loadFirstTimeUser();

// loads FAQ screen
int loadFAQ(Profile& userInformation);

 // loads easter-egg screen
 void loadGodMode();

#endif