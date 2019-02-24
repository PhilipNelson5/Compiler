extern int yyparse();
extern int yydebug;

#include "src/ProgramNode.hpp"
#include "src/RegisterPool.hpp"
#include "src/log/easylogging++.h"

#include <cstring>
#include <iostream>
#include <memory>

INITIALIZE_EASYLOGGINGPP

std::shared_ptr<ProgramNode> programNode;

void initEasyLogging(int argc, char** argv);
void showHelp();

int main(int argc, char** argv)
{
  initEasyLogging(argc, argv);

  yydebug = 0;
  auto f_source = false;
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
  }

  LOG(DEBUG) << "Parsing";
  yyparse();
  LOG(DEBUG) << "Parsing Complete";

  if (!f_parseOnly)
  {
    if (f_source)
    {
      LOG(DEBUG) << "Emitting Source";
      programNode->emitSource("");
    }
    else
    {
      LOG(DEBUG) << "Emitting Assembly";
      try
      {
        programNode->emit();
      }
      catch (const char* msg)
      {
        std::cout << msg << std::endl;
      }
    }
  }
}

void initEasyLogging(int argc, char* argv[])
{
  bool log_debug = false;
  bool log_warn = false;
  bool log_error = true;
  for (auto i = 1; i < argc; ++i)
  {
    if (strcmp(argv[i], "-ld") == 0 | strcmp(argv[i], "--log-debug") == 0)
      log_debug = true;
    if (strcmp(argv[i], "-lw") == 0 | strcmp(argv[i], "--log-warning") == 0)
      log_warn = true;
    if (strcmp(argv[i], "-le") == 0 | strcmp(argv[i], "--no-log-error") == 0)
      log_error = false;
  }
  /* clang-format off */
  std::string defaultLogConfig = R"(
* GLOBAL:
    FORMAT               =  "[%fbase:%line] %level %msg"
    ENABLED              =  true
    TO_FILE              =  false
    TO_STANDARD_OUTPUT   =  true
    MILLISECONDS_WIDTH   =  6
    PERFORMANCE_TRACKING =  true
    MAX_LOG_FILE_SIZE    =  2097152 ## 2MB
    LOG_FLUSH_THRESHOLD  =  1 ## Flush after every log
)";
  defaultLogConfig += "* DEBUG:\n";
  if (log_debug) defaultLogConfig += "    ENABLED = true\n";
  else defaultLogConfig += "    ENABLED = false\n";

  defaultLogConfig += "* WARNING:\n";
  if (log_warn) defaultLogConfig += "    ENABLED = true\n";
  else defaultLogConfig += "    ENABLED = false\n";

  defaultLogConfig += "* ERROR:\n";
  if (log_error) defaultLogConfig += "    ENABLED = true\n";
  else defaultLogConfig += "    ENABLED = false\n";
  /* clang-format on */

  START_EASYLOGGINGPP(argc, argv);

  el::Configurations conf;
  conf.parseFromText(defaultLogConfig);
  el::Loggers::setDefaultConfigurations(conf);
  el::Loggers::reconfigureAllLoggers(conf);
}

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
  std::cout << "-ld\t--log-debug\tenable debugging level logging\n";
  std::cout << "-lw\t--log-warn\tenable warning level logging\n";
  std::cout << "-le\t--no-log-error\tdisable error level logging\n";
  std::cout << std::endl;
}
