#include "comando.h"

typedef struct lista /* Lista com 3 strings de campos, todas relativas aos comandos */
{
    char nome [120];
    char comando [80];
    char comentario [300];
    int num_usados;
    int usado_recentemente;
    struct lista *prox;
}Lista;

/**
 * Função de criação de lista
 *
 *@return     retorna um ponteiro NULL
 */
Lista* cria(); /* Inicializa uma nova lista */

/**
 *Função de inserção de elementos no inicio da lista
 *
 *@param pinicio        ponteiro para o início da lista
 *@param comando        comando a ser incluído na lista
 *@param nome           nome a ser incluído na lista
 *@param comentario     comentário a ser incluído na lista
 *@param num_usados     numero de vezes que o comando foi usado
 *@return               retorna a nova lista criada
 */
Lista* insere_no_inicio(Lista *pinicio, char *comando, char *nome, char *comentario, int num_usados); /* Insere no começo de uma lista */

/**
 *Função que conta quantos elementos já existem na lista
 *
 *@param inicio        ponteiro inicial da lista
 *@return              retorna o número de nós da lista
 */
int conta_elementos(Lista *inicio); /* Conta os elementos de uma lista */

/**
 *Procura comando em lista encadeada simples
 *
 *@param inicio           ponteiro para início da lista
 *@param num              número comando específico a ser encontrado na lista
 *@return                 retorna a posição da lista com o comando específico
 */
Lista* encontra_comando(Lista *inicio, int num); /* Encontra um comando específico */

/**
 * Cria o arquivo para armazenar as entradas do usuário
 *
 *@param nome         nome do comando
 *@param comando      comando em si
 *@param              comentário sobre o comando
 */
int cria_ou_atualiza_arquivo(char* nome, char* comando, char* comentario, int num_usados); /* Cria um arquivo novo */

/**
 * Abre arquivo previamente criado e faz sua leitura, atribuindo os comandos a uma lista encadeada
 *
 *@param arquivo      ponteiro para arquivo a ser lido
 *@param lis          lista que vai armazenar os comandos lidos
 */
Lista* abre_arquivo(Lista *lis); /* Abre e lê um arquivo */


/**
 *Abre um arquivo e escreve por cima das informações do mesmo, com o objetivo de atualizar
 *
 *@param inicio        ponteiro para início da lista que irá reescrever o arquivo
 */
int reescreve_arquivo(Lista *inicio); /* Reescreve um arquivo */

/**
 *Remove um determinado comando do arquivo
 *
 *@param pcomando           posição do comando a ser removido
 *@param p1                 ponteiro inicial da lista aonde será procurado esse comando
*/

int remover_comando(Lista *pcomando, Lista *p1);

/**
 *Procura uma string nos comandos e seus campos
 *@param inicio       ínicio da lista que armazena os comandos em memória
 *@param string       string a ser procurada na lista
 *@return             retorna o nó da lista aonde tem o comando. se não for encontrado, retorna NULL
*/

Lista* procura_string(Lista *inicio, char *string);

/**
 *Ordena uma lista em ordem decrescente
 *@param pinicio       ínicio da lista que armazena os comandos em memória
*/

int ordena(Lista *pinicio);
