
#include <iostream>
#include <vector>
#include <ctime>
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

// global variables used across multiple functions for window size
int windowLength = 1600;
int windowWidth = 900;
RenderWindow mainWindow(sf::VideoMode(windowLength, windowWidth),
                          "Final Project, Main Window");


// profile class to store the profile data

class Profile {
  public:
    string name;
    int pointsEarned;
    int level;
    int progress;

    Profile(string proName, int proPointsEarned, int proLevel, int proProgress){
      this->name = proName;
      this->pointsEarned = proPointsEarned;
      this->level = proLevel;
      this->progress = proProgress;
    }
};

// creation of default profile/settings page
void loadDefaultProfile(Profile userInformation, vector<Task> taskInformation){

  RectangleShape basicOutline(sf::Vector2f(windowLength, windowWidth));

  RectangleShape timeOutline(sf::Vector2f(245, 75));
  timeOutline.setOutlineColor(Color::Black);
  timeOutline.setOutlineThickness(5);
  timeOutline.setPosition(1300,800);

  RectangleShape basicAvatar(sf::Vector2f(300, 300));
  basicAvatar.setFillColor(Color::Red);
  basicAvatar.setOutlineColor(Color::Black);
  basicAvatar.setOutlineThickness(8);
  basicAvatar.setPosition(50, 100);

  CircleShape avatarExample(100);
  avatarExample.setPosition(100, 150);
  avatarExample.setFillColor(Color::Black);


  // format and scale digital representaion of time
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  sf::Text digitalClock;
  digitalClock.setFont(font);
  digitalClock.setPosition(1300, 800);
  digitalClock.setFillColor(Color::Black);
  digitalClock.setCharacterSize(60);

  sf::Text profileHeader;
  profileHeader.setFont(font);
  profileHeader.setPosition(450, 80);
  profileHeader.setFillColor(Color::Black);
  profileHeader.setString("Profile Information:");
  profileHeader.setCharacterSize(65);

  sf::Text profileSpecifics;
  string profileInfo = "Name: " + userInformation.name + "\n\nPoints Earned: "  + to_string(userInformation.pointsEarned) + "\n\nProfile Level: " + to_string(userInformation.level) + "\n\nProgress to Next Level:";
  profileSpecifics.setFont(font);
  profileSpecifics.setPosition(500, 165);
  profileSpecifics.setFillColor(Color::Black);
  profileSpecifics.setString(profileInfo);
  profileSpecifics.setCharacterSize(40);

  sf::Text settingsHeader;
  settingsHeader.setFont(font);
  settingsHeader.setPosition(50, 500);
  settingsHeader.setFillColor(Color::Black);
  settingsHeader.setString("Settings and Information:");
  settingsHeader.setCharacterSize(65);


  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        mainWindow.close();
    }

    std::time_t stdTime = std::time(NULL);  // get new time
    std::tm stdNow = *std::localtime(&stdTime);

    mainWindow.clear();

    // format digital time on clock
    string digitalTime = std::asctime(&stdNow);
    digitalTime = digitalTime.substr(11, 8);
    digitalClock.setString(digitalTime);

    // draw clock componentse
    mainWindow.draw(basicOutline);
    mainWindow.draw(basicAvatar);
    mainWindow.draw(avatarExample);
    mainWindow.draw(timeOutline);
    mainWindow.draw(digitalClock);
    mainWindow.draw(profileHeader);
    mainWindow.draw(profileSpecifics);
    mainWindow.draw(settingsHeader);

    mainWindow.display();
  }
}

// creation of default main planner page
void loadDefaultMainPlanner(Profile userInformation, vector<Task> taskInformation) {

  RectangleShape basicOutline(sf::Vector2f(windowLength, windowWidth));

  RectangleShape timeOutline(sf::Vector2f(245, 75));
  timeOutline.setOutlineColor(Color::Black);
  timeOutline.setOutlineThickness(5);
  timeOutline.setPosition(1200,100);

  RectangleShape basicAvatar(sf::Vector2f(75,75));
  basicAvatar.setFillColor(Color::Red);
  basicAvatar.setOutlineColor(Color::Black);
  basicAvatar.setOutlineThickness(5);
  basicAvatar.setPosition(1500, 100);

  CircleShape avatarExample(25);
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
  headerUser.setPosition(100, 100);
  headerUser.setFillColor(Color::Black);
  headerUser.setCharacterSize(60);
  string identifier = userInformation.name + "'s Weekly Planner";
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
  addTask.setFillColor(Color::Black);
  addTask.setCharacterSize(50);
  string addTaskStr = "* Add Task";
  addTask.setString(addTaskStr);


  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed)

        mainWindow.close();
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
    for (int i = 0; i < 6; i++){
      verticalLine.setPosition(vertXStart + i*200, 200);
      tempButtonDays.setPosition(vertXStart -20 + i* 200, 210);
      mainWindow.draw(verticalLine);
      mainWindow.draw(tempButtonDays);
    }
    tempButtonDays.setPosition(1480, 210);
    mainWindow.draw(tempButtonDays);
    mainWindow.draw(timeOutline);
    mainWindow.draw(basicAvatar);
    mainWindow.draw(avatarExample);
    mainWindow.draw(digitalClock);
    mainWindow.draw(headerUser);
    mainWindow.draw(daysOfWeek);
    mainWindow.draw(addTask);
    mainWindow.display();
  }
}

// creation of default individual day planner
void loadDefaultDayPlanner(Profile userInformation, vector<Task> taskInformation){

  RectangleShape basicOutline(sf::Vector2f(windowLength, windowWidth));

  RectangleShape timeOutline(sf::Vector2f(245, 75));
  timeOutline.setOutlineColor(Color::Black);
  timeOutline.setOutlineThickness(5);
  timeOutline.setPosition(65,825);

  RectangleShape basicAvatar(sf::Vector2f(75,75));
  basicAvatar.setFillColor(Color::Red);
  basicAvatar.setOutlineColor(Color::Black);
  basicAvatar.setOutlineThickness(5);
  basicAvatar.setPosition(1400, 113);

  CircleShape avatarExample(25);
  avatarExample.setPosition(1413, 126);
  avatarExample.setFillColor(Color::Black);

  RectangleShape mainBox(sf::Vector2f(1400, 700));
  mainBox.setOutlineColor(Color::Blue);
  mainBox.setOutlineThickness(8);
  mainBox.setPosition(100, 100);

  RectangleShape horizontalLine(sf::Vector2f(1400, 8));
  horizontalLine.setFillColor(Color::Blue);
  horizontalLine.setPosition(100, 200);


  CircleShape tempButtonDays(20, 3);
  tempButtonDays.setFillColor(Color::Blue);
  tempButtonDays.setPosition(140, 170);
  tempButtonDays.rotate(270);


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
  headerUser.setPosition(210, 113);
  headerUser.setFillColor(Color::Black);
  headerUser.setCharacterSize(60);
  string identifier = userInformation.name + "'s Wednesday";
  headerUser.setString(identifier);


  sf::Text addTask;
  addTask.setFont(font);
  addTask.setPosition(1300, 825);
  addTask.setFillColor(Color::Black);
  addTask.setCharacterSize(50);
  string addTaskStr = "* Add Task";
  addTask.setString(addTaskStr);


  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed)

        mainWindow.close();
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
    mainWindow.draw(tempButtonDays);
    mainWindow.draw(timeOutline);
    mainWindow.draw(basicAvatar);
    mainWindow.draw(avatarExample);
    mainWindow.draw(digitalClock);
    mainWindow.draw(headerUser);
    mainWindow.draw(addTask);
    mainWindow.display();
  }
}

void loadPastelProfile(Profile userInformation, vector<Task> taskInformation);

void loadPastelMainPlanner(Profile userInformation, vector<Task> taskInformation) {

  vector<vector<uint8_t> > pastelColors = {{255, 209, 161}, {110, 255, 255},{255, 34, 145}, {0, 213, 106}};
  vector<vector<uint8_t> > pastelHeaderColors = {{255, 184, 110}, {34, 255, 255}, {213, 0, 107}, {0, 162, 81}};

  vector<vector<uint8_t> > pastelColorsBot = {{255, 182, 218}, {0, 213, 0},{9,9,255}};
  vector<vector<uint8_t> > pastelHeaderColorsBot = {{255, 131, 192}, {0,162,0}, {0,0,213}};



  RectangleShape basicOutline(sf::Vector2f(windowLength, windowWidth));
  basicOutline.setFillColor(Color(255, 255, 186));

  RectangleShape headerOutline(sf::Vector2f(1000, 80));
  headerOutline.setFillColor(Color{186, 186, 255});
  headerOutline.setPosition(300,100);

  RectangleShape timeOutline(sf::Vector2f(245, 75));
  timeOutline.setFillColor(Color(186, 186, 255));
  timeOutline.setPosition(65,825);

  RectangleShape basicAvatar(sf::Vector2f(75,75));
  basicAvatar.setFillColor(Color::Red);
  basicAvatar.setOutlineColor(Color::Black);
  basicAvatar.setOutlineThickness(5);
  basicAvatar.setPosition(1400, 100);

  CircleShape avatarExample(25);
  avatarExample.setPosition(1413, 113);
  avatarExample.setFillColor(Color::Black);

  RectangleShape sunStickyNote(sf::Vector2f(275, 275));

  RectangleShape sunStickyNoteHeader(sf::Vector2f(275, 75));


  CircleShape tempButtonDays(8);
  tempButtonDays.setFillColor(Color::Black);

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
  headerUser.setPosition(300, 100);
  headerUser.setFillColor(Color::Black);
  headerUser.setCharacterSize(60);
  string identifier = userInformation.name + "'s Weekly Planner";
  headerUser.setString(identifier);

  sf::Text daysOfWeek;
  daysOfWeek.setFont(font);
  daysOfWeek.setPosition(195, 220);
  daysOfWeek.setFillColor(Color::Black);
  daysOfWeek.setCharacterSize(60);
  string days = " Sun                  Mon               Tues                Wed\n\n\n\n\n              Thurs                Fri                   Sat";
  daysOfWeek.setString(days);

  sf::Text addTask;
  addTask.setFont(font);
  addTask.setPosition(1325, 825);
  addTask.setFillColor(Color::Black);
  addTask.setCharacterSize(50);
  string addTaskStr = "* Add Task";
  addTask.setString(addTaskStr);


  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed)

        mainWindow.close();
    }

    std::time_t stdTime = std::time(NULL);  // get new time
    std::tm stdNow = *std::localtime(&stdTime);

    mainWindow.clear();

    // format digital time on clock
    string digitalTime = std::asctime(&stdNow);
    digitalTime = digitalTime.substr(11, 8);
    digitalClock.setString(digitalTime);
    mainWindow.draw(basicOutline);
    for (int i = 0; i < 4; i++){
      sunStickyNote.setPosition(130 + i*350, 230);
      vector<uint8_t> color = pastelColors.at(i);
      sunStickyNote.setFillColor(Color{color.at(0), color.at(1), color.at(2)});
      vector<uint8_t> hColor = pastelHeaderColors.at(i);
      sunStickyNoteHeader.setPosition(130 + i*350, 230);
      sunStickyNoteHeader.setFillColor(Color{hColor.at(0), hColor.at(1), hColor.at(2)});
      tempButtonDays.setPosition(140 + i*350, 240);
      mainWindow.draw(sunStickyNote);
      mainWindow.draw(sunStickyNoteHeader);
      mainWindow.draw(tempButtonDays);
    }

    for (int i = 0; i < 3; i++){
      sunStickyNote.setPosition(330 + i*350, 575);
      vector<uint8_t> color = pastelColorsBot.at(i);
      sunStickyNote.setFillColor(Color{color.at(0), color.at(1), color.at(2)});
      vector<uint8_t> hColor = pastelHeaderColorsBot.at(i);
      sunStickyNoteHeader.setPosition(330 + i*350, 575);
      sunStickyNoteHeader.setFillColor(Color{hColor.at(0), hColor.at(1), hColor.at(2)});
      tempButtonDays.setPosition(340 + i*350, 585);
      mainWindow.draw(sunStickyNote);
      mainWindow.draw(sunStickyNoteHeader);
      mainWindow.draw(tempButtonDays);
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
};

void loadPastelDayPlanner(Profile userInformation, vector<Task> taskInformation){

  RectangleShape basicOutline(sf::Vector2f(windowLength, windowWidth));
  basicOutline.setFillColor(Color(255, 255, 186));

  RectangleShape timeOutline(sf::Vector2f(245, 75));
  timeOutline.setFillColor(Color(186, 186, 255));
  timeOutline.setPosition(65,825);

  RectangleShape basicAvatar(sf::Vector2f(75,75));
  basicAvatar.setFillColor(Color::Red);
  basicAvatar.setOutlineColor(Color::Black);
  basicAvatar.setOutlineThickness(5);
  basicAvatar.setPosition(1400, 113);

  CircleShape avatarExample(25);
  avatarExample.setPosition(1413, 126);
  avatarExample.setFillColor(Color::Black);

  RectangleShape mainBox(sf::Vector2f(1400, 600));
  mainBox.setFillColor(Color{255,34,145});
  mainBox.setPosition(100, 200);

  RectangleShape headerBox(sf::Vector2f(1400, 100));
  headerBox.setFillColor(Color{213,0,107});
  headerBox.setPosition(100, 100);

  CircleShape tempButtonDays(20, 3);
  tempButtonDays.setFillColor(Color::Black);
  tempButtonDays.setPosition(140, 170);
  tempButtonDays.rotate(270);


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
  headerUser.setPosition(210, 113);
  headerUser.setFillColor(Color::Black);
  headerUser.setCharacterSize(60);
  string identifier = userInformation.name + "'s Wednesday";
  headerUser.setString(identifier);


  sf::Text addTask;
  addTask.setFont(font);
  addTask.setPosition(1300, 825);
  addTask.setFillColor(Color::Black);
  addTask.setCharacterSize(50);
  string addTaskStr = "* Add Task";
  addTask.setString(addTaskStr);


  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed)

        mainWindow.close();
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
    mainWindow.draw(headerBox);
    mainWindow.draw(tempButtonDays);
    mainWindow.draw(timeOutline);
    mainWindow.draw(basicAvatar);
    mainWindow.draw(avatarExample);
    mainWindow.draw(digitalClock);
    mainWindow.draw(headerUser);
    mainWindow.draw(addTask);
    mainWindow.display();
  }
}

void loadNoteProfile(Profile userInformation, vector<Task> taskInformation);

void loadNoteMainPlanner(Profile userInformation, vector<Task> taskInformation){

  RectangleShape basicOutline(sf::Vector2f(windowLength, windowWidth));

  CircleShape blackRing(20);
  blackRing.setOutlineColor(Color::Black);
  blackRing.setOutlineThickness(8);

  CircleShape whiteRing(30);
  whiteRing.setFillColor(Color::White);


  RectangleShape basicAvatar(sf::Vector2f(75,75));
  basicAvatar.setFillColor(Color::Red);
  basicAvatar.setOutlineColor(Color::Black);
  basicAvatar.setOutlineThickness(5);
  basicAvatar.setPosition(1500, 100);

  CircleShape avatarExample(25);
  avatarExample.setPosition(1513, 113);
  avatarExample.setFillColor(Color::Black);



  RectangleShape horizontalLine(sf::Vector2f(1400, 8));
  horizontalLine.setFillColor(Color::Blue);
  horizontalLine.setPosition(100, 300);


  CircleShape tempButtonDays(8);
  tempButtonDays.setFillColor(Color::Blue);

  // format and scale digital representaion of time
  sf::Text digitalClock;
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  digitalClock.setFont(font);
  digitalClock.setPosition(1250, 210);
  digitalClock.setFillColor(Color{128,128,128});
  digitalClock.setCharacterSize(60);


  sf::Text headerUser;
  headerUser.setFont(font);
  headerUser.setPosition(125, 210);
  headerUser.setFillColor(Color{128,128,128});
  headerUser.setCharacterSize(60);
  string identifier = userInformation.name + "'s Weekly Planner";
  headerUser.setString(identifier);

  sf::Text daysOfWeek;
  daysOfWeek.setFont(font);
  daysOfWeek.setPosition(150, 400);
  daysOfWeek.setFillColor(Color::Blue);
  daysOfWeek.setCharacterSize(60);
  string days = "Sun      Mon      Tues     Wed    Thurs      Fri        Sat";
  daysOfWeek.setString(days);

  sf::Text addTask;
  addTask.setFont(font);
  addTask.setPosition(1300, 825);
  addTask.setFillColor(Color::Black);
  addTask.setCharacterSize(50);
  string addTaskStr = "* Add Task";
  addTask.setString(addTaskStr);


  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed)

        mainWindow.close();
    }

    std::time_t stdTime = std::time(NULL);  // get new time
    std::tm stdNow = *std::localtime(&stdTime);

    mainWindow.clear();

    // format digital time on clock
    string digitalTime = std::asctime(&stdNow);
    digitalTime = digitalTime.substr(11, 8);
    digitalClock.setString(digitalTime);
    mainWindow.draw(basicOutline);
    mainWindow.draw(horizontalLine);

    for (int i = 0; i < 35; i++){
      blackRing.setPosition(100 + i*40, 110);
      whiteRing.setPosition(110 + i*40, 102);
      mainWindow.draw(blackRing);
      mainWindow.draw(whiteRing);

    }
    for (int i = 0; i < 6; i++){
      tempButtonDays.setPosition(300 -20 + i* 200, 210);
      mainWindow.draw(tempButtonDays);
    }
    tempButtonDays.setPosition(1480, 210);
    mainWindow.draw(tempButtonDays);
    mainWindow.draw(basicAvatar);
    mainWindow.draw(avatarExample);
    mainWindow.draw(digitalClock);
    mainWindow.draw(headerUser);
    mainWindow.draw(daysOfWeek);
    mainWindow.draw(addTask);
    mainWindow.display();
  }
}

void loadNoteDayPlanner(Profile userInformation, vector<Task> taskInformation);

//NEED TO  ACTUALLY GET DATA FROM PROMPT SCREEN AND DATA COLLECTION
void loadFirstTimeUser() {
  // Defining Textbox Code
  sf::Font font; 
  font.loadFromFile("fonts/NewYork.ttf");
  Textbox firstName(30,sf::Color::Black, false);
  firstName.setFont(font);
  firstName.setLimit(true,10);
  firstName.setPosition({100, 100});
  sf::RectangleShape textfield = firstName.setTextField(); // Shape of textbox field follows where the firstName position is

  // Setting up window
  RectangleShape basicOutline(sf::Vector2f(windowLength, windowWidth));
  basicOutline.setFillColor(Color(255, 255, 255));

  // Setting up header
  sf::Text header; 
  header.setFont(font);
  header.setPosition(400, 20);
  header.setFillColor(Color::Black);
  header.setCharacterSize(50);
  string identifier = "Please enter your first and last name";
  header.setString(identifier);

  std::ofstream ofile;
  ofile.open("savedData.txt", std::ios_base::app);
  ofile << "Profile\t\t";
  // ofile << "Ben.Bartholemew.Lissner" << "\t\t" << 15 << "\t\t" << 1 << "\t\t" << 15 << "\n";  // NOTICE FORMAT, HAVE TO ADD A . INSTEAD OF A SPACE FOR STRTOK TO WORK
  
  while (mainWindow.isOpen()) {
    // close window if exit button is clicked
    sf::Event event;

    if (firstName.isMouseOver(mainWindow, textfield)){ //Only can select the textbox if within region
      firstName.setSelected(true);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){  //Deselect but it is broken if there is no text
      firstName.setSelected(false);
    }

    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        mainWindow.close();
      if (event.type == sf::Event::TextEntered)
        firstName.typedOn(event); // Allows user to type
    }
    mainWindow.clear();
    mainWindow.draw(basicOutline);
    mainWindow.draw(header);
    mainWindow.draw(textfield); // Displays textbox field
    firstName.drawTo(mainWindow); // Displays the Textbox
    mainWindow.display();
  }
  ofile << firstName.getText();
  ofile << "\n";
  ofile.close();
}

void loadFAQ(){
  
  };




void initialStartUp() {

  bool isNewUser = false;
  vector<string> profileLine;
  vector<Task> allTaskData;
  string dataLine;

  std::ifstream ifile("savedData.txt");

  if (ifile.peek() == std::ifstream::traits_type::eof()) isNewUser = true;


  if (isNewUser) loadFirstTimeUser();

  std::ifstream dataFile("savedData.txt");
    while (dataFile >> dataLine) {
      int lengthStr = dataLine.length() + 1;
      char lineAsCharArr[lengthStr];
      strcpy(lineAsCharArr, dataLine.c_str());

      if (dataLine.substr(0,4).compare("Prof")){
        char *token = strtok(lineAsCharArr, "\t\t");
        while (token != NULL) {
          profileLine.push_back(token);
          token = strtok(NULL, "\t\t");
        }
      }
      // FILL IN ONCE TASK CLASS IS SET UP
      else if (dataLine.substr(0,4).compare("Task")) {
      }
  }
  replace(profileLine.at(0).begin(), profileLine.at(0).end(), '.', ' ');
  Profile allUserInformation = Profile(profileLine.at(0), stoi(profileLine.at(1)), stoi(profileLine.at(2)), stoi(profileLine.at(3)));
  loadFirstTimeUser(); // (allUserInformation, allTaskData);

}





int main() {
  initialStartUp();
  return 0;
}
