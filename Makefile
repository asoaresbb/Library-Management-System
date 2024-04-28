build: test
	gcc -Wall cli.c library.c -o cli.exe

run: build
	./cli.exe

test:
	gcc -Wall library.c test_library.c -o test_library.exe
	./test_library.exe

	gcc -Wall test_cli.c -o test_cli.exe
	./test_cli.exe