#include "symbol_table.hpp"

extern int yyparse();
extern int yydebug;

int main()
{
  yydebug = 1;
  symbol_table.enter_scope();
  yyparse();
};
