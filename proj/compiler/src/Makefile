PROJ=ifj2019
SCANNER=scaner.c
STRING=dynamic_string.c
SCTACK=./stack/c202.c
FLAGS := -Wconversion -Wunreachable-code -Wextra -Wall  -Og   

# scanner.o: scanner.c
# gcc -o scanner.o scanner.c

main: ${PROJ}.c 
	gcc ${FLAGS} -o ${PROJ} ${PROJ}.c ${SCANNER} ${STRING} ${SCTACK} 

test: 
	./${PROJ} test.txt

val: 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${PROJ} test.txt
