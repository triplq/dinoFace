#include "Dino.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Dino::Dino(sf::Texture texture, const sf::Vector2f& pos) : Character(texture, pos){
    sprite->setScale(sf::Vector2f(0.3, 0.3));
    velocity_max = sf::Vector2f(100, 300);
}

void Dino::Draw(sf::RenderWindow& window){
    window.draw(*sprite);
}


void Dino::moveBy(const sf::Event::KeyPressed* kp, const float& dt, const bool& isPressed, const Level& lvl){
    if(isPressed){
        if(kp->scancode == sf::Keyboard::Scancode::D && velocity.x <= velocity_max.x)
            velocity.x += speed;
        if(kp->scancode == sf::Keyboard::Scancode::A && -velocity.x <= velocity_max.x) 
            velocity.x -= speed;
        if(kp->scancode == sf::Keyboard::Scancode::Space && grounded)
            velocity.y -= velocity_max.y;
    }
    else
        velocity.x = 0;
};

void Dino::Update(float& dt, const Level& lvl){

    Character::Update(dt, lvl);

    sprite->move(sf::Vector2f(dx, dy));
}