EXEC=GoBit
CC=g++
SRC=$(wildcard *.cpp)
HD=$(wildcard *.h)
OBJ=$(SRC:.cpp=.o)
HEADERPATH=-Igtest
LIBPATH=-Lgtest
LIBRARIES=-lgtest -lpthread

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
	$(CC) $(OBJ) $(DEBUG) $(PROF) $(OPT) $(HEADERPATH) -o $(EXEC) $(BOOST_LIB) $(LIBPATH) $(LIBRARIES)

%.o: %.cpp $(HD)
	$(CC) $(DEBUG) $(PROF) $(OPT) $(HEADERPATH) -c $< -o $@ 


clean:
	rm -f *.o
	rm -f *~
	rm -f $(EXEC)
