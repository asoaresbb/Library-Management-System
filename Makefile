build: test
	gcc -Wall cli.c gestao_livros.c -o cli.exe

run: build
	./cli.exe

test:
	gcc -Wall gestao_livros.c test_gestao_livros.c -o test_gestao_livros.exe
	./test_gestao_livros.exe

	#gcc -Wall test_cli.c -o test_cli.exe
	#./test_cli.exe