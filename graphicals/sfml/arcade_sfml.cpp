/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade
** File description:
** arcade_sfml
*/

#include "arcade_sfml.hpp"
#include "../../core/GameState.hpp"
#include "../../core/core.hpp"
namespace fs = std::filesystem;

MenuPrincipal::MenuPrincipal()
{
    wdw.create(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Arcade");
    r_graphics.setFillColor(sf::Color(75, 75, 150));
    r_graphics.setOutlineThickness(-10);
    r_graphics.setOutlineColor(sf::Color::Black);
    r_graphics.setSize(sf::Vector2f(WINDOW_SIZE_X / 3, WINDOW_SIZE_Y));

    if (!font.loadFromFile("./graphicals/sfml/press_start/prstartk.ttf"))
        throw GraphInitError("Failed to load SFML Font");

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
    if (!wdw.isOpen()) {
        gameState.setState(arcade::screenState::STOP);
        return;
    }
    conditionsKey(gameState);
    wdw.clear(sf::Color::Black);
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
        
    };
    text.setString("Username : " + username);
    textRect = text.getLocalBounds();
    text.setFillColor(sf::Color::White);
    // text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(100, 950);
    wdw.draw(text);
    wdw.display();
}

bool MenuPrincipal::isValidChar(char character)
{
    if (character >= 97 && character <= 122)
        return true;
    if (character >= 65 && character <= 90)
        return true;
    if (character >= 48 && character <= 57)
        return true;
    if (character == 32)
        return true;
    return false;
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
                if (selection[0] == 1 && selection[1] < graph_size - 1)
                    selection[1] += 1;
                if (selection[0] == 2 && selection[2] < game_size - 1)
                    selection[2] += 1;
            } else if (event.key.code == sf::Keyboard::Left) {
                selection[0] = 1;
            } else if (event.key.code == sf::Keyboard::Right) {
                selection[0] = 2;
            } else if (event.key.code == sf::Keyboard::Return) {
                if (username != "") {
                    gameState.setState(arcade::screenState::IN_GAME);
                    gameState.setGameLib(gameState.getGamesList()[selection[2]]);
                    gameState.setGraphLib(gameState.getGraphList()[selection[1]]);
                    gameState.setUsername(username);
                }
            } else if (event.key.code == sf::Keyboard::BackSpace) {
                if (username.size() >= 1)
                    username.pop_back();
            } else {}
        } else if (event.type == sf::Event::TextEntered) {
            if (this->isValidChar(event.text.unicode))
                username += event.text.unicode;
        }
    }
}

void MenuPrincipal::handleInput(arcade::GameState &gameState)
{
    sf::Event event;
    int ga_size = gameState.getGamesList().size();
    int gr_size = gameState.getGraphList().size();
    while (wdw.pollEvent(event))
        if (event.type == sf::Event::KeyReleased)
            gameState.setKey(arcade::keyPressed::NOTHING);
    for (int i = 0; i < 500; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        while (wdw.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed)
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                        gameState.setKey(arcade::keyPressed::LEFT_KEY);
                        break;
                    case sf::Keyboard::Right:
                        gameState.setKey(arcade::keyPressed::RIGHT_KEY);
                        break;
                    case sf::Keyboard::Up:
                        gameState.setKey(arcade::keyPressed::UP_KEY);
                        break;
                    case sf::Keyboard::Down:
                        gameState.setKey(arcade::keyPressed::DOWN_KEY);
                        break;
                    case sf::Keyboard::Escape:
                        gameState.setKey(arcade::keyPressed::ESC_KEY);
                        break;
                    case sf::Keyboard::Space:
                        gameState.setKey(arcade::keyPressed::SPACE_KEY);
                        break;
                    case sf::Keyboard::F1:
                        selection[2] = ((selection[2] < (ga_size - 1)) ? selection[2] + 1 : 0);
                        gameState.setGameLib(gameState.getGamesList()[selection[2]]);
                        gameState.setKey(arcade::keyPressed::NOTHING);
                        break;
                    case sf::Keyboard::F2:
                        selection[1] = ((selection[1] < (gr_size - 1)) ? selection[1] + 1 : 0);
                        gameState.setGraphLib(gameState.getGraphList()[selection[1]]);
                        break;
                    default:
                        break;
                }
            if (event.type == sf::Event::Closed)
                gameState.setState(arcade::screenState::STOP);
        }
    }
}

void MenuPrincipal::displayGame(arcade::GameState &gameState)
{
    handleInput(gameState);

    std::vector<std::string> map = gameState.getGameArray();
    int size = map.size();
    float x = 0;
    float y = 0;
    if (size > 0) {
        float width = WINDOW_SIZE_X / map[0].size();
        float height = WINDOW_SIZE_Y / size;
        sf::RectangleShape rect({width, height});
        rect.setPosition({x, y});
        for (int i = 0; i < size; i++) {
            int lineSize = map[i].size();
            for (int j = 0; j < lineSize; j++) {
                switch (map[i][j]) {
                case 'O':
                    rect.setFillColor(sf::Color(0, 165, 0, 255));
                    break;
                case 'o':
                    rect.setFillColor(sf::Color(0, 255, 0, 255));
                    break;
                case 'X':
                    rect.setFillColor(sf::Color(0, 0, 255, 255));
                    break;
                case ' ':
                    rect.setFillColor(sf::Color(0, 0, 0, 255));
                    break;
                case 'F':
                    rect.setFillColor(sf::Color(255, 0, 0, 255));
                    break;
                default:
                    break;
                }
                rect.setPosition({x, y});
                wdw.draw(rect);
                x += width;
            }
            x = 0;
            y += height;
        }
    }
    wdw.display();
}

void MenuPrincipal::displayWindow(arcade::GameState &gameState)
{
    arcade::screenState state = gameState.getState();
    switch (state) {
        case arcade::screenState::ARCADE_MENU:
            this->display(gameState);
            break;
        case arcade::screenState::IN_GAME:
            this->displayGame(gameState);
            break;

        default:
            break;
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
