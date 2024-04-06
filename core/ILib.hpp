/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** ILib
*/

#ifndef ILIB_HPP_
#define ILIB_HPP_

#include "GameState.hpp"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

namespace arcade
{
    class ILib;
}

class arcade::ILib {
    public:
        virtual arcade::libType getLibType() = 0;
        virtual ~ILib() = default;

    protected:
    private:
};

#endif /* !ILIB_HPP_ */
