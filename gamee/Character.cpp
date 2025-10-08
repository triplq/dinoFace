#include "Character.h"
#include <iostream>

Character::Character(sf::Texture n_texture, const sf::Vector2f& pos) : speed(100), texture(n_texture){
    sprite = new sf::Sprite(texture);
    sprite->setPosition(pos);
    sprite->setOrigin(sf::Vector2f(sprite->getGlobalBounds().size.x/2, sprite->getGlobalBounds().size.y/2));
    // on_floor = true;
    velocity = sf::Vector2f(0.f,0.f);
    dx = 0;
    dy = 0;
};

Character::~Character() { delete sprite; };

void Character::Update(float& dt, const Level& lvl){
    dx = velocity.x * dt;
    dy = velocity.y * dt;

    Character::isGrounded(dt, lvl);

    gravity(dt);


// gravity
};

void Character::gravity(const float& dt){

    if(!grounded){
        velocity.y += speed * dt * g;
    }
    else if(grounded)
        velocity.y = 0;
};

void Character::isGrounded(const float& dt, const Level& lvl){
    auto pos = sprite->getGlobalBounds();
    auto predictedBB = pos;
    predictedBB.position.y += dy;
    if(lvl.getIntersects(predictedBB)){
        grounded = true;
    }

    grounded = false;
};