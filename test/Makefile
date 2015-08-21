# Makefile pour les tests du projet Polysh
#
#           Author: Erick Gallesio [eg@unice.fr]
#    Creation date: 22-May-2010 15:53 (eg)
# Last file update:  8-Jun-2012 23:49 (eg)

SRCS = $(wildcard *.c)
EXES = $(SRCS:.c=)
LIB  = ../src/libpolysh.a

COPTS   = 
CC      = gcc
CFLAGS  = $(COPTS) -g -Wall -I../include 
LDFLAGS = -L../src -lpolysh

.PHONY: clean

%: %.c
	$(CC) $(CFLAGS) -o $@ $@.c $(LDFLAGS)

all: $(EXES)

$(EXES): $(LIB)

clean:
	rm -f $(EXES) *~