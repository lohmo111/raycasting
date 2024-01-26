#include <SFML/Graphics.hpp>
#include "Player.h"
//#include "Ray.h"
#include <list>
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
int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    window.setFramerateLimit(120);
    sf::RenderWindow window_3d(sf::VideoMode(800, 600), "My window");
    window_3d.setFramerateLimit(120);
    // init class examples
    Player player;
    sf::RectangleShape FenceRect;
    //// init new vars and containers
    sf::Vector2f velosity(0,0);
    float s = 300.f;
    float angle = 2.f;
    double x = 0, y = 0;

    //LIST WITH RAYS??

    sf::Vertex fence[] =
    {
        sf::Vertex(sf::Vector2f(150, 150)),
        sf::Vertex(sf::Vector2f(200, 200))
    };

    sf::Vertex fence1[] =
    {
        sf::Vertex(sf::Vector2f(250, 250)),
        sf::Vertex(sf::Vector2f(400, 400))
    };

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
            }
        }
        //movement along the x axis
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velosity.x = -1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velosity.x = 1;
        }
        else
            velosity.x = 0;
        // movement along the y axis
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            velosity.y = -1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            velosity.y = 1;
        }
        else
            velosity.y = 0;
        // rotation of unit
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.RotatePlayer(-angle);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.RotatePlayer(angle);
        }
        player.MovePlayer(velosity.x, velosity.y);
        //sf::Vector2f ray_coords(player.GetPosition().x + naxod(player, s, 0), player.GetPosition().y - cos((player.GetAngle() + 0) * 3.14159 / 180) * s);
        window.clear(sf::Color::Black);
        window_3d.clear(sf::Color::Black);
        for (int i = -50; i <= 50; i ++){
            sf::Vector2f ray_coords(player.GetPosition().x + naxod(player, s, i), player.GetPosition().y - cos(find_angle(player.GetAngle() + i) * 3.14159 / 180) * s);
            //printf("%f %f \n", ray_coords.x, ray_coords.y);
            double x1 = 150, y1 = 150, x2 = 400, y2 = 400, x3 = player.GetPosition().x, y3 = player.GetPosition().y, x4 = ray_coords.x, y4 = ray_coords.y;
            double a1, a2, b1, b2, c1, c2;
            a1 = y1 - y2;
            b1 = x2 - x1;
            c1 = x1 * y2 - x2 * y1;
            a2 = y3 - y4;
            b2 = x4 - x3;
            c2 = x3 * y4 - x4 * y3;
            intersect(a1, a2, b1, b2, c1, c2, x, y);
            

            if (check(player, ray_coords, x, y)) {
                if (lenght(ray_coords.x, ray_coords.y, player) >= lenght(x, y, player))
                    ray_coords = sf::Vector2f(float(x), float(y));
            }
            //printf("%f %f \n", player.GetAngle() + i);
            sf::Vertex line[] =
            {
                sf::Vertex(player.GetPosition()),
                sf::Vertex(ray_coords)

            };
            //production of a rectangles (3d)
            printf("####  %f  #####", find_len_rect(player, ray_coords, s));
            if (find_len_rect(player, ray_coords, s)) {
                FenceRect.setSize(sf::Vector2f(14, 100.f * s / find_len_rect(player, ray_coords, s) ));
                FenceRect.setPosition(sf::Vector2f(400.f +  14 * i , 100.f));
                int color = 255 - 250 * find_len_rect(player, ray_coords, s) / s;
                FenceRect.setFillColor(sf::Color(color, color, color));
                //FenceRect.getOrigin(sf::Vector2));
                window_3d.draw(FenceRect);
            }
            
           



            //drawing the rays
            window.draw(line, 2, sf::Lines);
        }
        //abs(window, player, ray_coords);

        //absc(window, player, ray_coords);
        //window.draw(line, 2, sf::Lines);
        printf("-----------------------------------------------------------------------------------------------------------------------\n");
         // draw 
        player.DrawPlayer(window);
        //for (sf::VertexArray ray : rays) {
         //   window.draw(ray);
        //}
        window.draw(fence, 2, sf::Lines);
        window.draw(fence1, 2, sf::Lines);
        // end the current frame
        window_3d.display();
        window.display();
    }

    return 0;
}
