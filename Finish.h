#pragma once
#include "SFML/Graphics.hpp"

class Finish {
private:
    sf::RectangleShape rectangle; // Прямоугольник, представляющий финиш

public:
    // Конструктор для задания позиции и размеров прямоугольника
    Finish(float x, float y, float width, float height) {
        rectangle.setPosition(x, y);
        rectangle.setSize({ width, height });
        rectangle.setFillColor(sf::Color::Green); // Цвет финиша для визуализации
    }

    // Метод проверки, находится ли игрок внутри прямоугольника
    bool isPlayerOnFinish(float playerX, float playerY) const {
        // Получаем границы прямоугольника
        float left = rectangle.getPosition().x;
        float top = rectangle.getPosition().y;
        float right = left + rectangle.getSize().x;
        float bottom = top + rectangle.getSize().y;

        // Проверяем, находится ли точка внутри прямоугольника
        return (playerX >= left && playerX <= right &&
            playerY >= top && playerY <= bottom);
    }

    // Метод для отрисовки финиша
    void draw(sf::RenderWindow& window) const {
        window.draw(rectangle);
    }
};
