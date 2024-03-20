/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IGraphic
*/

#ifndef IGRAPHICAL_HPP_
#define IGRAPHICAL_HPP_

#include <string>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

namespace Graphical{
    class IGraphical {
        public:
            IGraphical(std::string graphicalLibrary);
            void mainMenu(void);
            ~IGraphical();

        protected:
        private:
            void *_lib;
            double (*_mainMenu)(void);
            char *_error;
    };
    class GraphicalError : public std::exception {
        public:
            GraphicalError(std::string error) : _error(error) {};
            const char *what() const noexcept { return _error.c_str(); };
        private:
            const std::string _error;
    };
};

#endif /* !IGRAPHICAL_HPP_ */
