#ifndef __TEST_GAMEBOARD_H__
#define __TEST_GAMEBOARD_H__

#include "game/Tile.hpp"
#include "util/Random.h"
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <ostream>
#include <vector>

template <std::size_t x_size, std::size_t y_size>
class GameBoard {
#define BOARD_SIZE x_size* y_size
#define INDEX_OF_TILE(x, y) x + y * x_size
  public:
    GameBoard() {
        int index {0};
        std::for_each(_tiles.begin(), _tiles.end(), [this, &index](Tile& tile) { 
            _emptyTiles.push_back(&tile); 
            tile.setIndex(index++);
        });
        std::cout << "Board size = " << BOARD_SIZE << std::endl;
    }
    ~GameBoard() { }
    GameBoard(const GameBoard& other) = delete;
    GameBoard(GameBoard&&) = delete;
    GameBoard& operator=(const GameBoard& other) = delete;

    inline const Tile& get(const std::size_t& x, const std::size_t& y) const { return _tiles[x + y * x_size]; }
    inline Tile& get(const std::size_t& x, const std::size_t& y) { return _tiles[x + y * x_size]; }

    const int& getValue(const std::size_t& x, const std::size_t& y) const { return _tiles[x * x_size + y].getValue(); }

    void put(const std::size_t& x_pos, const std::size_t& y_pos, const int& value) { _tiles[x_pos * x_size + y_pos].setValue(value); }

    void move_down() {
        for (size_t x = 0; x < x_size; x++) {
            for (size_t y = 0; y < y_size - 1; y++) {
                Tile& tile = get(x, y);
                Tile& below = get(x, y + 1);

                if (tile.getValue() == 0)
                    continue;
                else if (below.getValue() == tile.getValue()) {
                    below.setValue(below.getValue() * 2);
                    tile.setValue(0);
                    _emptyTiles.push_back(&tile);
                    break;
                } else if (below.getValue() == 0) {
                    below.setValue(tile.getValue());
                    tile.setValue(0);
                    _emptyTiles.push_back(&tile);
                    _emptyTiles.erase(std::remove(_emptyTiles.begin(), _emptyTiles.end(), &below));
                    break;
                }
            }
        }
    }
    void move_up();
    void move_vertical();

    void move_left() {
        // combine
        for (size_t y = 0; y < y_size; y++) {
            for (size_t x = 0; x < x_size - 1; x++) {
                Tile& tile = get(x, y);
                Tile& rightTile = get(x + 1, y);

                if (tile.getValue() == 0)
                    continue;
                else if (rightTile.getValue() == tile.getValue()) {
                    tile.setValue(tile.getValue() * 2);
                    rightTile.setValue(0);
                    _emptyTiles.push_back(&rightTile);
                }
            }
        }

        // move left
        for (size_t y = 0; y < y_size; y++) {
            for (size_t x = x_size - 1; x > 0; x--) {
                Tile& tile = get(x, y);
                Tile& leftTile = get(x - 1, y);

                if (tile.getValue() == 0)
                    continue;
                else if (leftTile.getValue() == 0) {
                    leftTile.setValue(tile.getValue());
                    _emptyTiles.erase(std::remove(_emptyTiles.begin(), _emptyTiles.end(), &leftTile));
                    tile.setValue(0);
                    _emptyTiles.push_back(&tile);
                }
            }
        }
    }

    void move_right() {
        for (size_t y = 0; y < y_size; y++) {
            // the previous tile which does not have a value of 0
            Tile* previousNotNilTile {nullptr};
            Tile* firstNilTile {nullptr};

            // van rechts naar links
            for (int x = x_size - 1; x >= 0; x--) {
                Tile& tile = get(x, y);

                if (tile.getValue() == 0) {
                    if (firstNilTile == nullptr)
                        firstNilTile = &tile;
                } else if (previousNotNilTile == nullptr) {
                    if (firstNilTile != nullptr) { // geen tile met een waarde, maar wel eentje met 0, dus verplaats onze waarde naar de 0
                        setTileValue(firstNilTile, tile.getValue());
                        setTileValue(&tile, 0);
                        previousNotNilTile = firstNilTile;
                        firstNilTile = &_tiles[firstNilTile->getIndex() - 1];
                    } else { // geen tile voor ons om heen te verplaatsen
                        previousNotNilTile = &tile;
                    }
                } else if (previousNotNilTile->getValue() == tile.getValue()) { //merge met de andere
                    previousNotNilTile->setValue(tile.getValue() * 2);
                    tile.setValue(0);
                    _emptyTiles.push_back(&tile);
                    previousNotNilTile = nullptr;

                    if (firstNilTile == nullptr) firstNilTile = &tile;
                } else if (firstNilTile != nullptr) {
                    setTileValue(firstNilTile, tile.getValue());
                    setTileValue(&tile, 0);
                    previousNotNilTile = firstNilTile;
                    firstNilTile = &_tiles[previousNotNilTile->getIndex() - 1];
                } else {
                    previousNotNilTile = &tile;
                }
            }
        }
    }

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

    bool fillRandomEmptyTile(const Random& random) {
        if (!hasEmptyTiles())
            return false;

        Tile* tile = _emptyTiles.at(random.between<int>(0, _emptyTiles.size() - 1));
        tile->setValue(2);
        _emptyTiles.erase(std::remove(_emptyTiles.begin(), _emptyTiles.end(), tile));

        return true;
    }

    bool hasEmptyTiles() const { return _emptyTiles.size() > 0; }

    std::vector<Tile*>& getEmptyTiles() { return _emptyTiles; }

  private:
    void setTileValue(Tile* tile, const int& value) {
        if (tile->getValue() == 0 && value != 0) {
            _emptyTiles.erase(std::remove(_emptyTiles.begin(), _emptyTiles.end(), tile));
        } else if (tile->getValue() != 0 && value == 0) {
            _emptyTiles.push_back(tile);
        }
        tile->setValue(value);
    }

    int indexOf(const int& x, const int& y) { return x * x_size + y; }
    std::array<Tile, BOARD_SIZE> _tiles;
    std::vector<Tile*> _emptyTiles;
};

#endif // __TEST_GAMEBOARD_H__