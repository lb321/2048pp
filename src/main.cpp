/*******************************************************************************************
 *
 *   raylib [core] example - Basic window
 *
 *   Welcome to raylib!
 *
 *   To test examples, just press F6 and execute raylib_compile_execute script
 *   Note that compiled executable is placed in the same folder as .c file
 *
 *   You can find all basic examples on C:\raylib\raylib\examples folder or
 *   raylib official webpage: www.raylib.com
 *
 *   Enjoy using raylib. :)
 *
 *   This example has been created using raylib 1.0 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h
 *for details)
 *
 *   Copyright (c) 2014 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "Vector2.hpp"
#include "game/GameBoard.hpp"
#include "raylib-cpp.hpp"
#include "raylib.h"
#include "screen/GameScreen.h"
#include <iostream>
#include <ostream>
#include <string>

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------

    raylib::Window window(500, 500, "2048++");
    GameScreen gameScreen {window};
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!window.ShouldClose()) { // Detect window close button or ESC key
        float delta = window.GetFrameTime();
        // Update
        //----------------------------------------------------------------------------------

        gameScreen.update(delta);

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        {
            window.ClearBackground(RAYWHITE);
            window.DrawFPS();

            gameScreen.draw();
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    return 0;
}