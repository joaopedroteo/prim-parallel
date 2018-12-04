# Linux Makefile

APPLICATION = main.app
CXXFLAGS = -Wall -Wconversion -std=c++14 -O0 -g -pg
LDFLAGS =
LDLIBS =

CXX = mpicxx

OBJECTS = main.o Aresta.o Vertice.o LeArquivo.o Grafo.o Prim.o

# first, try to compile from this project
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

# second, try to compile from the core
%.o: structures/source/%.cpp structures/%.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

$(APPLICATION): $(OBJECTS) main.o
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f *.o *~ $(APPLICATION)
