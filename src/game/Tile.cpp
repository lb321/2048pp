#include "game/Tile.hpp"

Tile::Tile(const Tile *left, const Tile *right, const Tile *up,
           const Tile *down)
    : _left(left), _right(right), _up(up), _down(down), _value(0) {}

Tile::~Tile() {}

const int& Tile::getValue() const
{
  return _value;
}

void Tile::setValue(const int& value)
{
  this->_value = value;
}
