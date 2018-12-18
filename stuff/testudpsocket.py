#!/usr/bin/python
 
# Demo server to open port 8888
# Modified from Python tutorial docs
import socket
 
HOST = '127.0.0.1'       # Hostname to bind
PORT = 3999              # Open non-privileged port 8888 
 
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind((HOST, PORT))
s.listen(1)
conn, addr = s.accept()
print 'Connected by', addr
while 1:
    data = conn.recv(1024)
    if not data: break
    conn.send(data)
conn.close()
