import requests
from bs4 import BeautifulSoup
import time
import tkinter as tk

class Project(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)

        self.configure(background='black')
        self.title("Live Score")

        self.geometry("400x400")

        greeting = tk.Label(self, text="HELLO!! WELCOME TO THE CRICKET SCORE APP :)")
        greeting.pack()
        lbl = tk.Label(self, text="match number")
        lbl.pack()
        self.match_entry = tk.Entry(self)
        self.match_entry.pack()
        getButton = tk.Button(self, text='GET SCORE', command=self.getScore, fg = 'green')
        getButton.pack()
        quitButton = tk.Button(self, text='QUIT', command=self.quit, fg ='red')
        quitButton.pack()
        self.result = tk.Text(self)
        self.result.pack()

        self.matchUrl = None # initial value

    def update_result(self, data):
        self.result.delete(0.0, tk.END) # clear all the old data out
        self.result.insert(0.0, data) # put new data in

    def get_data(self):

        r = requests.get(self.matchUrl)
        soup = BeautifulSoup(r.text, 'lxml')
        score = soup.findAll('title')
        try:
            r.raise_for_status()
        except Exception as exc:
            self.update_result('Connection Failure. Try again!')
            self.matchUrl = None
            return
        self.update_result(time.strftime("updated: %H:%M:%S\n\n") + score[0].text)
        self.after(20000, self.get_data) # repeat this in 20,000 milliseconds

    def getScore(self):
        try:
            userInput = int(self.match_entry.get())
        except ValueError:
            self.update_result('Invalid input. Must enter a number. Try Again!')
            return # quit this function

        if userInput < 0 or userInput > 30:
            self.update_result('Invalid input. Number must be between 1 and 30. Try Again!')
            return

        url = "http://static.cricinfo.com/rss/livescores.xml"
        r = requests.get(url)
        soup = BeautifulSoup(r.text, 'lxml')

        i = 1
        for item in soup.findAll('item'):
            print(str(i) + '. ' + item.find('description').text)
            i = i + 1

        links = []
        for link in soup.findAll('item'):
            links.append(link.find('guid').text)

        if self.matchUrl is None:
            # we need to start the loop
            self.after(10, self.get_data)
        self.matchUrl = links[userInput - 1]

def main():
    app = Project()
    app.mainloop()