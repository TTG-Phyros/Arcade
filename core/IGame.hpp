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

class IGame {
    public:
        virtual arcade::libType getLibType() = 0;
        virtual ~IGame() = default;

    protected:
    private:
};

#endif /* !IGAME_HPP_ */
