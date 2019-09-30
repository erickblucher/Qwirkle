.default: all

all: qwirkle

clean:
	rm -rf qwirkle *.o *.dSYM

qwirkle: Tile.o Node.o LinkedList.o Util.o Grid.o Validator.o GameEngine.o GameMenu.o qwirkle.o GridTest.o LinkedList_test.o Validator_test.o TestAll.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: src/%.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^

%.o: test/%.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
