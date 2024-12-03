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

UPDATE_TIME = 1000	#milliseconds
SAVE_TIME = 3		#seconds

FULL_ALLARM = 1.0
TEMPERATURE_ALLARM = 2.0
TEMPERATURE__AND_FULL_ALLARM = 3.0


history_img_path = "./src/pc/history.png"
history_text_path = "./src/pc/history.txt"

# creates image file if not exists
file =  open(history_img_path, "w")
file.close()

#---------------Serial_communication---------------

arduino = serial.Serial(port='COM4', baudrate=9600, timeout=.1)

# writes in the serial line bytes 'x'
def serialSendIntruction(x):
	arduino.write(bytes(x, 'utf-8'))

# reads a line from the serial line
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

flag = 0.0
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
	if flag == FULL_ALLARM or flag == TEMPERATURE__AND_FULL_ALLARM or filling >= 100.0:
		fillingLabel.config(fg='red')
	else:
		fillingLabel.config(fg='black')
	if flag == TEMPERATURE_ALLARM or flag == TEMPERATURE__AND_FULL_ALLARM or temperature >= 50.0:
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
		image_label.config(image=img)
	except IOError:
		pass	

# unpack singularly filling and temperature values
def unpackData(values):
	global flag
	global filling
	global temperature
	rawValues = values.replace("'", "").replace("b", "").replace("\\r\\n", "").split(" ")
	floatValues = [float(x) for x in rawValues if x.isnumeric() or x.replace('.', '', 1).isnumeric()]
	
	if len(floatValues) == 3:
		flag = floatValues[0]
		filling = floatValues[1]
		temperature = floatValues[2]

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
		plt.ylim(ymin=0)
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
