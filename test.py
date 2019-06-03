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
type
    b = record aa, bb: integer; cc : real; end;
var
    sum : integer;
begin
   b.aa := a;
   f:=b.aa;
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
