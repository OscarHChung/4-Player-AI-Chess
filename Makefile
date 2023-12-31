CXX = g++ -std=c++20
CXXFLAGS = -Wall -g -MMD -I/opt/X11/include # use -MMD to generate dependencies
OBJECTS = main.o bishop.o empty.o game.o king.o knight.o pawn.o piece.o queen.o rook.o textdisplay.o player.o computer.o graphicsdisplay.o window.o # .o files depend upon .cc files with same names
DEPENDS = ${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=chess

# First target in the makefile is the default target.
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) -L/opt/X11/lib -lX11

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS)

-include ${DEPENDS}

.PHONY: clean 
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
