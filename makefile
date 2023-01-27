all: gp

gp: gp.o sort.o adjacencyList.o dfs.o floyd.o utility.o sort.h adjacencyList.h defns.h dfs.h floyd.h utility.h
	g++ -g gp.o sort.o adjacencyList.o dfs.o floyd.o utility.o -o gp

gp.o: gp.cpp sort.h adjacencyList.h defns.h dfs.h floyd.h utility.h
	g++ -g gp.cpp -c -o gp.o

sort.o: sort.cpp defns.h
	g++ -g sort.cpp -c -o sort.o

adjacencyList.o: adjacencyList.cpp defns.h
	g++ -g adjacencyList.cpp -c -o adjacencyList.o

dfs.o: dfs.cpp defns.h
	g++ -g dfs.cpp -c -o dfs.o

floyd.o: floyd.cpp defns.h
	g++ -g floyd.cpp -c -o floyd.o

utility.o: utility.cpp
	g++ -g utility.cpp -c -o utility.o

clean:
	rm *.o gp -rf
