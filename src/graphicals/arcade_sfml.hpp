/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade
** File description:
** arcade_sfml
*/

#ifndef ARCADE_SFML_HPP_
#define ARCADE_SFML_HPP_

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem> //std::filesystem

#define WINDOW_SIZE_X 1900
#define WINDOW_SIZE_Y 1000

enum {MENU, GAME};


class ICore
{
    public:
        virtual void update(int *mode) const = 0;
        virtual void display(sf::RenderWindow *wdw) const = 0;
        virtual void conditionsKey(sf::Event event, int *mode) const = 0;
};

class MenuPrincipal : public ICore
{
    public:
        MenuPrincipal();
        ~MenuPrincipal();
        void update(int *mode) const override;
        void display(sf::RenderWindow *wdw) const override;
        void conditionsKey(sf::Event event, int *mode) const override;

        mutable sf::RectangleShape r_graphics;
        mutable sf::Font font;
        mutable sf::Text text;
        std::vector<std::string> l_game;
        std::vector<std::string> l_graph;
        mutable std::vector<int> selection;
};

class Game
{
    public:
        sf::RenderWindow wdw;
        sf::Event event;
        int mode;
        std::vector<ICore *> list_mode;

        ICore *MPrinc;

        Game()
        {
            wdw.create(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Arcade");
            mode = MENU;
            MPrinc = new MenuPrincipal();
            list_mode.push_back(MPrinc);
        }

        ~Game()
        {
            delete MPrinc;
        }

        void rune()
        {
            std::cout << "Game run" << std::endl;
            while (wdw.isOpen()){
                while (wdw.pollEvent(event)) {
                    conditionsEvent();
                    conditionsKey();
                }
                update();
                display();
            }
        }

        void conditionsEvent()
        {
            if (event.type == sf::Event::Closed)
                wdw.close();
        }

        void conditionsKey()
        {
            if (mode == MENU)
                list_mode[MENU]->conditionsKey(event, &mode);
        }

        void update()
        {
            if (mode == MENU)
                list_mode[MENU]->update(&mode);
        }

        void display()
        {
            // Clear screen
            wdw.clear();

            if (mode == MENU)
                list_mode[MENU]->display(&wdw);

            // Update the window
            wdw.display();
        }

    private:
};

#endif /* !ARCADE_SFML_HPP_ */
