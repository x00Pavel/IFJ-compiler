PROJ=ifj2019
SCANNER=scaner.c
STRING=dynamic_string.c
SCTACK=./stack/c202.c
CFLAGS= -Wconversion -Wunreachable-code -Wextra -Wall  -O -g   


main: ${PROJ}.c 
	gcc ${CFLAGS} -D DEBUG -o ${PROJ} ${PROJ}.c ${SCANNER} ${STRING} ${SCTACK} 

val: main
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${PROJ} test.txt

test: main
	./${PROJ}



