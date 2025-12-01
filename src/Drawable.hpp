#pragma once
#include "Coord.hpp"
class Console;

enum ALIGNMENT
{
    TOPLEFT,
    TOPRIGHT,
    BOTTOMLEFT,
    BOTTOMRIGHT
};

class Drawable
{
private:
    Coord position;
    ALIGNMENT alignment;

public:
    Drawable(const Coord position, const ALIGNMENT alignment);
    void draw(Console *c) const;
};