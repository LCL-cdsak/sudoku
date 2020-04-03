all:solve transform generate

solve:solve.cpp sudoku.h
	g++ -o solve solve.cpp

transform:transform.cpp sudoku.h
	g++ -o transform transform.cpp

generate:generate.cpp sudoku.h
	g++ -o generate generate.cpp

