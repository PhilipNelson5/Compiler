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
  auto f_source = false;
  auto f_verbose = false;
  auto f_parseOnly = false;

  for (auto i = 1; i < argc; ++i)
  {
    if (strcmp(argv[i], "-s") == 0 | strcmp(argv[i], "--source") == 0)
      f_source = true;
    if (strcmp(argv[i], "-v") == 0 | strcmp(argv[i], "--verbose") == 0)
      f_source = true;
    if (strcmp(argv[i], "-p") == 0 | strcmp(argv[i], "--parse-only") == 0)
      f_parseOnly = true;
  }
  (void)f_verbose;

  if (!f_parseOnly)
  {
    if (f_source)
    {
      std::cout << "Emitting Source\n" << std::endl;
      programNode->emmitSource("");
    }
    else
    {
      std::cout << "Emitting Assembly\n" << std::endl;
      try
      {
        programNode->emmit();
      }
      catch (...)
      {
        std::cout << "Threw" << std::endl;
      }
    }
  }
};
