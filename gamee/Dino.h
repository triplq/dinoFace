#pragma once

#include "Character.h"
#include "Level.h"

class Dino : public Character{
public:
    Dino(sf::Texture texture, const sf::Vector2f& pos);

    void Draw(sf::RenderWindow& window) override;
    void Update(float& dt, const std::optional<sf::Event> e,  const Level& lvl) override;
};