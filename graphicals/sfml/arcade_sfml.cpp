/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade
** File description:
** arcade_sfml
*/

#include "arcade_sfml.hpp"
namespace fs = std::filesystem;

// extern "C" void mainMenu ()
int main()
{
    std::cout << "Main Menu test" << std::endl;
    Game *game = new Game();
    game->rune();
    delete game;
    return 0;
}

MenuPrincipal::MenuPrincipal()
{
    r_graphics.setFillColor(sf::Color(75, 75, 150));
    r_graphics.setOutlineThickness(-10);
    r_graphics.setOutlineColor(sf::Color::Black);
    r_graphics.setSize(sf::Vector2f(WINDOW_SIZE_X / 3, WINDOW_SIZE_Y));

    if (!font.loadFromFile("press_start/prstartk.ttf"))
        exit(84);

    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setString("");

    l_game.push_back("arcade_snake.so");
    l_game.push_back("arcade_nibbler.so");
    l_game.push_back("arcade_pacman.so");
    l_game.push_back("arcade_qix.so");
    l_game.push_back("arcade_centipede.so");
    l_game.push_back("arcade_solarfox.so");

    l_graph.push_back("arcade_ncurses.so");
    l_graph.push_back("arcade_sdl2.so");
    l_graph.push_back("arcade_ndk++.so");
    l_graph.push_back("arcade_aalib.so");
    l_graph.push_back("arcade_libcaca.so");
    l_graph.push_back("arcade_allegro5.so");
    l_graph.push_back("arcade_xlib.so");
    l_graph.push_back("arcade_gtk+.so");
    l_graph.push_back("arcade_sfml.so");
    l_graph.push_back("arcade_irrlicht.so");
    l_graph.push_back("arcade_opengl.so");
    l_graph.push_back("arcade_vulkan.so");
    l_graph.push_back("arcade_qt5.so");


    fs::path directory_path = "../lib";
    int i = 0;
    int flag = 0;
    while (i < l_graph.size()) {
        for (const auto& entry : fs::directory_iterator(directory_path)) {
            if (fs::is_regular_file(entry.path()) and entry.path().filename() != l_graph[i]) {
                flag++;
            } if (fs::is_regular_file(entry.path()) and entry.path().filename() == l_graph[i]) {
                flag = 0;
                break;
            }
        }
        i++;
        if (flag != 0) {
            l_graph.erase(l_graph.begin() + (i - 1));
            i = 0;
            flag = 0;
        }
    }

    i = 0;
    flag = 0;
    while (i < l_game.size()) {
        for (const auto& entry : fs::directory_iterator(directory_path)) {
            if (fs::is_regular_file(entry.path()) and entry.path().filename() != l_game[i]) {
                flag++;
            } if (fs::is_regular_file(entry.path()) and entry.path().filename() == l_game[i]) {
                flag = 0;
                break;
            }
        }
        i++;
        if (flag != 0) {
            l_game.erase(l_game.begin() + (i - 1));
            i = 0;
            flag = 0;
        }
    }

    selection.push_back(1);
    selection.push_back(0);
    selection.push_back(0);
}

MenuPrincipal::~MenuPrincipal()
{

}

void MenuPrincipal::update(int *mode) const
{

}

void MenuPrincipal::display(sf::RenderWindow *wdw) const
{
    sf::FloatRect textRect;
    for (int i = 0; i < 3; i++) {
        r_graphics.setPosition(r_graphics.getSize().x * i, 0);
        wdw->draw(r_graphics);

        if (i == 1) {
            for (int n = 0; n < l_game.size(); n++) {
                text.setString(l_game[n]);
                textRect = text.getLocalBounds();
                text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
                text.setPosition((r_graphics.getSize().x * i) + (r_graphics.getSize().x / 2), (text.getCharacterSize() + 50) + ((n+1) * 50));
                text.setFillColor(sf::Color::White);
                if (l_game[n] == l_game[selection[2]])
                    text.setFillColor(sf::Color::Black);
                wdw->draw(text);
            }
            text.setString("Games");
        } if (i == 0) {
            for (int n = 0; n < l_graph.size(); n++) {
                text.setString(l_graph[n]);
                textRect = text.getLocalBounds();
                text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
                text.setPosition((r_graphics.getSize().x * i) + (r_graphics.getSize().x / 2), (text.getCharacterSize() + 50) + ((n+1) * 50));
                text.setFillColor(sf::Color::White);
                if (l_graph[n] == l_graph[selection[1]])
                    text.setFillColor(sf::Color::Black);
                wdw->draw(text);
            }
            text.setString("Graphics");
        } if (i == 2)
            text.setString("Score");

        textRect = text.getLocalBounds();
        text.setFillColor(sf::Color::White);
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
        text.setPosition((r_graphics.getSize().x * i) + (r_graphics.getSize().x / 2), text.getCharacterSize() + 10);
        wdw->draw(text);
    };
}

void MenuPrincipal::conditionsKey(sf::Event event, int *mode) const
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            if (selection[selection[0]] > 0)
                selection[selection[0]] -= 1;
        } else if (event.key.code == sf::Keyboard::Down) {
            if (selection[0] == 1 && selection[selection[0]] < l_graph.size() - 1)
                selection[selection[0]] += 1;
            if (selection[0] == 2 && selection[selection[0]] < l_game.size() - 1)
                selection[selection[0]] += 1;
        } else if (event.key.code == sf::Keyboard::Left) {
            selection[0] = 1;
        } else if (event.key.code == sf::Keyboard::Right) {
            selection[0] = 2;
        } else if (event.key.code == sf::Keyboard::Return) {
            std::cout << "Menu Entré" << std::endl;
            mode[0] = GAME;
        }
    }
}
