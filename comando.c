#include "comando.h"

int executa_comando(char *comando)
{
    def_prog_mode();		/* Salva o estado da ncurses */
	endwin();			/* Sai temporariamente  */

    system(comando); /* Pega string e executa comando no terminal através da função system() */

    printf("\n\n\nAperte qualquer tecla para voltar ao programa...");
    while(getchar()!='\n'); /* Espera um enter sem acumular nada no buffer */

    reset_prog_mode(); /* Volta a ncurses */

    refresh();

    return 1;
}
