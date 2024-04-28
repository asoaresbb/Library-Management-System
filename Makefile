build: test
	gcc -Wall main.c library.c -o main.exe

run: build
	./main.exe

test:
	gcc -Wall library.c test_library.c -o test_library.exe
	./test_library.exe

	#bats --tap tests