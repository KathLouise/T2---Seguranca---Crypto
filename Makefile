CFLAGS += -g

all: wordlist brutexor
	rm -rf *.o

wordlist:
	gcc wordlist.c -o wordlist -lm $?
brutexor: 
	gcc brutexor.c -o brutexor -lssl -lcrypto -lm $?
clean:
	rm -rf *.o

faxina: clean 
	rm -rf teste 
