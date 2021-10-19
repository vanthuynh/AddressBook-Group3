#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdbool.h>

#include "address_book.h"
bool fileExists(char *fileName){
	struct stat buffer;

	return(stat(fileName, &buffer) == 0);
}

Status load_file(AddressBook *address_book)
{
	int ret = 1;
	if(fileExists(DEFAULT_FILE))
		ret = 0;

	//open file and copy list into 
	if (ret == 0)
	{
		//FILE EXISTS WORK ON THIS HERE

		// GO LINE BY LINE CREATING TYPECONTACT INFO
		// USING NAME EMAIL AND NUMBER
		// ADD THAT TO ADDRESSBOOK LIST
		/* 
		 * Do the neccessary step to open the file
		 * Do error handling
		 */ 
		address_book->fp = fopen(DEFAULT_FILE, "a+");
		if(address_book-> fp == NULL){
			perror("Unable to open file");
			exit(1);
		}
		char line[1024];
		int x = 0;
		//printf("this is count: %d\n", ab);
		while(fgets(line,sizeof(line), address_book->fp)){
			char * token;
			token = strtok(line, ",");
			ContactInfo newPerson;
			while(token != NULL){
				strcpy(newPerson.name[0], token);
				token = strtok(NULL, ",");
				strcpy(newPerson.phone_numbers[0], token);
				token = strtok(NULL, "\n");
				strcpy(newPerson.email_addresses[0], token);
				token = strtok(NULL, ",");
			}
			 printf("Name: %s ", newPerson.name[0]);
			 printf("Number: %s ", newPerson.phone_numbers[0]);
			 printf("Email: %s \n", newPerson.email_addresses[0]);
			//put newPerson into address_book->list
			//address_book->list[x] = newPerson;
			x++;
		}
		//printf("file exist");
		//printf("HELLO %s", address_book->list->si_no);
	}
	else
	{
		/* Create a file for adding entries */
		address_book->fp = fopen(DEFAULT_FILE, "a");
		printf("file not exist");
	}

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	//address_book->fp = fopen(DEFAULT_FILE, "w");
	fclose(address_book->fp);

	// if (address_book->fp == NULL)
	// {
	// 	return e_fail;
	// }

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 

	return e_success;
}