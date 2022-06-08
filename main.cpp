#include "level.h"

int main() {

    Window W = openWindow(window_width,window_height);
    setBackGround(backgroundColor);

    Structure game = title_screen();
    play(game);

    closeWindow(W);
    endGraphics();
    return 0;
}
