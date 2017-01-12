CXX = g++
CC  = gcc
SYSTEM = ubuntu
CFLAGS =  -Wall -W -Wno-format -g3 -O0 -fmessage-length=0 -MMD -MP -DDEBUG -DUBUNTU


LDFLAGS += -lpthread -lrt 

CC_SRCS += \
main.c \
cell.c \
drawer.c

ubuntu: all

all:
	$(CC) $(CC_SRCS) $(CFLAGS) -o main $(LDFLAGS)  
	
clean:
	rm -f main *.d *.o
