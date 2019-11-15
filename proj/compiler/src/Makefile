PROJ=ifj2019
SCANNER=scaner.c
STRING=dynamic_string.c
SCTACK=./stack/c202.c
TABLE=./hash_table/c016.c
CFLAGS= -Wconversion -Wunreachable-code -Wextra -Wall -O -g   


main: ${PROJ}.c 
	gcc ${CFLAGS} -D DEBUG -o ${PROJ} ${PROJ}.c ${SCANNER} ${STRING} ${SCTACK} ${TABLE}

rel: ${PROJ}.c
	gcc ${CFLAGS} -o ${PROJ} ${PROJ}.c ${SCANNER} ${STRING} ${SCTACK}

v1: 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${PROJ} test1.txt  
v2:  
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${PROJ} test2.txt  
v3:  
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${PROJ} test3.txt

t1: 
	./${PROJ} test1.txt
t2: 
	./${PROJ} test2.txt
t3: 
	./${PROJ} test3.txt


