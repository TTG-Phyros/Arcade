/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IGraph
*/

#ifndef IGRAPH_HPP_
#define IGRAPH_HPP_

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "GameState.hpp"

class IGraph {
    public:
        virtual void mainMenu(arcade::GameState *gameState) = 0;
        virtual arcade::libType getLibType() = 0;
        virtual ~IGraph() = default;

    protected:
    private:
};

#endif /* !IGRAPH_HPP_ */
