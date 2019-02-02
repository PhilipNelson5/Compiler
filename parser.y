%{
#include <iostream>
#include <cstring>
#include <map>

#include "symbol_table.hpp"

#define YYERROR_VERBOSE 1

extern "C" int yylex();
extern char * yytext;
extern unsigned int yylineno;
extern unsigned int yycolumn;
void yyerror(const char*);
%}

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
%type <int_val>  Expression
%type <char_val> CHAR_T
%type <str_val>  ID_T

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

Program           : OptConstDecls OptTypeDecls OptVariableDecls OptProcedureAndFunctionDeclList Block DOT_T {}
                  ;

/* 3.1.1 Constant Declerations */
OptConstDecls     : CONST_T ConstDeclList {}
                  | /* λ */ {}
                  ;

ConstDeclList     : ConstDeclList ConstDecl {}
                  | ConstDecl {}
                  ;

ConstDecl         : ID_T EQUAL_T Expression SEMI_COLON_T {}
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

ProcedureDecl                   : PROCEDURE_T ID_T OPEN_PAREN_T FormalParameters CLOSE_PAREN_T SEMI_COLON_T FORWARD_T SEMI_COLON_T {}
                                | PROCEDURE_T ID_T OPEN_PAREN_T FormalParameters CLOSE_PAREN_T SEMI_COLON_T Body SEMI_COLON_T {}
                                ;

FunctionDecl                    : FUNCTION_T ID_T OPEN_PAREN_T FormalParameters CLOSE_PAREN_T COLON_T Type SEMI_COLON_T FORWARD_T SEMI_COLON_T  {}
                                | FUNCTION_T ID_T OPEN_PAREN_T FormalParameters CLOSE_PAREN_T COLON_T Type SEMI_COLON_T Body SEMI_COLON_T {}
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

Block                           : BEGIN_T StatementSequence END_T {}
                                ;

/* 3.1.3 Type Declerations */
OptTypeDecls      : TYPE_T TypeDeclList {}
                  | /* λ */ {}
                  ;

TypeDeclList      : TypeDeclList TypeDecl {}
                  | TypeDecl {}
                  ;

TypeDecl          : ID_T EQUAL_T Type SEMI_COLON_T {}
                  ;

Type              : SimpleType {}
                  | RecordType {}
                  | ArrayType {}
                  ;

SimpleType        : ID_T {}
                  ;

RecordType        : RECORD_T OptFieldList END_T {}
                  ;

OptFieldList      : FieldList {}
                  | /* λ */ {}
                  ;

FieldList         : FieldList Field {}
                  | Field {}
                  ;

Field             : IdentList COLON_T Type SEMI_COLON_T {}
                  ;

ArrayType         : ARRAY_T OPEN_BRACKET_T Expression COLON_T CLOSE_BRACKET_T OF_T Type {}
                  ;

IdentList         : ID_T OptIdentList {}
                  ;

OptIdentList      : COMMA_T ID_T OptIdentList {}
                  | COMMA_T ID_T {}
                  | /* λ */ {}
                  ;  

/* 3.1.4 Variable Declerations */
OptVariableDecls  : VAR_T FieldList {}
                  | /* λ */ {}
                  ;

/* 3.2   CPSL Statements */
StatementSequence : Statement OptStatmentList {}
                  ;

OptStatmentList   : StatementList {}
                  | /* λ */ {}
                  ;

StatementList     : StatementList SEMI_COLON_T Statement {}
                  | SEMI_COLON_T Statement {}
                  ;

Statement         : Assignment {}
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

Assignment        : LValue ASSIGN_T Expression {}
                  ;

IfStatement            : IF_T Expression THEN_T StatementSequence OptElseIfStatementList OptElseStatement END_T {}
                       ;

OptElseIfStatementList : ElseIfStatementList {}
                       | /* λ */ {}
                       ;

ElseIfStatementList    : ElseIfStatementList ELSEIF_T Expression THEN_T StatementSequence {}
                       | ELSEIF_T Expression THEN_T StatementSequence {}
                       ;

OptElseStatement       :  ELSE_T StatementSequence END_T {}
                       ;

WhileStatement    : WHILE_T Expression DO_T StatementSequence END_T {}
                  ;

RepeatStatement   : REPEAT_T StatementSequence UNTIL_T Expression {}
                  ;

ForStatement      : FOR_T ID_T ASSIGN_T Expression TO_T Expression DO_T StatementSequence END_T {}
                  | FOR_T ID_T ASSIGN_T Expression TO_T Expression DOWNTO_T StatementSequence END_T {}
                  ;

StopStatement     : STOP_T {}
                  ;

ReturnStatement   : RETURN_T {}
                  | RETURN_T Expression {}
                  ;

ReadStatement     : READ_T OPEN_PAREN_T LValue OptLValueList CLOSE_PAREN_T {}
                  ;

OptLValueList     : OptLValueList COMMA_T LValue {}
                  | COMMA_T LValue {}
                  | /* λ */ {}
                  ;

WriteStatement    : WRITE_T OPEN_PAREN_T ExpressionList CLOSE_PAREN_T {}
                  ;

ExpressionList    : Expression OptExpressionList
                  ;

OptExpressionList : OptExpressionList COMMA_T Expression {}
                  | COMMA_T Expression {}
                  | /* λ */ {}
                  ;

ProcedureCall     : ID_T OPEN_PAREN_T OptArg OptArgList CLOSE_PAREN_T {}
                  ;

OptArg            : Expression {}
                  | /* λ */ {}
                  ;

OptArgList        : OptArgList COMMA_T Expression {}
                  | COMMA_T Expression {}
                  | /* λ */ {}
                  ;

NullStatement     : /* λ */ {}
                  ;

/* 3.3   Expressions */

Expression        : Expression OR_T Expression {}
                  | Expression AND_T Expression {}
                  | Expression EQUAL_T Expression {}
                  | Expression NEQUAL_T Expression {}
                  | Expression LTE_T Expression {}
                  | Expression GTE_T Expression {}
                  | Expression LT_T Expression {}
                  | Expression GT_T Expression {}
                  | Expression PLUS_T Expression {}
                  | Expression MINUS_T Expression {} {}
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

LValue            : ID_T OptMemberAccessOrSubscriptList {}
                  ;

OptMemberAccessOrSubscriptList : MemberAccessOrSubscriptList {}
                               | /* λ */ {}
                               ;

MemberAccessOrSubscriptList    : MemberAccessOrSubscriptList MemberAccess {}
                               | MemberAccessOrSubscriptList Subscript {}
                               | MemberAccess {}
                               | Subscript {}
                               ;

MemberAccess                   : DOT_T ID_T {}
                               ;

Subscript                      : OPEN_BRACKET_T Expression CLOSE_BRACKET_T {}
                               ;


%%

void yyerror(const char* msg)
{
  std::cerr << msg << std::endl;
  std::cerr << yylineno << ":" << yycolumn - strlen(yytext) << " " << yytext << std::endl;
}
