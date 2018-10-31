import time

def wait_for_database_connection( db_handle ):
  while True:
    print( "Waiting for database..." )

    try:
      db_handle.connect()
      print( "Connected to database." )
      return
    except Exception as e:
      print ( e )
      time.sleep(1)
