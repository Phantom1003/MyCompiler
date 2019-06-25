from SPL_parser import parser
from visualize import Viz
from ir_gen import Codegen
import os

TEST = """
program test;
const
    c_1 = 1;
var
    aa, x : integer;

    function test_for(var a : integer): integer;
    var
        sum : integer;
    begin
        sum := 0;
        for i := 0 to a do begin
            sum := sum + i;
        end;
        a:= 1;
        test_for := sum;
    end;

begin
    aa := 100;
    x := test_for(aa);
    writeln(x);
    write(aa);
end.

"""
def run_in_CLI(string):
    root = parser.parse(string)
    # v = Viz(root)
    # v.png()
    c = Codegen(root)
    c.codegen()
    c.crun(root.children[0].children[1].name, [])


readcode = open("code.txt", 'r')
code = readcode.read()
run_in_CLI(code)
readcode.close()
os.remove("code.txt")
