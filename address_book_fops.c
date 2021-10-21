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

		char line[1024];
		int x = 0;
		while(fgets(line,sizeof(line), address_book->fp)){
			char * token;
			token = strtok(line, ",");
			ContactInfo newPerson;
			while(token != NULL){
				strcpy(newPerson.name[0], token);
				for(int i = 0; i < 5; i++){
					token = strtok(NULL, ",");
					strcpy(newPerson.phone_numbers[i], token);
				}
				for(int i = 0; i < ; i++){
					token = strtok(NULL, ",");
					strcpy(newPerson.email_addresses[i], token);
				}
            token = strtok(NULL, "\n");
			}
			newPerson.si_no = (x+1);
			address_book->list[x] = newPerson;
			x++;
		}
		address_book->count = x;
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

	for(int i = 0; i < address_book->count; i++){
		fprintf(address_book->fp, "%s,", address_book->list[i].name);
		for(int j = 0; j < 5; j++){
			fprintf(address_book->fp, "%s,", address_book->list[i].phone_numbers[j]);
		}
		for(int j = 0; j < 5; j++){
			fprintf(address_book->fp, "%s,", address_book->list[i].email_addresses[j]);
		}
	}

	fclose(address_book->fp);
	return e_success;
}

/*

fprintf(address_book->fp, "%s,%s,%s\n", 
		address_book->list[i].name[0], address_book->list[i].phone_numbers[0]
		, address_book->list[i].email_addresses[0]);

*/