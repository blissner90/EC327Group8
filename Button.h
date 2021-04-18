#ifndef BUTTON_H
#define BUTTON_H

#include<iostream>
#include<ctime>
#include<sstream>

#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>



class Button:public sf::Drawable{
	{
		private:
			enum stateButton{idleButton = 0, hoverButton, activeButton};

			sf::RectangleShape shape;
			// sf::Font* font;
			sf::Text text;

			sf::Color idleColor;
			sf::Color hoverColor;
			sf::Color activeColor;

		public:
			Button(float x, float y, float width, float height, std::string text, 
				sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
			~Button();


		//Methods
		void drawButton(sf::RenderTarget& target, sf::RenderStates states) const;
		void updateButton(const sf::Vector2f mousePos);

		const bool isClicked() const;

	};
};
	#endif