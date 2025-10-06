#include "Dino.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Dino::Dino(sf::Texture texture, const sf::Vector2f& pos) : Character(texture, pos){
    sprite->setScale(sf::Vector2f(0.3, 0.3));
}

void Dino::Draw(sf::RenderWindow& window){
    window.draw(*sprite);
}


// 0-up 1-left 2-down 3-right
void Dino::Update(float& dt, const std::optional<sf::Event> e, const Level& lvl){


    if(const auto* kp = e->getIf<sf::Event::KeyPressed>()){
        int direction; 

        if(kp->scancode == sf::Keyboard::Scancode::S)
            direction = 2;
        if(kp->scancode == sf::Keyboard::Scancode::W)
            direction = 0;
        if(kp->scancode == sf::Keyboard::Scancode::A)
            direction = 1;
        if(kp->scancode == sf::Keyboard::Scancode::D)
            direction = 3;

        Character::tryMove(direction, dt, lvl);
    }
    
    Character::Update(dt, e, lvl);
}