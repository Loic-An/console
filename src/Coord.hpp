#pragma once
#include <sys/ioctl.h>

class Coord
{
private:
    int row;
    int col;

public:
    Coord(const int &row, const int &col);
    Coord(const winsize &obj);
    static const Coord TOPLEFT;
    static const Coord TOPRIGHT;
    static const Coord BOTTOMLEFT;
    static const Coord BOTTOMRIGHT;
    int getCol() const;
    int getRow() const;
};

inline const Coord Coord::TOPLEFT{1, 1};
inline const Coord Coord::TOPRIGHT{-1, 1};
inline const Coord Coord::BOTTOMLEFT{1, -1};
inline const Coord Coord::BOTTOMRIGHT{-1, -1};