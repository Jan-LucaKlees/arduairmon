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

  temp_1 = data["sensors"]["temp_1"]["value"]
  temp_2 = data["sensors"]["temp_2"]["value"]
  temp = ( temp_1 + temp_2 ) / 2

  hum_1 = data["sensors"]["rel_hum_1"]["value"]
  hum_2 = data["sensors"]["rel_hum_2"]["value"]
  hum = ( hum_1 + hum_2 ) / 2

  vcc = data["sensors"]["vcc"]["value"]

  new_measurement = Measurement(
    temperature = temp,
    relative_humidity = hum,
    vcc = vcc,
  )

  new_measurement.save( force_insert=True )
