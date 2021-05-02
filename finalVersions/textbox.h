// Copyright 2021 Matthew Collins matcoll@bu.edu
// Copyright 2021 Benjamin Lissner blissner@bu.edu
// Copyright 2021 Tiffany Lukmantara tiffaluk@bu.edu
// Copyright 2021 Juan Luis Ugarte jugarte@bu.edu

// Textbox class to allow user input into the OnTrack application

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

// mapping keys to variables for use through script
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27
#define TAB_KEY 9

class Textbox {
    public:
        Textbox() { } // Constructor for creating a textbox

        Textbox(int size, sf::Color color, bool isSelected) { // Defines the inputs for the textbox
            textbox.setCharacterSize(size);
            textbox.setFillColor(color);
            if (isSelected) {
                textbox.setString("_");  // indicator when selected
            }
            else {
                textbox.setString("");  // blank when not selected
            }
        }

        void setFont(sf::Font &font){  // sets the font of the textboxx
            textbox.setFont(font);
        }

        void setPosition(sf::Vector2f pos) {  // sets the position of the textbox
            textbox.setPosition(pos);
        }
        void setAsLimit(bool truth, int lim) {  // sets a character limit to textbox
            hasLimit = truth;
            limit = lim-1;
        }

        void setAsSelected(bool sel) {  // update the text as input is typed
            isSelected = sel;
            if(!sel) {
                std::string t = text.str();
                std::string newT = "";
                for (int i = 0; i < t.length(); i++) {
                    newT += t[i];
                }
                textbox.setString(newT);
            }
            else {
                textbox.setString(text.str() + "_");
            }
        }

        std::string getText() {  // allows text access
            return text.str();
        }

        void drawTo(sf::RenderWindow &window) {  // draws textbox to window
            window.draw(textbox);
        }

        void typedInput(sf::Event input) {  // translates the typed input into text using unicode codes
            if(isSelected) {
                int charTyped = input.text.unicode;
                if(charTyped < 128) {
                    if(hasLimit) {
                        if(text.str().length() <= limit) { 
                            inputLogic(charTyped);
                        }
                        else if(text.str().length() > limit && charTyped == DELETE_KEY) {  // special case: delete key
                            deleteLastChar();
                        }
                    }
                    else {
                        inputLogic(charTyped);
                    }
                }
            }
        }

        sf::RectangleShape setTextField(){  // creates and formats the region of typing
            sf::Vector2f pos = textbox.getPosition();
            textfield.setPosition(pos);
            textfield.setSize(sf::Vector2f(200,40));
            textfield.setFillColor(sf::Color::Black);

            textfield.setOutlineThickness(5);
            textfield.setOutlineColor(sf::Color::White);
            return textfield;
        }

        bool isMouseOver(sf::RenderWindow &window, sf::RectangleShape textboxrect){  // checks whether mouse is hovering over textbox when clicked
            textfield = textboxrect;
            float mouseX = sf::Mouse::getPosition(window).x;
            float mouseY = sf::Mouse::getPosition(window).y;

            float fieldPosX = textfield.getPosition().x;
            float fieldPosY = textfield.getPosition().y;

            float fieldxPosWidth = textfield.getPosition().x + textfield.getLocalBounds().width;
            float fieldyPosHeight = textfield.getPosition().y + textfield.getLocalBounds().height;

            if (mouseX < fieldxPosWidth && mouseX > fieldPosX && mouseY < fieldyPosHeight && mouseY > fieldPosY && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                return true;
            }
            return false;
        }

        
    private:  // class attributes for the textbox class
        sf::Text textbox;
        std::ostringstream text;
        sf::RectangleShape textfield;
        bool isSelected = false;
        bool hasLimit = false;
        int limit;


        void inputLogic(int charTyped) { // Get input from the user and formats the output
            if(charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY && charTyped != TAB_KEY){  // precents user from typing tab, which messes up savedData.txt
                text << static_cast<char>(charTyped);
            }
            else if (charTyped == DELETE_KEY) {  // special case, delete key needs to delete last char typed
                if (text.str().length() > 0) {
                    deleteLastChar();
                }
            }
            textbox.setString(text.str() + "_");
        }

        void deleteLastChar() {  // update string to remove last char if delete key (backspace) is typed
            std::string t = text.str();
            std::string newT = "";
            for(int i = 0; i < t.length() - 1; i++) {
                newT += t[i];
            }
            text.str("");
            text << newT;

            textbox.setString(text.str());
        }
};