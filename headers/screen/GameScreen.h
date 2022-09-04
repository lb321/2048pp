#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "raylib.h"
#include "util/Random.h"
#pragma once

#include "game/GameBoard.hpp"
#include "raylib-cpp.hpp"

class GameScreen {
  public:
    explicit GameScreen(raylib::Window& window);
    ~GameScreen();

    void update(float delta);
    void draw();

  private:
    GameBoard<8, 8> _gameboard;
    Vector2 _boardSize {8, 8};
    raylib::Color _foreground {0, 68, 130};
    raylib::Color _textColor {raylib::Color::DarkGray()};

    raylib::Window* _window;
    Random _random;
};

#endif