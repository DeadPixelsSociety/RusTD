#include <cmath>

#include "../include/config.hpp"

float getDistanceBetweenPoints(sf::Vector2f p1,sf::Vector2f p2)
{
    float distance_x = p2.x - p1.x;
    float distance_y = p2.y - p1.y;
    float distance = sqrt(pow(distance_x,2) + pow(distance_y,2));
    return distance;
}
