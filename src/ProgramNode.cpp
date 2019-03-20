#include "ProgramNode.hpp"

#include "ConstantDeclarationNode.hpp" // for ConstantDeclarationNode
#include "ListNode.hpp"                // for ListNode
#include "StatementNode.hpp"           // for StatementNode
#include "SymbolTable.hpp"             // for SymbolTable, symbol_table
#include "TypeDeclarationNode.hpp"     // for TypeDeclarationNode
#include "VariableDeclarationNode.hpp" // for VariableDeclarationNode

#include <iostream> // for operator<<, endl, basic_ostream
#include <memory>   // for shared_ptr, __shared_ptr_access

ProgramNode::ProgramNode(ListNode<ConstantDeclarationNode>*& cds,
                         ListNode<TypeDeclarationNode>*& tds,
                         ListNode<VariableDeclarationNode>*& vds,
                         ListNode<StatementNode>*& mBlock)
{
  constantDecls = ListNode<ConstantDeclarationNode>::makeVector(cds);

  typeDecls = ListNode<TypeDeclarationNode>::makeVector(tds);

  varDecls = ListNode<VariableDeclarationNode>::makeVector(vds);

  mainBlock = ListNode<StatementNode>::makeVector(mBlock);
}

void ProgramNode::emitSource(std::string indent)
{
  // Constant Declarations
  // ---------------------
  if (constantDecls.size() > 0u)
  {
    std::cout << indent << "CONST" << std::endl;
    for (auto&& constDecl : constantDecls)
    {
      constDecl->emitSource(indent + "  ");
    }
    std::cout << std::endl;
  }

  // Type Declarations
  // ---------------------
  if (typeDecls.size() > 0)
  {
    std::cout << indent << "TYPE" << std::endl;
    for (auto&& typeDecl : typeDecls)
    {
      typeDecl->emitSource(indent + "  ");
    }
    std::cout << std::endl;
  }

  // Variable Declarations
  // ---------------------
  if (varDecls.size() > 0)
  {
    std::cout << indent << "VAR" << std::endl;
    for (auto&& varDecl : varDecls)
    {
      varDecl->emitSource(indent + "  ");
    }
    std::cout << std::endl;
  }

  // Procedure and Function Declarations
  // -----------------------------------

  // Main Block
  // ---------------------
  std::cout << indent << "BEGIN" << std::endl;
  for (auto&& statement : mainBlock)
  {
    statement->emitSource(indent + "  ");
  }
  std::cout << indent << "END." << std::endl;
}

Value ProgramNode::emit()
{
  std::cout << ".text" << std::endl;
  std::cout << "la $gp, GLOBAL_AREA" << std::endl;

  // Constant Declarations
  // ---------------------
  // if (constantDecls.size() > 0u)
  //{
  // for (auto&& constDecl : constantDecls)
  //{
  // constDecl->emit();
  //}
  //}

  // Type Declarations
  // -----------------
  // if (constantDecls.size() > 0u)
  //{
  // for (auto&& typeDecl : typeDecls)
  //{
  // typeDecl->emit();
  //}
  //}

  // Variable Declarations
  // ---------------------
  // if (varDecls.size() > 0u)
  //{
  // for (auto&& varDecl : varDecls)
  //{
  // varDecl->emit();
  //}
  //}

  // Procedure and Function Declarations
  // -----------------------------------

  // Main Block
  // ---------------------
  for (auto&& statement : mainBlock)
  {
    statement->emit();
  }

  std::cout << "\n.data" << std::endl;
  symbol_table.printStrings();
  std::cout << "\n.align 2\nGLOBAL_AREA:" << std::endl;
  return {};
}
