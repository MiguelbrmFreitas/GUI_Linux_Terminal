#include "interface.h"

int selecionar(int c, int *selecao, int *escolha, int n_escolhas){
    switch(c) /* Dependendo do input, faz determinada coisa */
    {
        case KEY_UP: /* Seta para cima */
            if((*selecao) == 1) /* Se for 1 e UP for apertado, vai para a última opção */
                (*selecao) = n_escolhas;
            else /* Caso contrário, diminuí uma linha para a variável de seleção */
                (*selecao)--;
            break;
        case KEY_DOWN: /* Seta para baixo */
            if((*selecao) == n_escolhas) /* Se for a última opção, volta para a primeira */
                (*selecao) = 1;
            else /* Senão, aumenta uma linha para a variável de seleção */
                (*selecao)++;
            break;
        case 10: /* Enter */
            (*escolha) = (*selecao); /* Escolha recebe a posição da variável de seleção */
            break;
        default: /* Qualquer outra coisa. Mostra erro. */
            mvprintw(35, 0, "Operação inválida.");
            refresh();
            break;
    }
    return 1;
}


int print_menu(WINDOW *win, int selecao, int n_escolhas, char *escolhas[8]) /* 8 é o número máximo de comandos que podem ser armazenados */
{
	int x = 1, y = 2, i;

	box(win, 0, 0); /* Cria a janela */
	wbkgd(win, COLOR_PAIR(3)); /* Colore a janela */

	for(i = 0; i < n_escolhas; ++i)
	{
	    if(selecao == (i + 1)) /* Seleciona a escolha */
		{
		    wattron(win, A_REVERSE); /* Dá um highlight na próxima opção */
			mvwprintw(win, y, x, "%s", escolhas[i]); /* Printa a opção com highlight */
			wattroff(win, A_REVERSE); /* Cancela os highlights para as outras opções que vem */
		}
		else
			mvwprintw(win, y, x, "%s", escolhas[i]); /* Printa a opção sem highlight */

		y++; /* Incrementa a linha aonde será printada a próxima opção */
	}
	wrefresh(win); /* Atualiza a janela */
    return 1;
}

int imprime_lista(Lista *pinicio, WINDOW *win)
{
    Lista *aux;
    int i = 1;
    for(aux = pinicio; aux != NULL; aux = aux->prox) /* Imprime a lista de comandos na tela */
    {
        mvwprintw(win, i, 1, "%d) Nome do comando: %s | Comando: %s | Comentário: %s", i, aux->nome, aux->comando, aux->comentario);
        i++;
    }
    return 1;
}

void janela_procurar_comando(WINDOW *win)
{
    char input, *string = "\0";
    Lista *p1 = NULL;

    box(win, 0, 0); /* Cria a janela */
	wbkgd(win, COLOR_PAIR(3)); /* Colore a janela */

    p1 = abre_arquivo(p1);

    mvwprintw(win, 1, 1, "Diga uma palavra chave para procurar dentre os comandos: ");
    string = recebe_string(win, 120);

    p1 = procura_string(p1, string);

    if(!p1)
        mvwprintw(win, 3, 1, "Nenhum resultado encontrado!");
    else
    {
        mvwprintw(win, 3, 1, "O comando \"%s\", de nome %s foi encontrado.", p1->comando,p1->nome);
        mvwprintw(win, 4, 1, "Deseja executá-lo? (S/N) ");
        wrefresh(win);
        do{
            input = recebe_input_simples(win);
        }while(input != 's' && input != 'S' && input != 'n' && input != 'N');

        if(input == 's' || input == 'S')
        {
            executa_comando(p1->comando);
            p1->num_usados += 1; /* Incrementa o número de vezes que o comando foi usado */
            reescreve_arquivo(p1); /* Reescreve o arquivo com as novas informações */
        }
    }
    mvwprintw(win, 6, 1, "Pressione qualquer tecla para voltar...");
    wgetch(win);
}

void janela_criar_comando(WINDOW *win)
{
    char *comando, *nome_comando, *comentario = "Sem comentário", decisao;
    Lista *p1 = NULL;

    box(win, 0, 0);

    wbkgd(win, COLOR_PAIR(4)); /* COlore a janela */

    mvwprintw(win, 1,1, "Diga o nome do novo comando: ");

    nome_comando = recebe_string(win, 80);

    mvwprintw(win, 2, 1, "Diga o novo comando: ");

    comando = recebe_string(win, 120);

    mvwprintw(win, 3, 1, "Deseja adicionar um comentário sobre o comando? (S/N)");
    do{
        decisao = recebe_input_simples(win);
        if(decisao == 's' || decisao == 'S'){
            mvwprintw(win, 4, 1, "Diga o comentário: ");
            comentario = recebe_string(win, 300); /* Adiciona um comentário */
        }
    }while(decisao != 's' && decisao != 'S' && decisao != 'n' && decisao != 'N'); /* O loop acontece enquanto a decisão não for sim ou não */

    mvwprintw(win, 5,1, "O novo comando é: \"%s\", de nome \" %s \"", comando, nome_comando);
    mvwprintw(win, 6,1, "O comentário sobre ele é: %s", comentario);
    mvwprintw(win, 7,1, "Deseja salvar o comando? (S/N) ");
    do{
        decisao = recebe_input_simples(win);
        if(decisao == 's' || decisao == 'S')
            cria_ou_atualiza_arquivo(nome_comando, comando, comentario, 0); /* Salva comando em arquivo. */
    }while(decisao != 's' && decisao != 'S' && decisao != 'n' && decisao != 'N'); /* O loop acontece enquanto a decisão não for sim ou não */


    p1 = abre_arquivo(p1); /* Recebe as informações do arquivo */

    mvwprintw(win, 8,1, "Deseja executar o comando? (S/N) ");
    do{
        decisao = recebe_input_simples(win);
        if(decisao == 's' || decisao == 'S')
        {
            executa_comando(comando); /* Executa o comando */
            p1->num_usados += 1; /* Incrementa o número de vezes que o comando foi usado */
            reescreve_arquivo(p1); /* Reescreve o arquivo com as novas informações */
        }
    }while(decisao != 's' && decisao != 'S' && decisao != 'n' && decisao != 'N'); /* O loop acontece enquanto a decisão não for sim ou não */

    wclear(win); /* Limpa a janela */
    box(win, 0, 0); /* Faz o seu contorno novamente */

    if (decisao == 's' || decisao == 'S')
	mvwprintw(win, 2, 1, "Foi executado o comando \" %s \" ...", comando);
    mvwprintw(win, 5, 1, "Pressione qualquer tecla para voltar ao menu principal...");

    wrefresh(win); /* Atualiza a janela */
    wgetch(win); /* Aguarda uma tecla para sair */
}

void janela_abrir_comandos(WINDOW *menu_win)
{
    Lista *p1 = NULL, *pcomando = NULL;
    int c, n_escolhas, escolha = 0, selecao = 1, n_comandos = 0, num_comando, tentativas = 0;
    char *opcao_comando = "\0", *novoparametro, *novonome, *novocomentario, decisao;
    char *escolhas[] = { /* Possíveis escolhas */
			"Executar",
			"Adicionar parâmetro",
			"Salvar",
			"Salvar como",
			"Adicionar comentário",
			"Remover comando",
			"Sair"
		  };

    n_escolhas = sizeof(escolhas) / sizeof(char *);

    p1 = abre_arquivo(p1);

    n_comandos = conta_elementos(p1);

    box(menu_win, 0, 0); /* Cria a janela */

    wbkgd(menu_win, COLOR_PAIR(2)); /* Colore a janela */

    ordena(p1); /* Ordena o ponteiro para arquivo */
    imprime_lista(p1, menu_win);

    mvwprintw(menu_win, 26, 1, "Escolha o número do comando: ");
    do
    {
        if (tentativas)/* Se for a segunda tentativa e estiver errado, exibe mensagem de erro */
        {
            wmove(menu_win,26, 0);
            wclrtoeol(menu_win); /* Limpa a linha atual */
            mvwprintw(menu_win, 26, 1, "Valor inválido! Escolha novamente: ");
            wrefresh(menu_win);
        }
        opcao_comando = recebe_string(menu_win, 3);
        num_comando = atoi(opcao_comando);
        tentativas++;
    }while(num_comando <= 0 || num_comando > n_comandos); /* Enquanto for um número inválido, pede novamente */

    pcomando = encontra_comando(p1, num_comando);

    wclear(menu_win);

    mvwprintw(menu_win, 1, 1, "Comando selecionado -> Nome: %s | Comando: %s | Comentário: %s", pcomando->nome, pcomando->comando, pcomando->comentario);
    wrefresh(menu_win);

    print_menu(menu_win, selecao, n_escolhas, escolhas);
    do
    {
        mvprintw(35, 0, "                                                                 "); /* Limpa o aviso de erro da tela */
        c = recebe_input_simples(menu_win); /* Recebe um input do teclado */
        refresh();
        selecionar(c, &selecao, &escolha, n_escolhas); /* Deixa o usuário selecionar dentre as opções */
        print_menu(menu_win, selecao, n_escolhas, escolhas); /* Mostra o menu depois do input */
    }while(!escolha); /* Acontece enquanto nenhuma escolha tiver sido escolhida */

    wclear(menu_win); /* Limpa a janela */
    box(menu_win, 0, 0);

    if (escolha == 1) /* Executar */
    {
        executa_comando(pcomando->comando); /* Executa o comando escolhido pelo usuário */
        pcomando->num_usados += 1; /* Incrementa 1 no número de vezes que foi usado */
        reescreve_arquivo(p1);
        mvwprintw(menu_win, 2, 2, "Foi executado o comando \" %s \" ...", pcomando->comando);
        wrefresh(menu_win);
    }
    else if (escolha == 2) /* Adicionar parâmetro */
    {
        mvwprintw(menu_win, 2, 2, "O comando é: %s", pcomando->comando);
        mvwprintw(menu_win, 3, 2, "Escreva um parâmetro para ser adicionado: ");
        novoparametro = recebe_string(menu_win, 20); /* Lê o parâmetro */
        strcat(pcomando->comando, " "); /* Adiciona um espaço na frente do comando para facilitar a adição de parâmetros posteriormente */
        strcat(pcomando->comando, novoparametro); /* Concatena o parâmetro no final do comando para a região de memória do comando selecionado */
        reescreve_arquivo(p1); /* Reescreve o arquivo com um novo parâmetro */
        mvwprintw(menu_win, 4, 2, "O comando com o novo parâmetro agora é: %s", pcomando->comando);
        mvwprintw(menu_win, 5, 2, "Deseja executar com o novo parâmetro? (S/N)");
        do
        {
            decisao = recebe_input_simples(menu_win);
            if(decisao == 's' || decisao == 'S')
            {
                executa_comando(pcomando->comando);
                mvwprintw(menu_win, 6, 2, "Foi executado o comando \" %s \" ...", pcomando->comando);
            }
        }while(decisao != 's' && decisao != 'S' && decisao != 'n' && decisao != 'N');

        wrefresh(menu_win);
    }
    else if (escolha == 3) /* Salvar */
    {
        mvwprintw(menu_win, 2, 2, "O comando foi salvo com sucesso.");
    }
    else if (escolha == 4) /* Salvar como */
    {
        mvwprintw(menu_win, 2, 2, "O nome atual do comando é: %s", pcomando->nome);
        mvwprintw(menu_win, 3, 2, "Escreva o novo nome: ");
        novonome = recebe_string(menu_win, 120);
        strcpy(pcomando->nome, novonome); /* Atribuí o novo nome para a região de memória do nome do comando selecionado */
        reescreve_arquivo(p1); /* Reescreve o arquivo com o novo nome */
        mvwprintw(menu_win, 4, 2, "O comando com o novo nome agora é: %s", pcomando->nome);
    }
    else if (escolha == 5) /* Adicionar comentário */
    {
        mvwprintw(menu_win, 2, 2, "O comentário atual do comando é: %s", pcomando->comentario);
        mvwprintw(menu_win, 3, 2, "Escreva o novo comentário: ");
        novocomentario = recebe_string(menu_win, 300); /* Lê o novo comentário do teclado */
        strcpy(pcomando->comentario, novocomentario); /* Atribuí o novo nome para a região de memória do nome do comando selecionado */
        reescreve_arquivo(p1); /* Reescreve o arquivo com um novo comentário */
        mvwprintw(menu_win, 4, 2, "O comentário novo do comando agora é: %s", pcomando->comentario);
    }

    else if(escolha == 6) /* Remover comando */
    {
        mvwprintw(menu_win, 2, 2, "O comando \" %s \" foi removido.", pcomando->comando);
        remover_comando(pcomando, p1); /* Remove o comando */
    }

    else /* Sair */
        return;

    mvwprintw(menu_win, 10, 2, "Pressione qualquer tecla para voltar ao menu principal..."); /* Espera um input para voltar ao menu principal */
    wgetch(menu_win);
}
