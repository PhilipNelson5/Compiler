extern int yyparse();
extern int yydebug;

#include "src/ProgramNode.hpp"
#include "src/RegisterPool.hpp"

#include <cstring>
#include <iostream>
#include <memory>

std::shared_ptr<ProgramNode> programNode;

void showHelp()
{
  std::cout << "\n";
  std::cout << "     ______   _______    ______   __\n";
  std::cout << "    /      \\ |       \\  /      \\ |  \\\n";
  std::cout << "   |  $$$$$$\\| $$$$$$$\\|  $$$$$$\\| $$\n";
  std::cout << "   | $$   \\$$| $$__/ $$| $$___\\$$| $$\n";
  std::cout << "   | $$      | $$    $$ \\$$    \\ | $$\n";
  std::cout << "   | $$   __ | $$$$$$$  _\\$$$$$$\\| $$\n";
  std::cout << "   | $$__/  \\| $$      |  \\__| $$| $$_____\n";
  std::cout << "    \\$$    $$| $$       \\$$    $$| $$     \\\n";
  std::cout << "     \\$$$$$$  \\$$        \\$$$$$$  \\$$$$$$$$\n\n";

  std::cout << "-d\t--debug\t\tset yydebug to a positive value\n";
  std::cout << "-h\t--help\t\tshow this help message\n";
  std::cout << "-p\t--parse-only\tskip all assembly or source code emission\n";
  std::cout << "-s\t--source\tparse and emit source code\n";
  std::cout << "-v\t--verbose\textra print statements\n";
  std::cout << std::endl;
}

int main(int argc, char** argv)
{
  yydebug = 0;
  auto f_source = false;
  auto f_verbose = false;
  auto f_parseOnly = false;

  for (auto i = 1; i < argc; ++i)
  {
    if (strcmp(argv[i], "-h") == 0 | strcmp(argv[i], "--help") == 0)
    {
      showHelp();
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[i], "-d") == 0 | strcmp(argv[i], "--debug") == 0)
      yydebug = 1;
    if (strcmp(argv[i], "-p") == 0 | strcmp(argv[i], "--parse-only") == 0)
      f_parseOnly = true;
    if (strcmp(argv[i], "-s") == 0 | strcmp(argv[i], "--source") == 0)
      f_source = true;
    if (strcmp(argv[i], "-v") == 0 | strcmp(argv[i], "--verbose") == 0)
      f_verbose = true;
  }

  if (f_verbose) std::cout << "Parsing\n" << std::endl;
  yyparse();
  if (f_verbose) std::cout << "Parsing Complete\n" << std::endl;

  if (!f_parseOnly)
  {
    if (f_source)
    {
      if (f_verbose) std::cout << "Emitting Source\n" << std::endl;
      programNode->emitSource("");
    }
    else
    {
      if (f_verbose) std::cout << "Emitting Assembly\n" << std::endl;
      try
      {
        programNode->emit();
      }
      catch (...)
      {
        std::cout << "Threw" << std::endl;
      }
    }
  }

  {
    auto reg = RegisterPool::getInstance()->getRegister();
    std::cout << reg << std::endl;
  }

  auto reg = RegisterPool::getInstance()->getRegister();
  std::cout << reg << std::endl;
}
