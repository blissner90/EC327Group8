#include"UIDay.h"

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