#include "Coord.hpp"

Coord::Coord(const int &row = 1, const int &col = 1) : row(row), col(col)
{
}

Coord::Coord(const winsize &obj) : row(obj.ws_row), col(obj.ws_col)
{
}

int Coord::getCol() const
{
    return this->col;
}

int Coord::getRow() const
{
    return this->row;
}
