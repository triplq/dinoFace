#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Level{
private:
    std::vector<sf::FloatRect> collisionBB;

public:
    Level();

    bool getIntersects(const sf::FloatRect& dino_bb) const;
};