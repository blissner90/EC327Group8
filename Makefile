# Copyright 2021 Matthew Collins matcoll@bu.edu
# Copyright 2021 Benjamin Lissner blissner@bu.edu
# Makefile for adjustableclock.cpp

startup: project.cpp
	g++ project.cpp -o startup -lsfml-graphics -lsfml-window -lsfml-system