# Design_project_NYIT

In this project we developed a gesture recognition system using a supervised K-Nearest Neighbors algorithm to classify different gestures. This was done through observing the change in resonant frequency of a human's hand analyzed from inductive coil sensors through a microcontroller of an Arduino in the effort to move a vehicle (RC Car) move in specific directions. This provided a fulfilling experience with my team of Kevin Gay, Aritra Apon, Dave Persaud, and Yousef Ahmed with guidance by Reza K. Amineh

Arduino Program: ‘ldc_extraction.ino’
	This code is written to extract the data from the LDC1614 data acquisition board from the single channel used in our project (channel 2). This code initializes several parameters within the LDC such that the team did not have to continuously rely on the TI GUI, i.e. disabled the MSP multiplexer, set driver currents, and also deglitch filters. Finally, this code implements a multiplexer switching mechanism. The multiplexer channels are selected in a fixed series, each being activated by a specific digital pin configuration of the arduino. NOTE: do not have the serial monitor of the arduino IDE open while viewing the data streaming of the TI GUI because it will cause both to crash.

MATLAB Program: ‘ldc_extraction.mat’
	This code was used for data extraction to train the machine learning model. It reads 100 data points per run (this can be changed by increasing the size of the vector). The program also plots the data being read in real time. 
MATLAB Program: ‘live_gesture_recognition.mat’
	First, this program initiates the serial communication between the arduino and the MATLAB environment. Check to make sure when running the program that your arduino’s serial port is properly listed in this code. Next, it initiates the communication for the arduino mounted on the RC car along with its motor shield. NOTE: you must download the motor shield toolbox from Mathworks, it can simply be found by searching for toolboxes within the MATLAB environment. 
	After all of the serial communication is established, the code begins the live gesture recognition by first reading the serial data from the arduino, which is reading from the LDC. When this data is read, it is read into a tabular data structure because in the format which can be viewed on the team’s website, final presentation, and also the final report. The data is read in the column labeled ‘RawData’ and there is an empty column labeled ‘Gesture’. Then, after reading the data the model makes a prediction, or  classification in real time by contacting the trained machine learning  model and outputs that prediction as a string. Based on this predicted string, a series of if statements is used to send a command to the car’s four motors to perform a movement, or brake. 

Instructions
Run the ‘ldc_extraction.ino’ in the arduino IDE.
Run the ‘liveGestureRecognition.mat’ in MATLAB.
