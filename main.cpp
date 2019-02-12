extern int yyparse();
extern int yydebug;

#include "src/ProgramNode.hpp"

#include <cstring>
#include <iostream>
#include <memory>

std::shared_ptr<ProgramNode> programNode;

int main(int argc, char** argv)
{
  // yydebug = 1;
  yyparse();
  if (argc > 1 && strcmp(argv[1], "--source"))
  {
    std::cout << "Emitting Source\n" << std::endl;
    programNode->emmitSource();
  }
  else
  {
    std::cout << "Emitting Assembly\n" << std::endl;
    programNode->emmit();
  }
    std::cout << "DONE" << std::endl;
};
