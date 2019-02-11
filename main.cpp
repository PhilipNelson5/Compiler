extern int yyparse();
extern int yydebug;

#include "src/ProgramNode.hpp"
#include <memory>

std::shared_ptr<ProgramNode> programNode;

int main()
{
  //yydebug = 1;
  yyparse();
  programNode->emmit();
};
