from flask import Flask, request, render_template, jsonify
from datetime import datetime

from models import Measurement


DATE_FORMAT_JS = 'YYYY-MM-DD HH:mm:ss.SSSSSS'
DATE_FORMAT_PY = '%Y-%m-%d %H:%M:%S.%f'

app = Flask("airmon", template_folder="./web/templates")

@app.route('/')
def index():
  q = Measurement.select()

  raw_data = format_query( q )

  return render_template('index.html', raw_data = raw_data, DATE_FORMAT = DATE_FORMAT_JS )

@app.route('/json')
def json( ):
  from_date = request.args.get('from')
  to_date = request.args.get('to')

  q = Measurement.select()

  if from_date:
    from_date = datetime.strptime( request.args.get('from'), DATE_FORMAT_PY )
    q = q.where( Measurement.created_at > from_date )

  if to_date:
    to_date = datetime.strptime( request.args.get('to'), DATE_FORMAT_PY )
    q = q.where( Measurement.created_at < to_date )

  raw_data = format_query( q )

  return jsonify( raw_data )

def format_query( query ):
  raw_data = {
    'date': [],
    'temperature': [],
    'humidity': [],
    'vcc': []
  }

  for measurement in query:
    raw_data['date'].append( str( measurement.created_at ) )
    raw_data['temperature'].append( measurement.temperature )
    raw_data['humidity'].append( measurement.relative_humidity )
    raw_data['vcc'].append( measurement.vcc )

  return raw_data

