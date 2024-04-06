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
#include "ILib.hpp"

namespace arcade
{
    class IGraph;
    enum arcadeStepMenu {
        GRAPH = 0,
        GAMES,
        USERNAME
    };
}

class arcade::IGraph : public arcade::ILib {
    public:
        virtual void displayWindow(GameState &gs) = 0;
        virtual arcade::libType getLibType() = 0;
        virtual ~IGraph() = default;

    protected:
    private:
};

#endif /* !IGRAPH_HPP_ */
