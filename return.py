# _*_ coding:utf-8_*_
from tkinter import *

def submit(ev = None):
   p.set(u.get())

root = Tk()
root.title("测试")
frame = Frame(root)
frame.pack(padx=8, pady=8, ipadx=4)
lab1 = Label(frame, text="获取:")
lab1.grid(row=0, column=0, padx=5, pady=5, sticky=W)
#绑定对象到Entry
u = StringVar()
ent1 = Entry(frame, textvariable=u)
ent1.grid(row=0, column=1, sticky='ew', columnspan=2)
lab2 = Label(frame, text="显示:")
lab2.grid(row=1, column=0, padx=5, pady=5, sticky=W)
p = StringVar()
ent2 = Entry(frame, textvariable=p)
ent2.grid(row=1, column=1, sticky='ew', columnspan=2)
button = Button(frame, text="输入", command=submit, default='active')
button.grid(row=2, column=1)
lab3 = Label(frame, text="")
lab3.grid(row=2, column=0, sticky=W)
button2 = Button(frame, text="退出", command=quit)
button2.grid(row=2, column=2, padx=5, pady=5)
#以下代码居中显示窗口
root.update_idletasks()
x = (root.winfo_screenwidth() - root.winfo_reqwidth()) / 2
y = (root.winfo_screenheight() - root.winfo_reqheight()) / 2
root.geometry("+%d+%d" % (x, y))
#以下代码把回车绑定到对象Entry,这样输入完后按回车键就可以看到文字出现在另一个文本框中了。
ent1.bind("<Return>", submit) #注意这里是Return而不是Enter
#root.bind("<Return>", submit) #这句把回车绑定到窗口,无论光标在哪按回车会把文本复制

root.mainloop()

rt = Tk()
ent = Entry(rt)
ent.pack()
rt.mainloop()