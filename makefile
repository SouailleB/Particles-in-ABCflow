#PART THAT NEED TO BE MODIFIED: just type the name of the .cpp files after SOURCES=
SOURCES= point.cpp matrix.cpp quat.cpp rigid_body.cpp ode.cpp ABCflow.cpp model.cpp main.cpp
#END OF THE PART THAT NEED TO BE MODIFIED

# Name of the compiler
CXX=g++
# Arguments for the link edition step : all warnings & c++11 standart
LDFLAGS=-std=c++11 -Wall -Wextra
# Arguments for the compilation step : all warnings & c++11 standart
CPPFLAGS=-std=c++11 -Wall -Wextra -Wno-ignored-attributes
# Librairies : none
LDLIBS=

# List of the object fils (*.o), automaticaly generated
OBJETS=$(subst .cpp,.o,$(SOURCES))

all: build

build: $(OBJETS)
	$(CXX) $(LDFLAGS) -o run $(OBJETS) $(LDLIBS)

depend: .depend

.depend: $(SOURCES)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	rm $(OBJETS)

dist-clean: clean
	rm -f *~ .depend

include .depend
