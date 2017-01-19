%{
//**************************************
// lang.l
//
// Scanner definition file for CST 320 project
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Nov. 23, 2015
//

#include "tokens.h"

#define DO_RETURN(a) return (a)
//#define DO_RETURN(a) return Return(a)
int Return(int val);

%}

%option noyywrap
%option noinput
%option nounput
%option yylineno


    /* definitions go here. period is an example. */
period          [.]
int             [0-9]
whitespace      [ \t\n]


%%

    // token definitions go here. "if" is an example.
{whitespace}+

"("                         DO_RETURN('(');
")"                         DO_RETURN(')');
"["                         DO_RETURN('[');
"]"                         DO_RETURN(']');
";"                         DO_RETURN(';');
"+"                         DO_RETURN('+');
"-"                         DO_RETURN('-');
"*"                         DO_RETURN('*');
"/"                         DO_RETURN('/');

"end"                       DO_RETURN(END);

{int}+                      DO_RETURN(INT_VAL);

"//".+$                     //do nothing
"/*"[.$]+"*/"               //do nothing

.                           DO_RETURN(JUNK_TOKEN);

%%

// This function allows us to do extra processing on each token
int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}

