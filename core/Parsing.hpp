/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Parsing
*/

#ifndef PARSING_HPP_
#define PARSING_HPP_

#include <dlfcn.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

namespace arcade
{
    class Parsing;   
}


class arcade::Parsing {
    public:
        Parsing();
        ~Parsing();
        static std::map<std::string, int> parseOneScoreFile(std::string scoreFilePath);
        static std::map<std::string, std::map<std::string, int>> parseScoresFromFile(std::string scoresPath);
        static std::vector<std::string> getLibsFromPath(std::string libsPath);
        static std::vector<std::string> getGamesFromLibs(std::vector<std::string> allLibs, std::vector<std::string> graphLibs);
        static std::vector<std::string> getGraphFromLibs(std::vector<std::string> allLibs);

    protected:
    private:
};

#endif /* !PARSING_HPP_ */
