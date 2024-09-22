#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

void centerCircle(sf::CircleShape* shape, float wSize, float r) {
    sf::Vector2 initPosV(wSize/2 - r, wSize/2 - r);
    shape->setPosition(initPosV);
}

void move(sf::CircleShape *shape, sf::Vector2f oldPos, float speed, bool horizontal) {
    sf::Vector2f newPos(0, 0);
    if (horizontal) {
        newPos = sf::Vector2f(oldPos.x + speed, oldPos.y);
    }
    else {
        newPos = sf::Vector2f(oldPos.x, oldPos.y + speed);
    }
    shape->setPosition(newPos);
}

int main()
{
    using std::endl;
    // Global options
    std::size_t nPoints{1000}; // Number of points on circle
    // Render Window
    float wSize{1000};
    sf::RenderWindow window(sf::VideoMode(wSize, wSize), "SFML works!");
    // Frame rate
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);
    // Main entity
    float r{25};
    sf::CircleShape shape(r, nPoints);
    shape.setFillColor(sf::Color::Green);
    centerCircle(&shape, wSize, r);
    // Visual border
    float rB{400}; 
    sf::CircleShape border(rB, nPoints);    
    border.setFillColor(sf::Color::Black);
    border.setOutlineThickness(5);
    border.setOutlineColor(sf::Color::White);
    centerCircle(&border, wSize, rB);
    // Colision border
    float rCB{rB - r*2};
    sf::CircleShape cBorder(rCB, nPoints);
    cBorder.setFillColor(sf::Color::Black);
    cBorder.setOutlineThickness(1);
    cBorder.setOutlineColor(sf::Color::White);
    centerCircle(&cBorder, wSize, rCB);
    // Animation setup
    sf::Vector2f newPosV(0, 0);
    float speed{3.5};
    // Init clock
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Print FPS
        float currentTime = clock.restart().asSeconds();
        float fps = 1.0f / (currentTime);
        std::cout << fps << endl;
        // Moving the shape
            shape.move(0, -speed);
        
        // Colisions
        sf::FloatRect border_box = cBorder.getGlobalBounds();
        sf::FloatRect shape_box = shape.getGlobalBounds();

       // if (!shape_box.contains(border_box)) { // Fix collisions
        //    shape.move(0, -speed);
         //   std::cout << "Collision" << endl;
       // }
       // else {
        //    shape.move(0, speed);
       // }
        

        // Draw on screan
        window.clear();

        window.draw(border);
        window.draw(cBorder);
        window.draw(shape);
        
        window.display();
    }

    return 0;
}
