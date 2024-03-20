/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade
** File description:
** arcade_sfml
*/

#include "arcade_sfml.hpp"

extern "C" void mainMenu ()
{
    std::cout << "Main Menu test" << std::endl;
    Game *game = new Game();
    game->rune();
    delete game;
}

MenuPrincipal::MenuPrincipal()
{
    r_graphics.setFillColor(sf::Color(0, 0, 128)); // Couleur bleu foncé
    r_graphics.setPosition(100, 100); // Position du rectangle
    r_graphics.setSize(sf::Vector2f(200, 100));
}

MenuPrincipal::~MenuPrincipal()
{

}

void MenuPrincipal::update(int *mode) const
{

}

void MenuPrincipal::display(sf::RenderWindow *wdw) const
{
    wdw->draw(r_graphics);
}

void MenuPrincipal::conditionsKey(sf::Event event, int *mode) const
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            // ...
        } else if (event.key.code == sf::Keyboard::Down) {
            // ...
        }
    }
}
