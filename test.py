import time
import serial

ser = serial.Serial(
 port='/dev/ttyUSB0',
 baudrate = 9600,
 parity=serial.PARITY_NONE,
 stopbits=serial.STOPBITS_ONE,
 bytesize=serial.EIGHTBITS,
 timeout=1
)
counter=0


while 1:
 commande="0.1.1.1.1."
 ser.write(commande)
 x=ser.readline()
 print (x)
 time.sleep(1)