#PARTIE A MODIFIER : Liste des fichiers .cpp (et uniquement les .cpp) a compiler
SOURCES= point.cpp matrix.cpp quat.cpp rigid_body.cpp ode.cpp ABCflow.cpp model.cpp main.cpp
#FIN DE LA PARTIE A MODIFIER

# Nom du compilateur
CXX=g++
# Arguments pour l'etape d'édition de liens : all warnings & c++11 standart
LDFLAGS=-std=c++11 -Wall -Wextra
# Arguments pour l'etape de compilation : all warnings & c++11 standart
CPPFLAGS=-std=c++11 -Wall -Wextra -Wno-ignored-attributes
# Librairies : none
LDLIBS=

# Liste des fichiers objet (*.o), générée automagiquement
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
