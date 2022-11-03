# A simple Makefile for compiling small SDL projects

# set the compiler
CC := gcc

# set the compiler flags
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm

# add header files here
HDRS := inc/c_trees.h examples/render.h

# define main file (used for clean function, in order to build, use make MAIN=<dir>/<file>.c)
MAIN := examples/adj_list_tree_example.c examples/nested_obj_tree_example.c
# add source files here
SRCS := src/c_trees.c examples/render.c $(MAIN) 

# generate names of object files
OBJS := $(SRCS:.c=.o)

# name of executable
FILENAME := $(notdir $(MAIN))
EXEC := $(FILENAME:.c=)

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
ALL_EXECS = adj_list_tree_example nested_obj_tree_example main
clean:
	rm -f $(ALL_EXECS) $(OBJS)

.PHONY: all clean
