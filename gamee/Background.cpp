#include "Background.h"

Background::Background(sf::Texture n_texture) : texture(n_texture){
    sprite = new sf::Sprite(texture);
};

void Background::Draw(sf::RenderWindow& window){
    window.draw(*sprite);
};

Background::~Background(){ delete sprite; };