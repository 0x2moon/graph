all: main

main: main.c
	@gcc -g main.c -o main

small: main csv/small.csv
	@./main csv/small.csv

big: main csv/big.csv
	@./main csv/big.csv

clean:
	rm -f main
	rm -f graph_analysis.txt
