#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

LBITS := $(shell getconf LONG_BIT)
OS = $(shell lsb_release -si)

INC = -I/usr/include/libxml2 -Ilib/SFML-1.6/include
CFLAGS = -pedantic-errors -pedantic -Wall -DSFML_DYNAMIC

ifeq ($(LBITS),64)
	ifeq ($(OS),Fedora)
		LIB = /usr/lib64/libGL.so lib/SFML-1.6/lib-64/libsfml-window.so lib/SFML-1.6/lib-64/libsfml-system.so lib/SFML-1.6/lib-64/libsfml-network.so lib/SFML-1.6/lib-64/libsfml-graphics.so lib/SFML-1.6/lib-64/libsfml-audio.so /usr/lib64/libxml2.so lib/SFML-1.6/lib-64/libsfml-audio.so.1.6 lib/SFML-1.6/lib-64/libsfml-graphics.so.1.6 lib/SFML-1.6/lib-64/libsfml-network.so.1.6 lib/SFML-1.6/lib-64/libsfml-system.so.1.6 lib/SFML-1.6/lib-64/libsfml-window.so.1.6 
		LIBDIR = -Llib/SFML-1.6/lib-64
	endif

	ifeq ($(OS),Ubuntu)
		LIB = /usr/lib/x86_64-linux-gnu/mesa/libGL.so lib/SFML-1.6/lib-64/libsfml-window.so lib/SFML-1.6/lib-64/libsfml-system.so lib/SFML-1.6/lib-64/libsfml-network.so lib/SFML-1.6/lib-64/libsfml-graphics.so lib/SFML-1.6/lib-64/libsfml-audio.so /usr/lib/x86_64-linux-gnu/libxml2.so lib/SFML-1.6/lib-64/libsfml-audio.so.1.6 lib/SFML-1.6/lib-64/libsfml-graphics.so.1.6 lib/SFML-1.6/lib-64/libsfml-network.so.1.6 lib/SFML-1.6/lib-64/libsfml-system.so.1.6 lib/SFML-1.6/lib-64/libsfml-window.so.1.6 
		LIBDIR = -Llib/SFML-1.6/lib-64
	endif
else
	ifeq ($(OS),Fedora)	
		LIB = /usr/lib/libGL.so lib/SFML-1.6/lib-32/libsfml-window.so lib/SFML-1.6/lib-32/libsfml-system.so lib/SFML-1.6/lib-32/libsfml-network.so lib/SFML-1.6/lib-32/libsfml-graphics.so lib/SFML-1.6/lib-32/libsfml-audio.so /usr/lib/libxml2.so lib/SFML-1.6/lib-32/libsfml-audio.so.1.6 lib/SFML-1.6/lib-32/libsfml-graphics.so.1.6 lib/SFML-1.6/lib-32/libsfml-network.so.1.6 lib/SFML-1.6/lib-32/libsfml-system.so.1.6 lib/SFML-1.6/lib-32/libsfml-window.so.1.6
		LIBDIR = -Llib/SFML-1.6/lib-32
	endif

	ifeq ($(OS),Ubuntu)
		LIB = /usr/lib/i386-linux-gnu/mesa/libGL.so lib/SFML-1.6/lib-32/libsfml-window.so lib/SFML-1.6/lib-32/libsfml-system.so lib/SFML-1.6/lib-32/libsfml-network.so lib/SFML-1.6/lib-32/libsfml-graphics.so lib/SFML-1.6/lib-32/libsfml-audio.so /usr/lib/i386-linux-gnu/libxml2.so lib/SFML-1.6/lib-32/libsfml-audio.so.1.6 lib/SFML-1.6/lib-32/libsfml-graphics.so.1.6 lib/SFML-1.6/lib-32/libsfml-network.so.1.6 lib/SFML-1.6/lib-32/libsfml-system.so.1.6 lib/SFML-1.6/lib-32/libsfml-window.so.1.6
		LIBDIR = -Llib/SFML-1.6/lib-32
	endif
endif

LDFLAGS = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
SRC = src

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -pedantic -Wall
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = bin/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/spaceInvaders

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -fexpensive-optimizations -O3 -O2 -O1 -O
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS)
OBJDIR_RELEASE = bin/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/spaceInvaders

OBJ_DEBUG = $(OBJDIR_DEBUG)/Vaisseau.cpp.o $(OBJDIR_DEBUG)/Render.cpp.o $(OBJDIR_DEBUG)/Rocket.cpp.o $(OBJDIR_DEBUG)/Sons.cpp.o $(OBJDIR_DEBUG)/Utils.cpp.o $(OBJDIR_DEBUG)/VaisseauBonus.cpp.o $(OBJDIR_DEBUG)/main.cpp.o $(OBJDIR_DEBUG)/xml_niveau.cpp.o $(OBJDIR_DEBUG)/Ennemis.cpp.o $(OBJDIR_DEBUG)/Explosion.cpp.o $(OBJDIR_DEBUG)/Fenetre_SFML.cpp.o $(OBJDIR_DEBUG)/GestionFont.cpp.o $(OBJDIR_DEBUG)/Collisions.cpp.o $(OBJDIR_DEBUG)/GestionSprite.cpp.o $(OBJDIR_DEBUG)/Menus.cpp.o $(OBJDIR_DEBUG)/Particules.cpp.o $(OBJDIR_DEBUG)/RecupDonneesXML.cpp.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/Vaisseau.cpp.o $(OBJDIR_RELEASE)/Render.cpp.o $(OBJDIR_RELEASE)/Rocket.cpp.o $(OBJDIR_RELEASE)/Sons.cpp.o $(OBJDIR_RELEASE)/Utils.cpp.o $(OBJDIR_RELEASE)/VaisseauBonus.cpp.o $(OBJDIR_RELEASE)/main.cpp.o $(OBJDIR_RELEASE)/xml_niveau.cpp.o $(OBJDIR_RELEASE)/Ennemis.cpp.o $(OBJDIR_RELEASE)/Explosion.cpp.o $(OBJDIR_RELEASE)/Fenetre_SFML.cpp.o $(OBJDIR_RELEASE)/GestionFont.cpp.o $(OBJDIR_RELEASE)/Collisions.cpp.o $(OBJDIR_RELEASE)/GestionSprite.cpp.o $(OBJDIR_RELEASE)/Menus.cpp.o $(OBJDIR_RELEASE)/Particules.cpp.o $(OBJDIR_RELEASE)/RecupDonneesXML.cpp.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/Vaisseau.cpp.o: $(SRC)/Vaisseau.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $(SRC)/Vaisseau.cpp -o $(OBJDIR_DEBUG)/Vaisseau.cpp.o

$(OBJDIR_DEBUG)/Render.cpp.o: $(SRC)/Render.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $(SRC)/Render.cpp -o $(OBJDIR_DEBUG)/Render.cpp.o

$(OBJDIR_DEBUG)/Rocket.cpp.o: $(SRC)/Rocket.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $(SRC)/Rocket.cpp -o $(OBJDIR_DEBUG)/Rocket.cpp.o

$(OBJDIR_DEBUG)/Sons.cpp.o: $(SRC)/Sons.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $(SRC)/Sons.cpp -o $(OBJDIR_DEBUG)/Sons.cpp.o

$(OBJDIR_DEBUG)/Utils.cpp.o: $(SRC)/Utils.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $(SRC)/Utils.cpp -o $(OBJDIR_DEBUG)/Utils.cpp.o

$(OBJDIR_DEBUG)/VaisseauBonus.cpp.o: $(SRC)/VaisseauBonus.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $(SRC)/VaisseauBonus.cpp -o $(OBJDIR_DEBUG)/VaisseauBonus.cpp.o

$(OBJDIR_DEBUG)/main.cpp.o: $(SRC)/main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $(SRC)/main.cpp -o $(OBJDIR_DEBUG)/main.cpp.o

$(OBJDIR_DEBUG)/xml_niveau.cpp.o: $(SRC)/xml_niveau.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $(SRC)/xml_niveau.cpp -o $(OBJDIR_DEBUG)/xml_niveau.cpp.o

$(OBJDIR_DEBUG)/Ennemis.cpp.o: $(SRC)/Ennemis.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $(SRC)/Ennemis.cpp -o $(OBJDIR_DEBUG)/Ennemis.cpp.o

$(OBJDIR_DEBUG)/Explosion.cpp.o: $(SRC)/Explosion.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $(SRC)/Explosion.cpp -o $(OBJDIR_DEBUG)/Explosion.cpp.o

$(OBJDIR_DEBUG)/Fenetre_SFML.cpp.o: $(SRC)/Fenetre_SFML.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $(SRC)/Fenetre_SFML.cpp -o $(OBJDIR_DEBUG)/Fenetre_SFML.cpp.o

$(OBJDIR_DEBUG)/GestionFont.cpp.o: $(SRC)/GestionFont.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $(SRC)/GestionFont.cpp -o $(OBJDIR_DEBUG)/GestionFont.cpp.o

$(OBJDIR_DEBUG)/Collisions.cpp.o: $(SRC)/Collisions.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $(SRC)/Collisions.cpp -o $(OBJDIR_DEBUG)/Collisions.cpp.o

$(OBJDIR_DEBUG)/GestionSprite.cpp.o: $(SRC)/GestionSprite.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $(SRC)/GestionSprite.cpp -o $(OBJDIR_DEBUG)/GestionSprite.cpp.o

$(OBJDIR_DEBUG)/Menus.cpp.o: $(SRC)/Menus.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $(SRC)/Menus.cpp -o $(OBJDIR_DEBUG)/Menus.cpp.o

$(OBJDIR_DEBUG)/Particules.cpp.o: $(SRC)/Particules.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $(SRC)/Particules.cpp -o $(OBJDIR_DEBUG)/Particules.cpp.o

$(OBJDIR_DEBUG)/RecupDonneesXML.cpp.o: $(SRC)/RecupDonneesXML.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $(SRC)/RecupDonneesXML.cpp -o $(OBJDIR_DEBUG)/RecupDonneesXML.cpp.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/Vaisseau.cpp.o: $(SRC)/Vaisseau.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $(SRC)/Vaisseau.cpp -o $(OBJDIR_RELEASE)/Vaisseau.cpp.o

$(OBJDIR_RELEASE)/Render.cpp.o: $(SRC)/Render.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $(SRC)/Render.cpp -o $(OBJDIR_RELEASE)/Render.cpp.o

$(OBJDIR_RELEASE)/Rocket.cpp.o: $(SRC)/Rocket.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $(SRC)/Rocket.cpp -o $(OBJDIR_RELEASE)/Rocket.cpp.o

$(OBJDIR_RELEASE)/Sons.cpp.o: $(SRC)/Sons.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $(SRC)/Sons.cpp -o $(OBJDIR_RELEASE)/Sons.cpp.o

$(OBJDIR_RELEASE)/Utils.cpp.o: $(SRC)/Utils.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $(SRC)/Utils.cpp -o $(OBJDIR_RELEASE)/Utils.cpp.o

$(OBJDIR_RELEASE)/VaisseauBonus.cpp.o: $(SRC)/VaisseauBonus.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $(SRC)/VaisseauBonus.cpp -o $(OBJDIR_RELEASE)/VaisseauBonus.cpp.o

$(OBJDIR_RELEASE)/main.cpp.o: $(SRC)/main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $(SRC)/main.cpp -o $(OBJDIR_RELEASE)/main.cpp.o

$(OBJDIR_RELEASE)/xml_niveau.cpp.o: $(SRC)/xml_niveau.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $(SRC)/xml_niveau.cpp -o $(OBJDIR_RELEASE)/xml_niveau.cpp.o

$(OBJDIR_RELEASE)/Ennemis.cpp.o: $(SRC)/Ennemis.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $(SRC)/Ennemis.cpp -o $(OBJDIR_RELEASE)/Ennemis.cpp.o

$(OBJDIR_RELEASE)/Explosion.cpp.o: $(SRC)/Explosion.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $(SRC)/Explosion.cpp -o $(OBJDIR_RELEASE)/Explosion.cpp.o

$(OBJDIR_RELEASE)/Fenetre_SFML.cpp.o: $(SRC)/Fenetre_SFML.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $(SRC)/Fenetre_SFML.cpp -o $(OBJDIR_RELEASE)/Fenetre_SFML.cpp.o

$(OBJDIR_RELEASE)/GestionFont.cpp.o: $(SRC)/GestionFont.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $(SRC)/GestionFont.cpp -o $(OBJDIR_RELEASE)/GestionFont.cpp.o

$(OBJDIR_RELEASE)/Collisions.cpp.o: $(SRC)/Collisions.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $(SRC)/Collisions.cpp -o $(OBJDIR_RELEASE)/Collisions.cpp.o

$(OBJDIR_RELEASE)/GestionSprite.cpp.o: $(SRC)/GestionSprite.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $(SRC)/GestionSprite.cpp -o $(OBJDIR_RELEASE)/GestionSprite.cpp.o

$(OBJDIR_RELEASE)/Menus.cpp.o: $(SRC)/Menus.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $(SRC)/Menus.cpp -o $(OBJDIR_RELEASE)/Menus.cpp.o

$(OBJDIR_RELEASE)/Particules.cpp.o: $(SRC)/Particules.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $(SRC)/Particules.cpp -o $(OBJDIR_RELEASE)/Particules.cpp.o

$(OBJDIR_RELEASE)/RecupDonneesXML.cpp.o: $(SRC)/RecupDonneesXML.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $(SRC)/RecupDonneesXML.cpp -o $(OBJDIR_RELEASE)/RecupDonneesXML.cpp.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

install:
	if [ -e spaceInvaders ]; then rm spaceInvaders; fi

	ln -s bin/Release/spaceInvaders spaceInvaders
	
	if [ $(LBITS) = 64 ]; then \
		if [ $(OS) = Ubuntu ]; then \
			cp lib/SFML-1.6/lib-64/*.so.1.6 /lib/x86_64-linux-gnu; \
		else \
			if [ $(OS) = Fedora ]; then \
				cp lib/SFML-1.6/lib-64/*.so.1.6 /lib64; \
			fi \
		fi \
	else \
		if [ $(OS) = Ubuntu ]; then \
			cp lib/SFML-1.6/lib-32/*.so.1.6 /lib/i386-linux-gnu; \
		else \
			if [ $(OS) = Fedora ]; then \
				cp lib/SFML-1.6/lib-32/*.so.1.6 /lib/i686; \
			fi \
		fi \
	fi