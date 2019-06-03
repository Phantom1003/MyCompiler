from SPL_parser import parser
from visualize import Viz
from ir_gen import Codegen


TEST = """
program test;
const
    y = 1;
var
	a : integer;

function f(a:integer) : integer;
var
    b : array [1..5] of integer;
    sum : integer;
begin
case a of
5 : a := 1;
6 : a := 2;
9 : a := 3;
end;
b[1] := 1;
b[2] := 2;
b[3] := 3;
b[4] := 4;
b[5] := 5;
f:= b[a];
end
;
begin
f(5);
end
.

"""

root = parser.parse(TEST)
# v = Viz(root)
# v.png()

c = Codegen(root)
c.codegen()
