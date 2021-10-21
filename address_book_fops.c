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

void AdBookInit(AddressBook *address_book, int counter){
    if(address_book == NULL){
        printf("address book is null\n");
        return;
    }
    //address_book->count = counter;
    address_book->list = (ContactInfo*)calloc(counter, sizeof(ContactInfo));
    printf("finished malloc\n");
}

// void printList(AddressBook *address_book){
//     printf("PRINTING LIST\n");
//     for(int i = 0; i < address_book->count; i++){
//         printf("name: %s, number: %s, email: %s\n", address_book->list[i].name[0], 
//         address_book->list[i].phone_numbers[0],address_book->list[i].email_addresses[0]);
//     }
//     printf("\nLIST COMPLETE");
// }


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
		AdBookInit(address_book, 100);
		if(address_book-> fp == NULL){
			perror("Unable to open file");
			exit(1);
		}

		char line[1024];
		int x = 0;
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
			address_book->list[x] = newPerson;
			x++;
		}
		address_book->count = x;
		//printList(address_book);
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
	fclose(address_book->fp);
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	for (int i = 0; i < address_book->count; i++)
	{
		fprintf(address_book->fp, "%s,%s,%s\n",
				  address_book->list[i].name[0], address_book->list[i].phone_numbers[0], address_book->list[i].email_addresses[0]);
	}

	/*
     * Add the logic to save the file
     * Make sure to do error handling
     */
	fclose(address_book->fp);
	return e_success;
}