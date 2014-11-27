CCFLAGS = -I /usr/include $(INCLUDEDIRS) -std=c++11
LIBDIR = -L /usr/lib
INCLUDEDIRS = -I ../include/
OBJDIR = ../obj/
LNFLAGS = -lGL -lGLU -lGLEW -lglut -lm -Wno-write-strings
OBJECTS = main.o GLDonut.o
OBJS = $(addprefix $(OBJDIR), $(OBJECTS))
EXECUTALBE = ../bin/a3

$(EXECUTALBE): $(OBJS)
	g++ $(LIBDIR) -o $@ $^ $(LNFLAGS)
	
$(OBJDIR)%.o : %.cc
	g++ -c -o $@ $< $(CCFLAGS)

clean:
	rm -f ../include/*~ ../include/*% ../include/*# ../include/.#*
	rm -f ../src/*~ ../src/*% ../src/*# ../src/.#*
	rm -f ../obj/*.o

clean-all: clean
	rm -f $(EXECUTALBE)
