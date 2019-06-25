import tkinter as tk
from tkinter import filedialog
from tkinter import messagebox
from SPL_parser import parser
from visualize import Viz
from ir_gen import Codegen
import CompilerError, os



def openfile():
    filename = filedialog.askopenfilename(title='Open File', filetypes=[('SPL', '*.spl'), ('All Files', '*')])
    print(filename)
    with open(filename, "r")  as f:
        src.delete(0.0, tk.END)
        src.insert(tk.END, f.read())

def test_print():
    f = open("code.txt", 'w')
    f.write(src.get(0.0, tk.END))
    f.close()

    f = open("output.txt", "w")
    f.close()
    os.system('python ./test.py > output.txt ')

    f = open("output.txt", "r")
    during = f.read()
    f.close()
    os.remove("output.txt")
    # os.remove("input.txt")
    return during
    # print(f)



def printass():
    try:
        dst.config(state=tk.NORMAL)
        dst.delete(0.0, tk.END)
        astroot = parser.parse(src.get(0.0, tk.END))
        ircodegen = Codegen(astroot)
        dst.insert(tk.END, ircodegen.codegen())
        dst.config(state=tk.DISABLED)

    except CompilerError.SplTypeError as error:
        messagebox.showerror("Type Error", error.args[0])
    except CompilerError.MultiDefinedError as error:
        messagebox.showerror("Conflict declaration Error", error.args[0])
    except CompilerError.NotDefinedError as error:
        messagebox.showerror("Implicit declaration Error", error.args[0])
    except CompilerError.OpError as error:
        messagebox.showerror("Operation Error", error.args[0])
    except CompilerError.ExpressionError as error:
        messagebox.showerror("Expression Error", error.args[0])
    except CompilerError.ParseError as error:
        messagebox.showerror("Expression Error", error.args[0])
    except CompilerError.LexError as error:
        messagebox.showerror("Expression Error", error.args[0])
    # except AttributeError as error:
    #     messagebox.showerror("Syntax Error", error.args[0])

def showtree():
    astroot = parser.parse(src.get(0.0, tk.END))
    Viz(astroot).png()

def showir():
    astroot = parser.parse(src.get(0.0, tk.END))
    code = Codegen(astroot)
    result = code.irshow()
    # result = str(result).replace('\\', '\\\\')
    return str(result)

def showresult():
    def terminal_run(cmmd):
        # terminal_text.insert(tk.END, cmmd + "\n")
        if (cmmd == ""):
            return
        if (cmmd == "clear"):
            terminal_text.delete(0.0, tk.END)
            terminal_text.insert(tk.END, "MySPL Compiler > ")
            return
        if (cmmd == "exit"):
            terminal.destroy()
            terminal_text.insert(tk.END, "MySPL Compiler > ")
            return
        if (cmmd == "translate"):
            printass()
            terminal_text.insert(tk.END, "MySPL Compiler > ")
            return
        if (cmmd == "open"):
            openfile()
            terminal_text.insert(tk.END, "MySPL Compiler > ")
            return
        if (cmmd == "tree"):
            showtree()
            terminal_text.insert(tk.END, "MySPL Compiler > ")
            return
        if (cmmd == "ir"):
            ir = showir()
            terminal_text.insert(tk.END, ir + '\n' + "MySPL Compiler > ")
            return
        if (cmmd == "main"):
            res = test_print()
            terminal_text.insert(tk.END, "During RUNING... \n" + res + "MySPL Compiler > ")
            return
        if (cmmd == "info"):
            information =   '2019 SPRING&SUMMER  Compiler Principle Project:    Mini SPL  Compiler \n' \
                            'Surpport: \n' \
	                        '>> Pascal Language, generate assembly code \n' \
                            '>> Visual syntax tree \n' \
                            '>> Interactive command line Terminal \n' \
                            '>> Load code from file \n' \
                            '>> Executable function \n' \
                            'Author: Xu Jinyan/Xiang Liming/Peng Dishuo © ZJU'

            terminal_text.insert(tk.END, information + " \nMySPL Compiler > ")
            return
        func_list = cmmd.split("(")
        func_name = func_list[0]
        #terminal_text.insert(tk.END, func_name + " ")
        arg_string = func_list[1].split(")")
        arg_list = arg_string[0].split(",")
        arg_list_done = []
        for i in arg_list:
             for j in i.split(" "):
                 if (j != ""):
                     arg_list_done += [j]

        func_arg = []
        for arg in arg_list_done:
            func_arg += [int(arg)]
            #terminal_text.insert(tk.END, arg + " ")
        astroot = parser.parse(src.get(0.0, tk.END))
        ircodegen = Codegen(astroot)
        ircodegen.codegen()

        result = ircodegen.crun(func_name, func_arg)
        terminal_text.insert(tk.END, "Result of "+ cmmd + ": " + str(result) + " \nMySPL Compiler > ")

    def main_terminal(ev = None):
        src_command = terminal_text.get(0.0, tk.END)
        command_list = src_command[:-2].split("\n")
        terminal_run(command_list[-1][17:])

    terminal = tk.Toplevel(root)
    terminal.geometry("700x400")
    terminal.title("Terminal")
    terminal_text = tk.Text(terminal, font=('Yu Gothic UI',12))
    terminal_text.place(relx=0, rely=0, relheight=1, relwidth=1)
    terminal_text.insert(tk.END, "MySPL Compiler > ")
    terminal.bind('<Return>', main_terminal)



root= tk.Tk()
root.title('MySPL Compiler')
# root.geometry('1600x800')
w = root.winfo_screenwidth()
h = root.winfo_screenheight()
root.geometry("%dx%d" %(w/6*5, h/6*5))


src = tk.Text(root, font=('Yu Gothic UI',12))
srclb = tk.Label(root,text='Srouce code', font=('Yu Gothic UI',20))
srclb.place(relx=0.05, rely=0.015)
src.place(relx=0.05, rely=0.07, relheight=0.78, relwidth=0.4)

dst = tk.Text(root, font=('Yu Gothic UI',12))
dstlb = tk.Label(root,text='Assemble code', font=('Yu Gothic UI',20),)
dstlb.place(relx=0.55, rely=0.015)
dst.place(relx=0.55, rely=0.07, relheight=0.78, relwidth=0.4)

openbt = tk.Button(root, font=('Yu Gothic UI',15), text='Open', command=openfile)
openbt.place(relx=0.15, rely=0.9)
tranbt = tk.Button(root, font=('Yu Gothic UI',15), text='Translate', command=printass)
tranbt.place(relx=0.35, rely=0.9)
treebt = tk.Button(root, font=('Yu Gothic UI',15), text='Tree', command=showtree)
treebt.place(relx=0.55, rely=0.9)
runbt = tk.Button(root, font=('Yu Gothic UI',15), text='Terminal', command=showresult)
runbt.place(relx=0.75, rely=0.9)

root.resizable(width=False, height=False)
auth = tk.Label(root,text='Author: Xiang Liming/Xu Jinyan/Peng Dishuo © ZJU Compiler Principle 2019 SPRING&SUMMER', font=('Yu Gothic UI',10))
auth.place(relx=0, rely=0.97)
dst.config(state=tk.DISABLED)

root.mainloop()