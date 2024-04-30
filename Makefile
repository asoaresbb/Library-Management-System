test:
	@gcc -Wall gestao_livros.c test_gestao_livros.c -o test_gestao_livros.exe
	@./test_gestao_livros.exe

	@gcc -Wall gestao_emprestimos.c test_gestao_emprestimos.c -o test_gestao_emprestimos.exe
	@./test_gestao_emprestimos.exe

build: test
	@gcc -Wall cli.c gestao_livros.c gestao_emprestimos.c -o cli.exe

run: build
	@./cli.exe
