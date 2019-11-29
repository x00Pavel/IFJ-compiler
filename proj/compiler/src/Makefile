# author: Yadlouski Pavel

PROJ=ifj2019
SCANNER=scaner
STRING=dynamic_string
SCTACK=stack
TABLE=symtable
PARSER=parser
CODEGENERATOR=codegenerator
PREC_ANALYZE=preced_analyze
LINSTACK=linear_stack
CFLAGS= -Wconversion -Wunreachable-code -Wextra -Wall -O -g
#CFLAGS= -O -g

main: ${PROJ}.c 
	gcc ${CFLAGS} -D DEBUG -o ${PROJ} ${PROJ}.c ${SCANNER}.c ${STRING}.c ${SCTACK}.c ${TABLE}.c ${LINSTACK}.c ${PARSER}.c ${CODEGENERATOR}.c ${PREC_ANALYZE}.c 
rel: ${PROJ}.c
	gcc ${CFLAGS} -o ${PROJ} ${PROJ}.c ${SCANNER} ${STRING} ${SCTACK}

v1: 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${PROJ} < test1.txt  
v2:  
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${PROJ} < test2.txt  
v3:  
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${PROJ} < test3.txt
v4:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${PROJ} < test.txt
	

t1: 
	./${PROJ} < test1.txt 
t2: 
	./${PROJ} < test2.txt
t3: 
	./${PROJ} < test3.txt
t4:
	./${PROJ} < test.txt

clean:
	rm ifj2019 xyadlo00.zip 

zip:
	zip xyadlo00.zip ${PROJ}.c ${SCANNER}.c ${STRING}.c ${SCTACK}.c ${TABLE}.c ${LINSTACK}.c ${PARSER}.c ${CODEGENERATOR}.c ${PREC_ANALYZE}.c ${SCANNER}.h ${STRING}.h ${SCTACK}.h ${TABLE}.h ${LINSTACK}.h ${PARSER}.h ${CODEGENERATOR}.h ${PREC_ANALYZE}.h Makefile errors.h