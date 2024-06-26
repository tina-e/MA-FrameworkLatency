// based on chatgpt
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Windows.h>


const int WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int HEIGHT = GetSystemMetrics(SM_CYSCREEN);


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "framework", sf::Style::None);

    bool isPressed = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                isPressed = true;
            } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                isPressed = false;
            }
        }

        // Draw objects based on the current state
        if (isPressed) {
            window.clear(sf::Color::White);
        }
        else {
            window.clear(sf::Color::Black);
        }

        // Update the window
        window.display();
    }

    return 0;
}
