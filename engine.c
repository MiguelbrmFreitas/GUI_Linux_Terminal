#include "engine.h"

int inicializa_ncurses()
{
    initscr(); /* Inicializa a ncurses */
	curs_set(0); /* Some com o cursor */
	raw();	/* Desativar o buffer por linha. */
	start_color(); /* Habilita o uso de cores */
    return 1;
}

int encerra_ncurses()
{
    getch(); /* Espera um input para finalizar */
    endwin(); /* Define o fim da execução da ncurses */
    return 1;
}

int recebe_input_simples(WINDOW *menu_win)
{
    int c;

    noecho(); /* Impede que o caractere seja mostrado na tela */
    c = wgetch(menu_win); /* Recebe o input para determinada janela */
    echo(); /* Habilita novamente que se mostre caracteres na tela, para não interferir em funções posteriores */

    return c; /* Retorna o ASCII (ou macro) correspondente do caractere */
}

char* recebe_string(WINDOW *win, int n) /* É fácil de modificar essa função para ler dentro de uma janelinha, posteriormente */
{
    char *string = NULL; /* Declara e inicializa um ponteiro para char */
    string = (char*) malloc(n*sizeof(char)); /* Aloca como uma string de n caracteres (máximo para uma linha de comando) */

    wgetstr(win, string); /* Lê essa string do teclado na janela em questão */

    return string; /* Retorna a string lida */
}
