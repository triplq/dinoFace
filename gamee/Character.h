#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"

class Character{
protected:
    const float speed;
    sf::Sprite *sprite;
    sf::Texture texture;
    sf::Vector2f velocity;
    float g = 1000.0f;
    bool grounded;

    float dx;
    float dy;

public:
    Character(sf::Texture texture, const sf::Vector2f& pos);
    virtual ~Character();

    virtual void Draw(sf::RenderWindow& window) = 0;
    virtual void Update(float& dt, const Level& lvl);

    void collision(const float& dt, const Level& lvl);
    void gravity(const float& dt, const Level& lvl);
};