#include <SFML/Graphics.hpp>


#pragma once
class Wall
{
public:
	Wall(sf::Vector2f f, sf::Vector2f s) {
		first = f;
		second = s;
	}
	sf::Vector2f first;
	sf::Vector2f second;
    bool isontheplayer(double x, double y) {
        // ѕровер€ем, лежит ли точка на пр€мой
        if (std::fabs((x - first.x) * (second.y - first.y) - (y - first.y) * (second.x - first.x)) < 30) {
            // ѕровер€ем, лежит ли точка в пределах отрезка
            if (std::min(first.x, second.x) <= x && x <= std::max(first.x, second.x) &&
                std::min(first.y, second.y) <= y && y <= std::max(first.y, second.y)) {
                return true;
            }
        }
        return false;
    }
    double pointToSegmentDistance(double x0, double y0) {
        double px = second.x - first.x;
        double py = second.y - first.y;
        double norm = px * px + py * py;

        // Check if the segment is actually a point
        if (norm == 0.0) {
            return std::sqrt((x0 - first.x) * (x0 - first.x) + (y0 - first.y) * (y0 - first.y));
        }

        // Project point onto the line segment, clamping t to [0, 1]
        double t = ((x0 - first.x) * px + (y0 - first.y) * py) / norm;
        t = std::max(0.0, std::min(1.0, t));

        // Find the closest point on the segment
        double closestX = first.x + t * px;
        double closestY = first.y + t * py;

        // Calculate the distance from the point to the closest point
        double dx = x0 - closestX;
        double dy = y0 - closestY;
        return std::sqrt(dx * dx + dy * dy);
    }
};

