import threading
import serial
import time
from tkinter import *
from PIL import Image, ImageTk
import matplotlib.pyplot as plt
import numpy as np

# arduino = serial.Serial(port='COM4', baudrate=9600, timeout=.1)

UPDATE_TIME = 1000
SAVE_TIME = 6

#-------------GUI_initializzaiton------------------

root = Tk()
root.title("Operator Dashboard")
root.geometry('1000x700+450+200')
root.lift()

root.columnconfigure(0, weight=1)
root.columnconfigure(1, weight=1)
root.rowconfigure(0, weight=1)
root.rowconfigure(1, weight=5)
root.rowconfigure(2, weight=1)
root.resizable(False, False)

# clears history file
f = open('./src/pc/history.txt', 'w')
f.close()


fillingLabel = Label()
temperatureLabel = Label()
fillingLabel.grid(column=0, row=0)
temperatureLabel.grid(column=1, row=0)

filling = 55.5
temp = 25.6

#-----------Data_management-------------

# prints current values of sensors
def printData():
	fillingStr = "Filling: " + str(filling) + "%"
	tempStr = "Temperature: " + str(temp) + "°"
	
	fillingLabel.config(text=fillingStr)
	temperatureLabel.config(text=tempStr)

image_label = Label(root)
image_label.grid(column=0, row=1, columnspan=2)	

# prints current history graph
def updateImage():
	global img
	img = ImageTk.PhotoImage(Image.open("./src/pc/history.png"))
	image_label.config(image=img)

# calls periodically the functions to print values and graph
def updateData():
	printData()
	updateImage()
	root.after(UPDATE_TIME, updateData)

#------------Buttons_management------------

# function to perform when pressed 'empty' button
def empty():
	print('EMPTY')

# function to perform when pressed 'restore' button
def restore():
	print('RESTORE')

emptyButton = Button(text='Empty', command=empty, background='lightGray')
emptyButton.grid(column=0, row=2)

restoreButton = Button(text='Restore', command=restore, background='lightGray')
restoreButton.grid(column=1, row=2)

#-----------History_management-------------

# saves history data on file
def saveHistory(data):
	f = open('./src/pc/history.txt', 'a')
	f.write(data)
	f.close()

# reads history data from file
def readHistory():
	timeA = list()
	fillA = list()
	tempA = list()
	
	f = open('./src/pc/history.txt', 'r')
	tmp = f.read()
	f.close()
	tmps = tmp.split(" ")
	npTmp = np.array(tmps)
	for i in range(npTmp.size):
		if i == npTmp.size - 1:
			pass
		elif i % 4 == 0:
			timeA.append(float(npTmp[i]))
		elif i % 4 == 1:
			fillA.append(float(npTmp[i]))
		elif i % 4 == 2:
			tempA.append(float(npTmp[i]))
		elif i % 4 == 3:
			pass
	return timeA, fillA, tempA 

# generate a graph with history data and saves on a png
def generateGraph(time, fill, temp):
	plt.title("History")
	plt.plot(time, fill, 'b', label='Filling %')
	plt.plot(time, temp, 'r', label='Temperature')
	plt.ylim(ymin=0)
	plt.legend(loc="upper left")
	plt.savefig('src/pc/history.png')
	plt.close()
	
# history data loop, which saves data
def saveData():
	t0 = time.time()
	while(True):
		ts = time.time()
		# global filling
		# global temp
		string = str("{:.2f}".format((time.time() - t0)/60)) + " " + str(filling) + " " + str(temp) + " \n "
		saveHistory(string)
		timeA, fillA, tempA = readHistory()
		generateGraph(timeA, fillA, tempA)
		while(time.time() - ts < SAVE_TIME):
			pass
		# filling = filling + 0.5
		# temp = temp + 0.5

#-------------Main_code-----------------

saveDataThread = threading.Thread(target=saveData)
saveDataThread.daemon = True
saveDataThread.start()

updateData()

root.mainloop()