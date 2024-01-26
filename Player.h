#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player() {
		PlayerRect.setSize(sf::Vector2f(20.f, 20.f));
		PlayerRect.setPosition(sf::Vector2f(100.f, 100.f));
		PlayerRect.setFillColor(sf::Color::White);
		PlayerRect.setOrigin(sf::Vector2f(10.f, 10.f));
	}
	sf::Vector2f GetPosition() {
		return PlayerRect.getPosition();
	}
	void DrawPlayer(sf::RenderWindow& window) {
		window.draw(PlayerRect);
	}
	void MovePlayer(float vel_x, float vel_y) {
		PlayerRect.move(sf::Vector2f(vel_x, vel_y));
	}
	void RotatePlayer(float angle) {
		PlayerRect.rotate(angle);
	}
	float GetAngle() {
		return PlayerRect.getRotation();
	}
	
private:
	sf::RectangleShape PlayerRect;
};

