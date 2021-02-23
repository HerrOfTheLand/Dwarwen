CC = gcc
RM = rm
CFLAGS = -c -g -std=c99 -Wall -Wextra -Werror -pedantic
LDFLAGS = -g

SRC = ${wildcard src/*.c}
SRC += ${wildcard src/**/*.c}
HDR = ${wildcard include/*.h}
HDR += ${wildcard include/**/*.h}
OBJ = ${SRC:.c=.o}
EXEC = dwarven

all: ${SRC} ${OBJ} ${EXEC}

${EXEC}: ${OBJ}
	${CC} ${LDFLAGS} $^ -o $@

%.o: %.c ${HDR}
	${CC} ${CFLAGS} $< -o $@

clean:
	${RM} ${wildcard **/*.o} ${wildcard *.o} ${EXEC}