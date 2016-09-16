// Introduction to Flex, Brad Vander Zander and Ray Byler
/*
Reads lines from stdin and check to see whether each line contains a valid
credit card number. A valid credit card number is defined a s one that has four
groups of four members, each separated with an optional space or dash.
*/
%option noyywrap
%{
/*********************
 *****DEFINITIONS*****
 *********************/
%}

%{
// recognize wither or not a credit card number is valid
int line_num = 1;
%}

digit[0-9]
group {digit}{4}
%%

%{
/*********************
******RULES***********
**********************/
%}

  /*The carat(^) says that a credit card number must start
  at the beginning of the line and the $ says that the credit
  card number must end the line. */

^{group}([ -]?{group}){3}$ { printf(" Credit card number: %s\n", yytext); }

  /*The .* accumulates all the charactes on any line that does not match a valid
  credit card number*/
.* { printf("%d: error: %s \n", line_num, yytext);}
\n { line_num++; }
%%

/**********************
*****USER CODE*********
***********************/

int main(int argc, char *argv[])
{
  yylex();
}
