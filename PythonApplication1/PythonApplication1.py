from time import sleep
import serial
import numpy



ser = serial.Serial('COM3', 115200) # Establish the connection on a specific port
counter = 32 # Below 32 everything in ASCII is gibberish
while True:
     counter = counter + 1
     ser.write(chr(counter).encode('ascii')) # Convert the decimal number to ASCII then send it to the Arduino
     print (ser.readline().decode('ascii')) # Read the newest output from the Arduino
     sleep(0.1) # Delay for one tenth of a second
     if counter == 127:
        counter = 32
