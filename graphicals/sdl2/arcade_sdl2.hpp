/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** arcade_sdl2
*/

#ifndef ARCADE_SDL2_HPP_
    #define ARCADE_SDL2_HPP_

    #include "../../core/GameState.hpp"
    #include "../../core/IGraphical.hpp"

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>

    #include <map>
    #include <stdio.h>
    #include <string>
    #include <vector>
    #include <iostream>

    enum MainMenuMode { DEFAULT = 0, USERNAME, GAME };

    class arcadeSDL : public IGraph {
        public:
            arcadeSDL();
            ~arcadeSDL();
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
            void displayAll();
            void inputHandler();
            void handleKeyPress(SDL_Keycode key, int &selection, int size);
            arcade::libType getLibType();
            void mainMenu(arcade::GameState *gameState);

        protected:
        private:
            std::map<std::string, SDL_Rect> _categoryRects;
            std::vector<std::string> _gamesTitles;
            std::vector<std::string> _graphicalsTitles;
            std::map<SDL_Surface *, std::string> _scoresText;
            SDL_Surface * _usernameText;
            SDL_Rect _selectedGame;
            SDL_Rect _selectedGraphical;
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
