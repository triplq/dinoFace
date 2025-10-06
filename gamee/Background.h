#pragma once

#include <SFML/Graphics.hpp>

class Background{
private:
    sf::Texture texture;
    sf::Sprite* sprite;

public:
    Background(sf::Texture texture);
    void Draw(sf::RenderWindow& window);

    ~Background();
};