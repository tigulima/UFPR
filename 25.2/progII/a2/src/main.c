#include "../include/game.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    (void)argc;  // Suprime warning de parâmetro não usado
    (void)argv;
    Game *game = NULL;
    
    game = game_init();
    if (!game) {
        error_exit("Falha ao inicializar o jogo");
        return EXIT_FAILURE;
    }
    
    game_run(game);
    game_cleanup(game);
    
    return EXIT_SUCCESS;
}

