EXEC=GoBit
CC=g++
SRC=$(wildcard *.cpp)
HD=$(wildcard *.h)
OBJ=$(SRC:.cpp=.o)
LIBRARIES=-lpthread

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
	$(CC) $(OBJ) $(DEBUG) $(PROF) -o $(EXEC) $(BOOST_LIB) $(LIBRARIES) 

%.o: %.cpp $(HD)
	$(CC) $(DEBUG) $(PROF) -c $< -o $@ 


clean:
	rm -f *.o
	rm -f *~
	rm -f $(EXEC)
