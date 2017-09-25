

def writeStopWord(ruta):

	file = open(ruta,"rb")

	stringsLines = file.readlines()
	file.close()

	newfile = open("result","w")


	newfile.write("(define ListaStopWords '(") 

	for line in stringsLines:
		line=line.strip()

		newfile.write('"'+line+'"')
		newfile.write(" ")
			

	newfile.write("))")

	newfile.close()

writeStopWord("StopWords.txt")
