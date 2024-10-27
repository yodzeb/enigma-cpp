all:
	g++ -O3 -o e main.cpp
	#time ./e
profile:
	g++ -o e main.cpp -g -pg
	./e
	gprof e gmon.out  | less
