import subprocess

n = "100000000"
threads = ["1", "2", "4", "8", "16", "32", "64", "128"]
ops = ["0", "1", "2", "3"]
operations = ["exp", "log", "pow2", "sqrt"]

outFile = open('output.txt', 'a+')

for k in threads:
    outFile.write("K = " + k + "\n")
    op_code = -1
    for op in ops:
        s = 0
        sz = 0

        for i in xrange(0, 10):
            # Build command through for loop in listArgs.
            # Details are omitted.
            cmd = ["./client", n, k, op]

            result = subprocess.Popen(cmd, stdout=subprocess.PIPE)
            out = result.stdout.read()

            s += float(out.strip("\n"))
            sz += 1
        op_code += 1
        outFile.write(operations[op_code] + ": " + str(s/sz) + "\n")
    outFile.write("\n\n")
outFile.close()