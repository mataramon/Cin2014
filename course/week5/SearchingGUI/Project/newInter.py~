import subprocess
from Tkinter import *
from datetime import *
import tkFileDialog
import tkMessageBox
from PIL import *

class newInter:
	def __init__(self):
		self.main=Tk()
		self.main.title("Search&Suggest")
		self.ventana=Frame(self.main)
		self.ventana.grid(row=0, column=1)
		self.botmanage=Frame(self.main)
		self.botmanage.grid(row=1, column=0)
		self.titleS=Label(self.ventana, text="Search Text")
		self.titleS.grid(row=0, column=1)

		self.menu=Menu(self.main)
		self.main.config(menu=self.menu)

		self.about=Menu(self.menu, tearoff=0)
		self.menu.add_cascade(label="About", menu=self.about)
		self.about.add_command(label="About this Program", command=self.helpingDoc)

		self.exit=Menu(self.menu, tearoff=0)
		self.menu.add_cascade(label="Exit..", menu=self.exit)
		self.exit.add_command(label="Exit program", command=self.byebye)

		self.order=Label(self.ventana, text="Enter your search:")
		self.order.grid(row=1, column=0)

		self.inputtext=Entry(self.ventana, bg="GRAY", cursor="pencil")
		self.inputtext.config(width=15)
		self.inputtext.grid(row=1, column=1)

		self.search=Button(self.ventana, text="Search", width=5, height=1, command=self.look)
		self.search.grid(row=2, column=1)

	def look(self):
		research=self.inputtext.get()
		news="./Searching.exe "+research
		x=subprocess.check_output(news, shell=True)
		tkMessageBox.showinfo("Suggestion:", x)

	def byebye(self):
		self.main.destroy()

	def helpingDoc(self):
		tkMessageBox.showinfo("Information", "About project flow: \n\nThis program is intended to be used as an example of a seach engine with the autocomplete feature.\n\nIt uses a tree like structure to autocomplete a word using prefixes, presented using a simple GUI.\nAuthors:\n\nOctavio Gomez Navarro, Jorge Hernandez.\n\nFlow description:\n\n-User will be asked to input a word or part of it.\n\n-This word will then enter a process, pushing the search button, in which it will be analyzed character by character.\n\nFOR MORE INFORMATION FEEL FREE TO READ THE INCLUDED DOCUMENT 'READMEPLZ.TXT'")

	def run(self):
		self.main.mainloop()

app=newInter()
app.run()
