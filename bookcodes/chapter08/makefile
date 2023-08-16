#####################
# Makefile
#####################
SOURCE	:= week3.cpp week3_lib.cpp 
OJBS	:= week3.o weeek3_lib.o
TARGET	:= inline firstref secref swaps cubes strc_ref filefunct left

CC		:= gcc
CXX		:= g++
LIBS	:=
LDFLAGS	:=
DEFINS 	:=
INCLUDE	:= -I.
CFLAGS	:=
CXXFLAGS:=

# compile
# all: week2_exe week3_exe week4_exe week5_exe
all: $(TARGET)

inline: inline.cpp
	$(CXX) -o $@ $^

firstref: firstref.cpp
	$(CXX) -o $@ $^

secref: secref.cpp
	$(CXX) -o $@ $^

swaps: swaps.cpp
	$(CXX) -o $@ $^

cubes: cubes.cpp
	$(CXX) -o $@ $^

strc_ref: strc_ref.cpp
	$(CXX) -o $@ $^

filefunct: filefunct.cpp
	$(CXX) -o $@ $^

left: left.cpp
	$(CXX) 	-o $@ $^

.PHONY: clean

clean:
	rm $(TARGET)
cleanobj:
	rm *.o