#include "game/Tile.hpp"

Tile::~Tile() { }

const int& Tile::getValue() const { return _value; }

void Tile::setValue(const int& value) { this->_value = value; }

void Tile::setIndex(const int& i) { this->_index = i; }

const int& Tile::getIndex() const { return _index; }