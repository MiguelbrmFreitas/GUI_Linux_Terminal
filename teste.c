#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "CUnit/Basic.h"

static FILE* temp_file = NULL;

int init_suite1(void)
{
   if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
      return -1;
   }
   else {
      return 0;
   }
}

int clean_suite1(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}

void test_inicializa_ncurses(void) {
	int t = inicializa_ncurses();
	CU_ASSERT(t == 1);
}

void test_encerra_ncurses(void) {
	int t = encerra_ncurses();
	CU_ASSERT(t == 1);
}

void test_lista_cria(void){
	CU_ASSERT(NULL == cria());
}

void test_insere_no_inicio(void) {
	Lista *p1 = NULL;
 	p1 = insere_no_inicio(p1, "Comando","Nome","Comentário",1);

	CU_ASSERT(!strcmp(p1->comando,"Comando"));
	CU_ASSERT(!strcmp(p1->nome,"Nome"));
	CU_ASSERT(!strcmp(p1->comentario,"Comentário"));
   CU_ASSERT(p1->num_usados==1);
	/* Os dados da lista deve ser igual a Comando */
}

void test_conta_elementos(void){
	Lista *p1 = NULL;
 	p1 = insere_no_inicio(p1, "Comando 1","Nome 1","Comentário 1",1);
 	p1 = insere_no_inicio(p1, "Comando 2","Nome 2","Comentário 2",2);
 	p1 = insere_no_inicio(p1, "Comando 3","Nome 3","Comentário 3",3);
 	int t = conta_elementos(p1);
 	CU_ASSERT(t == 3);
}

void test_encontra_comando(void){
	Lista *p1 = NULL;
 	p1 = insere_no_inicio(p1, "Comando 1","Nome 1","Comentário 1",1);
 	p1 = insere_no_inicio(p1, "Comando 2","Nome 2","Comentário 2",2);
 	p1 = insere_no_inicio(p1, "Comando 3","Nome 3","Comentário 3",3);
 	Lista *p2 = NULL;
 	p2 = encontra_comando(p1,2);
 	CU_ASSERT(!strcmp(p2->comando,"Comando 2"));
}

void test_cria_ou_atualiza_arquivo(void){
	int t = cria_ou_atualiza_arquivo("Comando de teste", "cmd_teste", "cmt_teste",1);
	CU_ASSERT(t == 1);
}

void test_reescreve_arquivo(void){
	Lista *p1 = NULL;
 	p1 = insere_no_inicio(p1, "Comando de teste 2","cmd_teste_2","cmt_teste_2",1);
	CU_ASSERT(reescreve_arquivo(p1) == 1);
}

void test_print_menu(void){
	WINDOW *menu;
	menu = newwin(10,10,0,0);
	char *esc[] = {
		"Um",
		"Dois",
		"Três"
	};
	CU_ASSERT(print_menu(menu, 1, 3, esc) == 1);
}

void test_selecionar(void){
	int t1, t2;
	t1 = 1;
	t2 = 2;
	CU_ASSERT(selecionar(1,&t1,&t2,3) == 1);
}

void test_imprime_lista(void){
	WINDOW *menu;
	menu = newwin(100,100,0,0);
	Lista *p1 = NULL;
 	p1 = insere_no_inicio(p1, "Comando de teste 3","cmd_teste_3","cmt_teste_3",1);
 	CU_ASSERT(imprime_lista(p1,menu) == 1);
}

void test_executa_comando(void){
   int t = executa_comando("mkdir test_executa_comando");
   CU_ASSERT(t == 1);
}

void test_recebe_input_simples(void){
   WINDOW *menu;
   menu = newwin(10,10,0,0);
   int t = recebe_input_simples(menu);
   CU_ASSERT(t == -1);

}

void test_ordena(void){
   Lista *p1 = NULL;
   p1 = insere_no_inicio(p1, "Comando de teste 2","cmd_teste_2","cmt_teste_2",1);
   p1 = insere_no_inicio(p1, "Comando de teste 3","cmd_teste_3","cmt_teste_3",2);
   int t = ordena(p1);
   CU_ASSERT(t == 1);
}

void test_procura_string(void){
   Lista *p1 = NULL;
   p1 = insere_no_inicio(p1, "Comando de teste 2","cmd_teste_2","cmt_teste_2",1);
   Lista *p2 = procura_string(p1, "Comando de teste 2");
   CU_ASSERT(!strcmp(p2->comando,"Comando de teste 2"));
}

void test_abre_arquivo(void){
   Lista *p1 = NULL;
   p1 = abre_arquivo(p1);
   CU_ASSERT(1 == 1);
}

void test_remover_comando(void){
   Lista *p1 = insere_no_inicio(p1, "Comando de teste 2","cmd_teste_2","cmt_teste_2",1);
   Lista *p2 = NULL;
   int t = remover_comando(p1,p2);
   CU_ASSERT(t == 1);
}

//int janela_criar_comando(WINDOW *); /* Janela de criar novo comando */

//int janela_abrir_comandos(WINDOW *menu_win); /* Janela de abrir comando existente */


int main(){

	CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* Testes das funções */
   if ((NULL == CU_add_test(pSuite, "test of insere_no_inicio", test_insere_no_inicio))
   	//|| (NULL == CU_add_test(pSuite, "test of inicializa_ncurses", test_inicializa_ncurses))
   	|| (NULL == CU_add_test(pSuite, "test of encerra_ncurses", test_encerra_ncurses))
   	|| (NULL == CU_add_test(pSuite, "test of lista_cria", test_lista_cria))
   	|| (NULL == CU_add_test(pSuite, "test of conta_elementos", test_conta_elementos))
   	|| (NULL == CU_add_test(pSuite, "test of encontra_comando", test_encontra_comando))
   	|| (NULL == CU_add_test(pSuite, "test of cria_ou_atualiza_arquivo", test_cria_ou_atualiza_arquivo))
   	|| (NULL == CU_add_test(pSuite, "test of reescreve_arquivo", test_reescreve_arquivo))
   	|| (NULL == CU_add_test(pSuite, "test of print_menu",test_print_menu))
   	|| (NULL == CU_add_test(pSuite, "test of selecionar",test_selecionar))
   	|| (NULL == CU_add_test(pSuite, "test of imprime_lista",test_imprime_lista))
      || (NULL == CU_add_test(pSuite, "test of recebe_input_simples",test_recebe_input_simples))
      || (NULL == CU_add_test(pSuite, "test of ordena",test_ordena))
      || (NULL == CU_add_test(pSuite, "test of procura_string",test_procura_string))
      || (NULL == CU_add_test(pSuite, "test of abre_arquivo",test_abre_arquivo))
      || (NULL == CU_add_test(pSuite, "test of remover_comando",test_remover_comando))
      || (NULL == CU_add_test(pSuite, "test of executa_comando",test_executa_comando))

   	)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
