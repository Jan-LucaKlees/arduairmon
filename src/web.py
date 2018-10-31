from flask import Flask, render_template

from models import Measurement


app = Flask("airmon", template_folder="./web/templates")

@app.route('/')
def index():
  q = Measurement.select()

  count = q.count()

  dates = []
  temperatures = []
  relative_humidities = []

  for measurement in q:
    dates.append( str( measurement.created_at ) )
    temperatures.append( measurement.temperature )
    relative_humidities.append( measurement.relative_humidity )

  return render_template('index.html', count = count, temps=temperatures, hums=relative_humidities, dates=dates )

