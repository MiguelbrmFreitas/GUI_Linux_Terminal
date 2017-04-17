#include "arquivo.h"

#define LARGURA 35
#define ALTURA 8

/**
 * Exibe um menu com condições estabelecidas nos parâmetros
 *
 *@param win         Janela
 *@param selecao     variável de seleção que controla o highlight do menu
 *@param n_escolhas  número de possíveis escolhas
 *@param escolhas    vetor de strings com as possíveis escolhas
 */
int print_menu(WINDOW *win, int selecao, int n_escolhas, char *escolhas[8]); /* Printa o menu atual na tela  */

/**
 * Função que implementa a seleção de itens numa janela da biblioteca ncurses
 *
 *@param c           condição do switch
 *@param selecao     define o comando selecionado no momento
 *@param escolha     define a escolha final
 *@param n_escolhas  escolhas possíveis
 */
int selecionar(int c, int *selecao, int *escolha, int n_escolhas); /* Seleciona entre as opções */

/**
 * Imprime lista encadeada simples em tela
 *@param pinicio     ponteiro para o início da lista
 *@param win         janela aonde a lista será imprimida
 */
int imprime_lista(Lista *pinicio, WINDOW *win); /* Imprime lista na tela */

/**
 * Cria uma janela que armazena o comando digitado dentro dela
 *@param win        janela aonde aparecem as opções
 */
void janela_criar_comando(WINDOW *win); /* Janela de criar novo comando */

/**
 * Abre uma janela e executa comandos, além de pedir o nome, parâmetro e comentário(se quiser) relacionado ao comando
 *@param win        janela aonde aparecem as opções
 */
void janela_abrir_comandos(WINDOW *menu_win); /* Janela de abrir comando existente */

void janela_procurar_comando(WINDOW *win);
