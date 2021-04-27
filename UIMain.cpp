#include"UIMain.h"

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

// creation of post-it themed main planner page
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
}

// creation of dark themed main planner page
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