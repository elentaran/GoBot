EXEC=AleaBot
CC=g++
SRC=$(wildcard *.cpp)
HD=$(wildcard *.h)
OBJ=$(SRC:.cpp=.o)

all: $(EXEC)


debug: clean
	$(MAKE) $(MAKEFILE) DEBUG="-g"

prof: clean
	$(MAKE) $(MAKEFILE) PROF="-pg"


opt: clean
	$(MAKE) $(MAKEFILE) OPT="-O3"

boost: 
	$(MAKE) $(MAKEFILE) BOOST_LIB="/usr/local/lib/libboost_program_options.a"



$(EXEC): $(OBJ)
	$(CC) $(OBJ) $(DEBUG) $(PROF) $(OPT) -o $(EXEC) $(BOOST_LIB)

%.o: %.cpp $(HD)
	$(CC) $(DEBUG) $(PROF) $(OPT) -c $< -o $@ 

clean:
	rm -f *.o
	rm -f *~
	rm -f $(EXEC)
