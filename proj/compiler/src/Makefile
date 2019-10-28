PROJ=ifj2019
SCANNER=scanner.c
STRING=dynamic_string.c
FLAGS := -Wconversion -Wunreachable-code -Wextra -Wall  -Og   

# scanner.o: scanner.c
	# gcc -o scanner.o scanner.c

main: ${PROJ}.c 
	gcc ${FLAGS} -o ${PROJ} ${PROJ}.c scaner.c dynamic_string.c

test: 
	./${PROJ} test.txt

val: 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${PROJ} test.txt
