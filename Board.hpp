#pragma once
#include "Direction.hpp"
#include <string>

namespace ariel
{
    class Board
    {
    public:
        //constructor
        Board();

        void post(unsigned int row, unsigned int column, Direction direction, std::string post);

        std::string read(unsigned int row, unsigned int column, Direction direction, unsigned int numberOfChars);

        void show();
    };
}