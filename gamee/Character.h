#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"

class Character{
protected:
    float speed;
    float g = 980.0f;
    sf::Sprite *sprite;
    sf::Texture texture;
    bool on_floor;

public:
    Character(sf::Texture texture, const sf::Vector2f& pos);
    virtual ~Character();

    virtual void Draw(sf::RenderWindow& window) = 0;
    virtual void Update(float& dt, const std::optional<sf::Event> e, const Level& lvl); //const sf::Event::KeyPressed* kp
    virtual void tryMove(const int& direction, const float& dt, const Level& lvl);
    bool is_on_floor(const float& dt, const Level& lvl);
};