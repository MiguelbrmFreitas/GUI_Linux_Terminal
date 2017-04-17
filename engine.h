#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

/**
 * Função que inicializa a biblioteca ncurses no programa
 */
int inicializa_ncurses();

/**
 * Termina o uso da ncurses no programa, na espera de um input final
 */
int encerra_ncurses();

/**
 * Recebe um input de um caractere e retorna o seu código em ASCII no formato int para tratamento posterior
 *@param menu_win     janela aonde o input será lido
 *@return retorna o caractere lido
 */
int recebe_input_simples(WINDOW *menu_win); /* Recebe um único caractere do teclado */

/**
 * Recebe uma string em seu parâmetro para que ela seja tratada dentro da biblioteca
 *@param menu_win     janela aonde o input será lido
 *@param n            tamanho da string
 *@return retorna a string lida
 */
char* recebe_string(WINDOW *win, int n); /* Recebe uma string do teclado */
