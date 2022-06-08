#include "level.h"

int main() {

    Window W = openWindow(window_width,window_height);
    setBackGround(backgroundColor);

    //Structure game = title_screen();
    //Structure game = demoStructure();
    Structure game = level_1();
    play(game);

    closeWindow(W);
    endGraphics();
    return 0;
}
