/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** core
*/

#include "IGame.hpp"
#include "IGraphical.hpp"
#include "Parsing.hpp"
#include <iostream>
#include "string.h"

void argumentsGestion(int ac, char **av, arcade::GameState *gameState)
{
    if (ac != 2) {
        std::cout << "Not enough arguments, try with -h" << std::endl;
        exit(84);
    }
    if (strcmp(av[1], "-h") == 0) {
        std::cout << "./arcade [graphLib]" << std::endl;
        std::cout << "    graphLib = Name of the graphical lib by default" << std::endl;
        exit(84);
    }
    std::vector<std::string> graphList = gameState->getGraphList();
    if (std::find(graphList.begin(), graphList.end(), av[1]) != graphList.end())
        gameState->setGraphLib(av[1]);
    else {
        std::cout << "Graphical Lib does not exist in lib or is not a graphical lib" << std::endl;
        exit(84);
    }
}

// void printStringVector(std::vector<std::string> strings, std::string type)
// {
//     for (int i = 0; i < strings.size(); i++)
//         std::cout << type << " : " << strings[i] << std::endl;
// }

int main (int ac, char **av)
{
    arcade::GameState *gameState = new arcade::GameState();
    argumentsGestion(ac, av, gameState);
    while (1) {
        void *graphLib = dlopen(gameState->getGraphLib().c_str(), RTLD_LAZY);
        if (!graphLib) {
            fprintf(stderr, "%s\n", dlerror());
            exit(84);
        }

        dlerror();
        IGraph *(*instance)();
        *(void **)(&instance) = dlsym(graphLib, "instance");

        if (!instance) {
            fprintf(stderr, "%s\n", dlerror());
            exit(84);
        }
        dlerror();
        (*instance)()->mainMenu(gameState);
    }
    // // ! Boucle avec main menu qui set le gamestate
    // // ! Ensuite lancement du jeu avec la bonne lib graphique

    // arcade::Parsing *parsing = new arcade::Parsing();
    // parsing->parseScoresFromFile("./src/ressources/");
}
