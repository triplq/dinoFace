#include "Level.h"

Level::Level(){
    collisionBB.push_back(sf::FloatRect(sf::Vector2f(0,491), sf::Vector2f(800,50))); //пол пока так координаты, размер
    collisionBB.push_back(sf::FloatRect(sf::Vector2f(520, 375), sf::Vector2f(115, 30)));

};

bool Level::getIntersects(const sf::FloatRect& dino_bb) const{
    for(auto& bb : collisionBB){
        if(dino_bb.findIntersection(bb))
            return true;
    }

    return false;
};