#include "screen/GameScreen.h"
#include "raylib.h"
#include <iostream>

GameScreen::GameScreen(raylib::Window& window) : _window(&window) { }

GameScreen::~GameScreen() { }

void GameScreen::update(float delta) {
    if (IsKeyPressed(KEY_DOWN)) {
        _gameboard.move_down();

        if (_gameboard.hasEmptyTiles()) {
            std::vector<Tile*>& emptyTiles = _gameboard.getEmptyTiles();
            Tile* tile = emptyTiles.at(GetRandomValue(0, emptyTiles.size() - 1));
            tile->setValue(2);
            emptyTiles.erase(std::remove(emptyTiles.begin(), emptyTiles.end(), tile));
            std::cout << emptyTiles.size() << " empty tiles" << std::endl;
        }
    }
 }

void GameScreen::draw() {
    raylib::Vector2 tileSize {_window->GetSize() / _boardSize};

    for (int x = 0; x < _boardSize.x; x++) {
        for (int y = 0; y < _boardSize.y; y++) {
            const Tile& tile = _gameboard.get(x, y);
            float xPos {x * tileSize.x};
            float yPos {y * tileSize.y};
            _foreground.SetA(tile.getValue() * 10);
            _foreground.DrawRectangle(xPos + 5, yPos + 5, tileSize.x - 10, tileSize.y - 10);
            _textColor.DrawText(std::to_string(tile.getValue()), xPos - 5 + tileSize.x / 2.0f, yPos - 5+ tileSize.y / 2.0f, 20);
        }
    }
}