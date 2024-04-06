/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** arcade_sdl2
*/

#ifndef ARCADE_SDL2_HPP_
    #define ARCADE_SDL2_HPP_

    #include "../../core/IGraph.hpp"
    #include "../../core/ILib.hpp"

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>

    #include <map>
    #include <stdio.h>
    #include <string>
    #include <vector>
    #include <iostream>
    #include <thread>

    enum MainMenuMode { DEFAULT = 0, USERNAME, GAME };

    class arcadeSDL : public arcade::IGraph {
        public:
            arcadeSDL();
            ~arcadeSDL();
            void displayWindow(arcade::GameState &gameState);
            void initializeGameSelector(std::vector<std::string> games);
            void initializeGraphicalSelector(std::vector<std::string> graphicals);
            void initializeScoreViewer(std::map<std::string, int> scores);
            void initializeUsernameChanger();
            void setFont(TTF_Font *font);
            TTF_Font *getFont();
            void setRenderer(SDL_Renderer *renderer);
            SDL_Renderer *getRenderer();
            void setWindow(SDL_Window *window);
            SDL_Window *getWindow();
            void setMode(MainMenuMode mode);
            MainMenuMode getMode();
            void displayAll(arcade::GameState &gameState);
            void inputHandler(arcade::GameState &gameState);
            void handleKeyPress(SDL_Keycode key, int &selection, int size);
            arcade::libType getLibType();
            void mainMenu(arcade::GameState &gameState);
            void displayGame(arcade::GameState &gameState);
            void handleInput(arcade::GameState &gameState);

        protected:
        private:
            int _gameSelected = 0;
            int _graphicalSelected = 0; 
            std::string _username = "_";
            SDL_Window *_window;
            TTF_Font *_font;
            SDL_Renderer *_renderer;
            MainMenuMode _mode = DEFAULT;
    };

    SDL_Color Black = {0, 0, 0};
    SDL_Color White = {255, 255, 255};

#endif /* !ARCADE_SDL2_HPP_ */
