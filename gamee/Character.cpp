#include "Character.h"
#include <iostream>

Character::Character(sf::Texture n_texture, const sf::Vector2f& pos) : speed(900), texture(n_texture){
    sprite = new sf::Sprite(texture);
    sprite->setPosition(pos);
    on_floor = true;
};

Character::~Character() { delete sprite; };

void Character::Update(float& dt, const std::optional<sf::Event> e, const Level& lvl){
    if(is_on_floor(dt, lvl))
        std::cerr << "is on floor\n";
    else
        Character::tryMove(2, dt, lvl);
    // if(level.getIntersects(sprite->getGlobalBounds()))


// gravity
};


// 0-up 1-left 2-down 3-right
void Character::tryMove(const int& direction, const float& dt, const Level& lvl){
        switch(direction){
            case 0:
                if(is_on_floor(dt, lvl)){
                    sprite->move(sf::Vector2f(0, -100));
                    if(lvl.getIntersects(sprite->getGlobalBounds()))
                        sprite->move(sf::Vector2f(0, 100));
                }
                break;
            case 2:
                sprite->move(sf::Vector2f(0, dt*speed));
                if(lvl.getIntersects(sprite->getGlobalBounds()))
                    sprite->move(sf::Vector2f(0, -dt*speed));
                break;
            case 1:
                sprite->move(sf::Vector2f(-dt*speed, 0));
                if(lvl.getIntersects(sprite->getGlobalBounds()))
                    sprite->move(sf::Vector2f(dt*speed, 0));
                break;
            case 3:
                sprite->move(sf::Vector2f(dt*speed, 0));
                if(lvl.getIntersects(sprite->getGlobalBounds()))
                    sprite->move(sf::Vector2f(-dt*speed, 0));
                break;
        }
};

bool Character::is_on_floor(const float& dt, const Level& lvl){
    sprite->move(sf::Vector2f(0, dt*speed));
    if(lvl.getIntersects(sprite->getGlobalBounds())){
        sprite->move(sf::Vector2f(0, -dt*speed));
        return true;
    }
    sprite->move(sf::Vector2f(0, -dt*speed));

    return false;
};