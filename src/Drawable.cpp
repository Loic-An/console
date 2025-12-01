#include "Drawable.hpp"
#include "console.hpp"

Drawable::Drawable(const Coord position = Coord::TOPLEFT, const ALIGNMENT alignment = TOPLEFT) : position(position), alignment(alignment)
{
}

void Drawable::draw(Console *c) const
{
    c->write("Drawable<position=");
    c->write(position);
    switch (alignment)
    {
    case (TOPLEFT):
        c->write(";alignment=topleft>");
        break;
    case (TOPRIGHT):
        c->write(";alignment=topright>");
        break;
    case (BOTTOMLEFT):
        c->write(";alignment=bottomleft>");
        break;
    case (BOTTOMRIGHT):
        c->write(";alignment=bottomright>");
        break;
    }
}
