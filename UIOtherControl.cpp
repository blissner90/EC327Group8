#include"UIOtherControl.h"

// loads added task to planner and place it accordingly based on deadline
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

// loads set up screen if first time user
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

// loads FAQ screen
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

 // loads easter-egg screen
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