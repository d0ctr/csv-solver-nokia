
all: clear-exec-files compile clear-object-files run

compile:
	g++ csvparser.cpp main.cpp -o csvreader.exe
clear-object-files:
	rm -rf ?*.o
clear-exec-files:
	rm -rf ?*.exe
run:
	./csvreader.exe test.csv