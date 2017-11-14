import os
import subprocess
import time
from subprocess import Popen, PIPE

k = 128
y = 1
arrival = 1
# if arrival = 0: bulk arrival
# if arrival = 1: sequential arrival

def child():
	# Build command through for loop in listArgs.
	# Details are omitted.
	cmd = ["./client.out"]

	#Open/Create the output file
	outFile = open('output.txt', 'a+')

	result = subprocess.Popen(cmd, stdout=subprocess.PIPE)
	out = result.stdout.read()

	outFile.write(out)
	outFile.close()	

	os._exit(0)

for i in xrange(0,k):
	if (arrival == 1):
		time.sleep(y)
	newpid = os.fork()
	if newpid == 0:
		child()
		
	