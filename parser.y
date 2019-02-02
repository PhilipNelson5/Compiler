%{
#include <iostream>
#include <map>

#include "symbol_table.hpp"

extern "C" int yylex();
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

%type <int_val> NUMBER_T
%type <int_val> Expression
%type <int_val> Factor
%type <int_val> Term
%type <str_val> ID_T

%%

/* Opt prefix means zero or one   (?) */
/* List postfix means one or more (+) */
/* OptList means zero or more     (*) */

Program          : OptConstDecls OptTypeDecls OptVariableDecls OptProcedureAndFunctionDeclList Block DOT_T {}
                 ;

/* 3.1.1 Constant Declerations */
OptConstDecls    : CONST_T ConstDeclList {}
                 | /* λ */ {}
                 ;

ConstDeclList    : ConstDeclList ConstDecl {}
                 | ConstDecl {}
                 ;

ConstDecl        : ID_T EQUAL_T Expression SEMI_COLON_T {}
                 ;

/* 3.1.2 Procedure and Function Declarations */
OptProcedureAndFunctionDeclList : ProcedureAndFunctionDeclList {}
                                | /* λ */ {}
                                ;

ProcedureAndFunctionDeclList    : ProcedureAndFunctionDeclList Procedure  {}
                                | ProcedureAndFunctionDeclList Function {}
                                | Procedure {}
                                | Function {}
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
OptTypeDecls     : TYPE_T TypeDeclList {}
                 | /* λ */ {}
                 ;

TypeDeclList     : TypeDeclList TypeDecl {}
                 | TypeDecl {}
                 ;

TypeDecl         : ID_T EQUAL_T Type SEMI_COLON_T {}
                 ;

Type             : SimpleType {}
                 | RecordType {}
                 | ArrayType {}
                 ;

SimpleType       : ID_T {}
                 ;

RecordType       : RECORD_T OptFieldList END_T {}
                 ;

OptFieldList     : FieldList {}
                 | /* λ */ {}
                 ;

FieldList        : FieldList Field {}
                 | Field {}
                 ;

Field            : IdentList COLON_T Type SEMI_COLON_T {}
                 ;

ArrayType        : ARRAY_T OPEN_BRACKET_T Expression COLON_T CLOSE_BRACKET_T OF_T Type {}
                 ;

IdentList        : ID_T OptIdentList {}
                 ;

OptIdentList     : COMMA_T ID_T OptIdentList {}
                 | COMMA_T ID_T {}
                 | /* λ */ {}
                 ;  

/* 3.1.4 Variable Declerations */
OptVariableDecls : VAR_T FieldList {}
                 ;


/* 3.2   CPSL Statements */

/* 3.3   Expressions */


StatementList    : StatementList Statement {}
                 | {}
                 ;

Statement        : Expression SEMI_COLON_T {std::cout << $1 << std::endl;}
                 | SEMI_COLON_T {}
                 ;

Expression       : Expression PLUS_T Term {$$ = $1 + $3;}
                 | Expression MINUS_T Term {$$ = $1 - $3;}
                 | Term {$$ = $1;}
                 ;

Term             : Term MULTIPLY_T Factor { $$ = $1 * $3;}
                 | Term Factor { $$ = $1 * $2;}
                 | Term DIVIDE_T Factor { $$ = $1 / $3;}
                 | Factor {$$ = $1;}
                 ;

Factor           : OPEN_PAREN_T Expression CLOSE_PAREN_T {$$ = $2;}
                 | NUMBER_T {$$ = $1;}
                 | ID_T {$$ = symbol_table.lookup($1); delete($1);}
                 ;

%%

void yyerror(const char* msg)
{
  std::cerr << msg << std::endl;
}

