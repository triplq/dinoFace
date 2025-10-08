#include <SFML/Graphics.hpp>
#include "Dino.h"
#include "Background.h"
#include <iostream>

using namespace sf;
using namespace std;

int HIGHT = 600;
int WIDTH = 800;

int main() {
    VideoMode mode(Vector2u(800, 600));
    RenderWindow window(mode, "SFML Game");

    Level level;

    Dino dino(sf::Texture("Resources/boy.png"), Vector2f(400,420));
    Background back(sf::Texture("Resources/back.jpg.jpg"));
    Clock clock;

    while(window.isOpen()){
        auto dt = clock.restart().asSeconds();
        const auto e = window.pollEvent();

        if(e->is<sf::Event::Closed>())
            window.close();


        if(e->is<sf::Event::KeyPressed>() || e->is<sf::Event::KeyReleased>()){
            bool isPressed = (e->is<sf::Event::KeyPressed>());
            const auto* kp = e->getIf<sf::Event::KeyPressed>();
            dino.moveBy(kp, dt, isPressed, level);
        }

        dino.Update(dt, level);

        window.clear();
        back.Draw(window);
        dino.Draw(window);
        window.display();
    }


    return 0;
}
