#include "arquivo.h"

Lista* cria()
{
    return NULL;
}

Lista* insere_no_inicio(Lista *pinicio, char *comando, char *nome, char *comentario, int num_usados)
{
    Lista* novo;
    novo = (Lista*) malloc(sizeof(Lista)); /* aloca a lista */
    /*  Copia as strings de referência para os campos do nó da lista */
    novo->num_usados = num_usados;
    strcpy(novo->comando, comando);
    strcpy(novo->nome, nome);
    strcpy(novo->comentario, comentario);
    novo->prox = pinicio; /* O próximo é o novo início */

    return novo;
}

int conta_elementos(Lista *inicio)
{
    Lista *aux;
    int n = 0;

    for(aux = inicio; aux != NULL; aux = aux->prox) /* Percorre a lista e conta o número de nós (ou seja, de comandos) */
        n++;

    return n;
}

Lista* encontra_comando(Lista *inicio, int num)
{
    Lista *aux = NULL;
    int i = 1;

    aux = inicio;
    while(i != num) /* Enquanto i não for o número do comando escolhido, passa para o próximo nó */
    {
        aux = aux->prox;
        i++;
    }

    return aux; /* Retorna o elemento da lista com o comando escolhido */
}

Lista* procura_string(Lista *inicio, char *string)
{
    Lista *aux;

    aux = inicio;
    while(aux != NULL)
    {
        if(!strcmp(aux->comando,string) || strstr(aux->comando,string) ||
                !strcmp(aux->comentario, string) || strstr(aux->comentario,string) ||
                !strcmp(aux->nome, string) || strstr (aux->nome,string))
            break;
        aux = aux->prox;
    }

    return aux;
}

int ordena(Lista *pinicio)
{
    Lista *p1, *p2, *p3;
    int aux;
    char nome[120] = "\0", comando[120] = "\0", comentario[300] = "\0";
    if (pinicio != NULL)
    {
        p1 = pinicio; /* Ponteiro inicial */
        while (p1->prox != NULL) /* ENquanto o próximo do inicial for diferente de nulo */
        {
            p3 = p1; /* Armazena o inicial */
            p2 = p1->prox; /* Armazena o próximo do inicial */
            while (p2 != NULL) /* ENquanto p2 for diferente de nulo */
            {
                if (p3->num_usados < p2->num_usados) /* Se o p3 apontar pra um comando menos usado do que p2 */
                    p3 = p2;                         /* É efetuada a troca de ponteiros */
                p2 = p2->prox;
            }
            if (p1 != p3)
            { /* Efetua as trocas de acordo com o maior */
                aux = p3->num_usados;
                strcpy(nome, p3->nome);
                strcpy(comando, p3->comando);
                strcpy(comentario, p3->comentario);

                p3->num_usados = p1->num_usados;
                strcpy(p3->nome, p1->nome);
                strcpy(p3->comando, p1->comando);
                strcpy(p3->comentario, p1->comentario);

                p1->num_usados = aux;
                strcpy(p1->nome, nome);
                strcpy(p1->comando, comando);
                strcpy(p1->comentario, comentario);
            }
            p1 = p1->prox;
        }
    }
    return 1;
}

int cria_ou_atualiza_arquivo(char* nome, char* comando, char* comentario, int num_usados)
{
    FILE* arquivo;
    arquivo = fopen("lista_comandos.txt", "a+");				/*Cria o arquivo que armazena*/

    fprintf(arquivo, "%s:%s | %s - %d\n",nome,comando,comentario, num_usados); /* Escreve o novo comando no arquivo */

    fclose(arquivo);							/*E fecha*/
    return 1;
}

Lista* abre_arquivo(Lista *lis)
{
    lis = cria();
    int num_usados;
    char comando[80] = "\0";
    char nome[120] = "\0";
    char comentario[300] = "\0";
    FILE *arquivo = fopen("lista_comandos.txt","r");
    if(arquivo == NULL) /* Indica erro na abertura do arquivo */
    {
        exit(1);
    }

    do
    {
        fscanf(arquivo, "%[^:]:%[^|]|%[^-]-%d\n", nome, comando, comentario, &num_usados); /* Lê as strings no padrão do arquivo */
        if (comando[(strlen(comando))-1] != ' ' && comando[(strlen(comando))-2]);
        lis = insere_no_inicio(lis, comando, nome, comentario, num_usados); /* Insere as strings em uma lista */
    }
    while(!feof(arquivo));  /* Faz isso enquanto ainda tiverem registros no arquivo */
    fclose(arquivo);

    return lis;
}

int reescreve_arquivo(Lista *inicio)
{
    Lista *aux = NULL;
    FILE *arquivo;

    arquivo = fopen("lista_comandos.txt", "w"); /* Abre para escrever por cima. Ou seja, reescrever */

    for(aux = inicio; aux != NULL; aux = aux->prox) /* Escreve a lista no arquivo */
        fprintf(arquivo, "%s:%s | %s - %d\n",aux->nome,aux->comando,aux->comentario,aux->num_usados); /* Nos padrões do arquivo */

    fclose(arquivo);
    return 1;
}

int remover_comando(Lista *pcomando, Lista *p1)
{
    Lista *aux; /* Lista auxiliar */
    FILE *arq;

    arq = fopen("lista_comandos.txt", "w"); /* Abre para reescrever */

    for(aux = p1; aux != NULL; aux = aux->prox)
    {
        if(aux != pcomando) /* Se a lista for diferente da posição aonde tem o registro a ser removido, não coloca no arquivo novo */
            fprintf(arq, "%s:%s | %s - %d\n",aux->nome,aux->comando,aux->comentario,aux->num_usados); /* Nos padrões do arquivo */
    }

    fclose(arq);
    return 1;
}
