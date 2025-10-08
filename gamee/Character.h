#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"

class Character{
protected:
    const float speed;
    float g = 9.8f;
    sf::Sprite *sprite;
    sf::Texture texture;
    bool grounded;
    sf::Vector2f velocity;
    // const float E = 0.1f;

    float dx;
    float dy;

public:
    Character(sf::Texture texture, const sf::Vector2f& pos);
    virtual ~Character();

    virtual void Draw(sf::RenderWindow& window) = 0;
    virtual void Update(float& dt, const Level& lvl);
    bool isGrounded(const float& dt, const Level& lvl);
    void gravity(const float& dt);

};