import subprocess
import time
from subprocess import Popen, PIPE

k = 1
y = 1
arrival = 1
# if arrival = 0: bulk arrival
# if arrival = 1: sequential arrival

for i in xrange(0,k):
	# Build command through for loop in listArgs.
	# Details are omitted.
	cmd = ["./client.out"]
	if (arrival == 1):
		time.sleep(y)

	#Open/Create the output file
	outFile = open('output.txt', 'a+')

	result = subprocess.Popen(cmd, stdout=subprocess.PIPE)
	out = result.stdout.read()

	outFile.write(out)
	outFile.close()