#pragma once

#include "Character.h"
#include "Level.h"

class Dino : public Character{
private:
    sf::Vector2f velocity_max;

public:
    Dino(sf::Texture texture, const sf::Vector2f& pos);

    void Draw(sf::RenderWindow& window) override;

    void Update(float& dt, const Level& lvl) override;
    void moveBy(const sf::Event::KeyPressed* kp, const float& dt, const bool& isPressed, const Level& lvl);
};