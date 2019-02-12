%{
#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <sstream>

#define YYERROR_VERBOSE 1
#define DEBUG 1

extern "C" int yylex();
extern char * yytext;
extern std::string yylinetxt;
extern unsigned int yylineno;
extern unsigned int yycolumn;
void yyerror(const char*);
%}

%define parse.trace

%union
{
  int int_val;
  char char_val;
  char * str_val;
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

%type <int_val> COMMA_T

%type <int_val> Program
%type <int_val> OptConstDecls
%type <int_val> ConstDeclList
%type <int_val> ConstDecl
%type <int_val> OptProcedureAndFunctionDeclList
%type <int_val> ProcedureAndFunctionDeclList
%type <int_val> ProcedureDecl
%type <int_val> FunctionDecl
%type <int_val> FormalParameters
%type <int_val> FormalParameterList
%type <int_val> FormalParameter
%type <int_val> Body
%type <int_val> Block
%type <int_val> OptTypeDecls
%type <int_val> TypeDeclList
%type <int_val> TypeDecl
%type <int_val> Type
%type <int_val> SimpleType
%type <int_val> RecordType
%type <int_val> OptFieldList
%type <int_val> FieldList
%type <int_val> Field
%type <int_val> ArrayType
%type <int_val> OptIdentList
%type <int_val> IdentList
%type <int_val> OptVariableDecls
%type <int_val> StatementList
%type <int_val> Statement
%type <int_val> Assignment
%type <int_val> IfStatement
%type <int_val> ElseIfStatementList
%type <int_val> OptElseStatement
%type <int_val> WhileStatement
%type <int_val> RepeatStatement
%type <int_val> ForStatement
%type <int_val> StopStatement
%type <int_val> ReturnStatement
%type <int_val> ReadStatement
%type <int_val> LValueList
%type <int_val> WriteStatement
%type <int_val> ExpressionList
%type <int_val> OptExpressionList
%type <int_val> ProcedureCall
%type <int_val> NullStatement
%type <int_val> Expression
%type <int_val> LValue

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
                                  Block DOT_T {}
                                ;

/* 3.1.1 Constant Declerations */
OptConstDecls                   : CONST_T ConstDeclList {}
                                | /* λ */ {}
                                ;

ConstDeclList                   : ConstDeclList ConstDecl {}
                                | ConstDecl {}
                                ;

ConstDecl                       : ID_T EQUAL_T Expression SEMI_COLON_T {}
                                ;

/* 3.1.2 Procedure and Function Declarations */
OptProcedureAndFunctionDeclList : ProcedureAndFunctionDeclList {}
                                | /* λ */ {}
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

FormalParameter                 : VAR_T ID_T OptIdentList COLON_T Type {}
                                | REF_T ID_T OptIdentList COLON_T Type {}
                                |       ID_T OptIdentList COLON_T Type {}
                                ;

Body                            : OptConstDecls OptTypeDecls OptVariableDecls Block {}
                                ;

Block                           : BEGIN_T StatementList END_T {}
                                ;

/* 3.1.3 Type Declerations */
OptTypeDecls                    : TYPE_T TypeDeclList {}
                                | /* λ */ {}
                                ;

TypeDeclList                    : TypeDeclList TypeDecl {}
                                | TypeDecl {}
                                ;

TypeDecl                        : ID_T EQUAL_T Type SEMI_COLON_T {}
                                ;

Type                            : SimpleType {}
                                | RecordType {}
                                | ArrayType {}
                                ;

SimpleType                      : ID_T {}
                                ;

RecordType                      : RECORD_T OptFieldList END_T {}
                                ;

OptFieldList                    : FieldList {}
                                | /* λ */ {}
                                ;

FieldList                       : FieldList Field {}
                                | Field {}
                                ;

Field                           : ID_T OptIdentList COLON_T Type SEMI_COLON_T {}
                                ;

ArrayType                       : ARRAY_T
                                  OPEN_BRACKET_T Expression COLON_T Expression CLOSE_BRACKET_T
                                  OF_T Type {}
                                ;

OptIdentList                    : IdentList {}
                                | /* λ */ {}
                                ;

IdentList                       : IdentList COMMA_T ID_T {}
                                | COMMA_T ID_T {}
                                ;  

/* 3.1.4 Variable Declerations */
OptVariableDecls                : VAR_T FieldList {}
                                | /* λ */ {}
                                ;

/* 3.2   CPSL Statements */
StatementList                   : StatementList SEMI_COLON_T Statement {}
                                | Statement {}
                                ;

Statement                       : Assignment {}
                                | IfStatement {}
                                | WhileStatement {}
                                | RepeatStatement {}
                                | ForStatement {}
                                | StopStatement {}
                                | ReturnStatement {}
                                | ReadStatement {}
                                | WriteStatement {}
                                | ProcedureCall {}
                                | NullStatement {}
                                ;

Assignment                      : LValue ASSIGN_T Expression {}
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

WriteStatement                  : WRITE_T OPEN_PAREN_T ExpressionList CLOSE_PAREN_T {}
                                ;

ProcedureCall                   : ID_T OPEN_PAREN_T OptExpressionList CLOSE_PAREN_T {}
                                ;

OptExpressionList               : ExpressionList {}
                                | /* λ */ {}
                                ;

ExpressionList                  : ExpressionList COMMA_T Expression {}
                                | Expression {}
                                ;

NullStatement                   : /* λ */ {}
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
                                | LValue {}
                                | NUMBER_T {}
                                | STRING_T {}
                                | CHAR_T {}
                                ;

LValue                          : LValue DOT_T ID_T {}
                                | LValue OPEN_BRACKET_T Expression CLOSE_BRACKET_T {}
                                | ID_T {}
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
