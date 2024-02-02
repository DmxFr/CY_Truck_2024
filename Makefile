#CC := clang
#CFLAGS := -Wall -g -Wno-everything -pthread -lm
#
#SRCS := main.c model.c avl_ville.c  avl_trajet.c util.c io.c
#HEADERS := model.h avl_ville.h avl_trajet.h util.h io.h
#OBJS := $(SRCS:.c=.o)
#EXEC := main
#
#all: $(EXEC)
#
#$(EXEC): $(OBJS)
##    $(CC) $(CFLAGS) $(OBJS) -o $(EXEC)
#%.o: %.c
#	$(CC) $(CFLAGS) -c $< -o $@
#
#
#all: main
#
## main: $(OBJS) $(HEADERS)
## 	$(CC) $(CFLAGS) -O3 $(SRCS) -o "$@"
#
#main-debug: $(SRCS) $(HEADERS)
#	$(CC) $(CFLAGS) -O0 $(SRCS) -o "$@"
#
#clean:
#	rm -f main main-debug


#CC = gcc
#CFLAGS = -Wall 

#SRCS = main.c traitement_t.c traitement_s.c
#OBJS = $(SRCS:.c=.o)
##

#all: $(EXEC)

#$(EXEC): $(OBJS)
 #   $(CC) $(CFLAGS) $(OBJS) -o $(EXEC)
#%.o: %.c    $(CC) $(CFLAGS) -c $< -o $@
#clean:
 #   rm -f $(OBJS) $(EXEC)




#all: main

#CC = clang
#override CFLAGS += -g -Wno-everything -pthread -lm

#SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
#HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

#main: $(SRCS) $(HEADERS)
#	$(CC) $(CFLAGS) $(SRCS) -o "$@"

#main-debug: $(SRCS) $(HEADERS)
#	$(CC) $(CFLAGS) -O0 $(SRCS) -o "$@"

#clean:
#	rm -f main main-debug



#
#
#
#CC = gcc
#CFLAGS = -lm
#
#SRC_FILES = main.c model.c avl_ville.c avl_trajet.c util.c io.c
#OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))
#HEADER_FILES = model.h avl_ville.h avl_trajet.h util.h io.h
#
#EXECUTABLE = main
#
#all: $(EXECUTABLE)
#
#$(EXECUTABLE): $(OBJ_FILES)
#	$(CC) $(CFLAGS) $^ -o $@
#
#%.o: %.c $(HEADER_FILES)
#	$(CC) $(CFLAGS) -c $< -o $@
#
#clean:
#	rm -f $(OBJ_FILES) $(EXECUTABLE)



#all:main
#
#util.o : util.c util.h header.h
#	gcc -c util.c -o util.o
#
#model.o : model.c model.h util.c util.h header.h
#	gcc -c model.c model.h util.c util.h header.h -o model.o
#
#avl_ville.o : avl_ville.c avl_ville.h model.c model.h util.c util.h header.h
#	gcc -c avl_ville.c avl_ville.h model.c model.h util.c util.h header.h -o avl_ville.o
#
#avl_trajet.o : avl_trajet.c avl_trajet.h avl_ville.c avl_ville.h model.c model.h util.c util.h header.h
#	gcc -c avl_trajet.c avl_trajet.h avl_ville.c avl_ville.h model.c model.h util.c util.h header.h -o avl_trajet.o
#
#io.o : io.c io.h avl_trajet.c avl_trajet.h avl_ville.c avl_ville.h model.c model.h util.c util.h header.h
#	gcc -c io.c io.h avl_trajet.c avl_trajet.h avl_ville.c avl_ville.h model.c model.h util.c util.h header.h -o io.o
#
#main.o : main.c  io.c io.h header.h avl_trajet.c avl_trajet.h avl_ville.c avl_ville.h model.c model.h util.c util.h header.h
#	gcc -c main.c  io.c io.h header.h avl_trajet.c avl_trajet.h avl_ville.c avl_ville.h model.c model.h util.c util.h header.h -o main.o
#
#main : main.o io.o avl_trajet.o avl_ville.o model.o util.o
#	gcc main.o io.o avl_trajet.o avl_ville.o model.o util.o -o main
#
#clean :
#	rm -f *.o
#	rm -f main

main: *.c # recomplier à chaque fois car ne detecte pas les modifications ne venant pas de main.c
	rm -f main
	rm -f *.o 
	gcc -o progc/main main.c -lm

clean:
	rm -f main
	rm -f *.o