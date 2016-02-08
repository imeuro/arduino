import serial
Ino = serial.Serial('/dev/ttyACM0', 9600, timeout=30)

while 1 :
        try:
                curTemp=Ino.readline()
                print curTemp
                if curTemp :
                        f=open("./thermo/data/curTemp",'w')
                        f.write(curTemp)
                        f.close
        except:
                pass
