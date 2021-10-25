CC = gcc

all: program
ifeq ($(OS),Windows_NT)
    DELETE=del
	PATH=\\
else
    DELETE=rm
	PATH=/
endif

# program: src\\address_book_fops.c src\\address_book_menu.c src\\main.c
# 	$(CC) -o bin\\program src\\address_book_fops.c src\\address_book_menu.c src\\main.c

program: src$(PATH)address_book_fops.c src$(PATH)address_book_menu.c src$(PATH)main.c
	$(CC) -o bin$(PATH)program src$(PATH)address_book_fops.c src$(PATH)address_book_menu.c src$(PATH)main.c

clean: 
	rm bin/*.exe