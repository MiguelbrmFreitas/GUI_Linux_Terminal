all: testes projetofinal2


testes:teste.c
	gcc -Wall engine.c comando.c arquivo.c interface.c teste.c -ftest-coverage -fprofile-arcs -lncurses -lcunit -o teste
	./teste
clean:
	rm -rf teste

projetofinal2: main.c
	gcc engine.c comando.c arquivo.c interface.c main.c -lncurses -ftest-coverage -fprofile-arcs -o proj2
	./proj2
clean: 
	rm -rf main

