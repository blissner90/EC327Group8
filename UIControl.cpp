#include <iostream>
#include<functional>
#include <vector>
#include <ctime>
#include <time.h>
#include <cstring>
#include <string>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "tasks.h"
#include "textbox.h"

using std::cout;
using std::stoi;
using std::string;
using std::to_string;
using sf::RenderWindow;
using sf::RectangleShape;
using sf::CircleShape;
using sf::Color;
using std::strtok;
using std::vector;
using std::string;

// global variables used across multiple functions for window size and ALL POSSIBLE AVATAR COLORS
int windowLength = 1600;
int windowWidth = 900;
RenderWindow mainWindow(sf::VideoMode(windowLength, windowWidth),
                          "Final Project, Main Window");

vector<vector<uint8_t>> allPossibleColors = {{255, 0, 0}, {0, 0, 255}, {0, 180, 0}, {255,165,0}, {255,255, 0}, {255, 105, 180}};




// profile class to store the profile data

class Profile {
  public:
    string name;
    int pointsEarned;
    int level;
    int progress;
    int theme;
    int avatarColor;
    int avatarShape;

    Profile(string proName, int proPointsEarned, int proLevel, int proProgress, int proTheme, int proAvatarColor, int proAvatarShape){
      this->name = proName;
      this->pointsEarned = proPointsEarned;
      this->level = proLevel;
      this->progress = proProgress;
      this->theme = proTheme;
      this->avatarColor = proAvatarColor;
      this->avatarShape = proAvatarShape;
    }

    void updatePoints(int increase){
      this->pointsEarned = this->pointsEarned + increase;
      this->level = this->pointsEarned / 100;
      this->progress = this->pointsEarned % 100;
      if (this->pointsEarned > 100000){
        this->level = 99;
        this->progress = 100;
      }
    }
};

int getCurrTimeSec(){

  vector<string> daysOfWeekVec{"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  time_t epochtime = time(NULL);
    std::tm etime = *localtime(&epochtime);
    string currentDayStr = (ctime(&epochtime));
    currentDayStr = currentDayStr.substr(0,3);
    int currentDay;

    for (int i = 0; i < daysOfWeekVec.size(); i++){
        if (currentDayStr.compare(daysOfWeekVec.at(i)) == 0) currentDay = i;
      }

    string currentHourStr = ctime(&epochtime);
    int currentHour = stoi(currentHourStr.substr(11,2));
    string currentMinStr = ctime(&epochtime);
    int currentMin = stoi(currentMinStr.substr(14,2));
    int currentTime = (currentDay * 86400) + (currentHour * 3600) + (currentMin * 60);
    return currentTime;
}
// creation of default profile/settings page
int loadDefaultProfile(Profile& userInformation, vector<vector<Task>>& taskInformation){

  RectangleShape basicOutline(sf::Vector2f(windowLength, windowWidth));

  RectangleShape possibleColors(sf::Vector2f(30, 30));

  RectangleShape timeOutline(sf::Vector2f(245, 75));
  timeOutline.setOutlineColor(Color::Black);
  timeOutline.setOutlineThickness(5);
  timeOutline.setPosition(1300,800);


  RectangleShape progressBarOutline(sf::Vector2f(550, 30));
  progressBarOutline.setOutlineColor(Color::Black);
  progressBarOutline.setOutlineThickness(5);
  progressBarOutline.setPosition(1000, 405);

  RectangleShape progressBar(sf::Vector2f((userInformation.progress/100.0 * 550), 30));
  progressBar.setFillColor(Color::Blue);
  progressBar.setPosition(1000, 405);

  CircleShape backButton(20, 3);
  backButton.setPosition(50, 60);
  backButton.rotate(270);

  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  sf::Text progressText;
  progressText.setFont(font);
  progressText.setFillColor(Color::Blue);
  progressText.setString(to_string(userInformation.progress) + " / 100");
  progressText.setCharacterSize(15);
  progressText.setPosition(1250, 445);


  sf::Text digitalClock;
  digitalClock.setFont(font);
  digitalClock.setPosition(1300, 800);
  digitalClock.setFillColor(Color::Black);
  digitalClock.setCharacterSize(60);

  sf::Text profileHeader;
  profileHeader.setFont(font);
  profileHeader.setPosition(450, 22);
  profileHeader.setFillColor(Color::Black);
  profileHeader.setString("Profile Information:");
  profileHeader.setCharacterSize(65);

  sf::Text profileSpecifics;
  string profileInfo = "Name: " + userInformation.name + "\n\nPoints Earned: "  + to_string(userInformation.pointsEarned) + "\n\nProfile Level: " + to_string(userInformation.level) + "\n\nProgress to Next Level:";
  profileSpecifics.setFont(font);
  profileSpecifics.setPosition(500, 115);
  profileSpecifics.setFillColor(Color::Black);
  profileSpecifics.setString(profileInfo);
  profileSpecifics.setCharacterSize(40);

  sf::Text settingsHeader;
  settingsHeader.setFont(font);
  settingsHeader.setPosition(50, 450);
  settingsHeader.setFillColor(Color::Black);
  settingsHeader.setString("Settings and Information:");
  settingsHeader.setCharacterSize(65);

  sf::Text FAQ;
  FAQ.setFont(font);
  FAQ.setPosition(100, 550);
  FAQ.setString("Go to FAQ");
  FAQ.setCharacterSize(40);

  sf::Text changeTheme;
  changeTheme.setFont(font);
  changeTheme.setPosition(100, 625);
  changeTheme.setString("Select Theme:\n\nSelect Avatar Shape:\n\nSelect Avatar Color:");
  changeTheme.setCharacterSize(40);
  changeTheme.setFillColor(Color::Black);

  sf::Text defaultLabel;
  defaultLabel.setFont(font);
  defaultLabel.setPosition(425, 625);
  defaultLabel.setString("Default");
  defaultLabel.setCharacterSize(40);
  defaultLabel.setFillColor(Color::Black);

  sf::Text postItLabel;
  postItLabel.setFont(font);
  postItLabel.setPosition(671, 625);
  postItLabel.setString("Post-It");
  postItLabel.setCharacterSize(40);

  sf::Text currentLabel;
  currentLabel.setFont(font);
  currentLabel.setPosition(470, 675);
  currentLabel.setString("(current)");
  currentLabel.setCharacterSize(15);
  currentLabel.setFillColor(Color::Black);

  sf::Text unlocksAt5;
  unlocksAt5.setFont(font);
  unlocksAt5.setPosition(667, 675);
  unlocksAt5.setString("(unlocks at level 5)");
  unlocksAt5.setCharacterSize(15);
  unlocksAt5.setFillColor(Color::Black);

  sf::Text darkLabel;
  darkLabel.setFont(font);
  darkLabel.setPosition(900, 625);
  darkLabel.setString("Dark");
  darkLabel.setCharacterSize(40);

  sf::Text unlocksAt10;
  unlocksAt10.setFont(font);
  unlocksAt10.setPosition(876, 675);
  unlocksAt10.setString("(unlocks at level 10)");
  unlocksAt10.setCharacterSize(15);
  unlocksAt10.setFillColor(Color::Black);

  sf::Text moreCustom;
  moreCustom.setFont(font);
  moreCustom.setCharacterSize(15);
  moreCustom.setString("More customizable shapes and colors unlock at level 15!");
  moreCustom.setFillColor(Color::Black);
  moreCustom.setPosition(800, 777);

  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed){

        mainWindow.close();
        return -1;
      }
    }

    std::time_t stdTime = std::time(NULL);  // get new time
    std::tm stdNow = *std::localtime(&stdTime);

    mainWindow.clear();
    mainWindow.draw(basicOutline);

    // format digital time on clock
    string digitalTime = std::asctime(&stdNow);
    digitalTime = digitalTime.substr(11, 8);
    digitalClock.setString(digitalTime);

    backButton.setFillColor(Color::Black);

    if (backButton.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
      backButton.setFillColor(Color::Green);
      if (event.type == sf::Event::MouseButtonPressed) return 0;
    }

    FAQ.setFillColor(Color::Black);
    if (FAQ.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
      FAQ.setFillColor(Color::Green);
      if (event.type == sf::Event::MouseButtonPressed) return 1000;
    }

    postItLabel.setFillColor(Color::Black);
    if (userInformation.level >= 5){
      if (postItLabel.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        postItLabel.setFillColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) {
          userInformation.theme = 1;
          return 3;
        }
      }
    }
    else {
      postItLabel.setFillColor(Color::Red);
      mainWindow.draw(unlocksAt5);
    }

    darkLabel.setFillColor(Color::Black);
    if (userInformation.level >= 10){
      if (darkLabel.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        darkLabel.setFillColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) {
          userInformation.theme = 2;
          return 5;
        }
      }
    }
    else {
      darkLabel.setFillColor(Color::Red);
      mainWindow.draw(unlocksAt10);
    }

    RectangleShape basicAvatar(sf::Vector2f(300, 300));
    basicAvatar.setOutlineColor(Color::Black);
    basicAvatar.setOutlineThickness(8);
    basicAvatar.setPosition(50, 100);
    basicAvatar.setFillColor(Color{allPossibleColors.at(userInformation.avatarColor).at(0), allPossibleColors.at(userInformation.avatarColor).at(1), allPossibleColors.at(userInformation.avatarColor).at(2)});

    CircleShape avatarExample(100, userInformation.avatarShape);
    avatarExample.setPosition(100, 150);
    avatarExample.setFillColor(Color::Black);

    for (int i = 0; i < 6; i++){
      int j = i + 3;
      CircleShape possibleShapes(30, j);
      possibleShapes.setPosition(505 + i*100, 810);
      possibleColors.setPosition(520 + i*100, 728);

      possibleColors.setFillColor(Color{allPossibleColors.at(i).at(0), allPossibleColors.at(i).at(1), allPossibleColors.at(i).at(2)});
      possibleShapes.setFillColor(Color::Black);

      if ((userInformation.level < 15) && (i < 3)){
        mainWindow.draw(possibleColors);
        mainWindow.draw(possibleShapes);
        mainWindow.draw(moreCustom);

      if (possibleColors.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        if (event.type == sf::Event::MouseButtonPressed) userInformation.avatarColor = i;
      }
      if (possibleShapes.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        if (event.type == sf::Event::MouseButtonPressed) userInformation.avatarShape = j;
        }
      }
      else if (userInformation.level >= 15){
        mainWindow.draw(possibleColors);
        mainWindow.draw(possibleShapes);

      if (possibleColors.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        if (event.type == sf::Event::MouseButtonPressed) userInformation.avatarColor = i;
      }
      if (possibleShapes.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        if (event.type == sf::Event::MouseButtonPressed) userInformation.avatarShape = j;
        }
      }
    }

    // draw clock componentse
    mainWindow.draw(backButton);
    mainWindow.draw(basicAvatar);
    mainWindow.draw(avatarExample);
    mainWindow.draw(timeOutline);
    mainWindow.draw(digitalClock);
    mainWindow.draw(profileHeader);
    mainWindow.draw(profileSpecifics);
    mainWindow.draw(settingsHeader);
    mainWindow.draw(progressBarOutline);
    mainWindow.draw(progressBar);
    mainWindow.draw(progressText);
    mainWindow.draw(FAQ);
    mainWindow.draw(changeTheme);
    mainWindow.draw(defaultLabel);
    mainWindow.draw(postItLabel);
    mainWindow.draw(darkLabel);
    mainWindow.draw(currentLabel);
    mainWindow.display();
  }
  return 0;
}

// creation of default main planner page
int loadDefaultMainPlanner(Profile& userInformation, vector<vector<Task>>& taskInformation) {

  RectangleShape basicOutline(sf::Vector2f(windowLength, windowWidth));

  RectangleShape timeOutline(sf::Vector2f(245, 75));
  timeOutline.setOutlineColor(Color::Black);
  timeOutline.setOutlineThickness(5);
  timeOutline.setPosition(1200,100);

  RectangleShape basicAvatar(sf::Vector2f(75,75));
  basicAvatar.setFillColor(Color{allPossibleColors.at(userInformation.avatarColor).at(0), allPossibleColors.at(userInformation.avatarColor).at(1), allPossibleColors.at(userInformation.avatarColor).at(2)});
  basicAvatar.setOutlineThickness(5);
  basicAvatar.setPosition(1500, 100);

  CircleShape avatarExample(25, userInformation.avatarShape);
  avatarExample.setPosition(1513, 113);
  avatarExample.setFillColor(Color::Black);

  RectangleShape mainBox(sf::Vector2f(1400, 600));
  mainBox.setOutlineColor(Color::Blue);
  mainBox.setOutlineThickness(8);
  mainBox.setPosition(100, 200);

  RectangleShape horizontalLine(sf::Vector2f(1400, 8));
  horizontalLine.setFillColor(Color::Blue);
  horizontalLine.setPosition(100, 300);

  RectangleShape verticalLine(sf::Vector2f(8, 600));
  verticalLine.setFillColor(Color::Blue);
  int vertXStart = 300;

  CircleShape tempButtonDays(8);
  tempButtonDays.setFillColor(Color::Blue);

  RectangleShape progressBarOutline(sf::Vector2f(500, 30));
  progressBarOutline.setOutlineColor(Color::Black);
  progressBarOutline.setOutlineThickness(5);
  progressBarOutline.setPosition(550, 850);

  RectangleShape progressBar(sf::Vector2f((userInformation.progress/100.0 * 500), 30));
  progressBar.setFillColor(Color::Blue);
  progressBar.setPosition(550, 850);

  // format and scale digital representaion of time
  sf::Text digitalClock;
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  digitalClock.setFont(font);
  digitalClock.setPosition(1200, 100);
  digitalClock.setFillColor(Color::Black);
  digitalClock.setCharacterSize(60);


  sf::Text headerUser;
  headerUser.setFont(font);
  headerUser.setPosition(100, 105);
  headerUser.setFillColor(Color::Black);
  headerUser.setCharacterSize(47);
  string identifier = userInformation.name + "'s Week";
  headerUser.setString(identifier);

  sf::Text daysOfWeek;
  daysOfWeek.setFont(font);
  daysOfWeek.setPosition(150, 210);
  daysOfWeek.setFillColor(Color::Blue);
  daysOfWeek.setCharacterSize(60);
  string days = "Sun      Mon      Tues     Wed    Thurs      Fri        Sat";
  daysOfWeek.setString(days);

  sf::Text addTask;
  addTask.setFont(font);
  addTask.setPosition(1300, 825);
  addTask.setCharacterSize(50);
  string addTaskStr = "* Add Task";
  addTask.setString(addTaskStr);

  sf::Text taskMain;
  taskMain.setFont(font);
  taskMain.setCharacterSize(25);

  sf::Text taskTime;
  taskTime.setFont(font);
  taskTime.setCharacterSize(15);

  sf::Text progressText;
  progressText.setFont(font);
  progressText.setFillColor(Color::Blue);
  progressText.setString(to_string(userInformation.progress) + " / 100");
  progressText.setCharacterSize(15);
  progressText.setPosition(770, 825);

  sf::Text levelText;
  levelText.setFont(font);
  levelText.setFillColor(Color::Black);
  levelText.setString(to_string(userInformation.level));
  levelText.setCharacterSize(40);
  levelText.setPosition(480,839);

  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed){

        mainWindow.close();
        return -1;
      }
    }

    std::time_t stdTime = std::time(NULL);  // get new time
    std::tm stdNow = *std::localtime(&stdTime);

    mainWindow.clear();

    // format digital time on clock
    string digitalTime = std::asctime(&stdNow);
    digitalTime = digitalTime.substr(11, 8);
    digitalClock.setString(digitalTime);
    mainWindow.draw(basicOutline);
    mainWindow.draw(mainBox);
    mainWindow.draw(horizontalLine);
    mainWindow.draw(progressBarOutline);
    mainWindow.draw(progressBar);
    mainWindow.draw(progressText);
    mainWindow.draw(levelText);

    addTask.setFillColor(Color::Black);

    int dayIndex = 100;

    for (int i = 0; i < 7; i++){
      tempButtonDays.setFillColor(Color::Blue);
      verticalLine.setPosition(vertXStart + i*200, 200);
      tempButtonDays.setPosition(vertXStart -20 + i* 200, 210);
      if (tempButtonDays.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        tempButtonDays.setFillColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) return dayIndex;
      }
      mainWindow.draw(verticalLine);
      mainWindow.draw(tempButtonDays);
      dayIndex += 1;

    }
    basicAvatar.setOutlineColor(Color::Black);

    if (basicAvatar.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        basicAvatar.setOutlineColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) return 1;
    }
    int currentTime = getCurrTimeSec();

      for (int i = 0; i < 7; i++){
        for (int j = 0; j < taskInformation.at(i).size(); j++){
        taskTime.setFillColor(Color::Black);
        taskMain.setFillColor(Color::Black);
        double hourRemaining = (taskInformation.at(i).at(j).dueInSec - currentTime) / 3600.0;

        taskMain.setString("Task: " + taskInformation.at(i).at(j).taskName);
        taskMain.setPosition(110 + i * 200, 320 + j * 130);
        char buffer[50];
        if (hourRemaining < 0) {
          taskMain.setFillColor(Color::Red);
          sprintf(buffer, "Overdue By:\n%.2f hours", -hourRemaining);
        }
        else if (hourRemaining == 0){
          taskMain.setFillColor(Color::Red);
          sprintf(buffer, "Overdue By:\n%.2f hours", hourRemaining);
        }
        else if (hourRemaining <= 2){
          taskMain.setFillColor(Color{255,128,0});
          sprintf(buffer, "Time Remaining:\n%.2f hours", hourRemaining);
        }
        else{
          sprintf(buffer, "Time Remaining:\n%.2f hours", hourRemaining);
        }
        if (taskInformation.at(i).at(j).complete) {
          taskTime.setFillColor(Color::White);
          taskMain.setFillColor(Color::Green);
        }
        taskTime.setString(buffer);
        taskTime.setPosition(118 + i * 200, 360 + j * 130);
        mainWindow.draw(taskTime);
        mainWindow.draw(taskMain);
      }
    }
    mainWindow.draw(timeOutline);
    mainWindow.draw(basicAvatar);
    mainWindow.draw(avatarExample);
    mainWindow.draw(digitalClock);
    mainWindow.draw(headerUser);
    mainWindow.draw(daysOfWeek);

    if (addTask.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        addTask.setFillColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) return 2000;
    }


    mainWindow.draw(addTask);
    mainWindow.display();
  }
  return 0;
}

// creation of default individual day planner
int loadDefaultDayPlanner(Profile& userInformation, vector<vector<Task>>& taskInformation, string day){


  vector<string> daysOfWeek = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  int dayIndex = -1;
  for (int i = 0; i < daysOfWeek.size(); i++){
    if ((daysOfWeek.at(i)).compare(day) == 0) dayIndex = i;
  }

  int lengthSpecific = taskInformation.at(dayIndex).size();

  RectangleShape basicOutline(sf::Vector2f(windowLength, windowWidth));

  RectangleShape timeOutline(sf::Vector2f(245, 75));
  timeOutline.setOutlineColor(Color::Black);
  timeOutline.setOutlineThickness(5);
  timeOutline.setPosition(65,825);

  RectangleShape basicAvatar(sf::Vector2f(75,75));
  basicAvatar.setFillColor(Color{allPossibleColors.at(userInformation.avatarColor).at(0), allPossibleColors.at(userInformation.avatarColor).at(1), allPossibleColors.at(userInformation.avatarColor).at(2)});
  basicAvatar.setOutlineColor(Color::Black);
  basicAvatar.setOutlineThickness(5);
  basicAvatar.setPosition(1400, 113);

  CircleShape avatarExample(25, userInformation.avatarShape);
  avatarExample.setPosition(1413, 126);
  avatarExample.setFillColor(Color::Black);

  RectangleShape mainBox(sf::Vector2f(1400, 700));
  mainBox.setOutlineColor(Color::Blue);
  mainBox.setOutlineThickness(8);
  mainBox.setPosition(100, 100);

  RectangleShape horizontalLine(sf::Vector2f(1400, 8));
  horizontalLine.setFillColor(Color::Blue);
  horizontalLine.setPosition(100, 200);

  RectangleShape checkbox(sf::Vector2f(30,30));
  checkbox.setFillColor(Color::Black);
  RectangleShape checkboxFilled(sf::Vector2f(30,30));
  checkboxFilled.setFillColor(Color::Green);

  CircleShape tempButtonDays(20, 3);
  tempButtonDays.setFillColor(Color::Blue);
  tempButtonDays.setPosition(140, 170);
  tempButtonDays.rotate(270);

  RectangleShape progressBarOutline(sf::Vector2f(500, 30));
  progressBarOutline.setOutlineColor(Color::Black);
  progressBarOutline.setOutlineThickness(5);
  progressBarOutline.setPosition(550, 850);

  RectangleShape progressBar(sf::Vector2f((userInformation.progress/100.0 * 500), 30));
  progressBar.setFillColor(Color::Blue);
  progressBar.setPosition(550, 850);


  // format and scale digital representaion of time
  sf::Text digitalClock;
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  digitalClock.setFont(font);
  digitalClock.setPosition(65, 825);
  digitalClock.setFillColor(Color::Black);
  digitalClock.setCharacterSize(60);


  sf::Text headerUser;
  headerUser.setFont(font);
  headerUser.setPosition(198, 116);
  headerUser.setFillColor(Color::Black);
  headerUser.setCharacterSize(47);
  string identifier = userInformation.name + "'s " + day;
  headerUser.setString(identifier);


  sf::Text addTask;
  addTask.setFont(font);
  addTask.setPosition(1300, 825);
  addTask.setFillColor(Color::Black);
  addTask.setCharacterSize(50);
  string addTaskStr = "* Add Task";
  addTask.setString(addTaskStr);

  sf::Cursor cursor;

  sf::Text taskInfo;
  taskInfo.setFont(font);
  taskInfo.setCharacterSize(40);
  
  sf::Text taskDesc;
  taskDesc.setFont(font);
  taskDesc.setFillColor(Color::Black);
  taskDesc.setCharacterSize(26);

  sf::Text unmark;
  unmark.setFont(font);
  unmark.setFillColor(Color::Black);
  unmark.setCharacterSize(15);
  unmark.setString("Unmark");
  unmark.setStyle(sf::Text::Underlined);

  sf::Text deleteTask;
  deleteTask.setFont(font);
  deleteTask.setFillColor(Color::Red);
  deleteTask.setCharacterSize(40);
  deleteTask.setString("X");
  deleteTask.setStyle(sf::Text::Bold);

  sf::Text confirmation;
  confirmation.setFont(font);
  confirmation.setFillColor(Color::White);
  confirmation.setCharacterSize(0);
  confirmation.setString("   Click here to\nconfirm deletion");

  sf::Text progressText;
  progressText.setFont(font);
  progressText.setFillColor(Color::Blue);
  progressText.setCharacterSize(15);
  progressText.setPosition(770, 825);

  sf::Text levelText;
  levelText.setFont(font);
  levelText.setFillColor(Color::Black);
  levelText.setCharacterSize(40);
  levelText.setPosition(480,839);

  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed){

        mainWindow.close();
        return -1;
      }
    }
    std::time_t stdTime = std::time(NULL);  // get new time
    std::tm stdNow = *std::localtime(&stdTime);

    mainWindow.clear();

    // format digital time on clock
    string digitalTime = std::asctime(&stdNow);
    digitalTime = digitalTime.substr(11, 8);
    digitalClock.setString(digitalTime);
    tempButtonDays.setFillColor(Color::Blue);
    if (tempButtonDays.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
      tempButtonDays.setFillColor(Color::Green);
      if (event.type == sf::Event::MouseButtonPressed) return 0;
    }
    mainWindow.draw(basicOutline);
    mainWindow.draw(mainBox);
    mainWindow.draw(horizontalLine);
    mainWindow.draw(tempButtonDays);
    mainWindow.draw(timeOutline);
    mainWindow.draw(progressBarOutline);
    progressBar.setSize(sf::Vector2f((userInformation.progress/100.0 * 500), 30));
    mainWindow.draw(progressBar);
    progressText.setString(to_string(userInformation.progress) + " / 100");
    mainWindow.draw(progressText);
    levelText.setString(to_string(userInformation.level));
    mainWindow.draw(levelText);

    basicAvatar.setOutlineColor(Color::Black);

    if (basicAvatar.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        basicAvatar.setOutlineColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) return 1;
    }
    mainWindow.draw(basicAvatar);
    mainWindow.draw(avatarExample);
    mainWindow.draw(digitalClock);
    mainWindow.draw(headerUser);

    addTask.setFillColor(Color::Black);
    if (addTask.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        addTask.setFillColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) return 2000;
    }

    
    for (int i = 0; i < taskInformation.at(dayIndex).size(); i++){

        int addedPoints = 0;
        int currDiffernceSec = (taskInformation.at(dayIndex).at(i).dueInSec - getCurrTimeSec());

        if (taskInformation.at(dayIndex).at(i).complete) {
          unmark.setPosition(135, 270 + (i*145));
          mainWindow.draw(unmark);
          checkboxFilled.setPosition(150, 230 + (i*145));
          mainWindow.draw(checkboxFilled);
          if (unmark.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
            if (event.type == sf::Event::MouseButtonPressed) {
              taskInformation.at(dayIndex).at(i).complete = !taskInformation.at(dayIndex).at(i).complete;
              userInformation.updatePoints(-taskInformation.at(dayIndex).at(i).pointsgiven);
              taskInformation.at(dayIndex).at(i).pointsgiven = 0;
            }
          }
        }
        else {
          checkbox.setPosition(150, 230 + (i*145));
          mainWindow.draw(checkbox);
          if (checkbox.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
            if (event.type == sf::Event::MouseButtonPressed) {
              taskInformation.at(dayIndex).at(i).complete = !taskInformation.at(dayIndex).at(i).complete;
              if ((currDiffernceSec/3600) > 12) addedPoints = 25 + (2 * currDiffernceSec/3600);
              else if (currDiffernceSec < 0) addedPoints = 0;
              else addedPoints = 25;
              taskInformation.at(dayIndex).at(i).pointsgiven = addedPoints;
              userInformation.updatePoints(taskInformation.at(dayIndex).at(i).pointsgiven);
            }
          }
        }



        taskInfo.setFillColor(Color::Black);
        taskInfo.setString("Task Subject: " + taskInformation.at(dayIndex).at(i).taskName);
        vector<string> amPMlabel = {"AM","PM"};

        Task cTask = taskInformation.at(dayIndex).at(i);
        taskDesc.setString("\nTask Description: " + taskInformation.at(dayIndex).at(i).description + "\nTask Due Time: " + to_string(taskInformation.at(dayIndex).at(i).dueTime) + " " + amPMlabel.at(taskInformation.at(dayIndex).at(i).AmPm));
        taskInfo.setPosition(200, 220 + (i*145));
        taskDesc.setPosition(315, 240 + (i*145));
        mainWindow.draw(taskInfo);
        mainWindow.draw(taskDesc);

        deleteTask.setPosition(1400, 230 + (i*145));
        mainWindow.draw(deleteTask);

        if (deleteTask.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
            if (event.type == sf::Event::MouseButtonPressed) {
              confirmation.setPosition(1360, 290 + (i*145));
              confirmation.setFillColor(Color::Red);
              confirmation.setCharacterSize(13);
            }
          }
        mainWindow.draw(confirmation);
        if (confirmation.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
            if (event.type == sf::Event::MouseButtonPressed) {
              taskInformation.at(dayIndex).erase(taskInformation.at(dayIndex).begin() + i);
              confirmation.setCharacterSize(0);
              confirmation.setFillColor(Color::White);
              confirmation.setPosition(0,0);
            }
          }
        
       }



    mainWindow.draw(addTask);
    mainWindow.display();
  }
  return 0;
}

int loadPostItProfile(Profile& userInformation, vector<vector<Task>>& taskInformation){

  RectangleShape basicOutline(sf::Vector2f(windowLength, windowWidth));
  basicOutline.setFillColor(Color(255, 255, 186));

  RectangleShape possibleColors(sf::Vector2f(30, 30));

  RectangleShape infoOutline(sf::Vector2f(1135, 438));
  infoOutline.setFillColor(Color{110, 255, 255});
  infoOutline.setPosition(430,25);

  RectangleShape infoTop(sf::Vector2f(1135, 85));
  infoTop.setFillColor(Color{75, 226, 226});
  infoTop.setPosition(430,25);


  RectangleShape settingsOutline(sf::Vector2f(1200, 438));
  settingsOutline.setFillColor(Color{255, 34, 145});
  settingsOutline.setPosition(35,455);

  RectangleShape settingsTop(sf::Vector2f(1200, 80));
  settingsTop.setFillColor(Color{213, 0, 107});
  settingsTop.setPosition(35,455);


  RectangleShape timeOutline(sf::Vector2f(245, 75));
  timeOutline.setFillColor(Color{186, 186, 255});
  timeOutline.setPosition(1300,800);

  RectangleShape progressBarOutline(sf::Vector2f(550, 30));
  progressBarOutline.setOutlineColor(Color::Black);
  progressBarOutline.setOutlineThickness(5);
  progressBarOutline.setPosition(1000, 405);

  RectangleShape progressBar(sf::Vector2f((userInformation.progress/100.0 * 550), 30));
  progressBar.setFillColor(Color::Blue);
  progressBar.setPosition(1000, 405);

  CircleShape backButton(20, 3);
  backButton.setPosition(50, 60);
  backButton.rotate(270);

  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  sf::Text progressText;
  progressText.setFont(font);
  progressText.setFillColor(Color::Blue);
  progressText.setString(to_string(userInformation.progress) + " / 100");
  progressText.setCharacterSize(15);
  progressText.setPosition(1250, 445);


  sf::Text digitalClock;
  digitalClock.setFont(font);
  digitalClock.setPosition(1300, 800);
  digitalClock.setFillColor(Color::Black);
  digitalClock.setCharacterSize(60);

  sf::Text profileHeader;
  profileHeader.setFont(font);
  profileHeader.setPosition(450, 22);
  profileHeader.setFillColor(Color::Black);
  profileHeader.setString("Profile Information:");
  profileHeader.setCharacterSize(65);

  sf::Text profileSpecifics;
  string profileInfo = "Name: " + userInformation.name + "\n\nPoints Earned: "  + to_string(userInformation.pointsEarned) + "\n\nProfile Level: " + to_string(userInformation.level) + "\n\nProgress to Next Level:";
  profileSpecifics.setFont(font);
  profileSpecifics.setPosition(500, 115);
  profileSpecifics.setFillColor(Color::Black);
  profileSpecifics.setString(profileInfo);
  profileSpecifics.setCharacterSize(40);

  sf::Text settingsHeader;
  settingsHeader.setFont(font);
  settingsHeader.setPosition(50, 450);
  settingsHeader.setFillColor(Color::Black);
  settingsHeader.setString("Settings and Information:");
  settingsHeader.setCharacterSize(65);

  sf::Text FAQ;
  FAQ.setFont(font);
  FAQ.setPosition(100, 550);
  FAQ.setString("Go to FAQ");
  FAQ.setCharacterSize(40);

  sf::Text changeTheme;
  changeTheme.setFont(font);
  changeTheme.setPosition(100, 625);
  changeTheme.setString("Select Theme:\n\nSelect Avatar Shape:\n\nSelect Avatar Color:");
  changeTheme.setCharacterSize(40);
  changeTheme.setFillColor(Color::Black);


  sf::Text defaultLabel;
  defaultLabel.setFont(font);
  defaultLabel.setPosition(425, 625);
  defaultLabel.setString("Default");
  defaultLabel.setCharacterSize(40);

  sf::Text postItLabel;
  postItLabel.setFont(font);
  postItLabel.setPosition(671, 625);
  postItLabel.setString("Post-It");
  postItLabel.setCharacterSize(40);
  postItLabel.setFillColor(Color::Black);

  sf::Text currentLabel;
  currentLabel.setFont(font);
  currentLabel.setPosition(705, 675);
  currentLabel.setString("(current)");
  currentLabel.setCharacterSize(15);
  currentLabel.setFillColor(Color::Black);

  sf::Text darkLabel;
  darkLabel.setFont(font);
  darkLabel.setPosition(900, 625);
  darkLabel.setString("Dark");
  darkLabel.setCharacterSize(40);

  sf::Text unlocksAt10;
  unlocksAt10.setFont(font);
  unlocksAt10.setPosition(876, 675);
  unlocksAt10.setString("(unlocks at level 10)");
  unlocksAt10.setCharacterSize(15);
  unlocksAt10.setFillColor(Color::Black);

  sf::Text moreCustom;
  moreCustom.setFont(font);
  moreCustom.setCharacterSize(15);
  moreCustom.setString("More customizable shapes and colors unlock at level 15!");
  moreCustom.setFillColor(Color::Black);
  moreCustom.setPosition(800, 777);


  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed){

        mainWindow.close();
        return -1;
      }
    }

    std::time_t stdTime = std::time(NULL);  // get new time
    std::tm stdNow = *std::localtime(&stdTime);

    mainWindow.clear();
    mainWindow.draw(basicOutline);
    mainWindow.draw(backButton);
    mainWindow.draw(infoOutline);
    mainWindow.draw(infoTop);
    mainWindow.draw(settingsOutline);
    mainWindow.draw(settingsTop);
    mainWindow.draw(timeOutline);
    mainWindow.draw(digitalClock);
    mainWindow.draw(profileHeader);
    mainWindow.draw(profileSpecifics);
    mainWindow.draw(settingsHeader);
    mainWindow.draw(progressBarOutline);
    mainWindow.draw(progressBar);
    mainWindow.draw(progressText);
    mainWindow.draw(FAQ);
    mainWindow.draw(changeTheme);
    mainWindow.draw(defaultLabel);
    mainWindow.draw(postItLabel);
    mainWindow.draw(currentLabel);
    mainWindow.draw(darkLabel);

    // format digital time on clock
    string digitalTime = std::asctime(&stdNow);
    digitalTime = digitalTime.substr(11, 8);
    digitalClock.setString(digitalTime);

    backButton.setFillColor(Color::Black);
    if (backButton.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
      backButton.setFillColor(Color::Green);
      if (event.type == sf::Event::MouseButtonPressed) return 2;
    }

    FAQ.setFillColor(Color::Black);
    if (FAQ.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
      FAQ.setFillColor(Color::Green);
      if (event.type == sf::Event::MouseButtonPressed) return 1000;
    }
    defaultLabel.setFillColor(Color::Black);
    if (defaultLabel.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
      defaultLabel.setFillColor(Color::Green);
      if (event.type == sf::Event::MouseButtonPressed) {
        userInformation.theme = 0;
        return 1;
      }
    }

    darkLabel.setFillColor(Color::Black);
    if (userInformation.level >= 10){
      if (darkLabel.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        darkLabel.setFillColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) {
          userInformation.theme = 2;
          return 5;
        }
      }
    }
    else {
      darkLabel.setFillColor(Color{200,0,0});
      mainWindow.draw(unlocksAt10);
    }

    RectangleShape basicAvatar(sf::Vector2f(300, 300));
    basicAvatar.setOutlineColor(Color::Black);
    basicAvatar.setOutlineThickness(8);
    basicAvatar.setPosition(50, 100);
    basicAvatar.setFillColor(Color{allPossibleColors.at(userInformation.avatarColor).at(0), allPossibleColors.at(userInformation.avatarColor).at(1), allPossibleColors.at(userInformation.avatarColor).at(2)});

    CircleShape avatarExample(100, userInformation.avatarShape);
    avatarExample.setPosition(100, 150);
    avatarExample.setFillColor(Color::Black);

    for (int i = 0; i < 6; i++){
      int j = i + 3;
      CircleShape possibleShapes(30, j);
      possibleShapes.setPosition(505 + i*100, 810);
      possibleColors.setPosition(520 + i*100, 728);

      possibleColors.setFillColor(Color{allPossibleColors.at(i).at(0), allPossibleColors.at(i).at(1), allPossibleColors.at(i).at(2)});
      possibleShapes.setFillColor(Color::Black);

      if ((userInformation.level < 15) && (i < 3)){
        mainWindow.draw(possibleColors);
        mainWindow.draw(possibleShapes);
        mainWindow.draw(moreCustom);

      if (possibleColors.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        if (event.type == sf::Event::MouseButtonPressed) userInformation.avatarColor = i;
      }
      if (possibleShapes.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        if (event.type == sf::Event::MouseButtonPressed) userInformation.avatarShape = j;
        }
      }
      else if (userInformation.level >= 15){
        mainWindow.draw(possibleColors);
        mainWindow.draw(possibleShapes);

      if (possibleColors.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        if (event.type == sf::Event::MouseButtonPressed) userInformation.avatarColor = i;
      }
      if (possibleShapes.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        if (event.type == sf::Event::MouseButtonPressed) userInformation.avatarShape = j;
        }
      }
    }


    mainWindow.draw(basicAvatar);
    mainWindow.draw(avatarExample);


    
    mainWindow.display();
  }
  return 0;
}

int loadPostItMainPlanner(Profile& userInformation, vector<vector<Task>>& taskInformation) {

  vector<vector<uint8_t>> postItColors = {{255, 209, 161}, {110, 255, 255},{255, 34, 145}, {0, 213, 106}};
  vector<vector<uint8_t>> postItHeaderColors = {{255, 184, 110}, {75, 226, 226}, {213, 0, 107}, {0, 162, 81}};

  vector<vector<uint8_t>> postItColorsBot = {{255, 182, 218}, {0, 213, 0},{9,9,255}};
  vector<vector<uint8_t>> postItHeaderColorsBot = {{255, 131, 192}, {0,162,0}, {0,0,213}};



  RectangleShape basicOutline(sf::Vector2f(windowLength, windowWidth));
  basicOutline.setFillColor(Color(255, 255, 186));

  RectangleShape headerOutline(sf::Vector2f(1400, 90));
  headerOutline.setFillColor(Color{186, 186, 255});
  headerOutline.setPosition(100,50);

  RectangleShape timeOutline(sf::Vector2f(245, 75));
  timeOutline.setFillColor(Color(186, 186, 255));
  timeOutline.setPosition(15,825);

  RectangleShape basicAvatar(sf::Vector2f(75,75));
  basicAvatar.setFillColor(Color{allPossibleColors.at(userInformation.avatarColor).at(0), allPossibleColors.at(userInformation.avatarColor).at(1), allPossibleColors.at(userInformation.avatarColor).at(2)});
  basicAvatar.setOutlineThickness(5);
  basicAvatar.setPosition(1400, 57);

  CircleShape avatarExample(25, userInformation.avatarShape);
  avatarExample.setPosition(1413, 70);
  avatarExample.setFillColor(Color::Black);

  RectangleShape sunStickyNote(sf::Vector2f(325, 325));
  RectangleShape sunStickyNoteHeader(sf::Vector2f(325, 75));


  CircleShape tempButtonDays(8);
  tempButtonDays.setFillColor(Color::Black);

  RectangleShape progressBarOutline(sf::Vector2f(500, 30));
  progressBarOutline.setOutlineColor(Color::Black);
  progressBarOutline.setFillColor(Color({255,255,186}));
  progressBarOutline.setOutlineThickness(5);
  progressBarOutline.setPosition(550, 850);

  RectangleShape progressBar(sf::Vector2f((userInformation.progress/100.0 * 500), 30));
  progressBar.setFillColor(Color::Blue);
  progressBar.setPosition(550, 850);

  // format and scale digital representaion of time
  sf::Text digitalClock;
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  digitalClock.setFont(font);
  digitalClock.setPosition(15, 825);
  digitalClock.setFillColor(Color::Black);
  digitalClock.setCharacterSize(60);


  sf::Text headerUser;
  headerUser.setFont(font);
  headerUser.setPosition(105, 64);
  headerUser.setFillColor(Color::Black);
  headerUser.setCharacterSize(47);
  string identifier = userInformation.name + "'s Week";
  headerUser.setString(identifier);

  sf::Text daysOfWeek;
  daysOfWeek.setFont(font);
  daysOfWeek.setPosition(171, 172);
  daysOfWeek.setFillColor(Color::Black);
  daysOfWeek.setCharacterSize(60);
  string days = "Sun                   Mon                  Tues                  Wed\n\n\n\n\n              Thurs                Fri                   Sat";
  daysOfWeek.setString(days);

  sf::Text addTask;
  addTask.setFont(font);
  addTask.setPosition(1325, 825);
  addTask.setFillColor(Color::Black);
  addTask.setCharacterSize(50);
  string addTaskStr = "* Add Task";
  addTask.setString(addTaskStr);

  sf::Text taskMain;
  taskMain.setFont(font);
  taskMain.setCharacterSize(25);

  sf::Text taskTime;
  taskTime.setFont(font);
  taskTime.setCharacterSize(15);

  sf::Text progressText;
  progressText.setFont(font);
  progressText.setFillColor(Color::Blue);
  progressText.setString(to_string(userInformation.progress) + " / 100");
  progressText.setCharacterSize(15);
  progressText.setPosition(770, 825);

  sf::Text levelText;
  levelText.setFont(font);
  levelText.setFillColor(Color::Black);
  levelText.setString(to_string(userInformation.level));
  levelText.setCharacterSize(40);
  levelText.setPosition(480,839);

  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed){

        mainWindow.close();
        return -1;
      }
    }

    std::time_t stdTime = std::time(NULL);  // get new time
    std::tm stdNow = *std::localtime(&stdTime);

    mainWindow.clear();

    // format digital time on clock
    string digitalTime = std::asctime(&stdNow);
    digitalTime = digitalTime.substr(11, 8);
    digitalClock.setString(digitalTime);
    mainWindow.draw(basicOutline);

    basicAvatar.setOutlineColor(Color::Black);
    
    if (basicAvatar.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        basicAvatar.setOutlineColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) return 3;
    }


    int dayIndex = 200;

    int currentTime = getCurrTimeSec();

    for (int i = 0; i < 4; i++){
      tempButtonDays.setFillColor(Color::Black);
      sunStickyNote.setPosition(58 + i*380, 170);
      vector<uint8_t> color = postItColors.at(i);
      sunStickyNote.setFillColor(Color{color.at(0), color.at(1), color.at(2)});
      vector<uint8_t> hColor = postItHeaderColors.at(i);
      sunStickyNoteHeader.setPosition(58 + i*380, 170);
      sunStickyNoteHeader.setFillColor(Color{hColor.at(0), hColor.at(1), hColor.at(2)});
      tempButtonDays.setPosition(68 + i*380, 180);
      if (tempButtonDays.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        tempButtonDays.setFillColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) return dayIndex;
        }
      mainWindow.draw(tempButtonDays);
      dayIndex += 1;
      mainWindow.draw(sunStickyNote);
      mainWindow.draw(sunStickyNoteHeader);
      mainWindow.draw(tempButtonDays);
      for (int j = 0; j < taskInformation.at(i).size(); j++){
        taskTime.setFillColor(Color::Black);
        taskMain.setFillColor(Color::Black);
        double hourRemaining = (taskInformation.at(i).at(j).dueInSec - currentTime) / 3600.0;

        taskMain.setString("Task: " + taskInformation.at(i).at(j).taskName);
        taskMain.setPosition(65 + i * 380, 250 + (j * 60));
        char buffer[50];
        if (hourRemaining < 0) {
          taskMain.setFillColor(Color::Red);
          sprintf(buffer, "Overdue By:\n%.2f hours", -hourRemaining);
        }
        else if (hourRemaining == 0){
          taskMain.setFillColor(Color::Red);
          sprintf(buffer, "Overdue By:\n%.2f hours", hourRemaining);
        }
        else if (hourRemaining <= 2){
          taskMain.setFillColor(Color{255,128,0});
          sprintf(buffer, "Time Remaining:\n%.2f hours", hourRemaining);
        }
        else{
          sprintf(buffer, "Time Remaining:\n%.2f hours", hourRemaining);
        }
        if (taskInformation.at(i).at(j).complete) {
          taskTime.setFillColor(Color{color.at(0), color.at(1), color.at(2)});
          taskMain.setFillColor(Color::Green);
        }
        taskTime.setString(buffer);
        taskTime.setPosition(260 + i * 380, 250 + (j * 60));
        mainWindow.draw(taskTime);
        mainWindow.draw(taskMain);
      }
    }

    for (int i = 0; i < 3; i++){
      tempButtonDays.setFillColor(Color::Black);
      sunStickyNote.setPosition(278 + i*350, 525);
      vector<uint8_t> color = postItColorsBot.at(i);
      sunStickyNote.setFillColor(Color{color.at(0), color.at(1), color.at(2)});
      vector<uint8_t> hColor = postItHeaderColorsBot.at(i);
      sunStickyNoteHeader.setPosition(278 + i*350, 525);
      sunStickyNoteHeader.setFillColor(Color{hColor.at(0), hColor.at(1), hColor.at(2)});
      tempButtonDays.setPosition(288 + i*350, 535);
      if (tempButtonDays.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        tempButtonDays.setFillColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) return dayIndex;
        }
      mainWindow.draw(tempButtonDays);
      dayIndex += 1;
      mainWindow.draw(sunStickyNote);
      mainWindow.draw(sunStickyNoteHeader);
      mainWindow.draw(tempButtonDays);
      for (int j = 0; j < taskInformation.at(i+4).size(); j++){
        taskTime.setFillColor(Color::Black);
        taskMain.setFillColor(Color::Black);
        double hourRemaining = (taskInformation.at(i+4).at(j).dueInSec - currentTime) / 3600.0;

        taskMain.setString("Task: " + taskInformation.at(i+4).at(j).taskName);
        taskMain.setPosition(285 + i * 350, 610 + j * 60);
        char buffer[50];
        if (hourRemaining < 0) {
          taskMain.setFillColor(Color::Red);
          sprintf(buffer, "Overdue By:\n%.2f hours", -hourRemaining);
        }
        else if (hourRemaining == 0){
          taskMain.setFillColor(Color::Red);
          sprintf(buffer, "Overdue By:\n%.2f hours", hourRemaining);
        }
        else if (hourRemaining <= 2){
          taskMain.setFillColor(Color{255,128,0});
          sprintf(buffer, "Time Remaining:\n%.2f hours", hourRemaining);
        }
        else{
          sprintf(buffer, "Time Remaining:\n%.2f hours", hourRemaining);
        }
        if (taskInformation.at(i+4).at(j).complete) {
          taskTime.setFillColor(Color(Color{color.at(0), color.at(1), color.at(2)}));
          taskMain.setFillColor(Color::Green);
        }
        taskTime.setString(buffer);
        taskTime.setPosition(478 + i * 350, 610 + j * 60);
        mainWindow.draw(taskTime);
        mainWindow.draw(taskMain);
      }
    }

    addTask.setFillColor(Color::Black);
    if (addTask.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        addTask.setFillColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) return 2000;
    }

    mainWindow.draw(headerOutline);
    mainWindow.draw(timeOutline);
    mainWindow.draw(basicAvatar);
    mainWindow.draw(avatarExample);
    mainWindow.draw(digitalClock);
    mainWindow.draw(headerUser);
    mainWindow.draw(daysOfWeek);
    mainWindow.draw(addTask);
    mainWindow.display();
  }
  return 0;
};

int loadPostItDayPlanner(Profile& userInformation, vector<vector<Task>>& taskInformation, string day){

  vector<string> daysOfWeek = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  int dayIndex = -1;
  for (int i = 0; i < daysOfWeek.size(); i++){
    if ((daysOfWeek.at(i)).compare(day) == 0) dayIndex = i;
  }

  int lengthSpecific = taskInformation.at(dayIndex).size();

  RectangleShape basicOutline(sf::Vector2f(windowLength, windowWidth));
  basicOutline.setFillColor(Color(255, 255, 186));

  RectangleShape timeOutline(sf::Vector2f(245, 75));
  timeOutline.setFillColor(Color(186, 186, 255));
  timeOutline.setPosition(65,825);

  RectangleShape basicAvatar(sf::Vector2f(75,75));
  basicAvatar.setFillColor(Color{allPossibleColors.at(userInformation.avatarColor).at(0), allPossibleColors.at(userInformation.avatarColor).at(1), allPossibleColors.at(userInformation.avatarColor).at(2)});
  basicAvatar.setOutlineColor(Color::Black);
  basicAvatar.setOutlineThickness(5);
  basicAvatar.setPosition(1400, 113);

  CircleShape avatarExample(25, userInformation.avatarShape);
  avatarExample.setPosition(1413, 126);
  avatarExample.setFillColor(Color::Black);

  RectangleShape mainBox(sf::Vector2f(1400, 600));
  mainBox.setFillColor(Color{238,238,238});
  mainBox.setPosition(100, 200);

  RectangleShape headerBox(sf::Vector2f(1400, 100));
  headerBox.setFillColor(Color{215, 215, 215});
  headerBox.setPosition(100, 100);

  CircleShape tempButtonDays(20, 3);
  tempButtonDays.setFillColor(Color::Black);
  tempButtonDays.setPosition(140, 170);
  tempButtonDays.rotate(270);

  RectangleShape progressBarOutline(sf::Vector2f(500, 30));
  progressBarOutline.setFillColor(Color({255,255,186}));
  progressBarOutline.setOutlineColor(Color::Black);
  progressBarOutline.setOutlineThickness(5);
  progressBarOutline.setPosition(550, 850);

  RectangleShape progressBar(sf::Vector2f((userInformation.progress/100.0 * 500), 30));
  progressBar.setFillColor(Color::Blue);
  progressBar.setPosition(550, 850);

  RectangleShape checkbox(sf::Vector2f(30,30));
  checkbox.setFillColor(Color::Black);
  RectangleShape checkboxFilled(sf::Vector2f(30,30));
  checkboxFilled.setFillColor(Color::Green);

  // format and scale digital representaion of time
  sf::Text digitalClock;
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  digitalClock.setFont(font);
  digitalClock.setPosition(65, 825);
  digitalClock.setFillColor(Color::Black);
  digitalClock.setCharacterSize(60);


  sf::Text headerUser;
  headerUser.setFont(font);
  headerUser.setPosition(198, 116);
  headerUser.setFillColor(Color::Black);
  headerUser.setCharacterSize(47);
  string identifier = userInformation.name + "'s " + day;
  headerUser.setString(identifier);


  sf::Text addTask;
  addTask.setFont(font);
  addTask.setPosition(1300, 825);
  addTask.setFillColor(Color::Black);
  addTask.setCharacterSize(50);
  string addTaskStr = "* Add Task";
  addTask.setString(addTaskStr);

  sf::Cursor cursor;

  sf::Text taskInfo;
  taskInfo.setFont(font);
  taskInfo.setCharacterSize(40);
  
  sf::Text taskDesc;
  taskDesc.setFont(font);
  taskDesc.setFillColor(Color::Black);
  taskDesc.setCharacterSize(26);

  sf::Text unmark;
  unmark.setFont(font);
  unmark.setFillColor(Color::Black);
  unmark.setCharacterSize(15);
  unmark.setString("Unmark");
  unmark.setStyle(sf::Text::Underlined);

  sf::Text deleteTask;
  deleteTask.setFont(font);
  deleteTask.setFillColor(Color::Red);
  deleteTask.setCharacterSize(40);
  deleteTask.setString("X");
  deleteTask.setStyle(sf::Text::Bold);

  sf::Text confirmation;
  confirmation.setFont(font);
  confirmation.setFillColor(Color::White);
  confirmation.setCharacterSize(0);
  confirmation.setString("   Click here to\nconfirm deletion");

  sf::Text progressText;
  progressText.setFont(font);
  progressText.setFillColor(Color::Blue);
  progressText.setCharacterSize(15);
  progressText.setPosition(770, 825);

  sf::Text levelText;
  levelText.setFont(font);
  levelText.setFillColor(Color::Black);
  levelText.setCharacterSize(40);
  levelText.setPosition(480,839);


  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed){

        mainWindow.close();
        return -1;
      }
    }

    std::time_t stdTime = std::time(NULL);  // get new time
    std::tm stdNow = *std::localtime(&stdTime);

    mainWindow.clear();

    addTask.setFillColor(Color::Black);
    if (addTask.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        addTask.setFillColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) return 2000;
    }

    basicAvatar.setOutlineColor(Color::Black);
    if (basicAvatar.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        basicAvatar.setOutlineColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) return 3;
    }
    
    tempButtonDays.setFillColor(Color::Black);
    if (tempButtonDays.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
      tempButtonDays.setFillColor(Color::Green);
      if (event.type == sf::Event::MouseButtonPressed) return 2;
    }

    // format digital time on clock
    string digitalTime = std::asctime(&stdNow);
    digitalTime = digitalTime.substr(11, 8);
    digitalClock.setString(digitalTime);

    mainWindow.draw(basicOutline);
    mainWindow.draw(mainBox);
    mainWindow.draw(headerBox);
    mainWindow.draw(tempButtonDays);
    mainWindow.draw(timeOutline);
    mainWindow.draw(progressBarOutline);
    progressBar.setSize(sf::Vector2f((userInformation.progress/100.0 * 500), 30));
    mainWindow.draw(progressBar);
    progressText.setString(to_string(userInformation.progress) + " / 100");
    mainWindow.draw(progressText);
    levelText.setString(to_string(userInformation.level));
    mainWindow.draw(levelText);

    basicAvatar.setOutlineColor(Color::Black);

    if (basicAvatar.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        basicAvatar.setOutlineColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) return 1;
    }
    mainWindow.draw(basicAvatar);
    mainWindow.draw(avatarExample);
    mainWindow.draw(digitalClock);
    mainWindow.draw(headerUser);

    for (int i = 0; i < taskInformation.at(dayIndex).size(); i++){

        int addedPoints = 0;
        int currDiffernceSec = (taskInformation.at(dayIndex).at(i).dueInSec - getCurrTimeSec());

        if (taskInformation.at(dayIndex).at(i).complete) {
          unmark.setPosition(135, 270 + (i*145));
          mainWindow.draw(unmark);
          checkboxFilled.setPosition(150, 230 + (i*145));
          mainWindow.draw(checkboxFilled);
          if (unmark.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
            if (event.type == sf::Event::MouseButtonPressed) {
              taskInformation.at(dayIndex).at(i).complete = !taskInformation.at(dayIndex).at(i).complete;
              userInformation.updatePoints(-taskInformation.at(dayIndex).at(i).pointsgiven);
              taskInformation.at(dayIndex).at(i).pointsgiven = 0;
            }
          }
        }
        else {
          checkbox.setPosition(150, 230 + (i*145));
          mainWindow.draw(checkbox);
          if (checkbox.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
            if (event.type == sf::Event::MouseButtonPressed) {
              taskInformation.at(dayIndex).at(i).complete = !taskInformation.at(dayIndex).at(i).complete;
              if ((currDiffernceSec/3600) > 12) addedPoints = 25 + (2 * currDiffernceSec/3600);
              else if (currDiffernceSec < 0) addedPoints = 0;
              else addedPoints = 25;
              taskInformation.at(dayIndex).at(i).pointsgiven = addedPoints;
              userInformation.updatePoints(taskInformation.at(dayIndex).at(i).pointsgiven);
            }
          }
        }

        taskInfo.setFillColor(Color::Black);
        taskInfo.setString("Task Subject: " + taskInformation.at(dayIndex).at(i).taskName);
        vector<string> amPMlabel = {"AM","PM"};

        Task cTask = taskInformation.at(dayIndex).at(i);
        taskDesc.setString("\nTask Description: " + taskInformation.at(dayIndex).at(i).description + "\nTask Due Time: " + to_string(taskInformation.at(dayIndex).at(i).dueTime) + " " + amPMlabel.at(taskInformation.at(dayIndex).at(i).AmPm));
        taskInfo.setPosition(200, 220 + (i*145));
        taskDesc.setPosition(315, 240 + (i*145));
        mainWindow.draw(taskInfo);
        mainWindow.draw(taskDesc);

        deleteTask.setPosition(1400, 230 + (i*145));
        mainWindow.draw(deleteTask);

        if (deleteTask.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
            if (event.type == sf::Event::MouseButtonPressed) {
              confirmation.setPosition(1360, 290 + (i*145));
              confirmation.setFillColor(Color::Red);
              confirmation.setCharacterSize(13);
            }
          }
        mainWindow.draw(confirmation);
        if (confirmation.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
            if (event.type == sf::Event::MouseButtonPressed) {
              taskInformation.at(dayIndex).erase(taskInformation.at(dayIndex).begin() + i);
              confirmation.setCharacterSize(0);
              confirmation.setFillColor(Color(255,255,186));
              confirmation.setPosition(0,0);
            }
          }
        
       }
    mainWindow.draw(addTask);
    mainWindow.display();
  }
  return 0;
}

int loadDarkProfile(Profile& userInformation, vector<vector<Task>>& taskInformation){

  RectangleShape basicOutline(sf::Vector2f(windowLength, windowWidth));
  basicOutline.setFillColor(Color::Black);

  RectangleShape possibleColors(sf::Vector2f(30, 30));

  RectangleShape timeOutline(sf::Vector2f(245, 75));
  timeOutline.setOutlineColor(Color::White);
  timeOutline.setFillColor(Color::Black);
  timeOutline.setOutlineThickness(5);
  timeOutline.setPosition(1300,800);


  RectangleShape progressBarOutline(sf::Vector2f(550, 30));
  progressBarOutline.setOutlineColor(Color::White);
  progressBarOutline.setFillColor(Color::Black);
  progressBarOutline.setOutlineThickness(5);
  progressBarOutline.setPosition(1000, 405);

  RectangleShape progressBar(sf::Vector2f((userInformation.progress/100.0 * 550), 30));
  progressBar.setFillColor(Color::Blue);
  progressBar.setPosition(1000, 405);

  CircleShape backButton(20, 3);
  backButton.setPosition(50, 60);
  backButton.rotate(270);

  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  sf::Text progressText;
  progressText.setFont(font);
  progressText.setFillColor(Color::Blue);
  progressText.setString(to_string(userInformation.progress) + " / 100");
  progressText.setCharacterSize(15);
  progressText.setPosition(1250, 445);


  sf::Text digitalClock;
  digitalClock.setFont(font);
  digitalClock.setPosition(1300, 800);
  digitalClock.setFillColor(Color::White);
  digitalClock.setCharacterSize(60);

  sf::Text profileHeader;
  profileHeader.setFont(font);
  profileHeader.setPosition(450, 22);
  profileHeader.setFillColor(Color::White);
  profileHeader.setString("Profile Information:");
  profileHeader.setCharacterSize(65);

  sf::Text profileSpecifics;
  string profileInfo = "Name: " + userInformation.name + "\n\nPoints Earned: "  + to_string(userInformation.pointsEarned) + "\n\nProfile Level: " + to_string(userInformation.level) + "\n\nProgress to Next Level:";
  profileSpecifics.setFont(font);
  profileSpecifics.setPosition(500, 115);
  profileSpecifics.setFillColor(Color::White);
  profileSpecifics.setString(profileInfo);
  profileSpecifics.setCharacterSize(40);

  sf::Text settingsHeader;
  settingsHeader.setFont(font);
  settingsHeader.setPosition(50, 450);
  settingsHeader.setFillColor(Color::White);
  settingsHeader.setString("Settings and Information:");
  settingsHeader.setCharacterSize(65);

  sf::Text FAQ;
  FAQ.setFont(font);
  FAQ.setPosition(100, 550);
  FAQ.setString("Go to FAQ");
  FAQ.setCharacterSize(40);

  sf::Text changeTheme;
  changeTheme.setFont(font);
  changeTheme.setPosition(100, 625);
  changeTheme.setString("Select Theme:\n\nSelect Avatar Shape:\n\nSelect Avatar Color:");
  changeTheme.setCharacterSize(40);
  changeTheme.setFillColor(Color::White);

  sf::Text defaultLabel;
  defaultLabel.setFont(font);
  defaultLabel.setPosition(425, 625);
  defaultLabel.setString("Default");
  defaultLabel.setCharacterSize(40);
  defaultLabel.setFillColor(Color::White);

  sf::Text postItLabel;
  postItLabel.setFont(font);
  postItLabel.setPosition(671, 625);
  postItLabel.setString("Post-It");
  postItLabel.setCharacterSize(40);

  sf::Text currentLabel;
  currentLabel.setFont(font);
  currentLabel.setPosition(916, 675);
  currentLabel.setString("(current)");
  currentLabel.setCharacterSize(15);
  currentLabel.setFillColor(Color::White);

  sf::Text unlocksAt5;
  unlocksAt5.setFont(font);
  unlocksAt5.setPosition(667, 675);
  unlocksAt5.setString("(unlocks at level 5)");
  unlocksAt5.setCharacterSize(15);
  unlocksAt5.setFillColor(Color::White);

  sf::Text darkLabel;
  darkLabel.setFont(font);
  darkLabel.setPosition(900, 625);
  darkLabel.setString("Dark");
  darkLabel.setFillColor(Color::White);
  darkLabel.setCharacterSize(40);

  sf::Text unlocksAt10;
  unlocksAt10.setFont(font);
  unlocksAt10.setPosition(876, 675);
  unlocksAt10.setString("(unlocks at level 10)");
  unlocksAt10.setCharacterSize(15);
  unlocksAt10.setFillColor(Color::Black);

  sf::Text moreCustom;
  moreCustom.setFont(font);
  moreCustom.setCharacterSize(15);
  moreCustom.setString("More customizable shapes and colors unlock at level 15!");
  moreCustom.setFillColor(Color::White);
  moreCustom.setPosition(800, 777);


  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed){

        mainWindow.close();
        return -1;
      }
    }

    std::time_t stdTime = std::time(NULL);  // get new time
    std::tm stdNow = *std::localtime(&stdTime);

    mainWindow.clear();
    mainWindow.draw(basicOutline);

    // format digital time on clock
    string digitalTime = std::asctime(&stdNow);
    digitalTime = digitalTime.substr(11, 8);
    digitalClock.setString(digitalTime);

    backButton.setFillColor(Color::White);

    if (backButton.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
      backButton.setFillColor(Color::Green);
      if (event.type == sf::Event::MouseButtonPressed) return 4;
    }

    FAQ.setFillColor(Color::White);
    if (FAQ.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
      FAQ.setFillColor(Color::Green);
      if (event.type == sf::Event::MouseButtonPressed) return 1000;
    }
    postItLabel.setFillColor(Color::White);
    if (userInformation.level >= 5){
      if (postItLabel.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        postItLabel.setFillColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) {
          userInformation.theme = 1;
          return 3;
        }
      }
    }
    else {
      postItLabel.setFillColor(Color::Red);
      mainWindow.draw(unlocksAt5);
    }

    defaultLabel.setFillColor(Color::White);
    if (defaultLabel.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
      defaultLabel.setFillColor(Color::Green);
      if (event.type == sf::Event::MouseButtonPressed) {
        userInformation.theme = 0;
        return 1;
      }
    }


    RectangleShape basicAvatar(sf::Vector2f(300, 300));
    basicAvatar.setOutlineColor(Color::White);
    basicAvatar.setOutlineThickness(8);
    basicAvatar.setPosition(50, 100);
    basicAvatar.setFillColor(Color{allPossibleColors.at(userInformation.avatarColor).at(0), allPossibleColors.at(userInformation.avatarColor).at(1), allPossibleColors.at(userInformation.avatarColor).at(2)});

    CircleShape avatarExample(100, userInformation.avatarShape);
    avatarExample.setPosition(100, 150);
    avatarExample.setFillColor(Color::White);

    for (int i = 0; i < 6; i++){
      int j = i + 3;
      CircleShape possibleShapes(30, j);
      possibleShapes.setPosition(505 + i*100, 810);
      possibleColors.setPosition(520 + i*100, 728);

      possibleColors.setFillColor(Color{allPossibleColors.at(i).at(0), allPossibleColors.at(i).at(1), allPossibleColors.at(i).at(2)});
      possibleShapes.setFillColor(Color::White);

      if ((userInformation.level < 15) && (i < 3)){
        mainWindow.draw(possibleColors);
        mainWindow.draw(possibleShapes);
        mainWindow.draw(moreCustom);

      if (possibleColors.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        if (event.type == sf::Event::MouseButtonPressed) userInformation.avatarColor = i;
      }
      if (possibleShapes.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        if (event.type == sf::Event::MouseButtonPressed) userInformation.avatarShape = j;
        }
      }
      else if (userInformation.level >= 15){
        mainWindow.draw(possibleColors);
        mainWindow.draw(possibleShapes);

      if (possibleColors.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        if (event.type == sf::Event::MouseButtonPressed) userInformation.avatarColor = i;
      }
      if (possibleShapes.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        if (event.type == sf::Event::MouseButtonPressed) userInformation.avatarShape = j;
        }
      }
    }



    // draw clock componentse
    mainWindow.draw(backButton);
    mainWindow.draw(basicAvatar);
    mainWindow.draw(avatarExample);
    mainWindow.draw(timeOutline);
    mainWindow.draw(digitalClock);
    mainWindow.draw(profileHeader);
    mainWindow.draw(profileSpecifics);
    mainWindow.draw(settingsHeader);
    mainWindow.draw(progressBarOutline);
    mainWindow.draw(progressBar);
    mainWindow.draw(progressText);
    mainWindow.draw(FAQ);
    mainWindow.draw(changeTheme);
    mainWindow.draw(defaultLabel);
    mainWindow.draw(postItLabel);
    mainWindow.draw(currentLabel);
    mainWindow.draw(darkLabel);
    mainWindow.display();
  }
  return 0;
}

// creation of default main planner page
int loadDarkMainPlanner(Profile& userInformation, vector<vector<Task>>& taskInformation) {

   
  RectangleShape basicOutline(sf::Vector2f(windowLength, windowWidth));
  basicOutline.setFillColor(Color::Black);

  RectangleShape timeOutline(sf::Vector2f(245, 75));
  timeOutline.setOutlineColor(Color::White);
  timeOutline.setFillColor(Color::Black);
  timeOutline.setOutlineThickness(5);
  timeOutline.setPosition(1200,100);

  RectangleShape basicAvatar(sf::Vector2f(75,75));
  basicAvatar.setFillColor(Color{allPossibleColors.at(userInformation.avatarColor).at(0), allPossibleColors.at(userInformation.avatarColor).at(1), allPossibleColors.at(userInformation.avatarColor).at(2)});
  basicAvatar.setOutlineThickness(5);
  basicAvatar.setPosition(1500, 100);

  CircleShape avatarExample(25, userInformation.avatarShape);
  avatarExample.setPosition(1513, 113);


  RectangleShape mainBox(sf::Vector2f(1400, 600));
  mainBox.setFillColor(Color::Black);
  mainBox.setOutlineColor(Color::Blue);
  mainBox.setOutlineThickness(8);
  mainBox.setPosition(100, 200);

  RectangleShape horizontalLine(sf::Vector2f(1400, 8));
  horizontalLine.setFillColor(Color::Blue);
  horizontalLine.setPosition(100, 300);

  RectangleShape verticalLine(sf::Vector2f(8, 600));
  verticalLine.setFillColor(Color::Blue);
  int vertXStart = 300;

  CircleShape tempButtonDays(8);
  tempButtonDays.setFillColor(Color::Blue);

  RectangleShape progressBarOutline(sf::Vector2f(500, 30));
  progressBarOutline.setOutlineColor(Color::White);
  progressBarOutline.setFillColor(Color::Black);
  progressBarOutline.setOutlineThickness(5);
  progressBarOutline.setPosition(550, 850);

  RectangleShape progressBar(sf::Vector2f((userInformation.progress/100.0 * 500), 30));
  progressBar.setFillColor(Color::Blue);
  progressBar.setPosition(550, 850);

  // format and scale digital representaion of time
  sf::Text digitalClock;
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  digitalClock.setFont(font);
  digitalClock.setPosition(1200, 100);
  digitalClock.setFillColor(Color::White);
  digitalClock.setCharacterSize(60);


  sf::Text headerUser;
  headerUser.setFont(font);
  headerUser.setPosition(100, 105);
  headerUser.setFillColor(Color::White);
  headerUser.setCharacterSize(47);
  string identifier = userInformation.name + "'s Week";
  headerUser.setString(identifier);

  sf::Text daysOfWeek;
  daysOfWeek.setFont(font);
  daysOfWeek.setPosition(150, 210);
  daysOfWeek.setFillColor(Color::Blue);
  daysOfWeek.setCharacterSize(60);
  string days = "Sun      Mon      Tues     Wed    Thurs      Fri        Sat";
  daysOfWeek.setString(days);

  sf::Text addTask;
  addTask.setFont(font);
  addTask.setPosition(1300, 825);
  addTask.setCharacterSize(50);
  string addTaskStr = "* Add Task";
  addTask.setString(addTaskStr);

  sf::Text taskMain;
  taskMain.setFont(font);
  taskMain.setCharacterSize(25);

  sf::Text taskTime;
  taskTime.setFont(font);
  taskTime.setCharacterSize(15);

  sf::Text progressText;
  progressText.setFont(font);
  progressText.setFillColor(Color::Blue);
  progressText.setString(to_string(userInformation.progress) + " / 100");
  progressText.setCharacterSize(15);
  progressText.setPosition(770, 825);

  sf::Text levelText;
  levelText.setFont(font);
  levelText.setFillColor(Color::White);
  levelText.setString(to_string(userInformation.level));
  levelText.setCharacterSize(40);
  levelText.setPosition(480,839);


  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed){

        mainWindow.close();
        return -1;
      }
    }

    std::time_t stdTime = std::time(NULL);  // get new time
    std::tm stdNow = *std::localtime(&stdTime);

    mainWindow.clear();

    // format digital time on clock
    string digitalTime = std::asctime(&stdNow);
    digitalTime = digitalTime.substr(11, 8);
    digitalClock.setString(digitalTime);
    mainWindow.draw(basicOutline);
    mainWindow.draw(mainBox);
    mainWindow.draw(horizontalLine);
    mainWindow.draw(progressBarOutline);
    mainWindow.draw(progressBar);
    mainWindow.draw(progressText);
    mainWindow.draw(levelText);

    addTask.setFillColor(Color::White);

    int dayIndex = 300;

    for (int i = 0; i < 7; i++){
      tempButtonDays.setFillColor(Color::Blue);
      verticalLine.setPosition(vertXStart + i*200, 200);
      tempButtonDays.setPosition(vertXStart -20 + i* 200, 210);
      if (tempButtonDays.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        tempButtonDays.setFillColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) return dayIndex;
      }
      mainWindow.draw(verticalLine);
      mainWindow.draw(tempButtonDays);
      dayIndex += 1;

    }
    basicAvatar.setOutlineColor(Color::White);

    if (basicAvatar.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        basicAvatar.setOutlineColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) return 5;
    }

    int currentTime = getCurrTimeSec();

      for (int i = 0; i < 7; i++){
        for (int j = 0; j < taskInformation.at(i).size(); j++){
        taskTime.setFillColor(Color::White);
        taskMain.setFillColor(Color::White);
        double hourRemaining = (taskInformation.at(i).at(j).dueInSec - currentTime) / 3600.0;

        taskMain.setString("Task: " + taskInformation.at(i).at(j).taskName);
        taskMain.setPosition(110 + i * 200, 320 + j * 130);
        char buffer[50];
        if (hourRemaining < 0) {
          taskMain.setFillColor(Color::Red);
          sprintf(buffer, "Overdue By:\n%.2f hours", -hourRemaining);
        }
        else if (hourRemaining == 0){
          taskMain.setFillColor(Color::Red);
          sprintf(buffer, "Overdue By:\n%.2f hours", hourRemaining);
        }
        else if (hourRemaining <= 2){
          taskMain.setFillColor(Color{255,128,0});
          sprintf(buffer, "Time Remaining:\n%.2f hours", hourRemaining);
        }
        else{
          sprintf(buffer, "Time Remaining:\n%.2f hours", hourRemaining);
        }
        if (taskInformation.at(i).at(j).complete) {
          taskTime.setFillColor(Color::Black);
          taskMain.setFillColor(Color::Green);
        }
        taskTime.setString(buffer);
        taskTime.setPosition(118 + i * 200, 360 + j * 130);
        mainWindow.draw(taskTime);
        mainWindow.draw(taskMain);
      }
    }

    mainWindow.draw(timeOutline);
    mainWindow.draw(basicAvatar);
    mainWindow.draw(avatarExample);
    mainWindow.draw(digitalClock);
    mainWindow.draw(headerUser);
    mainWindow.draw(daysOfWeek);

    if (addTask.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        addTask.setFillColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) return 2000;
    }


    mainWindow.draw(addTask);
    mainWindow.display();
  }
  return 0;
}

// creation of default individual day planner
int loadDarkDayPlanner(Profile& userInformation, vector<vector<Task>>& taskInformation, string day){

  vector<string> daysOfWeek = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  int dayIndex = -1;
  for (int i = 0; i < daysOfWeek.size(); i++){
    if ((daysOfWeek.at(i)).compare(day) == 0) dayIndex = i;
  }

  int lengthSpecific = taskInformation.at(dayIndex).size();

  RectangleShape basicOutline(sf::Vector2f(windowLength, windowWidth));
  basicOutline.setFillColor(Color::Black);

  RectangleShape timeOutline(sf::Vector2f(245, 75));
  timeOutline.setOutlineColor(Color::White);
  timeOutline.setFillColor(Color::Black);
  timeOutline.setOutlineThickness(5);
  timeOutline.setPosition(65,825);

  RectangleShape basicAvatar(sf::Vector2f(75,75));
  basicAvatar.setFillColor(Color{allPossibleColors.at(userInformation.avatarColor).at(0), allPossibleColors.at(userInformation.avatarColor).at(1), allPossibleColors.at(userInformation.avatarColor).at(2)});
  basicAvatar.setOutlineColor(Color::White);
  basicAvatar.setOutlineThickness(5);
  basicAvatar.setPosition(1400, 113);

  CircleShape avatarExample(25, userInformation.avatarShape);
  avatarExample.setPosition(1413, 126);

  RectangleShape mainBox(sf::Vector2f(1400, 700));
  mainBox.setOutlineColor(Color::Blue);
  mainBox.setFillColor(Color::Black);
  mainBox.setOutlineThickness(8);
  mainBox.setPosition(100, 100);

  RectangleShape horizontalLine(sf::Vector2f(1400, 8));
  horizontalLine.setFillColor(Color::Blue);
  horizontalLine.setPosition(100, 200);

  RectangleShape checkbox(sf::Vector2f(30,30));
  checkbox.setFillColor(Color::White);
  RectangleShape checkboxFilled(sf::Vector2f(30,30));
  checkboxFilled.setFillColor(Color::Green);

  CircleShape tempButtonDays(20, 3);
  tempButtonDays.setFillColor(Color::Blue);
  tempButtonDays.setPosition(140, 170);
  tempButtonDays.rotate(270);

  RectangleShape progressBarOutline(sf::Vector2f(500, 30));
  progressBarOutline.setOutlineColor(Color::White);
  progressBarOutline.setFillColor(Color::Black);
  progressBarOutline.setOutlineThickness(5);
  progressBarOutline.setPosition(550, 850);

  RectangleShape progressBar(sf::Vector2f((userInformation.progress/100.0 * 500), 30));
  progressBar.setFillColor(Color::Blue);
  progressBar.setPosition(550, 850);


  // format and scale digital representaion of time
  sf::Text digitalClock;
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  digitalClock.setFont(font);
  digitalClock.setPosition(65, 825);
  digitalClock.setFillColor(Color::White);
  digitalClock.setCharacterSize(60);


  sf::Text headerUser;
  headerUser.setFont(font);
  headerUser.setPosition(198, 116);
  headerUser.setFillColor(Color::White);
  headerUser.setCharacterSize(47);
  string identifier = userInformation.name + "'s " + day;
  headerUser.setString(identifier);


  sf::Text addTask;
  addTask.setFont(font);
  addTask.setPosition(1300, 825);
  addTask.setFillColor(Color::White);
  addTask.setCharacterSize(50);
  string addTaskStr = "* Add Task";
  addTask.setString(addTaskStr);

  sf::Cursor cursor;

  sf::Text taskInfo;
  taskInfo.setFont(font);
  taskInfo.setCharacterSize(40);
  
  sf::Text taskDesc;
  taskDesc.setFont(font);
  taskDesc.setFillColor(Color::White);
  taskDesc.setCharacterSize(26);

  sf::Text unmark;
  unmark.setFont(font);
  unmark.setFillColor(Color::White);
  unmark.setCharacterSize(15);
  unmark.setString("Unmark");
  unmark.setStyle(sf::Text::Underlined);

  sf::Text deleteTask;
  deleteTask.setFont(font);
  deleteTask.setFillColor(Color::Red);
  deleteTask.setCharacterSize(40);
  deleteTask.setString("X");
  deleteTask.setStyle(sf::Text::Bold);

  sf::Text confirmation;
  confirmation.setFont(font);
  confirmation.setFillColor(Color::White);
  confirmation.setCharacterSize(0);
  confirmation.setString("   Click here to\nconfirm deletion");

  sf::Text progressText;
  progressText.setFont(font);
  progressText.setFillColor(Color::Blue);
  progressText.setCharacterSize(15);
  progressText.setPosition(770, 825);

  sf::Text levelText;
  levelText.setFont(font);
  levelText.setFillColor(Color::White);
  levelText.setCharacterSize(40);
  levelText.setPosition(480,839);


  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed){

        mainWindow.close();
        return -1;
      }
    }
    std::time_t stdTime = std::time(NULL);  // get new time
    std::tm stdNow = *std::localtime(&stdTime);

    mainWindow.clear();

    // format digital time on clock
    string digitalTime = std::asctime(&stdNow);
    digitalTime = digitalTime.substr(11, 8);
    digitalClock.setString(digitalTime);

    tempButtonDays.setFillColor(Color::Blue);
    if (tempButtonDays.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
      tempButtonDays.setFillColor(Color::Green);
      if (event.type == sf::Event::MouseButtonPressed) return 4;
    }
    mainWindow.draw(basicOutline);
    mainWindow.draw(mainBox);
    mainWindow.draw(horizontalLine);
    mainWindow.draw(tempButtonDays);
    mainWindow.draw(timeOutline);
    mainWindow.draw(progressBarOutline);
    progressBar.setSize(sf::Vector2f((userInformation.progress/100.0 * 500), 30));
    mainWindow.draw(progressBar);
    progressText.setString(to_string(userInformation.progress) + " / 100");
    mainWindow.draw(progressText);
    levelText.setString(to_string(userInformation.level));
    mainWindow.draw(levelText);


    basicAvatar.setOutlineColor(Color::White);

    if (basicAvatar.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        basicAvatar.setOutlineColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) return 5;
    }
    mainWindow.draw(basicAvatar);
    mainWindow.draw(avatarExample);
    mainWindow.draw(digitalClock);
    mainWindow.draw(headerUser);

    addTask.setFillColor(Color::White);
    if (addTask.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        addTask.setFillColor(Color::Green);
        if (event.type == sf::Event::MouseButtonPressed) return 2000;
    }

    for (int i = 0; i < taskInformation.at(dayIndex).size(); i++){

        int addedPoints = 0;
        int currDiffernceSec = (taskInformation.at(dayIndex).at(i).dueInSec - getCurrTimeSec());

        if (taskInformation.at(dayIndex).at(i).complete) {
          unmark.setPosition(135, 270 + (i*145));
          mainWindow.draw(unmark);
          checkboxFilled.setPosition(150, 230 + (i*145));
          mainWindow.draw(checkboxFilled);
          if (unmark.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
            if (event.type == sf::Event::MouseButtonPressed) {
              taskInformation.at(dayIndex).at(i).complete = !taskInformation.at(dayIndex).at(i).complete;
              userInformation.updatePoints(-taskInformation.at(dayIndex).at(i).pointsgiven);
              taskInformation.at(dayIndex).at(i).pointsgiven = 0;
            }
          }
        }
        else {
          checkbox.setPosition(150, 230 + (i*145));
          mainWindow.draw(checkbox);
          if (checkbox.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
            if (event.type == sf::Event::MouseButtonPressed) {
              taskInformation.at(dayIndex).at(i).complete = !taskInformation.at(dayIndex).at(i).complete;
              if ((currDiffernceSec/3600) > 12) addedPoints = 25 + (2 * currDiffernceSec/3600);
              else if (currDiffernceSec < 0) addedPoints = 0;
              else addedPoints = 25;
              taskInformation.at(dayIndex).at(i).pointsgiven = addedPoints;
              userInformation.updatePoints(taskInformation.at(dayIndex).at(i).pointsgiven);
            }
          }
        }

        taskInfo.setFillColor(Color::White);
        taskInfo.setString("Task Subject: " + taskInformation.at(dayIndex).at(i).taskName);
        vector<string> amPMlabel = {"AM","PM"};

        Task cTask = taskInformation.at(dayIndex).at(i);
        taskDesc.setString("\nTask Description: " + taskInformation.at(dayIndex).at(i).description + "\nTask Due Time: " + to_string(taskInformation.at(dayIndex).at(i).dueTime) + " " + amPMlabel.at(taskInformation.at(dayIndex).at(i).AmPm));
        taskInfo.setPosition(200, 220 + (i*145));
        taskDesc.setPosition(315, 240 + (i*145));
        mainWindow.draw(taskInfo);
        mainWindow.draw(taskDesc);

        deleteTask.setPosition(1400, 230 + (i*145));
        mainWindow.draw(deleteTask);

        if (deleteTask.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
            if (event.type == sf::Event::MouseButtonPressed) {
              confirmation.setPosition(1360, 290 + (i*145));
              confirmation.setFillColor(Color::Red);
              confirmation.setCharacterSize(13);
            }
          }
        mainWindow.draw(confirmation);
        if (confirmation.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
            if (event.type == sf::Event::MouseButtonPressed) {
              taskInformation.at(dayIndex).erase(taskInformation.at(dayIndex).begin() + i);
              confirmation.setCharacterSize(0);
              confirmation.setFillColor(Color::Black);
              confirmation.setPosition(0,0);
            }
          }
        
       }

    mainWindow.draw(addTask);
    mainWindow.display();
  }
  return 0;
}

int loadAddTask(Profile& userInformation, vector<vector<Task>>& allTaskData) {

  CircleShape backButton(20, 3);
  backButton.setPosition(50, 60);
  backButton.rotate(270);

  sf::Text morePrompt;
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");

  sf::Text entryPrompt;
  entryPrompt.setFont(font);
  entryPrompt.setPosition(30, 75);
  entryPrompt.setFillColor(Color::White);
  entryPrompt.setString("Adding Tasks to Your OnTrack Planner...");
  entryPrompt.setCharacterSize(78);
  entryPrompt.setOutlineColor(Color::Blue);
  entryPrompt.setOutlineThickness(10);


  morePrompt.setFont(font);
  morePrompt.setPosition(25, 190);
  morePrompt.setFillColor(Color::White);
  morePrompt.setString("\nPlease input the following information about your task:\n\nTask Subject:\n\nTask Description:\n\nSelect Due Day:\n\nSelect Due Time:\n\nSelect AM/PM:");
  morePrompt.setCharacterSize(50);

  sf::Text isCompleted;
  isCompleted.setFont(font);

  int selectedDay = -1;
  int selectedHour = -1;
  int selectedAPM = -1;

  vector<string> daysOfWeek{"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  vector<string> times{"12","1","2","3","4","5","6","7","8","9","10","11"};
  vector<string> ampmVector{"AM", "PM"};

  sf::Text day;
  day.setCharacterSize(60);
  day.setFont(font);

  sf::Text listTime;
  listTime.setCharacterSize(58);
  listTime.setFont(font);

  sf::Text ampm;
  ampm.setCharacterSize(60);
  ampm.setFont(font);

  sf::Text maxChar;
  maxChar.setFont(font);
  maxChar.setString("(5 character max)\n\n\n\n\n\n\n\n(40 character max)");
  maxChar.setCharacterSize(12);
  maxChar.setPosition(30, 422);

  Textbox taskNameTB(60,sf::Color::White, false);
  taskNameTB.setFont(font);
  taskNameTB.setAsLimit(true,5);
  taskNameTB.setPosition({440, 350});
  sf::RectangleShape textfieldTN = taskNameTB.setTextField(); // Shape of textbox field follows where the firstName position is
  textfieldTN.setSize(sf::Vector2f(300,80)); // Set size of textbox field

  Textbox taskDescTB(30,sf::Color::White,false);
  taskDescTB.setFont(font);
  taskDescTB.setAsLimit(true,40);
  taskDescTB.setPosition({440, 490});
  sf::RectangleShape textfieldTD = taskDescTB.setTextField();
  textfieldTD.setSize(sf::Vector2f(1140,40));
  

  
  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;

    if (taskNameTB.isMouseOver(mainWindow, textfieldTN)){ //Only can select the textbox if within region
      taskNameTB.setAsSelected(true);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || (!taskNameTB.isMouseOver(mainWindow, textfieldTN) && sf::Mouse::isButtonPressed(sf::Mouse::Left))){  //Deselect but it is broken if there is no text
      taskNameTB.setAsSelected(false);
    }
    if (taskDescTB.isMouseOver(mainWindow, textfieldTD)){ //Only can select the textbox if within region
      taskDescTB.setAsSelected(true);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || (!taskDescTB.isMouseOver(mainWindow, textfieldTD) && sf::Mouse::isButtonPressed(sf::Mouse::Left))){  //Deselect but it is broken if there is no text
      taskDescTB.setAsSelected(false);
    }

    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed){
        mainWindow.close();
        return -1;
      }
      if (event.type == sf::Event::TextEntered){
        taskNameTB.typedInput(event); // Allows user to type
        taskDescTB.typedInput(event);
      }
    }
    mainWindow.clear();

    backButton.setFillColor(Color::White);

    if (backButton.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
      backButton.setFillColor(Color::Green);
      if (event.type == sf::Event::MouseButtonPressed) return (userInformation.theme * 2);
    }

    mainWindow.draw(backButton);



    for (int i = 0; i < 7; i++){
      day.setFillColor(Color::White);
      day.setString(daysOfWeek.at(i));
      day.setOrigin(day.getLocalBounds().width /2 , day.getLocalBounds().height /2);
      day.setPosition(550 + (i* 150), 608);
      if (day.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        if (event.type == sf::Event::MouseButtonPressed) selectedDay = i;
      }
      if (selectedDay == i){
        day.setFillColor(Color::Green);
      }
      mainWindow.draw(day);
    }

    for (int i = 0; i < 12; i++){
      listTime.setFillColor(Color::White);
      listTime.setString(times.at(i));
      listTime.setOrigin(listTime.getLocalBounds().width /2 , listTime.getLocalBounds().height /2);
      listTime.setPosition(470 + (i* 96), 715);
      if (listTime.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        if (event.type == sf::Event::MouseButtonPressed) selectedHour = i;
      }
      if (selectedHour == i){
        listTime.setFillColor(Color::Green);
      }
      mainWindow.draw(listTime);
    }

    for (int i = 0; i < 2; i++){
      ampm.setFillColor(Color::White);
      ampm.setString(ampmVector.at(i));
      ampm.setPosition(500 + (i* 150), 805);
      if (ampm.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        if (event.type == sf::Event::MouseButtonPressed) selectedAPM = i;
      }
      if (selectedAPM == i){
        ampm.setFillColor(Color::Green);
      }
      mainWindow.draw(ampm);
    }


    mainWindow.draw(entryPrompt);
    mainWindow.draw(morePrompt);
    mainWindow.draw(maxChar);

    mainWindow.draw(textfieldTN); // Displays textbox field
    mainWindow.draw(textfieldTD);

    taskNameTB.drawTo(mainWindow); // Displays the Textbox
    taskDescTB.drawTo(mainWindow);
  

    if ((taskNameTB.getText().compare("") == 0) || (taskDescTB.getText().compare("") == 0) || (selectedDay == -1) || (selectedHour == -1) || (selectedAPM == -1)){
        isCompleted.setPosition(1150, 840);
        isCompleted.setString("ALL FIELDS REQUIRED BEFORE SUBMITTING");
        isCompleted.setFillColor(Color::Red);
        isCompleted.setCharacterSize(20);
      }
    else{
      int taskDue = (selectedDay * 86400) + (3600 * (selectedHour + (12 * selectedAPM)));

      int currentTime = getCurrTimeSec();

      if (currentTime > taskDue){
        isCompleted.setPosition(900, 840);
        isCompleted.setString("ATTEMPTING TO SET DUE DATE IN THE PAST, PLEASE CHECK INPUTS");
        isCompleted.setCharacterSize(20);
        isCompleted.setFillColor(Color::Red);
        }
      else if (allTaskData.at(selectedDay).size() == 4){
        isCompleted.setPosition(950, 840);
        isCompleted.setString("MAX AMOUNT OF TASKS REACHED FOR THE SELECTED DAY");
        isCompleted.setCharacterSize(20);
        isCompleted.setFillColor(Color::Red);
        }
      else{
        if (taskDescTB.getText().compare("UUDDLRLRBA") == 0) isCompleted.setString("PROCEED WITH CAUTION:");
        else isCompleted.setString("ADD TASK TO PLANNER");
        isCompleted.setPosition(1150, 840);
        isCompleted.setFillColor(Color::White);
        isCompleted.setCharacterSize(30);
        if (isCompleted.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
          isCompleted.setFillColor(Color::Green);
          if (event.type == sf::Event::MouseButtonPressed){
            if (taskDescTB.getText().compare("UUDDLRLRBA") == 0) return -2;
            Task createdTask = Task(taskNameTB.getText(), taskDescTB.getText(), selectedDay, selectedHour, selectedAPM); 
            allTaskData.at(selectedDay).push_back(createdTask);
            if (allTaskData.at(selectedDay).size() > 1){
              for (int i = 0; i < allTaskData.at(selectedDay).size()-1; i++){
                for (int j = 0; j < allTaskData.at(selectedDay).size() - i -1; j++){
                  if (allTaskData.at(selectedDay).at(j).dueInSec > allTaskData.at(selectedDay).at(j+1).dueInSec){
                      Task temp = allTaskData.at(selectedDay).at(j);
                      allTaskData.at(selectedDay).at(j) = allTaskData.at(selectedDay).at(j+1);
                      allTaskData.at(selectedDay).at(j+1) =  temp;
                  }
                }
              }
            }
            return userInformation.theme * 2;
          }
        }
        }
      }

    mainWindow.draw(isCompleted);

    mainWindow.display();
    }

    return 0;
}

int loadFirstTimeUser() {

  RectangleShape possibleColors(sf::Vector2f(75, 75));

  RectangleShape selectedColorOutline(sf::Vector2f(75,75));
  selectedColorOutline.setOutlineThickness(8);
  selectedColorOutline.setOutlineColor(Color::White);

  sf::Text entryPrompt;
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  entryPrompt.setFont(font);
  entryPrompt.setPosition(30, 75);
  entryPrompt.setFillColor(Color::White);
  entryPrompt.setString("WELCOME TO OnTrack: WEEKLY PLANNER");
  entryPrompt.setCharacterSize(78);
  entryPrompt.setOutlineColor(Color::Blue);
  entryPrompt.setOutlineThickness(10);

  sf::Text morePrompt;
  morePrompt.setFont(font);
  morePrompt.setPosition(25, 190);
  morePrompt.setFillColor(Color::White);
  morePrompt.setString("Our records indicate that this is your first time accessing our service.\nPlease tell us a bit about yourself:\n\nFIRST NAME:\n\nLAST NAME:\n\nFAVORITE COLOR:\n\nFAVORITE SHAPE:");
  morePrompt.setCharacterSize(49);

  sf::Text maxChar;
  maxChar.setFont(font);
  maxChar.setFillColor(Color::White);
  maxChar.setString("(10 character max)");
  maxChar.setCharacterSize(12);

  sf::Text permanent;
  permanent.setFont(font);
  permanent.setString("(NAME CANNOT BE CHANGED)");
  permanent.setCharacterSize(13);
  permanent.setPosition(85, 555);

  sf::Text isCompleted;
  isCompleted.setFont(font);
  isCompleted.setPosition(1150, 840);

  Textbox firstNameTB(60,sf::Color::White, false);
  firstNameTB.setFont(font);
  firstNameTB.setAsLimit(true,10);
  firstNameTB.setPosition({380, 350});
  sf::RectangleShape textfieldFN = firstNameTB.setTextField(); // Shape of textbox field follows where the firstName position is
  textfieldFN.setSize(sf::Vector2f(600,80)); // Set size of textbox field

  Textbox lastNameTB(60,sf::Color::White,false);
  lastNameTB.setFont(font);
  lastNameTB.setAsLimit(true,10);
  lastNameTB.setPosition({380, 460});
  sf::RectangleShape textfieldLN = lastNameTB.setTextField();
  textfieldLN.setSize(sf::Vector2f(600,80));

  int selectedColor = -1;
  int selectedShape = -1;
  
  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;

    if (firstNameTB.isMouseOver(mainWindow, textfieldFN)){ //Only can select the textbox if within region
      firstNameTB.setAsSelected(true);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || (!firstNameTB.isMouseOver(mainWindow, textfieldFN) && sf::Mouse::isButtonPressed(sf::Mouse::Left))){  //Deselect but it is broken if there is no text
      firstNameTB.setAsSelected(false);
    }
    if (lastNameTB.isMouseOver(mainWindow, textfieldLN)){ //Only can select the textbox if within region
      lastNameTB.setAsSelected(true);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || (!lastNameTB.isMouseOver(mainWindow, textfieldLN) && sf::Mouse::isButtonPressed(sf::Mouse::Left))){  //Deselect but it is broken if there is no text
      lastNameTB.setAsSelected(false);
    }

    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed){
        mainWindow.close();
        return -1;
      }
      if (event.type == sf::Event::TextEntered){
        firstNameTB.typedInput(event); // Allows user to type
        lastNameTB.typedInput(event);
      }
    }
    mainWindow.clear();

    mainWindow.draw(entryPrompt);
    mainWindow.draw(morePrompt);

    for (int i = 0; i < 2; i++){
      maxChar.setPosition(130, 420 + i*110);
      mainWindow.draw(maxChar);
    }
    mainWindow.draw(textfieldFN); // Displays textbox field
    mainWindow.draw(textfieldLN);
    firstNameTB.drawTo(mainWindow); // Displays the Textbox
    lastNameTB.drawTo(mainWindow);

    if (selectedColor != -1) {
      selectedColorOutline.setPosition(680 + selectedColor*300, 575);
      selectedColorOutline.setOutlineColor(Color{0,255,0});
      selectedColorOutline.setOutlineThickness(8);
      mainWindow.draw(selectedColorOutline);
    }

    if (selectedShape != -1){
      CircleShape selectedShapeOutline(50, selectedShape);
      selectedShapeOutline.setOutlineThickness(8);
      selectedShapeOutline.setPosition(670 + (selectedShape - 3)*300, 700);
      selectedShapeOutline.setOutlineColor(Color(0, 255, 0));
      mainWindow.draw(selectedShapeOutline);
    }

    for (int i = 0; i < 3; i++){
      int j = i + 3;
      CircleShape possibleShapes(50, j);
      possibleShapes.setPosition(670 + i*300, 700);
      possibleColors.setPosition(680 + i*300, 575);

      possibleColors.setFillColor(Color{allPossibleColors.at(i).at(0), allPossibleColors.at(i).at(1), allPossibleColors.at(i).at(2)});

      mainWindow.draw(permanent);
      mainWindow.draw(possibleColors);
      mainWindow.draw(possibleShapes);

      if (possibleColors.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        if (event.type == sf::Event::MouseButtonPressed) selectedColor = i;
      }
      if (possibleShapes.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
        if (event.type == sf::Event::MouseButtonPressed) selectedShape = j;
      }
    }

    if ((selectedShape == -1) || (selectedColor == -1) || (firstNameTB.getText().compare("") == 0) || (lastNameTB.getText().compare("") == 0)){
        isCompleted.setString("ALL FIELDS REQUIRED BEFORE SUBMITTING");
        isCompleted.setFillColor(Color::Red);
        isCompleted.setCharacterSize(20);
      }
    else{
        isCompleted.setString("CONTINUE:");
        isCompleted.setFillColor(Color::White);
        isCompleted.setCharacterSize(40);
        if (isCompleted.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
          isCompleted.setFillColor(Color::Green);
          if (event.type == sf::Event::MouseButtonPressed){
            string firstName = firstNameTB.getText();
            string lastName = lastNameTB.getText();
            std::replace(firstName.begin(), firstName.end(), ' ', '.');
            std::replace(lastName.begin(), lastName.end(), ' ', '.');

            std::ofstream ofile;
            ofile.open("savedData.txt", std::ios_base::app);
            ofile << "Profile\t" << firstName << "." << lastName << "\t" << 0 << "\t" << 0 << "\t" << 0 << "\t" << 0 << "\t" << selectedColor <<  "\t" << selectedShape;
            return 0;
          }
        }
      }

    mainWindow.draw(isCompleted);


    mainWindow.display();
    }

    return 0;
}

int loadFAQ(Profile& userInformation){

  CircleShape backButton(20, 3);
  backButton.setPosition(75, 75);
  backButton.rotate(270);

  CircleShape exampleBackButton(10, 3);
  exampleBackButton.setPosition(842, 300);
  exampleBackButton.rotate(270);
  exampleBackButton.setFillColor(Color::White);

  CircleShape exampleBackButton2(10);
  exampleBackButton2.setPosition(909, 280);
  exampleBackButton2.setFillColor(Color::White);

  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");

  sf::Text welcomeMessage;
  welcomeMessage.setFont(font);
  welcomeMessage.setPosition(375, 10);
  welcomeMessage.setFillColor(Color::White);
  welcomeMessage.setOutlineThickness(5);
  welcomeMessage.setOutlineColor(Color::Blue);
  welcomeMessage.setCharacterSize(80);
  welcomeMessage.setString("WEEKLY PLANNER FAQ");

  sf::Text answersPrompt;
  answersPrompt.setFont(font);
  answersPrompt.setPosition(45, 100);
  answersPrompt.setFillColor(Color::White);
  answersPrompt.setString("\nA: The Weekly Planner is designed for you to keep track of a weekly set of events of to-do's which reset every Sunday at midnight.\nTo add a task, simply click 'Add Task' on either the week or day planner and fill in the requested information. We will handle\nformatting the task grid and the time remaining!\n\n\nA: Navigation throughout the app is handled by buttons marked as           ,           , or the profile icon. These buttons will change color\nwhen hovered over indicating their function.\n\n\nA: Tasks can be marked as completed on the Day planner page by clicking the bullet point in front of the specific task.\nThis click will be accompanied by a change in color of the bullet point indicating successful completion.\n\n\nA: Leveling up occurs through the completion of tasks and marking them within the application. Every 100 points results in a level up\n(check the progress bar for updates) and points are assigned based on whether tasks are completed on time for 25 points\n(with bonus points for submitting more than 12 hours before due date) or late for 0 points. Higher levels unlock more customizable\noptions.\n\n\nA: The current implementation of OnTrack allows a maximum of 4 concurrent tasks for a given day. If you have more than 4 tasks we \nrecommend deleting a task once it is completed on the individual day planner page. This will free up a task slot and will not remove\nthe points received for task completion.\n\n\nA: 01001011 01101111 01101110 01100001 01101101 01101001 00100000 01000011 01101111 01100100 01100101");
  answersPrompt.setCharacterSize(25);

  sf::Text questionsPrompt;
  questionsPrompt.setFont(font);
  questionsPrompt.setStyle(sf::Text::Underlined);
  questionsPrompt.setPosition(45, 100);
  questionsPrompt.setFillColor(Color::White);
  questionsPrompt.setString("Q: How do I use the Weekly Planner?\n\n\n\n\nQ: How do I navigate through the different pages?\n\n\n\nQ: How do I mark a task as complete?\n\n\n\nQ: How do I level up? How do points work?\n\n\n\n\n\nQ: How can I add more than 4 tasks per day?\n\n\n\n\nQ: I hear there is a really cool GOD MODE Easter Egg...");
  questionsPrompt.setCharacterSize(25);

  while (mainWindow.isOpen()){
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed){
        mainWindow.close();
        return -1;
      }
    }
    mainWindow.clear();

    backButton.setFillColor(Color::White);

    if (backButton.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
      backButton.setFillColor(Color::Green);
      if (event.type == sf::Event::MouseButtonPressed) return (userInformation.theme * 2 + 1);
    }


    mainWindow.draw(welcomeMessage);
    mainWindow.draw(questionsPrompt);
    mainWindow.draw(answersPrompt);
    mainWindow.draw(exampleBackButton);
    mainWindow.draw(backButton);
    mainWindow.draw(exampleBackButton2);
    mainWindow.display();
  }
  return 0;
  
  };

void loadGodMode() {

  RectangleShape basicOutline(sf::Vector2f(windowLength, windowWidth));
  basicOutline.setFillColor(Color{110, 255, 255});

  RectangleShape possibleColors(sf::Vector2f(30, 30));

  RectangleShape timeOutline(sf::Vector2f(245, 75));
  timeOutline.setOutlineColor(Color::Black);
  timeOutline.setOutlineThickness(5);
  timeOutline.setPosition(1300,800);


  RectangleShape progressBarOutline(sf::Vector2f(550, 30));
  progressBarOutline.setOutlineColor(Color::Black);
  progressBarOutline.setOutlineThickness(5);
  progressBarOutline.setPosition(1000, 405);

  RectangleShape progressBar(sf::Vector2f((550), 30));
  progressBar.setFillColor(Color::Blue);
  progressBar.setPosition(1000, 405);

  CircleShape backButton(20, 3);
  backButton.setPosition(50, 60);
  backButton.rotate(270);

  RectangleShape basicAvatar(sf::Vector2f(268, 284));
  basicAvatar.setOutlineColor(Color::Black);
  basicAvatar.setOutlineThickness(8);
  basicAvatar.setPosition(80, 130);

  sf::Image profCarruthers;
  profCarruthers.create(800,800,sf::Color::Yellow);
  profCarruthers.loadFromFile("GodMode2.jpg");

  sf::Texture proftexture;
  proftexture.loadFromImage(profCarruthers);

  sf::Sprite profsprite;
  profsprite.setTexture(proftexture);
  auto profsize = proftexture.getSize();
  profsprite.setOrigin(profsize.x/2, profsize.y/2);

  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  sf::Text progressText;
  progressText.setFont(font);
  progressText.setFillColor(Color::Blue);
  progressText.setString("100 / 100");
  progressText.setCharacterSize(15);
  progressText.setPosition(1250, 445);

  sf::Text digitalClock;
  digitalClock.setFont(font);
  digitalClock.setPosition(1300, 800);
  digitalClock.setFillColor(Color::Black);
  digitalClock.setCharacterSize(60);

  sf::Text profileHeader;
  profileHeader.setFont(font);
  profileHeader.setPosition(450, 22);
  profileHeader.setFillColor(Color::Black);
  profileHeader.setString("Profile Information:");
  profileHeader.setCharacterSize(65);

  sf::Text profileSpecifics;
  string profileInfo = "Name: Jeffrey Carruthers\n\nPoints Earned: 10000000000000\n\nProfile Level: 42\n\nProgress to Next Level:";
  profileSpecifics.setFont(font);
  profileSpecifics.setPosition(500, 115);
  profileSpecifics.setFillColor(Color::Black);
  profileSpecifics.setString(profileInfo);
  profileSpecifics.setCharacterSize(40);

  sf::Text settingsHeader;
  settingsHeader.setFont(font);
  settingsHeader.setPosition(50, 450);
  settingsHeader.setFillColor(Color::Black);
  settingsHeader.setString("Settings and Information:");
  settingsHeader.setCharacterSize(65);

  sf::Text FAQ;
  FAQ.setFont(font);
  FAQ.setPosition(100, 550);
  FAQ.setString("Go to FAQ");
  FAQ.setCharacterSize(40);

  sf::Text changeTheme;
  changeTheme.setFont(font);
  changeTheme.setPosition(100, 625);
  changeTheme.setString("Select Theme:\n\nSelect Avatar Shape:\n\nSelect Avatar Color:");
  changeTheme.setCharacterSize(40);
  changeTheme.setFillColor(Color::Black);

  sf::Text defaultLabel;
  defaultLabel.setFont(font);
  defaultLabel.setPosition(425, 625);
  defaultLabel.setString("Default");
  defaultLabel.setCharacterSize(40);
  defaultLabel.setFillColor(Color::Black);

  sf::Text postItLabel;
  postItLabel.setFont(font);
  postItLabel.setPosition(671, 625);
  postItLabel.setString("Post-It");
  postItLabel.setCharacterSize(40);

  sf::Text darkLabel;
  darkLabel.setFont(font);
  darkLabel.setPosition(900, 625);
  darkLabel.setString("Dark");
  darkLabel.setCharacterSize(40);

  sf::Text godMode;
  godMode.setFont(font);
  godMode.setCharacterSize(25);
  godMode.setString("WELCOME TO GOD MODE");
  godMode.setFillColor(Color::Black);
  godMode.setPosition(66, 90);

  vector<sf::Vector2f> savedSpritePositions;


  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed){

        mainWindow.close();
        return;
      }
    }

    std::time_t stdTime = std::time(NULL);  // get new time
    std::tm stdNow = *std::localtime(&stdTime);

    mainWindow.clear();
    mainWindow.draw(basicOutline);

    // format digital time on clock
    string digitalTime = std::asctime(&stdNow);
    digitalTime = digitalTime.substr(11, 8);
    digitalClock.setString(digitalTime);

    backButton.setFillColor(Color::Black);
    if (backButton.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
      backButton.setFillColor(Color::Green);
    }

    FAQ.setFillColor(Color::Black);
    if (FAQ.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
      FAQ.setFillColor(Color::Green);
    }

    defaultLabel.setFillColor(Color::Black);
    if (defaultLabel.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
      defaultLabel.setFillColor(Color::Green);
    }
    postItLabel.setFillColor(Color::Black);
    if (postItLabel.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
      postItLabel.setFillColor(Color::Green);
    }
    darkLabel.setFillColor(Color::Black);
    if (darkLabel.getGlobalBounds().contains(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)))){
      darkLabel.setFillColor(Color::Green);
    }



    for (int i = 0; i < 6; i++){
      int j = i + 3;
      CircleShape possibleShapes(30, j);
      possibleShapes.setPosition(505 + i*100, 810);
      possibleColors.setPosition(520 + i*100, 728);

      possibleColors.setFillColor(Color{allPossibleColors.at(i).at(0), allPossibleColors.at(i).at(1), allPossibleColors.at(i).at(2)});
      possibleShapes.setFillColor(Color::Black);
      mainWindow.draw(possibleShapes);
      mainWindow.draw(possibleColors);
    }

    // draw clock componentse
    mainWindow.draw(backButton);
    mainWindow.draw(timeOutline);
    mainWindow.draw(digitalClock);
    mainWindow.draw(profileHeader);
    mainWindow.draw(profileSpecifics);
    mainWindow.draw(settingsHeader);
    mainWindow.draw(progressBarOutline);
    mainWindow.draw(progressBar);
    mainWindow.draw(progressText);
    mainWindow.draw(FAQ);
    mainWindow.draw(changeTheme);
    mainWindow.draw(defaultLabel);
    mainWindow.draw(postItLabel);
    mainWindow.draw(darkLabel);
    mainWindow.draw(basicAvatar);
    for (int i = 0; i < 2; i++){
      for (int j = 0; j < 2; j++){
        profsprite.setPosition(148 + i*134,200+j*142);
        mainWindow.draw(profsprite);
      }
    }
    mainWindow.draw(godMode);

    if ((event.type == sf::Event::MouseButtonPressed) && savedSpritePositions.size() < 50) savedSpritePositions.push_back(mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow)));
    
    for (int i = 0; i < savedSpritePositions.size(); i++){
      profsprite.setPosition(savedSpritePositions.at(i));
      mainWindow.draw(profsprite);
    }
    mainWindow.display();
  }
  return;
}



int initialStartUp() {
  bool isNewUser = false;
  vector<string> profileLine;
  vector<vector<Task>> allTaskData(7);
  string dataLine;
  vector<string> daysOfWeek{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

  vector<std::function<int(Profile&, vector<vector<Task>>&)>> vectorOfFunc{loadDefaultMainPlanner, loadDefaultProfile, loadPostItMainPlanner, loadPostItProfile, loadDarkMainPlanner, loadDarkProfile};
  vector<std::function<int(Profile&, vector<vector<Task>>&, string)>> vectorOfDayFunc{loadDefaultDayPlanner, loadPostItDayPlanner, loadDarkDayPlanner};

  std::ifstream ifile("savedData.txt");

  if (ifile.peek() == std::ifstream::traits_type::eof()) isNewUser = true;

  int closedFirstTime = 0;

  if (isNewUser) closedFirstTime = loadFirstTimeUser();

  if (closedFirstTime == -1) return 0;


  std::ifstream dataFile("savedData.txt");
    while (std::getline(dataFile, dataLine)) {
      int lengthStr = dataLine.length() + 1;
      char lineAsCharArr[lengthStr];
      strcpy(lineAsCharArr, dataLine.c_str());

      if (dataLine.substr(0,4).compare("Prof") == 0){
        char *token = strtok(lineAsCharArr, "\t");
        while (token != NULL) {
          profileLine.push_back(token);
          token = strtok(NULL, "\t");
        }
      }
      // FILL IN ONCE TASK CLASS IS SET UP
      if (dataLine.substr(0,4).compare("Task") == 0) {
        char *token = strtok(lineAsCharArr, "\t");
        vector<string> taskLine;
        while (token != NULL) {
          taskLine.push_back(token);
          token = strtok(NULL, "\t");  
        }
        std::replace(taskLine.at(1).begin(), taskLine.at(1).end(), '.', ' ');
        std::replace(taskLine.at(2).begin(), taskLine.at(2).end(), '.', ' ');
        Task nTask = Task(taskLine.at(1), taskLine.at(2), stoi(taskLine.at(3)), stoi(taskLine.at(4)), stoi(taskLine.at(5)), bool(stoi(taskLine.at(6))), stoi(taskLine.at(7)));
        allTaskData.at(stoi(taskLine.at(3))).push_back(nTask);
      }
    }

  std::replace(profileLine.at(1).begin(), profileLine.at(1).end(), '.', ' ');
  Profile allUserInformation = Profile(profileLine.at(1), stoi(profileLine.at(2)), stoi(profileLine.at(3)), stoi(profileLine.at(4)), stoi(profileLine.at(5)), stoi(profileLine.at(6)), stoi(profileLine.at(7)));
  
  int nextState = vectorOfFunc.at(allUserInformation.theme * 2)(allUserInformation, allTaskData);
  while (nextState >= 0){
    if (nextState < 10) nextState = vectorOfFunc.at(nextState)(allUserInformation, allTaskData);
    else if (nextState < 200) nextState = vectorOfDayFunc.at(0)(allUserInformation, allTaskData, daysOfWeek.at(nextState%100));
    else if (nextState < 300) nextState = vectorOfDayFunc.at(1)(allUserInformation, allTaskData, daysOfWeek.at(nextState%100));
    else if (nextState < 400) nextState = vectorOfDayFunc.at(2)(allUserInformation, allTaskData, daysOfWeek.at(nextState%100));
    else if (nextState == 1000) nextState = loadFAQ(allUserInformation);
    else if (nextState == 2000) nextState = loadAddTask(allUserInformation, allTaskData);
  }
  std::ofstream ofile;
  ofile.open("savedData.txt", std::ios_base::trunc);
  string nameAsInput = allUserInformation.name;
  replace(nameAsInput.begin(), nameAsInput.end(), ' ', '.');
  ofile << "Profile\t" << nameAsInput << "\t" << allUserInformation.pointsEarned << "\t" << allUserInformation.level << "\t" << allUserInformation.progress << "\t" << allUserInformation.theme << "\t" << allUserInformation.avatarColor <<  "\t" << allUserInformation.avatarShape << "\n";
  for (int i = 0; i < 7; i++){
    for (int j = 0; j < allTaskData.at(i).size(); j++){
        Task cTask = allTaskData.at(i).at(j);
        replace(cTask.taskName.begin(), cTask.taskName.end(), ' ', '.');
        replace(cTask.description.begin(), cTask.description.end(), ' ', '.');
        ofile << "Task\t" << cTask.taskName << "\t" << cTask.description  << "\t" << cTask.dueDate << "\t" << cTask.dueTime << "\t" << cTask.AmPm << "\t" << cTask.complete << "\t" << cTask.pointsgiven << "\n";
    }
  }

  time_t epochtime = time(NULL);
  std::tm etime = *localtime(&epochtime);
  string currentDayStr = (ctime(&epochtime));
  currentDayStr = currentDayStr.substr(0,3);
  ofile << to_string(epochtime) <<"\t" << currentDayStr << "\n";

  if (nextState == -2){
    loadGodMode();
  }

  return 0;
}
