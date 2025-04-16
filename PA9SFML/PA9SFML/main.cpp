#include "Header.hpp"

int main()
{
    RenderWindow window(VideoMode({ windowWidth, windowHeight }), "Game Name");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}