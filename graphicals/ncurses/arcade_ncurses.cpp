/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** arcade_ncurses
*/

#include "arcade_ncurses.hpp"

MainMenu::MainMenu() {
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    cbreak();
    start_color();
}

MainMenu::~MainMenu()
{
    endwin();
}

void MainMenu::displayMenu(arcade::GameState &gameState) {
    clear();

    std::vector<std::string> games = gameState.getGamesList();
    std::vector<std::string> graphics = gameState.getGraphList();

    displayHeader();
    displayGameMenu(games, selectedGameIndex);
    displayGraphicMenu(graphics, selectedGraphicIndex, selectedCategory);
    displayScoreMenu(gameState.getGameScores(games[selectedGameIndex]));

    refresh();

    int ch = getch();
    handleInput(ch, games.size(), graphics.size(), gameState);

    if (ch == 10 && username.size() > 1) {
        printSelectedGameAndGraphic(games[selectedGameIndex], graphics[selectedGraphicIndex]);
        gameState.setState(arcade::screenState::IN_GAME);
        gameState.setGameLib(games[selectedGameIndex]);
        gameState.setGraphLib(graphics[selectedGraphicIndex]);
        gameState.setUsername(username);
    }
}

void MainMenu::displayHeader() {
    box(mainMenu, ACS_VLINE, ACS_HLINE);
    mvwprintw(mainMenu, 0, 26, " Arcade ");
    mvwprintw(mainMenu, 18, 2, ("Username : " + username).c_str());
    mvwprintw(mainMenu, 19, 2, "ARROW KEY to navigate and ENTER when you have selected your game and graphic lib");
}

void MainMenu::displayGameMenu(const std::vector<std::string>& games, int selectedGameIndex) {
    box(gameMenu, ACS_VLINE, ACS_HLINE);
    mvwprintw(gameMenu, 0, 6, " Games ");

    int size = games.size();

    for (int i = 0; i < size; ++i) {
        if (selectedGameIndex == i)
            wattron(gameMenu, A_REVERSE);
        mvwprintw(gameMenu, 2 + i * 2, 2, "%s", games[i].c_str());
        wattroff(gameMenu, A_REVERSE);
    }
}

void MainMenu::displayGraphicMenu(const std::vector<std::string>& graphics, int selectedGraphicIndex, int selectedCategory) {
    box(graphicMenu, ACS_VLINE, ACS_HLINE);
    mvwprintw(graphicMenu, 0, 4, " Graphics ");

    int size = graphics.size();

    for (int i = 0; i < size; ++i) {
        if (selectedGraphicIndex == i && selectedCategory == 1)
            wattron(graphicMenu, A_REVERSE);
        mvwprintw(graphicMenu, 2 + i * 2, 2, "%s", graphics[i].c_str());
        wattroff(graphicMenu, A_REVERSE);
    }
}

void MainMenu::displayScoreMenu(std::map<std::string, int> scores) {
    box(scoreMenu, ACS_VLINE, ACS_HLINE);
    mvwprintw(scoreMenu, 0, 6, " Score ");
    std::map<std::string, int>::iterator it = scores.begin();
    for (int i = 0; it != scores.end(); ++it, i++) {
        mvwprintw(scoreMenu, 2 + i * 2, 2, "%s %d", it->first.c_str(), it->second);
    }
}

void MainMenu::handleInput(int ch, int numGames, int numGraphics, arcade::GameState &gameState)
{
    if (ch == KEY_DOWN) {
        if (selectedCategory == 0) {
            selectedGameIndex++;
            if (selectedGameIndex >= numGames)
                selectedGameIndex = numGames - 1;
        } else {
            selectedGraphicIndex++;
            if (selectedGraphicIndex >= numGraphics)
                selectedGraphicIndex = numGraphics - 1;
        }
    } else if (ch == KEY_UP) {
        if (selectedCategory == 0) {
            selectedGameIndex--;
            if (selectedGameIndex < 0)
                selectedGameIndex = 0;
        } else {
            selectedGraphicIndex--;
            if (selectedGraphicIndex < 0)
                selectedGraphicIndex = 0;
        }
    } else if (ch == KEY_RIGHT)
        selectedCategory = 1;
    else if (ch == KEY_LEFT)
        selectedCategory = 0;
    else if (ch == 27)
        gameState.setState(arcade::screenState::STOP);
    else if (ch == KEY_BACKSPACE) {
        if (username.size() >= 1)
            username.pop_back();
    } else if (ch != 10)
        username += ch;
}

void MainMenu::printSelectedGameAndGraphic(const std::string& selectedGame, const std::string& selectedGraphic)
{
    clear();
    int a = 0, b = 3;
    time_t startTime = time(nullptr);
    while (true){
        clear();
        printw("Selected Game: %s\n", selectedGame.c_str());
        printw("Selected Graphic Library: %s\n", selectedGraphic.c_str());
        printw("\nthe game will start in %d\n\n", b);
        if (a == 0){
            printw("\n(°_°)\n(  (>\n/  \\ \n");
            a = 1;
            b--;
        } else {
            printw  ("\n(°_°)\n<)  )\n/  \\ \n");
            a = 0;
        }
        if (time(nullptr) - startTime >= 4) break;
        usleep(500000);
        refresh();
    }
}

void MainMenu::inputHandler(arcade::GameState &gameState)
{
    int keyPressed = getch();
    if (keyPressed == 27)
        gameState.setState(arcade::screenState::GAME_END);
    if (keyPressed == KEY_UP)
        gameState.setKey(arcade::keyPressed::UP_KEY);
    if (keyPressed == KEY_DOWN)
        gameState.setKey(arcade::keyPressed::DOWN_KEY);
    if (keyPressed == KEY_LEFT)
        gameState.setKey(arcade::keyPressed::LEFT_KEY);
    if (keyPressed == KEY_RIGHT)
        gameState.setKey(arcade::keyPressed::RIGHT_KEY);
    if (keyPressed == 32)
        gameState.setKey(arcade::keyPressed::SPACE_KEY);
    if (keyPressed == 103 || keyPressed == 71) {
        int numGames = gameState.getGamesList().size();
        selectedGameIndex++;
        if (selectedGameIndex >= numGames)
            selectedGameIndex = 0;
        gameState.setGameLib(gameState.getGamesList()[selectedGameIndex]);
        gameState.setKey(arcade::keyPressed::NOTHING);
    }
    if (keyPressed == 104 || keyPressed == 72) {
        int numGraph = gameState.getGraphList().size();
        selectedGraphicIndex++;
        if (selectedGraphicIndex >= numGraph)
            selectedGraphicIndex = 0;
        gameState.setGraphLib(gameState.getGraphList()[selectedGraphicIndex]);
    }
}

void MainMenu::drawMap(std::vector<std::string> gameMap)
{
    for (size_t i = 0; i < gameMap.size(); ++i) {
        for (size_t j = 0; j <= gameMap[i].size(); ++j) {
            if (gameMap[i][j] == 'X') {
                init_pair(1, COLOR_RED, COLOR_BLUE);
                wattron(mapgaming, COLOR_PAIR(1));
                mvwprintw(mapgaming, 2 + i, ((90 - (gameMap[i].size() * 2)) / 2) + (j * 2), "%s", "  ");
                wattroff(mapgaming, COLOR_PAIR(1));
            } else if (gameMap[i][j] == 'O') {
                init_pair(2, COLOR_RED, COLOR_YELLOW);
                wattron(mapgaming, COLOR_PAIR(2));
                mvwprintw(mapgaming, 2 + i, ((90 - (gameMap[i].size() * 2)) / 2) + (j * 2), "%s", "  ");
                wattroff(mapgaming, COLOR_PAIR(2));
            } else if (gameMap[i][j] == 'o') {
                init_pair(3, COLOR_RED, COLOR_GREEN);
                wattron(mapgaming, COLOR_PAIR(3));
                mvwprintw(mapgaming, 2 + i, ((90 - (gameMap[i].size() * 2)) / 2) + (j * 2), "%s", "  ");
                wattroff(mapgaming, COLOR_PAIR(3));
            } else if (gameMap[i][j] == 'F') {
                init_pair(4, COLOR_RED, COLOR_RED);
                wattron(mapgaming, COLOR_PAIR(4));
                mvwprintw(mapgaming, 2 + i, ((90 - (gameMap[i].size() * 2)) / 2) + (j * 2), "%s", "  ");
                wattroff(mapgaming, COLOR_PAIR(4));
            } else if (gameMap[i][j] == ' ') {
                mvwprintw(mapgaming, 2 + i, ((90 - (gameMap[i].size() * 2)) / 2) + (j * 2), "%s", "  ");
            }
        }
    }
}

void MainMenu::displayGame(arcade::GameState &gameState)
{
    clear();
    std::vector<std::string> gameMap = gameState.getGameArray();
    box(mapgaming, ACS_VLINE, ACS_HLINE);
    mvwprintw(mapgaming, 1, 41, " Arcade ");

    drawMap(gameMap);

    refresh();
    timeout(1);
    inputHandler(gameState);
    usleep(500000);
    timeout(-1);
}

void MainMenu::displayWindow(arcade::GameState &gameState)
{
    arcade::screenState state = gameState.getState();
    switch (state) {
    case arcade::screenState::ARCADE_MENU:
        this->displayMenu(gameState);
        break;
    case arcade::screenState::IN_GAME:
        this->displayGame(gameState);
        break;

    default:
        break;
    }
}

arcade::libType MainMenu::getLibType()
{
    return arcade::libType::GRAPHICALS;
}

extern "C" MainMenu *instance()
{
    return new MainMenu();
}
