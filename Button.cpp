#include"Button.h"

Button::Button(float x, float y, float width, float height, 
		std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) 
		{
			this->stateButton = idleButton;

			this->shape.setSize(sf::Vector2f(width, height));
			this->shape.setPosition(sf::Vector2f(x,y));

			this->text.setString(text);
			this->text.setFillColor(sf::Color::White);
			this->text.setCharacterSize(12);
			this->text.setPosition(
				this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f);
				this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - (this->text.getGlobalBounds().height / 2.f);
			);

			this->idleColor = idleColor;
			this->hoverColor = hoverColor;
			this->activeColor = activeColor;
			this->shape.setFillColor(this->idleColor);


		}

void drawButton(sf::RenderTarget& target) const
		{
			// target->draw(this->shape);
			// target->draw(this->text);
			target.draw(shape);
		}

void updateButton(const sf::Vector2f mousePos)
		{
			this->buttonState = idleButton;

			if(this->shape.getGlobalBounds().contains(mousePos)) {
				this->stateButton = hoverButton;
			}

			if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				this->stateButton = activeButton;
			}

			switch(this->stateButton)
			{
				case idleButton:
					this->shape.setFillColor(this->idleColor);
					break;
				case hoverButton:
					this->shape.setFillColor(this->hoverColor);
					break;
				case activeButton:
					this->shape.setFillColor(this->activeColor);
					break;

				default:
					this->shape.setFillColor(this->idleColor);
					break;
			}

			
		}

const bool isClicked() const;
		{
			if(this->stateButton == activeButton) {
				return true;
			}

			return false;
		}
