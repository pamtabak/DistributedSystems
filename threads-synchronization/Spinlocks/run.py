import subprocess
from subprocess import Popen, PIPE

n = ["100000000", "1000000000", "10000000000"]
k = ["1","2","3","4","5","6","7","8","9","10","15","20","30"]

for vectorSize in xrange(len(n)):
	for threads in xrange(len(k)):
		for i in xrange(0,10):
			# Build command through for loop in listArgs.
			# Details are omitted.
			cmd = ["./main.out", n[vectorSize], k[threads]]

			# Open/Create the output file
			outFile = open('output.txt', 'a+')

			result = subprocess.Popen(cmd, stdout=subprocess.PIPE)
			out = result.stdout.read()

			outFile.write(out)
			outFile.close()

		outFile = open('output.txt', 'a+')
		outFile.write("\n")
	outFile = open('output.txt', 'a+')
	outFile.write("\n\n")