from flask import Flask, render_template

from models import Measurement


app = Flask("airmon", template_folder="./web/templates")

@app.route('/')
def index():
  q = Measurement.select()

  raw_data = {
    'date': [],
    'temperature': [],
    'humidity': [],
    'vcc': []
  }

  for measurement in q:
    raw_data['date'].append( str( measurement.created_at ) )
    raw_data['temperature'].append( measurement.temperature )
    raw_data['humidity'].append( measurement.relative_humidity )
    raw_data['vcc'].append( measurement.vcc )

  return render_template('index.html', raw_data = raw_data )

