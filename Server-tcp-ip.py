import socket
import sys
import datetime
import time
from time import sleep


HOST = '192.168.16.193' 
PORT = 1100

time.sleep(1)

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('# Socket created')
#s.connect((HOST, PORT))
try:
    s.bind((HOST, PORT))
except socket.error as msg:
    print('# Bind failed. ')
    sys.exit()

print('# Socket bind complete')

# Start listening on socket
s.listen(10)
print('# Socket now listening')



# Receive data from client

while True:     
    # Wait for client
    conn, addr = s.accept()
    print('# Connected to Entry Cam ' + addr[0] + ':' + str(addr[1]))
    
    data = conn.recv(2048)
    line = data.decode('UTF-8')    # convert to string (Python 3 only)
    line = line.replace("\n","")   # remove newline character
    sleep(0.1)
    if line != '':
        print( line + " " + str(datetime.datetime.now()))
        
    
s.close()
