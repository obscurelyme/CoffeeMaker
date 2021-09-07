#include <iostream>
#include <fstream>
#include <filesystem>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <spdlog/spdlog.h>

void OnMouseDown(sf::Event::MouseButtonEvent *event)
{
    std::string buttonPressed = event->button == sf::Mouse::Right ? "Right" : "Left";
    spdlog::debug("{} mouse button was pressed at coords ({}, {})", buttonPressed, event->x, event->y);
}

void OnMouseUp(sf::Event::MouseButtonEvent *event)
{
}

void OnClick(sf::Event::MouseButtonEvent *event)
{
}

void OnKeyDown(sf::Event::KeyEvent *event)
{
    spdlog::debug("{} Key was pressed", event->code);
}

void OnKeyUp(sf::Event::KeyEvent *event)
{
    spdlog::debug("{} Key was released", event->code);
}

int main(int argc, char **argv)
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Hello SFML");

    sf::RenderWindow window{sf::VideoMode{800, 600}, "Hello SFML"};
    window.setVerticalSyncEnabled(true);
    window.setActive(true);
    spdlog::debug("Window created");
    sf::ContextSettings ctxSettings = window.getSettings();
    spdlog::debug("OpenGL Context Settings: \nAnti Alias: {}\nDepth Bits: {}\nOpenGL Version: {}.{}\nsRGB Capable: {}\nStencil Bits: {}",
                  ctxSettings.antialiasingLevel,
                  ctxSettings.depthBits,
                  ctxSettings.majorVersion,
                  ctxSettings.minorVersion,
                  ctxSettings.sRgbCapable,
                  ctxSettings.stencilBits);

    // Load fonts
    std::string executableDirectory = std::filesystem::weakly_canonical(std::filesystem::path(argv[0])).parent_path().string();
    std::string relativeFontFile = "/assets/fonts/Roboto/Roboto-Regular.ttf";
    std::string fontFilePath = executableDirectory.append(relativeFontFile);
    sf::Font font;
    if (!font.loadFromFile(fontFilePath))
    {
        spdlog::debug("Could not load Roboto-Regular.ttf from directory {}", fontFilePath);
    }
    spdlog::debug("Successfully loaded {} font-family.", font.getInfo().family);

    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color(100, 250, 50));

    sf::Text text{"Hello", font, 48};
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Regular);
    text.setPosition(200, 200);

    bool running = true;
    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::MouseButtonPressed:
                OnMouseDown(&(event.mouseButton));
                OnClick(&(event.mouseButton));
                break;
            case sf::Event::MouseButtonReleased:
                OnMouseUp(&(event.mouseButton));
                break;
            case sf::Event::KeyPressed:
                OnKeyDown(&(event.key));
                break;
            case sf::Event::KeyReleased:
                OnKeyUp(&(event.key));
                break;
            case sf::Event::Resized:
                glViewport(0, 0, event.size.width, event.size.height);
                break;
            case sf::Event::JoystickConnected:
                break;
            case sf::Event::JoystickDisconnected:
                break;
            case sf::Event::Closed:
                running = false;
                break;
            default:
                break;
            }
        }

        window.clear(sf::Color::Blue);

        window.draw(shape);
        // window.draw(text); // program crashes on window.display() when this is called

        window.display();
    }

    // TODO: release resources...

    window.close();
    return 0;
}
