#include "Board.hpp"
#include "Direction.hpp"
#include <string>

namespace ariel
{

    //constructor
    Board::Board() {}

    void Board::post(unsigned int row, unsigned int column, Direction direction, std::string post) {}

    std::string Board::read(unsigned int row, unsigned int column, Direction direction, unsigned int numberOfChars)
    {
        return " ";
    }

    void Board::show() {}

}