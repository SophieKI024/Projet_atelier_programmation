#include "level.h"

int main() {
    openWindow(window_width,window_height);
    setBackGround(backgroundColor);
    Structure game = title_screen();
    play(game, 10000);
    endGraphics();
    return 0;
}
