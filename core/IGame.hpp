/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "GameState.hpp"
#include "ILib.hpp"

namespace arcade {
    class IGame;
};

class arcade::IGame : public arcade::ILib {
    public:
        virtual arcade::libType getLibType() = 0;
        virtual void updateGameState(arcade::GameState &gameState) = 0;
        virtual ~IGame() = default;

    protected:
    private:
};

#endif /* !IGAME_HPP_ */
