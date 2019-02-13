%{
#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>

#include "src/Node.hpp"
#include "src/ExpressionNode.hpp"
#include "src/StatementNode.hpp"
#include "src/ListNode.hpp"
#include "src/LvalueNode.hpp"
#include "src/WriteStatementNode.hpp"
#include "src/IntegerConstantNode.hpp"
#include "src/ProgramNode.hpp"
#include "src/VariableDeclarationNode.hpp"
#include "src/AssignmentStatementNode.hpp"

#define YYERROR_VERBOSE 1
#define DEBUG 1

extern "C" int yylex();
extern char * yytext;
extern std::string yylinetxt;
extern unsigned int yylineno;
extern unsigned int yycolumn;
extern std::shared_ptr<ProgramNode> programNode;
void yyerror(const char*);

%}

%define parse.trace

%union
{
  int int_val;
  char char_val;
  char * str_val;
  Node * node;
  ExpressionNode * expressionNode;
  LvalueNode * lvalue;
  VariableDeclarationNode * varDeclNode;
  ListNode<ExpressionNode> * expressionList;
  ListNode<VariableDeclarationNode> * varDelcList;
  ListNode<StatementNode> * statementList;
  ListNode<std::string> * identList;
  WriteStatementNode * writeStatementNode;
  StatementNode * statementNode;
  AssignmentStatementNode * assignmentNode;
}

%token ARRAY_T
%token BEGIN_T
%token CHR_T
%token CONST_T
%token DO_T
%token DOWNTO_T
%token ELSE_T
%token ELSEIF_T
%token END_T
%token FOR_T
%token FORWARD_T
%token FUNCTION_T
%token IF_T
%token OF_T
%token ORD_T
%token PRED_T
%token PROCEDURE_T
%token READ_T
%token RECORD_T

%token REF_T
%token REPEAT_T
%token RETURN_T
%token STOP_T
%token SUCC_T
%token THEN_T
%token TO_T
%token TYPE_T
%token UNTIL_T
%token VAR_T
%token WHILE_T
%token WRITE_T

%token ID_T;

%token PLUS_T
%token MINUS_T
%token UNARY_MINUS_T
%token MULTIPLY_T
%token DIVIDE_T
%token AND_T
%token OR_T
%token NOT_T
%token EQUAL_T
%token NEQUAL_T
%token LT_T
%token LTE_T
%token GT_T
%token GTE_T
%token DOT_T
%token COMMA_T
%token COLON_T
%token SEMI_COLON_T
%token OPEN_PAREN_T
%token CLOSE_PAREN_T
%token OPEN_BRACKET_T
%token CLOSE_BRACKET_T
%token ASSIGN_T
%token MOD_T

%token NUMBER_T
%token CHAR_T
%token STRING_T

%type <int_val>  NUMBER_T
%type <char_val> CHAR_T
%type <str_val>  ID_T

%type <node> Program
%type <node> OptConstDecls
%type <node> ConstDeclList
%type <node> ConstDecl
%type <node> OptProcedureAndFunctionDeclList
%type <node> ProcedureAndFunctionDeclList
%type <node> ProcedureDecl
%type <node> FunctionDecl
%type <node> FormalParameters
%type <node> FormalParameterList
%type <node> FormalParameter
%type <statementList> Block
%type <node> OptTypeDecls
%type <node> TypeDeclList
%type <node> TypeDecl
%type <str_val> Type
%type <str_val> SimpleType
%type <node> RecordType
%type <varDelcList> OptFieldList
%type <varDelcList> FieldList
%type <varDeclNode> Field
%type <node> ArrayType
%type <identList> IdentList
%type <varDelcList> OptVariableDecls
%type <varDelcList> VariableDeclList
%type <varDeclNode> VariableDecl
%type <statementList> StatementList
%type <statementNode> Statement
%type <assignmentNode> Assignment
%type <node> IfStatement
%type <node> ElseIfStatementList
%type <node> OptElseStatement
%type <node> WhileStatement
%type <node> RepeatStatement
%type <node> ForStatement
%type <node> StopStatement
%type <node> ReturnStatement
%type <node> ReadStatement
%type <node> LValueList
%type <writeStatementNode> WriteStatement
%type <expressionList> OptExpressionList
%type <expressionList> ExpressionList
%type <node> ProcedureCall
%type <expressionNode> Expression
%type <lvalue> LValue

%right     UNARY_MINUS_T
%left      MULTIPLY_T DIVIDE_T MOD_T
%left      PLUS_T MINUS_T
%nonassoc  EQUAL_T NEQUAL_T LT_T LTE_T GT_T GTE_T 
%left      NOT_T
%left      AND_T
%left      OR_T

%%

/* Opt prefix means zero or one   (?) */
/* List postfix means one or more (+) */
/* OptList means zero or more     (*) */

Program                         : OptConstDecls
                                  OptTypeDecls
                                  OptVariableDecls
                                  OptProcedureAndFunctionDeclList
                                  Block DOT_T
                                  {
                                    /*programNode = new ProgramNode($1, $2, $3, $4, $5);*/
                                    programNode = std::make_shared<ProgramNode>($3, $5);
                                  }
                                ;

/* 3.1.1 Constant Declerations */
OptConstDecls                   : CONST_T ConstDeclList { $$ = nullptr; }
                                | /* λ */ { $$ = nullptr; }
                                ;

ConstDeclList                   : ConstDeclList ConstDecl {}
                                | ConstDecl {}
                                ;

ConstDecl                       : ID_T EQUAL_T Expression SEMI_COLON_T {}
                                ;

/* 3.1.2 Procedure and Function Declarations */
OptProcedureAndFunctionDeclList : ProcedureAndFunctionDeclList { $$ = nullptr; }
                                | /* λ */ { $$ = nullptr; }
                                ;

ProcedureAndFunctionDeclList    : ProcedureAndFunctionDeclList ProcedureDecl  {}
                                | ProcedureAndFunctionDeclList FunctionDecl {}
                                | ProcedureDecl {}
                                | FunctionDecl {}
                                ;

ProcedureDecl                   : PROCEDURE_T ID_T OPEN_PAREN_T FormalParameters CLOSE_PAREN_T
                                    SEMI_COLON_T FORWARD_T SEMI_COLON_T {}
                                | PROCEDURE_T ID_T OPEN_PAREN_T FormalParameters CLOSE_PAREN_T
                                    SEMI_COLON_T Body SEMI_COLON_T {}
                                ;

FunctionDecl                    : FUNCTION_T ID_T OPEN_PAREN_T FormalParameters CLOSE_PAREN_T
                                    COLON_T Type SEMI_COLON_T FORWARD_T SEMI_COLON_T  {}
                                | FUNCTION_T ID_T OPEN_PAREN_T FormalParameters CLOSE_PAREN_T
                                    COLON_T Type SEMI_COLON_T Body SEMI_COLON_T {}
                                ;

FormalParameters                : FormalParameterList  {}
                                | /* λ */ {}
                                ;

FormalParameterList             : FormalParameterList SEMI_COLON_T FormalParameter {}
                                | FormalParameter {}
                                ;

FormalParameter                 : VAR_T IdentList COLON_T Type {}
                                | REF_T IdentList COLON_T Type {}
                                |       IdentList COLON_T Type {}
                                ;

Body                            : OptConstDecls OptTypeDecls OptVariableDecls Block {}
                                ;

Block                           : BEGIN_T StatementList END_T { $$ = $2; }
                                ;

/* 3.1.3 Type Declerations */
OptTypeDecls                    : TYPE_T TypeDeclList { $$ = nullptr; }
                                | /* λ */ { $$ = nullptr; }
                                ;

TypeDeclList                    : TypeDeclList TypeDecl {}
                                | TypeDecl {}
                                ;

TypeDecl                        : ID_T EQUAL_T Type SEMI_COLON_T {}
                                ;

Type                            : SimpleType { $$ = $1;}
                                | RecordType {}
                                | ArrayType {}
                                ;

SimpleType                      : ID_T { $$ = $1; }
                                ;

RecordType                      : RECORD_T OptFieldList END_T {}
                                ;

OptFieldList                    : FieldList { $$ = $1; }
                                | /* λ */ { $$ = nullptr; }
                                ;

FieldList                       : FieldList Field {}
                                | Field {}
                                ;

Field                           : IdentList COLON_T Type SEMI_COLON_T {}
                                ;

ArrayType                       : ARRAY_T
                                  OPEN_BRACKET_T Expression COLON_T Expression CLOSE_BRACKET_T
                                  OF_T Type {}
                                ;

IdentList                       : IdentList COMMA_T ID_T
                                  {
                                    $$ = new ListNode<std::string>(new std::string($3), $1);
                                  }
                                | ID_T
                                  {
                                    $$ = new ListNode<std::string>(new std::string($1));
                                  }
                                ;  

/* 3.1.4 Variable Declerations */
OptVariableDecls                : VAR_T VariableDeclList { $$ = $2; }
                                | /* λ */ { $$ = nullptr; }
                                ;

VariableDeclList                : VariableDeclList VariableDecl
                                  {
                                    $$ = new ListNode<VariableDeclarationNode>($2, $1);
                                  }
                                | VariableDecl
                                  {
                                    $$ = new ListNode<VariableDeclarationNode>($1);
                                  }
                                ;

VariableDecl                    : IdentList COLON_T Type SEMI_COLON_T
                                  {
                                    $$ = new VariableDeclarationNode($1, $3);
                                  }
                                ;

/* 3.2   CPSL Statements */
StatementList                   : StatementList SEMI_COLON_T Statement
                                  {
                                    $$ = new ListNode<StatementNode>($3, $1);
                                  }
                                | Statement
                                  {
                                    $$ = new ListNode<StatementNode>($1);
                                  }
                                ;

Statement                       : Assignment {}
                                | IfStatement {}
                                | WhileStatement {}
                                | RepeatStatement {}
                                | ForStatement {}
                                | StopStatement {}
                                | ReturnStatement {}
                                | ReadStatement {}
                                | WriteStatement { $$ = $1; }
                                | ProcedureCall {}
                                | { $$ = nullptr; }
                                ;

Assignment                      : LValue ASSIGN_T Expression { $$ = new AssignmentStatementNode($1, $3); }
                                ;

IfStatement                     : IfHeader ThenBody ElseIfStatementList OptElseStatement END_T {}
                                ;

IfHeader                        : IF_T Expression {}
                                ;

ThenBody                        : THEN_T StatementList {}
                                ;

ElseIfStatementList             : ElseIfStatementList ElseIfHeader ThenBody{}
                                | /* λ */ {}
                                ;

ElseIfHeader                    : ELSEIF_T Expression {}
                                ;

OptElseStatement                : ELSE_T StatementList {}
                                | /* λ */ {}
                                ;

WhileStatement                  : WHILE_T Expression DO_T StatementList END_T {}
                                ;

RepeatStatement                 : REPEAT_T StatementList UNTIL_T Expression {}
                                ;

ForStatement                    : FOR_T ID_T ASSIGN_T Expression TO_T Expression
                                    DO_T StatementList END_T {}
                                | FOR_T ID_T ASSIGN_T Expression DOWNTO_T Expression
                                    DO_T StatementList END_T {}
                                ;

StopStatement                   : STOP_T {}
                                ;

ReturnStatement                 : RETURN_T {}
                                | RETURN_T Expression {}
                                ;

ReadStatement                   : READ_T OPEN_PAREN_T LValueList CLOSE_PAREN_T {}
                                ;

LValueList                      : LValueList COMMA_T LValue {}
                                | LValue {}
                                ;

WriteStatement                  : WRITE_T OPEN_PAREN_T ExpressionList CLOSE_PAREN_T
                                  { 
                                    $$ = new WriteStatementNode($3);
                                  }
                                ;

ProcedureCall                   : ID_T OPEN_PAREN_T OptExpressionList CLOSE_PAREN_T {}
                                ;

OptExpressionList               : ExpressionList { $$ = $1; }
                                | /* λ */ { $$ = nullptr; }
                                ;

ExpressionList                  : ExpressionList COMMA_T Expression
                                  {
                                    $$ = new ListNode<ExpressionNode>($3, $1);
                                  }
                                | Expression
                                  {
                                    $$ = new ListNode<ExpressionNode>($1);
                                  }
                                ;

/* 3.3   Expressions */

Expression                      : Expression OR_T Expression {}
                                | Expression AND_T Expression {}
                                | Expression EQUAL_T Expression {}
                                | Expression NEQUAL_T Expression {}
                                | Expression LTE_T Expression {}
                                | Expression GTE_T Expression {}
                                | Expression LT_T Expression {}
                                | Expression GT_T Expression {}
                                | Expression PLUS_T Expression {}
                                | Expression MINUS_T Expression {}
                                | Expression MULTIPLY_T Expression {}
                                | Expression DIVIDE_T Expression {}
                                | Expression MOD_T Expression {}
                                | NOT_T Expression {}
                                | MINUS_T Expression %prec UNARY_MINUS_T {}
                                | OPEN_PAREN_T Expression CLOSE_PAREN_T {}
                                | ProcedureCall {}
                                | CHR_T OPEN_PAREN_T Expression CLOSE_PAREN_T {}
                                | ORD_T OPEN_PAREN_T Expression CLOSE_PAREN_T {}
                                | PRED_T OPEN_PAREN_T Expression CLOSE_PAREN_T {}
                                | SUCC_T OPEN_PAREN_T Expression CLOSE_PAREN_T {}
                                | LValue { $$ = $1; }
                                | NUMBER_T { $$ = new IntegerConstantNode($1); }
                                | STRING_T {}
                                | CHAR_T {}
                                ;

LValue                          : LValue DOT_T ID_T { $$ = nullptr; }
                                | LValue OPEN_BRACKET_T Expression CLOSE_BRACKET_T { $$ = nullptr; }
                                | ID_T { $$ = new LvalueNode($1); }
                                 ;

%%

void yyerror(const char* msg)
{
  std::string restofline;
  std::getline(std::cin, restofline);

  std::cerr << msg << std::endl;

  std::stringstream ss;
  ss << yylineno << ":" << yycolumn - strlen(yytext) << " " ;

  std::cerr << ss.str();
  std::cerr << yylinetxt << restofline << std::endl;

  for(auto i = 0u; i < ss.str().length(); ++i)
  {
    std::cout << " ";
  }

  for(auto i = 0u; i < yylinetxt.length()-1; ++i)
  {
    std::cout << "~";
  }

  std::cout << "^" << std::endl;
}
