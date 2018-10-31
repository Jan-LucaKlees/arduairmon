#!/bin/sh

cd /airmon

# -u for unbuffered output so we can see pythong prints when running docker-compose up
python3 -u sense.py

