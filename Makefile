# A simple Makefile for compiling small SDL projects

# set the compiler
CC := gcc

# set the compiler flags
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm

# add header files here
HDRS := inc/c_trees.h inc/type_utils.h inc/game_loop.h inc/render.h

# add source files here
SRCS := src/c_trees.c src/main.c src/game_loop.c src/render.c

# generate names of object files
OBJS := $(SRCS:.c=.o)

# name of executable
EXEC := main

# default recipe
all: $(EXEC)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe for building object files
# $(OBJS): $(@:.o=.c) $(HDRS) Makefile
# 	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# $(OBJDIR)/%.o: %.c
# 	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
