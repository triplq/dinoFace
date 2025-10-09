#include "Character.h"
#include <iostream>

Character::Character(sf::Texture n_texture, const sf::Vector2f& pos) : speed(50), texture(n_texture){
    sprite = new sf::Sprite(texture);
    sprite->setPosition(pos);
    sprite->setOrigin(sf::Vector2f(sprite->getGlobalBounds().size.x/2, sprite->getGlobalBounds().size.y/2));
    velocity = sf::Vector2f(0.f,0.f);
    dx = 0;
    dy = 0;
};

Character::~Character() { delete sprite; };

void Character::Update(float& dt, const Level& lvl){
    dx = velocity.x * dt;
    dy = velocity.y * dt;

    gravity(dt, lvl);

// gravity
};

void Character::collision(const float& dt, const Level& lvl){

};

void Character::gravity(const float& dt, const Level& lvl){
    auto pos = sprite->getGlobalBounds();
    auto predictedBB = pos;
    predictedBB.position.y += dy;
    if(lvl.getIntersects(predictedBB)){
        grounded = true;
        velocity.y = 0;
    }
    else{
        velocity.y +=  dt * g;
        grounded = false;
    }
};