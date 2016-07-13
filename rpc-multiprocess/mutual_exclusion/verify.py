import re #regex

numberOfClients = 128;

with open("file.txt") as f:
    content = f.readlines()

def removeDuplicates(content):
	result = []
	for item in content:
		if item not in result:
			result.append(item)
	return result

def matchLines(result):
	ok = True
	for item in result:
		split = item.split(' = ')
		if (split[0] != "I`m client with process id"):
			return False
		number = split[1].strip()
		rule = re.compile(r'^-?[0-9]+$')
		if not rule.search(number):
			return False
	return ok

result = removeDuplicates(content)
if (len(result) != numberOfClients):
	print("False")
else:
	ok = matchLines(result)
	print(ok)