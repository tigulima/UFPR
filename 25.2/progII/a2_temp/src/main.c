#include "../include/game.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    (void)argc;  // Suprime warning de parâmetro não usado
    (void)argv;
    Game *game = NULL;
    
    // Inicializa o jogo
    game = game_init();
    if (!game) {
        error_exit("Falha ao inicializar o jogo");
        return EXIT_FAILURE;
    }
    
    // Loop principal do jogo
    game_run(game);
    
    // Limpeza e encerramento
    game_cleanup(game);
    
    return EXIT_SUCCESS;
}

