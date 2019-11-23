/**
 * \file ./stack.c
 * \brief Implementation of stack 
 * 
 * \author Yadlouski Pavel (xyadlo00@stud.fit.vutbr.cz)
 * 
 * \note Ispeared by solution from IAL course (du1)
 * 
 * \date 2019
 */

#include "stack.h"

int STACK_SIZE = MAX_STACK;

void stackError ( int error_code ){

	static const char* SERR_STRINGS[MAX_SERR+1] = {"Unknown error","Stack error: INIT","Stack error: PUSH","Stack error: TOP"};
	if ( error_code <= 0 || error_code > MAX_SERR )
		error_code = 0;
	fprintf (stdout, "%s\n", SERR_STRINGS[error_code] );
}

void stackInit ( tStack* s ) {
	if (s == NULL){
		stackError(SERR_INIT);
	}
	else {
		s->top = -1;
	}
}

int stackEmpty ( const tStack* s ) {

	return (s->top != -1) ? 0 : 1;

}

int stackFull ( const tStack* s ) {
	return (s->top == STACK_SIZE - 1) ? 1 : 0;
}

int stackTop ( const tStack* s ) {
	if (stackEmpty(s) == 1){
		stackError(SERR_TOP);
	}
	return s->arr[s->top];
}


void stackPop ( tStack* s ) {
	if (s->top != -1){
		s->arr[s->top] = 0;	
		s->top--;
	}
}


void stackPush ( tStack* s, int c ) {
	if(s == NULL){
		stackError(SERR_PUSH);
	}

	if (stackFull(s) == 0){
		s->top ++;
		s->arr[s->top] = c;
	}
	else {
		stackError(SERR_PUSH);
	}
}

