# Copyright 2021 Matthew Collins matcoll@bu.edu
# Copyright 2021 Benjamin Lissner blissner@bu.edu
# Makefile for adjustableclock.cpp

OBJS = project.o UIControl.o UIProfile.o
CXX = g++
CXXFLAGS = -std=c++11
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system
startup: project.cpp
			$(CXX) -o startup project.cpp $(LDLIBS) $(CXXFLAGS) 

project.o: project.cpp UIControl.cpp Profile.h UIProfile.h
UIControl.o: UIControl.cpp Profile.h UIProfile.h
Profile.o: Profile.cpp Profile.h
UIProfile.o: UIProfile.cpp UIProfile.h Profile.h

clean:
			$(RM) startup $(OBJS)
