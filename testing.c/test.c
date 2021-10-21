#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char name[1][32];
	char phone_numbers[5][32];
	char email_addresses[5][32];
	int si_no;
} ContactInfo;

typedef struct
{
	FILE *fp;
	ContactInfo *list;
	int count;	
} AddressBook;

int main(){
    printf("sup\n");
    char name[10];
    FILE* pointer  = fopen("address_book.csv", "r");
    
    
    if(pointer == NULL){
        perror("Unable to open file");
        exit(1);
    }
    char line[200];
    while(fgets(line, sizeof(line), pointer)){
        char *token;
        token = strtok(line,",");
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

    }

    printf("My name is: %s", name);
}

