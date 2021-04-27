#include"UIProfile.h"

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

// creation of post-it themed profile/settings page
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

// creation of dark themed profile/settings page
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