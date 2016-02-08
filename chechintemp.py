import serial
Ino = serial.Serial('/dev/ttyACM0', 9600, timeout=5)

while 1 :
        try:
                curTemp=Ino.readline()
                print curTemp
                f=open("thermo/data/curTemp",'w')
                f.write(curTemp)
                f.close
        except:
                pass
