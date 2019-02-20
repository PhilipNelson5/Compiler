cmake_minimum_required(VERSION 2.8)
project(cpsl)

find_package(BISON)
find_package(FLEX)

bison_target(Parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
flex_target(Scanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp)
add_flex_bison_dependency(Scanner Parser)

set(EXTRA_COMPILE_FLAGS "-g3 -std=c++14")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

set(cpsl_srcs
  main.cpp

  #src/symbol_table.cpp
  #src/symbol_table.hpp
  src/AddNode.cpp
  src/AddNode.hpp
  src/AssignmentStatementNode.cpp
  src/AssignmentStatementNode.hpp
  src/CharacterConstantNode.cpp
  src/CharacterConstantNode.hpp
  src/CharacterExpressionNode.cpp
  src/CharacterExpressionNode.hpp
  src/ConstantDeclarationNode.cpp
  src/ConstantDeclarationNode.hpp
  src/EqualExpressionNode.cpp
  src/EqualExpressionNode.hpp
  src/ExpressionNode.cpp
  src/ExpressionNode.hpp
  src/IntegerConstantNode.cpp
  src/IntegerConstantNode.hpp
  src/ListNode.hpp
  src/LvalueNode.cpp
  src/LvalueNode.hpp
  src/Node.hpp
  src/NotEqualExpressionNode.cpp
  src/NotEqualExpressionNode.hpp
  src/OrdinalExpressionNode.cpp
  src/OrdinalExpressionNode.hpp
  src/ProgramNode.cpp
  src/ProgramNode.hpp
  src/ReadStatementNode.cpp
  src/ReadStatementNode.hpp
  src/RegisterPool.cpp
  src/RegisterPool.hpp
  src/SimpleTypeNode.cpp
  src/SimpleTypeNode.hpp
  src/StatementNode.hpp
  src/StopStatementNode.cpp
  src/StopStatementNode.hpp
  src/StringConstantNode.cpp
  src/StringConstantNode.hpp
  src/TypeDeclarationNode.cpp
  src/TypeDeclarationNode.hpp
  src/VariableDeclarationNode.cpp
  src/VariableDeclarationNode.hpp
  src/WriteStatementNode.cpp
  src/WriteStatementNode.hpp

  ${BISON_Parser_OUTPUTS}
  ${FLEX_Scanner_OUTPUTS}
)
source_group("Cpsl" FILES ${cpsl_srcs})

add_executable(cpsl ${cpsl_srcs})
target_link_libraries(cpsl ${FLEX_LIBRARIES} ${BISON_LIBRARIES})
target_include_directories(cpsl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

