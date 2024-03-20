/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IGraphical
*/

#include "IGraphical.hpp"

Graphical::IGraphical::IGraphical(std::string graphicalLibrary)
{
    _lib = dlopen(graphicalLibrary.c_str(), RTLD_LAZY);
    if (!_lib) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }

    dlerror();
    *(void **)(&_mainMenu) = dlsym(_lib, "mainMenu");

    if ((_error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", _error);
        exit(84);
    }
}

void Graphical::IGraphical::mainMenu()
{
    (*_mainMenu)();
}

Graphical::IGraphical::~IGraphical()
{
    dlclose(_lib);
}
