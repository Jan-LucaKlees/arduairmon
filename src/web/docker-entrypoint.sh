#!/bin/sh

cd /airmon

# -u for unbuffered output so we can see pythong prints when running docker-compose up
FLASK_APP=web.py FLASK_ENV=development python -m flask run --host=0.0.0.0

