/**
 * \file ./errors.h
 * \brief All types of errors
 * 
 * \author Yadlouski Pavel (xyadlo00@stud.fit.vutbr.cz)
 * 
 * \date 2019
 */

#ifndef _ERROR_H
#define _ERROR_H

/* If everthing ok*/
#define OK 0
/* Error in lexical analyzer                */
#define ERR_LEXER  1
/* Error in syntax analyzer                 */
#define ERR_SYNTAX 2
/* Error with undefind function or variable */
#define ERR_UNDEF  3
/* Error in incompatible type of operands   */
#define ERR_INCOMPATIBLE 4
/* Error in parameters of function          */
#define ERR_PARAM  5
/* Other semantic errors*/
#define ERR_OTHER  6
/* Error in devision by 0                   */
#define ERR_DEV_ZERO 9
/* Internal errors (in malloc etc.)         */
#define ERR_INTERNAL 99

#endif // _ERROR_H