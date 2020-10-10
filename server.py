import cherrypy, serial, time

arduino = serial.Serial(
    port='/dev/ttyUSB0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)


class Server(object):
    def decode(self, commande=None):
        if commande:
            arduino.write(commande.encode())
            return arduino.readline()

    decode.exposed = True


class Robot():
    def send(commande):
        ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
        ser.flush()

        ser.write(commande.encode())
        return ser.readline().rstrip()

    cherrypy.quickstart(Server(), config="/home/pi/r2d2/server.conf")
