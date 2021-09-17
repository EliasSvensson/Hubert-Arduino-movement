import serial
import time

arduino = serial.Serial(port='/dev/ttyACM0', baudrate=57600, timeout=.1)
time.sleep(2)
while True:
  arduino.write(1)
