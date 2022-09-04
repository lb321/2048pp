#ifndef __TEST_GAMEBOARD_H__
#define __TEST_GAMEBOARD_H__

#include "game/Tile.hpp"
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <vector>

template <std::size_t x_size, std::size_t y_size>
class GameBoard {
#define BOARD_SIZE x_size* y_size
  public:
    GameBoard() {
        std::for_each(_tiles.begin(), _tiles.end(), [this](Tile& tile) { _emptyTiles.push_back(&tile); });
        std::cout << "Board size = " << BOARD_SIZE << std::endl;
    }
    ~GameBoard() { }
    GameBoard(const GameBoard& other) = delete;
    GameBoard(GameBoard&&) = delete;
    GameBoard& operator=(const GameBoard& other) = delete;

    const Tile& get(const std::size_t& x, const std::size_t& y) const { return _tiles[x * x_size + y]; }
    Tile& get(const std::size_t& x, const std::size_t& y) { return _tiles[x * x_size + y]; }

    const int& getValue(const std::size_t& x, const std::size_t& y) const { return _tiles[x * x_size + y].getValue(); }

    void put(const std::size_t& x_pos, const std::size_t& y_pos, const int& value) { _tiles[x_pos * x_size + y_pos].setValue(value); }

    void move_down() {
        for (size_t x = 0; x < x_size; x++) {
            for (int y = 0; y < y_size - 1; y++) {
                Tile& _tile = get(x, y);
                Tile& _below = get(x, y + 1);

                if (_tile.getValue() == 0)
                    continue;
                else if (_below.getValue() == _tile.getValue()) {
                    _below.setValue(_below.getValue() * 2);
                    _tile.setValue(0);
                    _emptyTiles.push_back(&_tile);
                    break;
                } else if (_below.getValue() == 0) {
                    _below.setValue(_tile.getValue());
                    _tile.setValue(0);
                    _emptyTiles.push_back(&_tile);
                    _emptyTiles.erase(std::remove(_emptyTiles.begin(), _emptyTiles.end(), &_below));
                    break;
                }
            }
        }
    }
    void move_up();
    void move_vertical();

    void print_board() {
        for (int x = 0; x < x_size; x++) {
            std::cout << "|";
            for (int y = 0; y < y_size; y++) {
                const int* i = &getValue(x, y);
                std::cout << *i << "|";
            }
            std::cout << std::endl;
        }
    }

    bool hasEmptyTiles() const { return _emptyTiles.size() > 0; }

    std::vector<Tile*>& getEmptyTiles() { return _emptyTiles; }

  private:
    std::array<Tile, BOARD_SIZE> _tiles;
    std::vector<Tile*> _emptyTiles;
};

#endif // __TEST_GAMEBOARD_H__