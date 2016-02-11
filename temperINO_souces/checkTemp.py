# checks temp from /dev/ttyACM0 every 30s,
# writes temp to file so it can be displayed in web app.
# It is not elegant at all. I know.
# Possibly it will be replaced by an on demand connection to serial via php

import serial
Ino = serial.Serial('/dev/ttyACM0', 9600, timeout=30)

Ino.write('3')
f=open("./thermo/data/curTx",'w')
f.write('3')
f.close

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
