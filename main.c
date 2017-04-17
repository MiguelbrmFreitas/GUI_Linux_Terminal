#include "interface.h"

/*
 * Int main:
 * Função principal onde o programa será executado e tomará decisões lógicas em relação as escolhas do usuário
 */
int main()
{
    WINDOW *menu_win, *win2;
	int selecao = 1, escolha = 0, c, n_escolhas, continuar = 1, startx = 0, starty = 0, existe_registro = 1;
	char *escolhas[] = { /* Possíveis escolhas */
			"Criar",
			"Abrir lista de comandos",
			"Procurar comando",
			"Sair",
		  };

    n_escolhas = sizeof(escolhas) / sizeof(char *); /* Número de possíveis escolhas */

    inicializa_ncurses(); /* Funções básicas de inicialização da ncurses */

	init_pair(1, COLOR_GREEN, COLOR_BLACK); /* Define um par de cor que deixa as letras verdes e o fundo negro */
	init_pair(2, COLOR_BLUE, COLOR_WHITE); /* Define um par de cor que deixa as letras azuis e o fundo branco */
	init_pair(3, COLOR_BLACK, COLOR_WHITE); /* Define um par de cor que deixa as letras negras e o fundo branco */
    init_pair(4, COLOR_CYAN, COLOR_WHITE);

	startx = 1; /* Inicializa as posições iniciais da janela */
	starty = 3;


	do{
        clear(); /* LImpa a tela */

        if ( fopen("lista_comandos.txt", "r") == NULL ) /* Flag que indica se registro existe */
            existe_registro = 0; /* Não existe */
        else
            existe_registro = 1; /* Existe */

        menu_win = newwin(ALTURA, LARGURA, starty, startx);

        c = 0;
        selecao = 1;
        escolha = 0;

        keypad(menu_win, TRUE); /* Habilita input para a janela criada */
        attron(COLOR_PAIR(1)); /* Colore a tela com o par de cor anteriormente criado */

        mvprintw(0, 0, "Use as setas para escolher a opção relativa a uma linha de comando.\nAperte enter para selecionar.");
        if (!existe_registro) /* Se não existir registro, exibe erro */
            mvprintw(12, 0, "Atenção! Não existem comandos para abrir! Você deve criar novos registros de comandos. ");

        mvprintw(18, 0, "P.S.: Quando um comando for executado, você vai ser redirecionado para o terminal para ver o resultado. Enter para voltar ao programa");
        mvprintw(19, 0, "P.S.S.: Lembre-se que o resultado nem sempre aparece no terminal, muitas vezes aparece na pasta do programa.");
        refresh();
        print_menu(menu_win, selecao, n_escolhas, escolhas);
        do
        {
            c = recebe_input_simples(menu_win); /* Recebe um input do teclado */
            mvprintw(26, 0, "                                                                 "); /* Limpa o aviso de erro da tela */
            refresh();
            selecionar(c, &selecao, &escolha, n_escolhas); /* Seleciona entre uma das opções */
            print_menu(menu_win, selecao, n_escolhas, escolhas); /* Mostra o menu depois do input */
        }while(!escolha); /* Acontece enquanto nenhuma escolha tiver sido escolhida */

        mvprintw(starty + ALTURA, 0, "Sua escolha foi: %d\n", escolha);
        refresh();

        if(escolha == 1) /* Criar */
        {
            mvprintw(18, 0, "                                                                                                                                                            "); /* Limpa as linhas */
            mvprintw(19, 0, "                                                                                                                                                            ");
            refresh();
            win2 = newwin((ALTURA+4), (LARGURA + 65), (starty + ALTURA + 2), startx); /* Cria nova janela */
            keypad(win2, TRUE); /* Habilita uso de teclado na janela */
            janela_criar_comando(win2); /* Chama a função que mostra a janela para criar novo comando */

        }
        else if(escolha == 2 || escolha == 3) /* Abrir ou Procurar */
        {
            if ( fopen("lista_comandos.txt", "r") != NULL ) /* Verifica se existe algum registro para abrir */
            {
                if (escolha == 2)
                {
                    clear();
                    mvprintw(0, 0, "Use as setas para escolher a opção relativa ao comando em questão.");
                    mvprintw(1, 0, "Aperte enter para selecionar uma opção.");
                    refresh();

                    win2 = newwin((ALTURA + 20), (LARGURA + 90), starty, startx); /* Cria a nova janela */
                    keypad(win2, TRUE); /* Habilita uso de teclado na janela */

                    janela_abrir_comandos(win2); /* Chama a função que mostra a janela para abrir u, comando */
                }
                else
                {
                    clear();
                    win2 = newwin((ALTURA + 5), (LARGURA + 50), starty, startx); /* Cria a nova janela */
                    keypad(win2, TRUE); /* Habilita uso de teclado na janela */

                    janela_procurar_comando(win2);
                }
            }
            else /* Se não existir, exibe erro */
            {
                clear();
                mvprintw(26, 0, "Não existem registros para abrir!");
                refresh();
            }
        }

        else /* Sair */
            continuar = 0; /* Sai do loop */

        delwin(menu_win); /* Deleta a janela do menu principal */
        delwin(win2); /* Deleta a janela da escolha */

    }while(continuar); /* Enquanto a variável continuar for diferente de 0, o loop continua */

	encerra_ncurses(); /* Encerra a ncurses */
	return 0;
}
