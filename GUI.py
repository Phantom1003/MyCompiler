from tkinter import *
from tkinter import filedialog
from tkinter import messagebox
from PIL import Image
from SPL_parser import parser
from visualize import Viz
from ir_gen import Codegen


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
        global root
        root = parser.parse(src.get(0.0, END))


        ircodegen = Codegen(root)
        dst.insert(END, ircodegen.codegen())
        # raise SplTypeError(["mmm"])
    except SplTypeError as error:
        messagebox.showerror("Error", error.args)

def showtree():
    Viz(root).png()


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
tranbt.place(relx=0.47, rely=0.9)
treebt = Button(root, font=('Yu Gothic UI',15), text='Tree', command=showtree)
treebt.place(relx=0.74, rely=0.9)

root.mainloop()