/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade
** File description:
** arcade_sfml
*/

#include "arcade_sfml.hpp"
#include "../../core/GameState.hpp"
namespace fs = std::filesystem;

MenuPrincipal::MenuPrincipal()
{
    wdw.create(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Arcade");
    r_graphics.setFillColor(sf::Color(75, 75, 150));
    r_graphics.setOutlineThickness(-10);
    r_graphics.setOutlineColor(sf::Color::Black);
    r_graphics.setSize(sf::Vector2f(WINDOW_SIZE_X / 3, WINDOW_SIZE_Y));

    if (!font.loadFromFile("./graphicals/sfml/press_start/prstartk.ttf"))
        exit(84);

    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setString("");

    selection.push_back(1);
    selection.push_back(0);
    selection.push_back(0);
}

MenuPrincipal::~MenuPrincipal()
{

}

void MenuPrincipal::display(arcade::GameState &gameState)
{
    sf::FloatRect textRect;
    std::vector<std::string> l_game = gameState.getGamesList();
    std::vector<std::string> l_graph = gameState.getGraphList();
    for (int i = 0; i < 3; i++) {
        r_graphics.setPosition(r_graphics.getSize().x * i, 0);
        wdw.draw(r_graphics);

        if (i == 1) {
            int game_size = l_game.size();
            for (int n = 0; n < game_size; n++) {
                text.setString(l_game[n]);
                textRect = text.getLocalBounds();
                text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
                text.setPosition((r_graphics.getSize().x * i) + (r_graphics.getSize().x / 2), (text.getCharacterSize() + 50) + ((n+1) * 50));
                text.setFillColor(sf::Color::White);
                if (l_game[n] == l_game[selection[2]])
                    text.setFillColor(sf::Color::Black);
                wdw.draw(text);
            }
            text.setString("Games");
        } if (i == 0) {
            int graph_size = l_graph.size();
            for (int n = 0; n < graph_size; n++) {
                text.setString(l_graph[n]);
                textRect = text.getLocalBounds();
                text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
                text.setPosition((r_graphics.getSize().x * i) + (r_graphics.getSize().x / 2), (text.getCharacterSize() + 50) + ((n+1) * 50));
                text.setFillColor(sf::Color::White);
                if (l_graph[n] == l_graph[selection[1]])
                    text.setFillColor(sf::Color::Black);
                wdw.draw(text);
            }
            text.setString("Graphics");
        } if (i == 2)
            text.setString("Score");

        textRect = text.getLocalBounds();
        text.setFillColor(sf::Color::White);
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
        text.setPosition((r_graphics.getSize().x * i) + (r_graphics.getSize().x / 2), text.getCharacterSize() + 10);
        wdw.draw(text);
    };
}

void MenuPrincipal::conditionsKey(arcade::GameState &gameState)
{
    sf::Event event;
    std::vector<std::string> l_game = gameState.getGamesList();
    std::vector<std::string> l_graph = gameState.getGraphList();
    int game_size = l_game.size();
    int graph_size = l_graph.size();
    while (wdw.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                if (selection[selection[0]] > 0)
                    selection[selection[0]] -= 1;
            } else if (event.key.code == sf::Keyboard::Down) {
                if (selection[0] == 1 && selection[selection[0]] < graph_size - 1)
                    selection[selection[0]] += 1;
                if (selection[0] == 2 && selection[selection[0]] < game_size - 1)
                    selection[selection[0]] += 1;
            } else if (event.key.code == sf::Keyboard::Left) {
                selection[0] = 1;
            } else if (event.key.code == sf::Keyboard::Right) {
                selection[0] = 2;
            } else if (event.key.code == sf::Keyboard::Return) {
                std::cout << "Menu Entré" << std::endl;
                gameState.setState(arcade::screenState::IN_GAME);
            }
        }
    }
}

void MenuPrincipal::displayWindow(arcade::GameState &gameState)
{
    arcade::screenState state = gameState.getState();
    while (state != arcade::screenState::STOP) {
        switch (state) {
            case arcade::screenState::ARCADE_MENU:
                this->conditionsKey(gameState);
                this->display(gameState);
                break;
            
            default:
                break;
        }
    }
}

arcade::libType MenuPrincipal::getLibType()
{
    return arcade::libType::GRAPHICALS;
}

extern "C" MenuPrincipal *instance()
{
    return new MenuPrincipal();
}
