from SPL_parser import parser
from visualize import Viz
from ir_gen import Codegen


TEST = """
program test;
const
    y = 1;
var
	x : integer;
function f(a:integer) : integer;
var
    sum : integer;
begin
    sum := 0;
    if a = 0 then f := 1
    else begin
        if a = 1 then f:= 2
        else begin
            f := 3;
        end;
        f := 4;
    end;
    f:= 5;
end
;
begin
    x := f(0);
end
.
"""

root = parser.parse(TEST)
# v = Viz(root)
# v.png()

c = Codegen(root)
c._codegen(root)
