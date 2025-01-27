#pragma once
#include "SFML/Graphics.hpp"

class Finish {
private:
    sf::RectangleShape rectangle; // �������������, �������������� �����

public:
    // ����������� ��� ������� ������� � �������� ��������������
    Finish(float x, float y, float width, float height) {
        rectangle.setPosition(x, y);
        rectangle.setSize({ width, height });
        rectangle.setFillColor(sf::Color::Green); // ���� ������ ��� ������������
    }

    // ����� ��������, ��������� �� ����� ������ ��������������
    bool isPlayerOnFinish(float playerX, float playerY) const {
        // �������� ������� ��������������
        float left = rectangle.getPosition().x;
        float top = rectangle.getPosition().y;
        float right = left + rectangle.getSize().x;
        float bottom = top + rectangle.getSize().y;

        // ���������, ��������� �� ����� ������ ��������������
        return (playerX >= left && playerX <= right &&
            playerY >= top && playerY <= bottom);
    }

    // ����� ��� ��������� ������
    void draw(sf::RenderWindow& window) const {
        window.draw(rectangle);
    }
};
