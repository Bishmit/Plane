#include"Game.h"

int main() {
    Game game;
    while (game.running()) {
        game.pollEvents(); 
        game.Update();
        game.render();
    }
    return 0;
}