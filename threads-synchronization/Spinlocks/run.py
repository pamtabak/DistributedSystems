import subprocess
from subprocess import Popen, PIPE

while True:
	# Build command through for loop in listArgs.
	# Details are omitted.
	cmd = ["./main.out", "1000", "30"]

	# Open/Create the output file
	outFile = open('output.txt', 'a+')

	result = subprocess.Popen(cmd, stdout=subprocess.PIPE)
	out = result.stdout.read()

	outFile.write(out)
	outFile.close()