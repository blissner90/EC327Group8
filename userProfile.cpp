#include <iostream>
#include <string>
#include <vector>
using namespace std;


//might need an Icon class with point cost and 

class userProfile {
    public:
      string userName;
      int userPoints; //how many points the user currently has
      int totalPointsGained; // how many points the user has accrued overall 
      int userLevel; //what the level of the user is
      vector<icons?> userIcons; //the available icons for the user to use
      icon personalIcon; // the icon the user is currently using

      userProfile();
      void spendPoints(int usedpoints);
      void determineLevel();
      void changeIcon();

    private:

};

// use scin to represent inputted data

userProfile::userProfile(){
  scin >> userName
  userLevel = 0;
  userPoints = 0;
  totalPointsGained = 0;
  personalIcon = "circle";  // calling the default icon as circle 
}

userProfile::spendPoints(int usedpoints ){
  userPoints = userPoints - usedpoints;
};


// max rank of 3 for now
userProfile::determineLevel(){
  if(totalPointsGained < 1000){
    userLevel = 0;

  }else if(totalPointsGained < 2000){
    userLevel = 1;

  }else if(totalPointsGained < 3000){
    userLevel = 2;

  }else{
    userLevel = 3;

  }
};


// icons will be in vector where lowest level is 0 and is first and 3 is highest level and furthest right
userProfile::changeIcon(int iconNumber){
  personalIcon = userIcons.at(iconNumber);

};