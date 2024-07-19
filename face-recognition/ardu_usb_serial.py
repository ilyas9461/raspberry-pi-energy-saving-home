import serial
import time

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)

while True:
    kmt =ser.readline() #ser.read_until('\r', size=None)
    
    #kmt =ser.read_until('.', size=None)  #çalışmadı
    
    str= kmt.decode('utf-8').rstrip()
    if len(str) > 0:
       # print(str)
        if str == "ACK":
            print(str)
            ser.write(b"TAMAM\n")
            
    ser.write(b"YAK\n")
    print("YAK")
    time.sleep(5)
