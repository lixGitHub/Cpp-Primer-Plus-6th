#####################
# Makefile
#####################
# SOURCE	:= week3.cpp week3_lib.cpp 
# OJBS	:= week3.o weeek3_lib.o
TARGET	:= pointer swap crash crash2 crash_log time exception

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

pointer: pointer.cpp
	$(CXX) -o $@ $^

swap: swap.cpp
	$(CXX) -o $@ $^

crash: crash.cpp
	$(CXX) -o $@ $^

crash2: crash2.cpp
	$(CXX) -o $@ $^

time: time.cpp
	$(CXX) -o $@ $^

crash_log: crash_log.cpp
	$(CXX) -o $@ $^

exception: exception.cpp
	$(CXX) -o $@ $^

# left: left.cpp
# 	$(CXX) 	-o $@ $^

.PHONY: clean

clean:
	rm $(TARGET)
cleanobj:
	rm *.o