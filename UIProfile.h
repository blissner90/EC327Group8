#ifndef UIPROFILE_H
#define UIPROFILE_H

// creation of default profile/settings page
int loadDefaultProfile(Profile& userInformation, vector<vector<Task>>& taskInformation);

// creation of post-it themed profile/settings page
int loadPostItProfile(Profile& userInformation, vector<vector<Task>>& taskInformation);

// creation of dark themed profile/settings page
int loadDarkProfile(Profile& userInformation, vector<vector<Task>>& taskInformation)


#endif