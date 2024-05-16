#include "header.h"

const int width = 153;
const int height = 227;
int main(){
    sf::RenderWindow window(sf::VideoMode(1500, 800), "Pasyans");
    sf::Sprite sprite[208];
    sf::Texture text;
    text.loadFromFile("picture.png",sf::IntRect(0, 0, 155, 227));
    sprite[0].setTexture(text);
    sprite[0].setScale(0.5,0.5);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear();
        window.draw(sprite[0]);
        window.display();
    }
    return 0;
}
