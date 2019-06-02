from tkinter import *
from tkinter import filedialog
from tkinter import messagebox
from PIL import Image
from SPL_parser import parser
from visualize import Viz
from ir_gen import Codegen
from CompilerError import *
import CompilerError


class SplTypeError(BaseException):
    def __init__(self, args):
        self.args = args

def openfile():
    filename = filedialog.askopenfilename(title='Open File', filetypes=[('SPL', '*.spl'), ('All Files', '*')])
    print(filename)
    with open(filename, "r")  as f:
        src.delete(0.0, END)
        src.insert(END, f.read())

def printass():
    try:
        dst.delete(0.0, END)
        astroot = parser.parse(src.get(0.0, END))
        ircodegen = Codegen(astroot)
        dst.insert(END, ircodegen.codegen())
    except CompilerError.SplTypeError as error:
        messagebox.showerror("Error", error.args[0])

def showtree():
    astroot = parser.parse(src.get(0.0, END))
    Viz(astroot).png()

def showresult():
    def terminal_run(cmmd):
        # terminal_text.insert(END, cmmd + "\n")
        if (cmmd == ""):
            return
        if (cmmd == "clear"):
            terminal_text.delete(0.0, END)
            return
        if (cmmd == "exit"):
            terminal.destroy()
            return
        func_list = cmmd.split("(")
        func_name = func_list[0]
        #terminal_text.insert(END, func_name + " ")
        arg_string = func_list[1].split(")")
        arg_list = arg_string[0].split(",")
        arg_list_done = []
        for i in arg_list:
            for j in i.split(" "):
                if (j != ""):
                    arg_list_done += j
        func_arg = []
        for arg in arg_list_done:
            func_arg += [int(arg)]
            #terminal_text.insert(END, arg + " ")
        astroot = parser.parse(src.get(0.0, END))
        ircodegen = Codegen(astroot)
        ircodegen.codegen()
        result = ircodegen.crun(func_name, func_arg)
        terminal_text.insert(END, "Result of "+ cmmd + ": " + str(result) + " \n")


    def main_terminal(ev = None):
        src_command = terminal_text.get(0.0, END)
        command_list = src_command[:-2].split("\n")

        terminal_run(command_list[-1])




    terminal = Toplevel(root)
    terminal.geometry("700x400")
    terminal.title("Terminal")
    terminal_text = Text(terminal, font=('Yu Gothic UI',12))
    terminal_text.place(relx=0, rely=0, relheight=1, relwidth=1)
    terminal.bind('<Return>', main_terminal)



root= Tk()
root.title('MySPL Compiler')
root.geometry('1600x800')

src = Text(root, font=('Yu Gothic UI',12))
srclb = Label(root,text='Srouce code', font=('Yu Gothic UI',20))
srclb.place(relx=0.05, rely=0.015)
src.place(relx=0.05, rely=0.07, relheight=0.78, relwidth=0.4)

dst = Text(root, font=('Yu Gothic UI',12))
dstlb = Label(root,text='Assemble code', font=('Yu Gothic UI',20),)
dstlb.place(relx=0.55, rely=0.015)
dst.place(relx=0.55, rely=0.07, relheight=0.78, relwidth=0.4)

openbt = Button(root, font=('Yu Gothic UI',15), text='Open', command=openfile)
openbt.place(relx=0.2, rely=0.9)
tranbt = Button(root, font=('Yu Gothic UI',15), text='Translate', command=printass)
tranbt.place(relx=0.4, rely=0.9)
treebt = Button(root, font=('Yu Gothic UI',15), text='Tree', command=showtree)
treebt.place(relx=0.6, rely=0.9)
runbt = Button(root, font=('Yu Gothic UI',15), text='Run', command=showresult)
runbt.place(relx=0.8, rely=0.9)


root.mainloop()