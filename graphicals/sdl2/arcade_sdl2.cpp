/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** arcade_sdl2
*/

#include "arcade_sdl2.hpp"
#include "../../core/GameState.hpp"
#include "../../core/core.hpp"

arcadeSDL::arcadeSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw GraphInitError("Échec de l'initialisation de la SDL : " + std::string(SDL_GetError()));

    this->setWindow(SDL_CreateWindow(
    "Main Menu SDL2",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    640,
    320,
    SDL_WINDOW_SHOWN));

    this->setRenderer(SDL_CreateRenderer(this->getWindow(), -1, 0));

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    if (TTF_Init() < 0)
        throw GraphInitError("Error while initing TTF module of SDL\n");
    this->setFont(TTF_OpenFont("./graphicals/sdl2/arcadeFont.ttf", 15));
    if (!this->getFont())
        throw GraphInitError("Error while loading the font of SDL");
}

void arcadeSDL::setFont(TTF_Font *font)
{
    _font = font;
}

TTF_Font *arcadeSDL::getFont()
{
    return _font;
}

void arcadeSDL::setRenderer(SDL_Renderer *renderer)
{
    _renderer = renderer;
}

SDL_Renderer *arcadeSDL::getRenderer()
{
    return _renderer;
}

void arcadeSDL::setWindow(SDL_Window *window)
{
    _window = window;
}

SDL_Window *arcadeSDL::getWindow()
{
    return _window;
}

MainMenuMode arcadeSDL::getMode()
{
    return _mode;
}

void arcadeSDL::setMode(MainMenuMode mode)
{
    _mode = mode;
}

void arcadeSDL::displayGameList(arcade::GameState &gameState)
{
    SDL_Rect gameRect = {10, 30, 200, 220};
    SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(_renderer, &gameRect);
    SDL_Rect gamesRect = {25, 40, 170, 20};

    int i = 0;

    std::vector<std::string> gameList = gameState.getGamesList();
    SDL_Rect selectedGame = {23, 40, 172, 20};
    for (const auto &lib : gameList) {
        if (strcmp(lib.c_str(), gameList[_gameSelected].c_str()) == 0) {
            selectedGame.y = gamesRect.y;
            SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 150);
            SDL_RenderDrawRect(_renderer, &selectedGame);
            SDL_RenderFillRect(_renderer, &selectedGame);
        }
        SDL_Surface *surfaceGame = TTF_RenderText_Solid(_font, lib.c_str(), ((strcmp(lib.c_str(), gameList[_gameSelected].c_str())) == 0 ? Black : White));
        SDL_RenderCopy(_renderer, SDL_CreateTextureFromSurface(_renderer, surfaceGame), NULL, &gamesRect);
        gamesRect.y += 30;
        i++;
    }
}

void arcadeSDL::displayGraphList(arcade::GameState &gameState)
{
    SDL_Rect graphicalRect = {220, 30, 200, 220};
    SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(_renderer, &graphicalRect);
    SDL_Rect graphicalsRect = {233, 40, 172, 20};
    int i = 0;

    std::vector<std::string> graphList = gameState.getGraphList();
    SDL_Rect selectedGraphical = {233, 40, 172, 20};
    for (const auto &lib : graphList) {
        if (strcmp(lib.c_str(), graphList[_graphicalSelected].c_str()) == 0) {
            selectedGraphical.y = graphicalsRect.y;
            SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 150);
            SDL_RenderDrawRect(_renderer, &selectedGraphical);
            SDL_RenderFillRect(_renderer, &selectedGraphical);
        }
        SDL_Surface *surfaceGraphical = TTF_RenderText_Solid(_font, lib.c_str(), ((strcmp(lib.c_str(), graphList[_graphicalSelected].c_str())) == 0 ? Black : White));
        SDL_Texture *graphicalName = SDL_CreateTextureFromSurface(_renderer, surfaceGraphical);
        SDL_RenderCopy(_renderer, graphicalName, NULL, &graphicalsRect);
        graphicalsRect.y += 30;
        i++;
    }
}

void arcadeSDL::displayScores(arcade::GameState &gameState)
{
    SDL_Rect scoreRect = {430, 30, 200, 220};
    SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(_renderer, &scoreRect);
    SDL_Rect scoreNameRect = {440, 40, 80, 20};
    SDL_Rect scoreScoreRect = {540, 40, 80, 20};
    std::map<std::string, int> scores = gameState.getGameScores(gameState.getGamesList()[_gameSelected]);
    std::map<std::string, int>::iterator itScore = scores.begin();
    for (; itScore != scores.end(); ++itScore) {
        SDL_Surface *surfaceMessageName = TTF_RenderText_Solid(_font, itScore->first.c_str(), {255, 255, 255});
        SDL_Texture *MessageName = SDL_CreateTextureFromSurface(_renderer, surfaceMessageName);
        SDL_RenderCopy(_renderer, MessageName, NULL, &scoreNameRect);
        std::string score = std::to_string(itScore->second);
        SDL_Surface *surfaceMessageScore = TTF_RenderText_Solid(_font, score.c_str(), {255, 255, 255});
        SDL_Texture *MessageScore = SDL_CreateTextureFromSurface(_renderer, surfaceMessageScore);
        scoreScoreRect.x = 540;
        scoreScoreRect.w = 80;
        int offset = 80 - (10 * score.length());
        scoreScoreRect.x += offset;
        scoreScoreRect.w -= offset;
        SDL_RenderCopy(_renderer, MessageScore, NULL, &scoreScoreRect);
        scoreNameRect.y += 30;
        scoreScoreRect.y += 30;
    }
}

void arcadeSDL::displayUsername(arcade::GameState &gameState)
{
    SDL_Rect usernameRectCat = {10, 260, 620, 50};
    SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(_renderer, &usernameRectCat);
    SDL_Rect usernameRect = {30, 275, 100, 20};
    SDL_Surface *usernameText = TTF_RenderText_Solid(_font, "Username : ", {255, 255, 255});
    SDL_Texture *usernameName = SDL_CreateTextureFromSurface(_renderer, usernameText);
    SDL_RenderCopy(_renderer, usernameName, NULL, &usernameRect);

    if (_mode == USERNAME) {
        usernameRect.x += usernameRect.w + 10;
        SDL_Surface *currentUsername = TTF_RenderText_Solid(_font, _username.c_str(), {255, 255, 255});
        usernameRect.w = 10 * _username.size();
        SDL_Texture *currentUserNameText = SDL_CreateTextureFromSurface(_renderer, currentUsername);
        SDL_RenderCopy(_renderer, currentUserNameText, NULL, &usernameRect);
    }
}

void arcadeSDL::displayAll(arcade::GameState &gameState)
{
    this->displayGameList(gameState);
    this->displayGraphList(gameState);
    this->displayScores(gameState);
    this->displayUsername(gameState);
}

void arcadeSDL::handleKeyPress(SDL_Keycode key, int& selection, int size) {
    if (_mode == DEFAULT || _mode == GAME) {
        if (key == SDLK_F1 || key == SDLK_F3) {
            selection = selection == 0 ? (size - 1) : selection - 1;
        } else if (key == SDLK_F2 || key == SDLK_F4) {
            selection = selection == (size - 1) ? 0 : selection + 1;
        }
    }
}

void arcadeSDL::inputHandler(arcade::GameState &gameState)
{
    SDL_Event event;

    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            exit(0);
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_F1:
                case SDLK_F2:
                    handleKeyPress(event.key.keysym.sym, _gameSelected, gameState.getGamesList().size());
                    break;
                case SDLK_F3:
                case SDLK_F4:
                    handleKeyPress(event.key.keysym.sym, _graphicalSelected, gameState.getGraphList().size());
                    break;

                case SDLK_RETURN:
                    if (_mode == USERNAME && _username.size() > 1) {
                        gameState.setState(arcade::screenState::IN_GAME);
                        gameState.setGameLib(gameState.getGamesList()[_gameSelected]);
                        gameState.setGraphLib(gameState.getGraphList()[_graphicalSelected]);
                        _username.pop_back();
                        gameState.setUsername(_username);
                        _mode = GAME;
                    }
                    _mode = _mode == DEFAULT ? USERNAME : _mode;
                    break;

                case SDLK_ESCAPE:
                    if (_mode == USERNAME) {
                        _mode = DEFAULT;
                        _username = "_";
                    }
                    break;

                case SDLK_BACKSPACE:
                    if (_mode == USERNAME) {
                        if (_username.size() > 1) {
                            _username.pop_back();
                            _username.pop_back();
                            _username += "_";
                        }
                    }
                    break;

                default:
                    break;
            }
            break;
        case SDL_TEXTINPUT:
            if (_mode == USERNAME) {
                _username.pop_back();
                _username += event.text.text;
                _username += "_";
            }
            break;
        default:
            break;
    }
}

arcadeSDL::~arcadeSDL()
{
    if (this->getWindow())
        SDL_DestroyWindow(this->getWindow());
    SDL_Quit();
}

arcade::libType arcadeSDL::getLibType()
{
    return arcade::libType::GRAPHICALS;
}

void arcadeSDL::mainMenu(arcade::GameState &gameState)
{
    this->inputHandler(gameState);
    SDL_SetRenderDrawColor(this->getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(this->getRenderer());
    this->displayAll(gameState);
    SDL_RenderPresent(this->getRenderer());
}

void arcadeSDL::handleInput(arcade::GameState &gameState)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
        if (event.type == SDL_KEYUP)
            gameState.setKey(arcade::keyPressed::NOTHING);
    for (int i = 0; i < 500; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        while(SDL_PollEvent(&event)) {                
            if (event.type == SDL_KEYDOWN)
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        gameState.setKey(arcade::keyPressed::LEFT_KEY);
                        break;
                    case SDLK_RIGHT:
                        gameState.setKey(arcade::keyPressed::RIGHT_KEY);
                        break;
                    case SDLK_UP:
                        gameState.setKey(arcade::keyPressed::UP_KEY);
                        break;
                    case SDLK_DOWN:
                        gameState.setKey(arcade::keyPressed::DOWN_KEY);
                        break;
                    case SDLK_ESCAPE:
                        gameState.setState(arcade::screenState::STOP);
                        break;
                    case SDLK_SPACE:
                        gameState.setKey(arcade::keyPressed::SPACE_KEY);
                        break;
                    case SDLK_F1:
                    case SDLK_F2:
                        handleKeyPress(event.key.keysym.sym, _gameSelected, gameState.getGamesList().size());
                        gameState.setGameLib(gameState.getGamesList()[_gameSelected]);
                        gameState.setKey(arcade::keyPressed::NOTHING);
                        break;
                    case SDLK_F3:
                    case SDLK_F4:
                        handleKeyPress(event.key.keysym.sym, _graphicalSelected, gameState.getGraphList().size());
                        gameState.setGraphLib(gameState.getGraphList()[_graphicalSelected]);
                        break;
                    default:
                        break;
                }
        }
    }
}

void arcadeSDL::displayGame(arcade::GameState &gameState)
{
    handleInput(gameState);
    SDL_SetRenderDrawColor(this->getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(this->getRenderer());
    std::vector<std::string> map = gameState.getGameArray();
    int size = map.size();
    if (size > 0) {
        int width = 640 / map[0].size();
        int height = 320 / size;
        SDL_Rect rect = {0, 0, width, height};
        for (int i = 0; i < size; i++) {
            int lineSize = map[i].size();
            for (int j = 0; j < lineSize; j++) {
                switch (map[i][j]) {
                    case 'O':
                        SDL_SetRenderDrawColor(this->getRenderer(), 0, 165, 0, 255);
                        break;
                    case 'o':
                        SDL_SetRenderDrawColor(this->getRenderer(), 0, 255, 0, 255);
                        break;
                    case 'X':
                        SDL_SetRenderDrawColor(this->getRenderer(), 0, 0, 255, 255);
                        break;
                    case ' ':
                        SDL_SetRenderDrawColor(this->getRenderer(), 0, 0, 0, 255);
                        break;
                    case 'F':
                        SDL_SetRenderDrawColor(this->getRenderer(), 255, 0, 0, 255);
                        break;
                    default:
                        break;
                }
                SDL_RenderDrawRect(this->getRenderer(), &rect);
                SDL_RenderFillRect(this->getRenderer(), &rect);
                rect.x += width;
            }
            rect.x = 0;
            rect.y += height;
        }
    }
    SDL_RenderPresent(this->getRenderer());
}

void arcadeSDL::displayWindow(arcade::GameState &gameState)
{
    arcade::screenState state = gameState.getState();
    switch (state) {
        case arcade::screenState::ARCADE_MENU:
            this->mainMenu(gameState);
            break;
        case arcade::screenState::IN_GAME:
            this->displayGame(gameState);
            break;

        default:
            break;
    }
}

extern "C" arcadeSDL *instance()
{
    return new arcadeSDL();
}
