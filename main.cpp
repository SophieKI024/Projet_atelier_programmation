#include "level.h"

int main() {

    Window W = openWindow(window_width,window_height);
    setBackGround(backgroundColor);

    bool stop=false;
    while(!stop){
    Structure game = title_screen(stop);
    play(game);
    setBackGround(backgroundColor);
    }

    closeWindow(W);
    endGraphics();
    return 0;
}
