from datetime import datetime
from peewee import *
import os

from .wait import wait_for_database_connection


db_name = os.environ['DB_NAME']
db_username = os.environ['DB_USERNAME']
db_password = os.environ['DB_PASSWORD']

# defining our database
db = PostgresqlDatabase(db_name, user=db_username, password=db_password, host='db')


class Measurement(Model):
  created_at = DateTimeField(default=datetime.now, unique=True, primary_key=True)

  temperature = FloatField(null=True)
  relative_humidity = FloatField(null=True)
  air_pressure = FloatField(null=True)
  co2 = FloatField(null=True)
  vcc = FloatField(null=True)

  class Meta:
    database = db


wait_for_database_connection( db )

db.create_tables(models=[Measurement], safe=True)
