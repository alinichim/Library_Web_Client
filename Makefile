# Copyright (C) Alin Ichim 2023
CC = g++
LDFLAGS =
CFLAGS = -Wall -Wextra -std=c++11 -g
EXENAME = client
SRCDIR = source
BUILDDIR = bin
INCDIR = include
LOGDIR = logs
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRC))

.PHONY: all clean clean-logs $(EXENAME)

all: $(EXENAME)

$(shell mkdir -p $(BUILDDIR))
$(shell mkdir -p $(LOGDIR))

$(EXENAME): $(OBJ)
	$(CC) -o $(EXENAME) $(LDFLAGS) $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -I./$(INCDIR) -o $@ $<

clean-bin:
	rm -rf $(EXENAME) $(OBJ)

clean-logs:
	rm -rf $(LOGDIR)/*

clean: clean-bin clean-logs
	