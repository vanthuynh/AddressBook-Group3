#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    address_book->list = (ContactInfo*)calloc(counter, sizeof(ContactInfo));
}

Status load_file(AddressBook *address_book)
{
	int ret = 1;
	if(fileExists(DEFAULT_FILE))
		ret = 0;

	if (ret == 0)
	{
		address_book->fp = fopen(DEFAULT_FILE, "a+");
		AdBookInit(address_book, 100);
		if(address_book->fp == NULL){
			perror("Unable to open file");
			exit(1);
		}

		FILE* pointer  = fopen("address_book.csv", "r");
		char line[500];
		int x = 0;
		while(fgets(line, sizeof(line), pointer)){
			char* token2 = strtok(line, "\n");
        	char *token = strtok(token2, ",");
			int numCount = 0;
			int emCount = 0;
			ContactInfo newPerson;
			for(int i = 0 ; i <= 10; i++){
				if(i == 0){
				strcpy(newPerson.name[0], token); 
				token = strtok(NULL, ",");
				}
				else if (i > 0 && i <= 5){
					strcpy(newPerson.phone_numbers[numCount], token); 
					numCount++;
					token = strtok(NULL, ",");
				}
				else if (i > 5){
					strcpy(newPerson.email_addresses[emCount], token); 
					emCount++;
					token = strtok(NULL, ",");
				}
			}
			newPerson.si_no = (x+1);
			address_book->list[x] = newPerson;
			x++;
		}
		address_book->count = x;
		//printList(address_book);
	}
	else
	{
		address_book->fp = fopen(DEFAULT_FILE, "a");
		AdBookInit(address_book, 100);
		address_book->count = 0;

		printf("file not exist but now made");
	}

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	fclose(address_book->fp);
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	// for(int i = 0; i < address_book->count; i++){
	// 	fprintf(address_book->fp, "%s,%s,%s\n", 
	// 	address_book->list[i].name[0], address_book->list[i].phone_numbers[0]
	// 	, address_book->list[i].email_addresses[0]);
	// }

	for(int i = 0; i < address_book->count; i++){
		fprintf(address_book->fp, "%s,", address_book->list[i].name[0]);
		for(int j = 0; j < 5; j++){
			fprintf(address_book->fp, "%s,", address_book->list[i].phone_numbers[j]);
		}
		for(int j = 0; j < 4; j++){
			fprintf(address_book->fp, "%s,", address_book->list[i].email_addresses[j]);
		}
		fprintf(address_book->fp, "%s\n", address_book->list[i].email_addresses[4]);
	}

	fclose(address_book->fp);
	return e_success;
}