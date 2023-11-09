all : rwk ist
rwk : rwk.c
	gcc rwk.c -o rwk -lm -Wall -Wextra
ist : ist.c
	gcc ist.c -o ist -lm -Wall -Wextra
