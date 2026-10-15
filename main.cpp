#include "engine.hpp"
#include <windows.h>

int main() {
    engine eng(100, 40, 3, 10, 10, 90);
    while (!eng.getIsEnd()) {
        for (int keyCode = 0; keyCode < 256; ++keyCode) {
            if (GetAsyncKeyState(keyCode) & 0x8000) { // Convert the key code to ASCII character
                char keyChar = static_cast<char>(keyCode);
                if (keyChar == 'W') eng.movePlayerUp();
                if (keyChar == 'S') eng.movePlayerDown();
            }
        }
        eng.update();
    }

    return 0;
}