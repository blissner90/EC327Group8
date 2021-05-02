// Copyright 2021 Matthew Collins matcoll@bu.edu
// Copyright 2021 Benjamin Lissner blissner@bu.edu
// Copyright 2021 Tiffany Lukmantara tiffaluk@bu.edu
// Copyright 2021 Juan Luis Ugarte jugarte@bu.edu

// Profile class to store user information for the OnTrack application

#include <string>

using std::string;

class Profile {
  public:
    // class attributes including the user's name as a string and ints which store the information for the user's
    // current points, current level, current level progress, their current selected theme, avatar color and 
    // avatar shape
    string name;
    int pointsEarned;
    int level;
    int progress;
    int theme;
    int avatarColor;
    int avatarShape;

    // Constructor for the profile class, initializing all class attributes
    Profile(string proName, int proPointsEarned, int proLevel, int proProgress, int proTheme, int proAvatarColor, int proAvatarShape){
      this->name = proName;
      this->pointsEarned = proPointsEarned;
      this->level = proLevel;
      this->progress = proProgress;
      this->theme = proTheme;
      this->avatarColor = proAvatarColor;
      this->avatarShape = proAvatarShape;
    }

    // updatePoints() takes an integer representing the amount of points earned by completion of a task and updates the profile class
    // attributes to reflect the earned points
    void updatePoints(int increase){
      this->pointsEarned = this->pointsEarned + increase;
      this->level = this->pointsEarned / 100;
      this->progress = this->pointsEarned % 100;
      if (this->pointsEarned >= 10000){  // set max level as 99
        this->level = 99;
        this->progress = 100;
      }
    }
};