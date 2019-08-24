all:
	g++ -std=c++11 $(f).cpp -o $(f) -Wall -Wno-sign-compare
run:
	./main strong