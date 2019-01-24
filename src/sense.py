import serial
import json

from models import Measurement


# open serial connection to our Arduino
ser = serial.Serial( '/dev/ttyUSB0', 9600)

# read values from serial connection and write them to our db
while 1 :
  line = ser.readline()
  data = json.loads( line.decode( "utf-8" ) )

  print( data )

  temp = data["sensors"]["temp"]["value"]

  hum = data["sensors"]["rel_hum"]["value"]

  # vcc = data["sensors"]["vcc"]["value"]

  new_measurement = Measurement(
    temperature = temp,
    relative_humidity = hum,
    # vcc = vcc,
  )

  new_measurement.save( force_insert=True )

