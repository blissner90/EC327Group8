#include"Profile.h"

    Profile::Profile(string proName, int proPointsEarned, int proLevel, 
    			int proProgress, int proTheme, int proAvatarColor, int proAvatarShape){
      this->name = proName;
      this->pointsEarned = proPointsEarned;
      this->level = proLevel;
      this->progress = proProgress;
      this->theme = proTheme;
      this->avatarColor = proAvatarColor;
      this->avatarShape = proAvatarShape;
    }

    void Profile::updatePoints(int increase){
      this->pointsEarned = this->pointsEarned + increase;
      this->level = this->pointsEarned / 100;
      this->progress = this->pointsEarned % 100;
      if (this->pointsEarned > 100000){
        this->level = 99;
        this->progress = 100;
      }
    }
