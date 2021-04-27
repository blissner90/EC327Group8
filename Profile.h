#ifndef PROFILE_H
#define PROFILE_H

class Profile {
  public:
    string name;
    int pointsEarned;
    int level;
    int progress;
    int theme;
    int avatarColor;
    int avatarShape;

    Profile(string proName, int proPointsEarned, int proLevel, 
            int proProgress, int proTheme, int proAvatarColor, int proAvatarShape)

    void updatePoints(int increase);
    
};

#endif