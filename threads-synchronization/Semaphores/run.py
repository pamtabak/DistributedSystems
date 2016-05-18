import subprocess
from subprocess import Popen, PIPE

n = ["2", "4", "8", "16", "32"]
k = [("1","1"), ("2","2"), ("5","5"), ("10","10"), ("2","10"), ("10","2")]

for vectorSize in xrange(len(n)):
	for threads in xrange(len(k)):
		for i in xrange(0,10):
			# Build command through for loop in listArgs.
			# Details are omitted.
			cmd = ["./main.out", k[threads][0], k[threads][1], n[vectorSize], "10000"]

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