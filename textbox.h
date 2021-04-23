#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
    public:
        Textbox() { } // Constructor for creating a textbox

        Textbox(int size, sf::Color color, bool isSelected) { // Defines the inputs for the textbox
            textbox.setCharacterSize(size);
            textbox.setFillColor(color);
            if (isSelected) {
                textbox.setString("_");
            }
            else {
                textbox.setString("");
            }
        }

        void setFont(sf::Font &font){
            textbox.setFont(font);
        }

        void setPosition(sf::Vector2f pos) {
            textbox.setPosition(pos);
        }
        void setAsLimit(bool truth, int lim) {
            hasLimit = truth;
            limit = lim-1;
        }

        void setAsSelected(bool sel) {
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

        std::string getText() {
            return text.str();
        }

        void drawTo(sf::RenderWindow &window) {
            window.draw(textbox);
        }

        void typedInput(sf::Event input) {
            if(isSelected) {
                int charTyped = input.text.unicode;
                if(charTyped < 128) {
                    if(hasLimit) {
                        if(text.str().length() <= limit) {
                            inputLogic(charTyped);
                        }
                        else if(text.str().length() > limit && charTyped == DELETE_KEY) {
                            deleteLastChar();
                        }
                    }
                    else {
                        inputLogic(charTyped);
                    }
                }
            }
        }

        sf::RectangleShape setTextField(){
            sf::Vector2f pos = textbox.getPosition();
            textfield.setPosition(pos);
            textfield.setSize(sf::Vector2f(200,40));
            textfield.setFillColor(sf::Color::White);

            textfield.setOutlineThickness(5);
            textfield.setOutlineColor(sf::Color::Black);
            return textfield;
        }

        bool isMouseOver(sf::RenderWindow &window, sf::RectangleShape textboxrect){
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
            // else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            //     return false;
            // }
            return false;
        }

        
    private:
        sf::Text textbox;
        std::ostringstream text;
        sf::RectangleShape textfield;
        bool isSelected = false;
        bool hasLimit = false;
        int limit;


        void inputLogic(int charTyped) { // Get input from the user
            if(charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY){
                text << static_cast<char>(charTyped);
            }
            else if (charTyped == DELETE_KEY) {
                if (text.str().length() > 0) {
                    deleteLastChar();
                }
            }
            textbox.setString(text.str() + "_");
        }

        void deleteLastChar() {
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