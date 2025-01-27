#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Wall.h"
#include "Finish.h"
#include <list>
#include <string>
#include <stdio.h>
#include <math.h>


float find_len_rect(Player& player, sf::Vector2f& ray_vector, float std_len) {
    float xx = ray_vector.x;
    float yy = ray_vector.y;
    float ray_len = (sqrt(pow(xx - player.GetPosition().x, 2) + pow(yy - player.GetPosition().y, 2)));
    if (std_len - (ceil(ray_len)) <= 1) {
        //printf("\nNE PERES %f %f %f\n", ray_len, std_len, ceil(ray_len) - std_len);
        return 0;
    }
    else {
        //printf("\nPERES%f\n", ray_len);
        return ray_len;
    }
}
float find_angle(float angle) {
    //printf(" angles %f ", angle);
    if (angle <= 0)
        angle = (360 + angle);
    if (angle >= 360) {
        //printf("%f %f \n", (360 * ((int)angle / 360)), angle);
        angle = angle - (360 * round(angle / 360));
    }
    //printf("%f \n", angle);
    return angle;

}
int check(Player& player, sf::Vector2f& ray_coords, float x, float y) {
    int a = 0, c = 0;
    //printf("%f %f % f\n", player.GetPosition().x, ray_coords.x, x);
    
    if (player.GetPosition().x <= ray_coords.x) {
        a = (player.GetPosition().x <= x and x <= ray_coords.x);
    }
    else a = (player.GetPosition().x >= x and x >= ray_coords.x);
    int b = ((150 <= x and x <= 200) or (250 <= x and x <= 400));
    if (player.GetPosition().y <= ray_coords.y) {
        c = (player.GetPosition().y <= y  and y<= ray_coords.y);
    }
    else c = (player.GetPosition().y >= y and y >= ray_coords.y);
    return a && b && c;
}
int naxod(Player& player, float s, int delta = 0) {
    if (find_angle(player.GetAngle() + delta) >= 180) {
        return -sqrt(pow(s, 2) - pow(cos(find_angle(player.GetAngle() + delta) * 3.14159 / 180) * s, 2));
    }
    return sqrt(pow(s, 2) - pow(cos((player.GetAngle() + delta) * 3.14159 / 180) * s, 2));
}
int lenght(double x, double y, Player& player) {
    double x0 = player.GetPosition().x;
    double y0 = player.GetPosition().y;
    double res = sqrt(pow((x - x0), 2) + pow((y - y0), 2));
    if (res >= 0) return res;
    return -res;
}
void intersect(double a1, double a2, double b1, double b2, double c1, double c2, double& x, double& y)
{
    double det = a1 * b2 - a2 * b1;
    x = (b1 * c2 - b2 * c1) / det;
    y = (a2 * c1 - a1 * c2) / det;
}

// ������� ���������� ����������� ���� ��������
bool intersect_segments(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2, sf::Vector2f& intersect) {
    float denom = (p2.x - p1.x) * (q2.y - q1.y) - (p2.y - p1.y) * (q2.x - q1.x);

    // ���� ����������� ����� ����, ������� �����������
    if (denom == 0) {
        return false;
    }

    float t = ((q1.x - p1.x) * (q2.y - q1.y) - (q1.y - p1.y) * (q2.x - q1.x)) / denom;
    float u = ((q1.x - p1.x) * (p2.y - p1.y) - (q1.y - p1.y) * (p2.x - p1.x)) / denom;

    // ���� t � u ����� ����� 0 � 1, ������ ������� ������������
    if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
        intersect.x = p1.x + t * (p2.x - p1.x);
        intersect.y = p1.y + t * (p2.y - p1.y);
        return true;
    }

    return false;
}


float anglel(float ang) {
    ang = fabs(360 - ang);
    return ang * 3.14159265 / 180;
}


void endGame(sf::RenderWindow& window, const std::string& message) {
    // ������� ������ ���
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color::Black);

    // ����������� ����� ��� ������
    sf::Font font;
    if (!font.loadFromFile("ArialBlack.ttf")) { // ��������� ���������� ���� � ������
        std::cout << "�� ������� ��������� ����� arial.ttf" << std::endl;
        return;
    }

    sf::Text endText;
    endText.setFont(font);
    endText.setString(message);
    endText.setCharacterSize(50); // ������ ������
    endText.setFillColor(sf::Color::White);
    endText.setStyle(sf::Text::Bold);

    // ���������� ����� �� ������
    sf::FloatRect textBounds = endText.getLocalBounds();
    endText.setOrigin(textBounds.width / 2, textBounds.height / 2);
    endText.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    // ������� ���� ��� ����������� ������
    sf::Clock clock;
    bool isRunning = true;
    while (isRunning) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                isRunning = false;
                window.close();
            }
        }

        // ���� ������ 5 ������, ��������� ����
        if (clock.getElapsedTime().asSeconds() > 5) {
            isRunning = false;
        }

        // ������ ������ ����� � �����
        window.clear();
        window.draw(background);
        window.draw(endText);
        window.display();
    }
}


int main() {
    // ������� ����
    sf::RenderWindow window(sf::VideoMode(900, 900), "My window");
    window.setFramerateLimit(120);

    sf::RenderWindow window_3d(sf::VideoMode(1200, 600), "3D View");
    window_3d.setFramerateLimit(120);

    // ������������� ������
    Player player;
    sf::RectangleShape FenceRect;
    Finish finish(520, 602, 78, 96);

    // ������������� ����� ���������� � �����������
    sf::Vector2f velocity(0, 0);
    float s = 300.f;
    float angle = 2.f;
    double x = 0, y = 0;

    // ��������� ���������
    //std::vector<std::pair<sf::Vector2f, sf::Vector2f>> walls = generate_maze(800, 600, 40);
    std::vector<Wall> walls = {
        // ������� ������� ���������
        Wall({520, 602}, {598, 602}),   // ������� �������
        Wall({598, 602}, {598, 698}),   // ����� �������
        Wall({598, 698}, {520, 698}), // ������ �������

        Wall({50, 50}, {750, 50}),   // ������� �������
        Wall({50, 50}, {50, 750}),   // ����� �������
        Wall({750, 50}, {750, 750}), // ������ �������
        Wall({50, 750}, {750, 750}), // ������ �������

        // �������� � ����������� �������� � �������������
        Wall({200, 50}, {200, 250}),   // ������������ ����� �����
        Wall({200, 250}, {300, 250}),  // �������������� ����� �����
        Wall({300, 250}, {300, 150}),  // ������������ ����������� ����� ������
        Wall({300, 150}, {400, 150}),  // �������������� ����������� �����
        Wall({400, 150}, {400, 250}),  // ������������ ����������� ������ �����
        Wall({400, 250}, {550, 250}),  // �������������� ������ ����� ������
        Wall({550, 250}, {550, 400}),  // ������������ ������ �����
        Wall({550, 400}, {450, 400}),  // �������������� ������ ����� ������
        Wall({450, 400}, {450, 500}),  // ������������ ����������� ����� �����
        Wall({450, 500}, {300, 500}),  // �������������� ����������� ����� �����
        Wall({300, 500}, {300, 400}),  // ������������ ����� ����� �����
        Wall({300, 400}, {150, 400}),  // �������������� ����� ����� �����
        Wall({150, 400}, {150, 600}),  // ������������ ����� ����� ������
        Wall({150, 600}, {350, 600}),  // �������������� ����������� ����� �����
        Wall({350, 600}, {350, 700}),  // ������������ ����������� ����� �����
        Wall({350, 700}, {600, 700}),  // �������������� ������ ������ �����
        Wall({600, 700}, {600, 600}),  // ������������ ������ ������ �����
        Wall({600, 600}, {450, 600}),  // �������������� ������ �����
        Wall({450, 600}, {450, 550}),  // ������������ ������ ������ �����
    };





    while (window_3d.isOpen()) {
        window.clear(sf::Color::Black);
        window_3d.clear(sf::Color::Black);

        sf::Event event;
        while (window_3d.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window_3d.close();
            }
        }

        // �������� � �������
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velocity.x = -1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velocity.x = 1;
        }
        else {
            velocity.x = 0;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            velocity.y = -1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            velocity.y = 1;
        }
        else {
            velocity.y = 0;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.RotatePlayer(-angle);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.RotatePlayer(angle);
        }
        double xx = velocity.x * cos(anglel(player.GetAngle())) + velocity.y * sin(anglel(player.GetAngle()));
        double yy = velocity.y * cos(anglel(player.GetAngle())) - velocity.x * sin(anglel(player.GetAngle()));
        bool flag = true;

        for (auto& wall : walls) {

            if (wall.pointToSegmentDistance(player.GetPosition().x + xx, player.GetPosition().y + yy) < 2) {
                //printf("%f", wall.pointToSegmentDistance(player.GetPosition().x + xx, player.GetPosition().y + yy));
                flag = false;
                break;
            }
        }
        if (flag) {
           
            player.MovePlayer(xx, yy);
        }
        if (finish.isPlayerOnFinish(player.GetPosition().x, player.GetPosition().y)) {
            endGame(window_3d, "Congratulations! You won!");
            break; 
        }
        // ������� ����� ��� ���������
        for (int i = -50; i <= 50; i++) {
            sf::Vector2f ray_coords(player.GetPosition().x + naxod(player, s, i), player.GetPosition().y - cos(find_angle(player.GetAngle() + i) * 3.14159 / 180) * s);
            sf::Vector2f intersection;

            // �������� ����������� � ������ ������
            for (auto& wall : walls) {
                if (intersect_segments(player.GetPosition(), ray_coords, wall.first, wall.second, intersection)) {
                    if (lenght(ray_coords.x, ray_coords.y, player) >= lenght(intersection.x, intersection.y, player)) {
                        ray_coords = intersection; // ��������� ���������� ����
                    }
                }
            }

            // ��������� ����
            sf::Vertex line[] = {
                sf::Vertex(player.GetPosition()),
                sf::Vertex(ray_coords)
            };

            // ��������� 3D ��������������� (����)
            if (find_len_rect(player, ray_coords, s)) {
                FenceRect.setSize(sf::Vector2f(14, 100.f * s / find_len_rect(player, ray_coords, s)));
                FenceRect.setPosition(sf::Vector2f(400.f + 14 * i, 100.f));
                int color = 255 - 250 * find_len_rect(player, ray_coords, s) / s;
                FenceRect.setFillColor(sf::Color(color, color, color));
                if (finish.isPlayerOnFinish(ray_coords.x, ray_coords.y)){
                    FenceRect.setFillColor(sf::Color(0, color, 0));
                }
                window_3d.draw(FenceRect);
            }

            window.draw(line, 2, sf::Lines);
        }

        player.DrawPlayer(window);
        finish.draw(window);
        // ����������� ���� ���� ���������
        for (auto& wall : walls) {
            sf::VertexArray wall_line(sf::Lines, 2);
            wall_line[0].position = wall.first;
            wall_line[1].position = wall.second;
            window.draw(wall_line);
        }

        window_3d.display();
        window.display();
    }

    return 0;
}