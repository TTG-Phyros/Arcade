/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** arcade_sdl2
*/

#include "arcade_sdl2.hpp"

void arcadeSDL::initializeGameSelector(std::vector<std::string> games)
{

    SDL_Rect rect = {10, 30, 200, 220};

    SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(_renderer, &rect);
    _categoryRects.insert({std::string("Games"), rect});

    SDL_Rect selectedGameRect = {23, 40, 172, 20};

    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 150);
    SDL_RenderDrawRect(_renderer, &selectedGameRect);
    SDL_RenderFillRect(_renderer, &selectedGameRect);
    _selectedGame = selectedGameRect;

    SDL_Rect gamesRect = {25, 40, 170, 20};
    _categoryRects.insert({"GamesRect", gamesRect});

    int size = games.size();
    std::smatch matches;

    for (int i = 0; i < size; i++) {
        std::regex_search(games[i], matches, std::regex(".*arcade_(\\w+).so"));
        if (matches.size() == 2) {
            std::string temp = matches[1];
            int offset = 20 - temp.size();
            _gamesTitles.push_back(std::string(offset / 2, ' ') + temp + std::string((offset / 2) + (offset % 2), ' '));
            SDL_Surface *surfaceMessage = TTF_RenderText_Solid(_font, _gamesTitles[_gamesTitles.size() - 1].c_str(), (i == _gameSelected ? Black : White));
            SDL_Texture *Message = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);
            SDL_RenderCopy(_renderer, Message, NULL, &gamesRect);
            gamesRect.y += 30;
        }
        i++;
    }
}

void arcadeSDL::initializeGraphicalSelector(std::vector<std::string> graphicals)
{
    SDL_Rect rect = {220, 30, 200, 220};

    SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(_renderer, &rect);
    _categoryRects.insert({std::string("Graphicals"), rect});

    SDL_Rect selectedGraphicalRect = {233, 40, 172, 20};

    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 150);
    SDL_RenderDrawRect(_renderer, &selectedGraphicalRect);
    SDL_RenderFillRect(_renderer, &selectedGraphicalRect);
    _selectedGraphical = selectedGraphicalRect;

    SDL_Rect graphicalRect = {235, 40, 170, 20};
    _categoryRects.insert({std::string("GraphicalsRect"), graphicalRect});

    int size = graphicals.size();
    std::smatch matches;

    for (int i = 0; i < size; i++) {
        std::regex_search(graphicals[i], matches, std::regex(".*arcade_(\\w+).so"));
        if (matches.size() == 2) {
            std::string temp = matches[1];
            int offset = 20 - temp.size();
            _graphicalsTitles.push_back(std::string(offset / 2, ' ') + temp + std::string((offset / 2) + (offset % 2), ' '));
            SDL_Surface *surfaceMessage = TTF_RenderText_Solid(_font, _graphicalsTitles[_graphicalsTitles.size() - 1].c_str(), (i == _graphicalSelected ? Black : White));
            SDL_Texture *Message = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);
            SDL_RenderCopy(_renderer, Message, NULL, &graphicalRect);
            graphicalRect.y += 30;
        }
        i++;
    }
}

void arcadeSDL::initializeScoreViewer(std::map<std::string, int> scores)
{
    SDL_Rect rect = {430, 30, 200, 220};

    SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(_renderer, &rect);
    _categoryRects.insert({std::string("Scores"), rect});

    SDL_Rect scoreNameRect = {440, 40, 80, 20};

    SDL_Rect scoreScoreRect = {540, 40, 80, 20};
    _categoryRects.insert({std::string("ScoresNameRect"), scoreNameRect});
    _categoryRects.insert({std::string("ScoresScoreRect"), scoreScoreRect});

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
        _scoresText.insert({surfaceMessageName, score});
        scoreNameRect.y += 30;
        scoreScoreRect.y += 30;
    }
}

void arcadeSDL::initializeUsernameChanger()
{
    SDL_Rect rect = {10, 260, 620, 50};

    SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(_renderer, &rect);
    _categoryRects.insert({std::string("Username"), rect});

    SDL_Rect usernameRect = {30, 275, 100, 20};
    _categoryRects.insert({std::string("UsernameRect"), usernameRect});

    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(_font, "Username : ", {255, 255, 255});
    SDL_Texture *Message = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);
    SDL_RenderCopy(_renderer, Message, NULL, &usernameRect);
    _usernameText = surfaceMessage;
}

arcadeSDL::arcadeSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
        exit(84);
    }

    this->setWindow(SDL_CreateWindow(
        "Main Menu SDL2",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        320,
        SDL_WINDOW_SHOWN
    ));

    this->setRenderer(SDL_CreateRenderer(this->getWindow(), -1, 0));

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    if (TTF_Init() < 0) {
        fprintf(stdout, "Error while initing TTF module\n");
        exit(84);
    }

    this->setFont(TTF_OpenFont("./graphicals/sdl2/arcadeFont.ttf", 15));
    if (!this->getFont()) {
        fprintf(stdout, "Error while loading the font");
        exit(84);
    }
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

void arcadeSDL::displayAll()
{
    SDL_Rect gameRect = _categoryRects.find("Games")->second;
    SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(_renderer, &gameRect);
    SDL_Rect gamesRect = _categoryRects.find("GamesRect")->second;

    int i = 0;

    for (const auto &lib : _gamesTitles) {
        if (i == _gameSelected) {
            _selectedGame.y = gamesRect.y;
            SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 150);
            SDL_RenderDrawRect(_renderer, &_selectedGame);
            SDL_RenderFillRect(_renderer, &_selectedGame);
        }
        SDL_Surface *surfaceGame = TTF_RenderText_Solid(_font, lib.c_str(), (i == _gameSelected ? Black : White));
        SDL_RenderCopy(_renderer, SDL_CreateTextureFromSurface(_renderer, surfaceGame), NULL, &gamesRect);
        gamesRect.y += 30;
        i++;
    }

    SDL_Rect graphicalRect = _categoryRects.find("Graphicals")->second;
    SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(_renderer, &graphicalRect);
    SDL_Rect graphicalsRect = _categoryRects.find("GraphicalsRect")->second;
    i = 0;

    for (const auto &lib : _graphicalsTitles) {
        if (i == _graphicalSelected) {
            _selectedGraphical.y = graphicalsRect.y;
            SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 150);
            SDL_RenderDrawRect(_renderer, &_selectedGraphical);
            SDL_RenderFillRect(_renderer, &_selectedGraphical);
        }
        SDL_Surface *surfaceGraphical = TTF_RenderText_Solid(_font, lib.c_str(), (i == _graphicalSelected ? Black : White));
        SDL_Texture *graphicalName = SDL_CreateTextureFromSurface(_renderer, surfaceGraphical);
        SDL_RenderCopy(_renderer, graphicalName, NULL, &graphicalsRect);
        graphicalsRect.y += 30;
        i++;
    }

    SDL_Rect scoreRect = _categoryRects.find("Scores")->second;
    SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(_renderer, &scoreRect);
    SDL_Rect scoreNameRect = _categoryRects.find("ScoresNameRect")->second;
    SDL_Rect scoreScoreRect = _categoryRects.find("ScoresScoreRect")->second;
    for (auto &object : _scoresText) {
        SDL_Texture *scoreName = SDL_CreateTextureFromSurface(_renderer, object.first);
        SDL_RenderCopy(_renderer, scoreName, NULL, &scoreNameRect);
        scoreNameRect.y += 30;
        SDL_Surface *surfaceMessageScore = TTF_RenderText_Solid(_font, object.second.c_str(), {255, 255, 255});
        SDL_Texture *scoreScore = SDL_CreateTextureFromSurface(_renderer, surfaceMessageScore);
        scoreScoreRect.x = 540;
        scoreScoreRect.w = 80;
        int offset = 80 - (10 * object.second.length());
        scoreScoreRect.x += offset;
        scoreScoreRect.w -= offset;
        SDL_RenderCopy(_renderer, scoreScore, NULL, &scoreScoreRect);
        scoreScoreRect.y += 30;
    }

    SDL_Rect usernameRectCat = _categoryRects.find("Username")->second;
    SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(_renderer, &usernameRectCat);
    SDL_Rect usernameRect = _categoryRects.find("UsernameRect")->second;
    SDL_Texture *usernameName = SDL_CreateTextureFromSurface(_renderer, _usernameText);
    SDL_RenderCopy(_renderer, usernameName, NULL, &usernameRect);

    if (_mode == USERNAME) {
        usernameRect.x += usernameRect.w + 10;
        SDL_Surface *currentUsername = TTF_RenderText_Solid(_font, _username.c_str(), {255, 255, 255});
        usernameRect.w = 10 * _username.size();
        SDL_Texture *currentUserNameText = SDL_CreateTextureFromSurface(_renderer, currentUsername);
        SDL_RenderCopy(_renderer, currentUserNameText, NULL, &usernameRect);
    }
}

void arcadeSDL::handleKeyPress(SDL_Keycode key, int& selection, int size) {
    if (_mode == DEFAULT) {
        if (key == SDLK_F1 || key == SDLK_F3) {
            selection = selection == 0 ? (size - 1) : selection - 1;
        } else if (key == SDLK_F2 || key == SDLK_F4) {
            selection = selection == (size - 1) ? 0 : selection + 1;
        }
    }
}

void arcadeSDL::inputHandler()
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
                    handleKeyPress(event.key.keysym.sym, _gameSelected, _gamesTitles.size());
                    break;
                case SDLK_F3:
                case SDLK_F4:
                    handleKeyPress(event.key.keysym.sym, _graphicalSelected, _graphicalsTitles.size());
                    break;

                case SDLK_RETURN:
                    _mode = (_mode == USERNAME && _username.size() > 1) ? GAME : _mode;
                    _mode = _mode == DEFAULT ? USERNAME : _mode;
                    break;

                case SDLK_ESCAPE:
                    if (_mode == USERNAME) {
                        _mode = DEFAULT;
                        _username = "_";
                    }
                    _mode = _mode == GAME ? USERNAME : _mode;
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

}

arcade::libType arcadeSDL::getLibType()
{
    return arcade::libType::GRAPHICALS;
}

void arcadeSDL::mainMenu(arcade::GameState *gameState)
{
    std::map<std::string, int> scores = {
        {"Michel", 50},
        {"Patrick", 1002},
        {"Adam", 567}
    };
    this->initializeGameSelector(gameState->getGamesList());
    this->initializeGraphicalSelector(gameState->getGraphList());
    this->initializeScoreViewer(scores);
    this->initializeUsernameChanger();
    while (this->getWindow()) {
        this->inputHandler();
        SDL_SetRenderDrawColor(this->getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(this->getRenderer());
        this->displayAll();
        SDL_RenderPresent(this->getRenderer());
    }

    if (this->getWindow())
        SDL_DestroyWindow(this->getWindow());
    SDL_Quit();
}

extern "C" arcadeSDL *instance()
{
    return new arcadeSDL();
}
