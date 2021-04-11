#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Task{
    
    public:
        string taskName;
        time_t currentTime;
        time_t deadlineTime;
        time_t remainingTime;
        int expectedLength;
        int pointsAwarded;
        bool complete = false;

    private:

};