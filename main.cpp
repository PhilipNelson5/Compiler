extern int yyparse();
extern int yydebug;

#include "src/ProgramNode.hpp"

#include <cstring>
#include <iostream>
#include <memory>

std::shared_ptr<ProgramNode> programNode;

void showHelp()
{
  std::cout << std::endl;
  std::cout << "     ______   _______    ______   __       " << std::endl;
  std::cout << "    /      \\ |       \\  /      \\ |  \\      " << std::endl;
  std::cout << "   |  $$$$$$\\| $$$$$$$\\|  $$$$$$\\| $$      " << std::endl;
  std::cout << "   | $$   \\$$| $$__/ $$| $$___\\$$| $$      " << std::endl;
  std::cout << "   | $$      | $$    $$ \\$$    \\ | $$      " << std::endl;
  std::cout << "   | $$   __ | $$$$$$$  _\\$$$$$$\\| $$      " << std::endl;
  std::cout << "   | $$__/  \\| $$      |  \\__| $$| $$_____ " << std::endl;
  std::cout << "    \\$$    $$| $$       \\$$    $$| $$     \\" << std::endl;
  std::cout << "     \\$$$$$$  \\$$        \\$$$$$$  \\$$$$$$$$" << std::endl
            << std::endl;

  std::cout << "-d\t--debug\t\tset yydebug to a positive value" << std::endl;
  std::cout << "-h\t--help\t\tshow this help message" << std::endl;
  std::cout << "-p\t--parse-only\tskip all assembly or source code emission"
            << std::endl;
  std::cout << "-s\t--source\tparse and emit source code" << std::endl;
  std::cout << "-v\t--verbose\textra print statements" << std::endl;
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
    if (strcmp(argv[i], "-s") == 0 | strcmp(argv[i], "--source") == 0)
      f_source = true;
    if (strcmp(argv[i], "-v") == 0 | strcmp(argv[i], "--verbose") == 0)
      f_verbose = true;
    if (strcmp(argv[i], "-p") == 0 | strcmp(argv[i], "--parse-only") == 0)
      f_parseOnly = true;
    if (strcmp(argv[i], "-d") == 0 | strcmp(argv[i], "--debug") == 0)
      yydebug = 1;
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
};
