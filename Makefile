.SILENT:

tests:
	gcc -Wall gestao_livros.c test_gestao_livros.c -o test_gestao_livros.exe
	./test_gestao_livros.exe
	echo "✅ Testes gestao_livros."

	gcc -Wall gestao_emprestimos.c test_gestao_emprestimos.c -o test_gestao_emprestimos.exe
	./test_gestao_emprestimos.exe
	echo "✅ Testes gestao_emprestimos."

userTests:
	gcc -Wall test_cli.c -o test_cli.exe
	./test_cli.exe
	echo "✅ Testes funcionais."

build: tests userTests
	gcc -Wall cli.c gestao_livros.c gestao_emprestimos.c -o cli.exe

run: build
	./cli.exe
