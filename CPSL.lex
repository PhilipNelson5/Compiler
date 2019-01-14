%{
#include<iostream>
extern "C" int yylex();
%}

%%

array|ARRAY {std::cout << "TOKEN::ARRAY" << std::endl;}
begin|BEGIN {std::cout << "TOKEN::BEGIN" << std::endl;}
chr|CHR {std::cout << "TOKEN::CHR" << std::endl;}
const|CONST {std::cout << "TOKEN::CONST" << std::endl;}
do|DO {std::cout << "TOKEN::DO" << std::endl;}
downto|DOWNTO {std::cout << "TOKEN::DOWNTO" << std::endl;}
else|ELSE {std::cout << "TOKEN::ELSE" << std::endl;}
elseif|ELSEIF {std::cout << "TOKEN::ELSEIF" << std::endl;}
end|END {std::cout << "TOKEN::END" << std::endl;}
for|FOR {std::cout << "TOKEN::FOR" << std::endl;}
forward|FORWARD {std::cout << "TOKEN::FORWARD" << std::endl;}
function|FUNCTION {std::cout << "TOKEN::FUNCTION" << std::endl;}
if|IF {std::cout << "TOKEN::IF" << std::endl;}
of|OF {std::cout << "TOKEN::OF" << std::endl;}
ord|ORD {std::cout << "TOKEN::ORD" << std::endl;}
pred|PRED {std::cout << "TOKEN::PRED" << std::endl;}
procedure|PROCEDURE {std::cout << "TOKEN::PROCEDURE" << std::endl;}
read|READ {std::cout << "TOKEN::READ" << std::endl;}
record|RECORD {std::cout << "TOKEN::RECORD" << std::endl;}
ref|REF {std::cout << "TOKEN::REF" << std::endl;}
repeat|REPEAT {std::cout << "TOKEN::REPEAT" << std::endl;}
return|RETURN {std::cout << "TOKEN::RETURN" << std::endl;}
stop|STOP {std::cout << "TOKEN::STOP" << std::endl;}
succ|SUCC {std::cout << "TOKEN::SUCC" << std::endl;}
then|THEN {std::cout << "TOKEN::THEN" << std::endl;}
to|TO {std::cout << "TOKEN::TO" << std::endl;}
type|TYPE {std::cout << "TOKEN::TYPE" << std::endl;}
until|UNTIL {std::cout << "TOKEN::UNTIL" << std::endl;}
var|VAR {std::cout << "TOKEN::VAR" << std::endl;}
while|WHILE {std::cout << "TOKEN::WHILE" << std::endl;}
write|WRITE {std::cout << "TOKEN::WRITE" << std::endl;}

[a-zA-Z][a-zA-Z0-9_]* {std::cout << "TOKEN:ID" << std::endl;}

[ \t\n]* {std::cout << "TOKEN::DELIM" << std::endl;}

\+ {std::cout << "TOKEN::OP_PLUS" << std::endl;}
\- {std::cout << "TOKEN::OP_MINUS" << std::endl;}
\* {std::cout << "TOKEN::OP_MULTIPLY" << std::endl;}
\/ {std::cout << "TOKEN::OP_DIVIDE" << std::endl;}
\& {std::cout << "TOKEN::OP_AND" << std::endl;}
\| {std::cout << "TOKEN::OP_OR" << std::endl;}
\~ {std::cout << "TOKEN::OP_NOT" << std::endl;}
\= {std::cout << "TOKEN::OP_EQUAL" << std::endl;}
\<\> {std::cout << "TOKEN::OP_NEQUAL" << std::endl;}
\< {std::cout << "TOKEN::DELIM" << std::endl;}
\<= {std::cout << "TOKEN::DELIM" << std::endl;}
\> {std::cout << "TOKEN::DELIM" << std::endl;}
\>= {std::cout << "TOKEN::DELIM" << std::endl;}
\. {std::cout << "TOKEN::DELIM" << std::endl;}
, {std::cout << "TOKEN::DELIM" << std::endl;}
: {std::cout << "TOKEN::DELIM" << std::endl;}
; {std::cout << "TOKEN::DELIM" << std::endl;}
\( {std::cout << "TOKEN::DELIM" << std::endl;}
\) {std::cout << "TOKEN::DELIM" << std::endl;}
\[ {std::cout << "TOKEN::DELIM" << std::endl;}
\] {std::cout << "TOKEN::DELIM" << std::endl;}
:= {std::cout << "TOKEN::DELIM" << std::endl;}
\% {std::cout << "TOKEN::DELIM" << std::endl;}

0[0-9]+ {std::cout << "TOKEN::NUM_CONST_OCT" << std::endl;}
0[xX][a-fA-F0-9]+ {std::cout << "TOKEN::NUM_CONST_HEX" << std::endl;}
0[bB][01]+ {std::cout << "TOKEN::NUM_CONST_BIN" << std::endl;}
[0-9]+ {std::cout << "TOKEN::NUM_CONST_DEC" << std::endl;}

\'.\' {std::cout << "TOKEN::CHAR" << std::endl;}
\'\\[nrbtf]\' {std::cout << "TOKEN::CHAR" << std::endl;}
\'\\.\' {std::cout << "TOKEN::CHAR" << std::endl;}

\"(\\.|[^"\\])*\" {std::cout << "TOKEN::STRING" << std::endl;}

\$.*$ {std::cout << "COMMENT" << std::endl;}

%%

int main()
{
  yylex();
}
