import threading
import serial
import time
from tkinter import *
from PIL import Image, ImageTk, ImageFile
import matplotlib.pyplot as plt
ImageFile.LOAD_TRUNCATED_IMAGES = True

GET_DATA = '0'
EMPTY = '1'
RESTORE = '2'

UPDATE_TIME = 500	#milliseconds
SAVE_TIME = 3		#seconds

history_img_path = "./src/pc/history.png"
history_text_path = "./src/pc/history.txt"

#---------------Serial_communication---------------

arduino = serial.Serial(port='COM4', baudrate=9600, timeout=.1)

def serialSendIntruction(x):
	arduino.write(bytes(x, 'utf-8'))

def serialGetResult():
	time.sleep(0.05) 
	data = arduino.readline() 
	return str(data)

#-------------GUI_initializzaiton------------------

root = Tk()
root.title("Operator Dashboard")
root.geometry('1000x700+450+200')
root.lift()

root.columnconfigure(0, weight=1)
root.columnconfigure(1, weight=1)
root.rowconfigure(0, weight=1)
root.rowconfigure(1, weight=2)
root.rowconfigure(2, weight=3)
root.rowconfigure(2, weight=2)
root.resizable(False, False)


titleLabel = Label(text='OPERATOR DASHBOARD', font=(30))
titleLabel.grid(column=0, row=0, columnspan=2)

fillingLabel = Label(font=(50))
temperatureLabel = Label(font=(50))
fillingLabel.grid(column=0, row=1)
temperatureLabel.grid(column=1, row=1)

filling = 0.0
temperature = 25.0

timeArray = []
fillArray = []
tempArray = []

#-----------Data_management-------------

# prints current values of sensors
def printData():
	fillingStr = "Filling: " + str(filling) + "%"
	tempStr = "Temperature: " + str(temperature) + "°"
	
	fillingLabel.config(text=fillingStr)
	temperatureLabel.config(text=tempStr)
	if filling >= 100.0:
		fillingLabel.config(fg='red')
	else:
		fillingLabel.config(fg='black')
	if temperature >= 50.0:
		temperatureLabel.config(fg='red')
	else:
		temperatureLabel.config(fg='black')

image_label = Label(root)
image_label.grid(column=0, row=2, columnspan=2)	

# prints current history graph
def updateImage():
	global img
	try:
		photo = Image.open(history_img_path)
		img = ImageTk.PhotoImage(photo)
		photo.close()
	except IOError:
		pass	
	image_label.config(image=img)

# unpack singularly filling and temperature values
def unpackData(values):
	global filling
	global temperature
	rawValues = values.replace("'", "").replace("b", "").replace("\\r\\n", "").split(" ")
	floatValues = [float(x) for x in rawValues if x.isnumeric() or x.replace('.', '', 1).isnumeric()]
	
	if len(floatValues) == 2:
		filling = floatValues[0]
		temperature = floatValues[1]

# calls periodically the functions to print values and graph
def updateData():
	serialSendIntruction(GET_DATA)
	values = serialGetResult()
	unpackData(values)
	printData()
	updateImage()
	root.after(UPDATE_TIME, updateData)

#------------Buttons_management------------

# function to perform when pressed 'empty' button
def empty():
	serialSendIntruction(EMPTY)

# function to perform when pressed 'restore' button
def restore():
	serialSendIntruction(RESTORE)

emptyButton = Button(text='Empty', command=empty, background='lightGray')
emptyButton.grid(column=0, row=3)

restoreButton = Button(text='Restore', command=restore, background='lightGray')
restoreButton.grid(column=1, row=3)

#-----------History_management-------------

# generate a graph with history data and saves on a png
def generateGraph():
	try:
		maxFill = [100]*len(fillArray)
		maxTemp = [50]*len(tempArray)

		plt.title("History")
		plt.plot(timeArray, fillArray, 'c', label='Filling %')
		plt.plot(timeArray, tempArray, 'r', label='Temperature')
		plt.plot(timeArray, maxFill, 'paleturquoise', label='Max Filling', linewidth=0.5)
		plt.plot(timeArray, maxTemp, 'salmon', label='Max Temperature', linewidth=0.5)
		plt.ylim(ymin=0, ymax=110)
		plt.xlabel("minutes")
		plt.legend(loc="upper left")
		plt.locator_params(axis='x', nbins=10)
		plt.savefig(history_img_path)
		plt.close()

	except MemoryError:
		pass
	

# history data loop, which saves data
def saveData():
	t0 = time.time()
	while(True):
		ts = time.time()
		timeArray.insert(0, float("{:.2f}".format((time.time() - t0)/60)))
		fillArray.insert(0, filling)
		tempArray.insert(0, temperature)
		if len(timeArray) > 200:
			timeArray.pop(200)
			fillArray.pop(200)
			tempArray.pop(200)
		generateGraph()
		while(time.time() - ts < SAVE_TIME):
			pass
		
#-------------Main_code-----------------

saveDataThread = threading.Thread(target=saveData)
saveDataThread.daemon = True
saveDataThread.start()

updateData()

root.mainloop()