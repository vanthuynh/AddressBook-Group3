#include <stdio.h>
// #include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
//#include "abk_log.h"
#include "address_book_menu.h"
#include "address_book.h"

/* clean the input buffer */
void clean_stdin()
{
	while (getchar() != '\n')
		;
}

int getUserInt(const char *prompt)
{
	int userInput;
	while (1)
	{
		printf("%s", prompt);
		scanf_s("%d", &userInput);
		if (userInput >= 0)
			return userInput;
		printf("*Note: Please only enter positive number: ");
		clean_stdin();
	}
}

int getBoundedInt(const char *prompt, int lowBound, int highBound)
{
	int userInput;
	while (1)
	{
		userInput = getUserInt(prompt);
		if (lowBound <= userInput && userInput <= highBound)
			break;
		printf("Please enter a value in the range [%d..%d]\nPlease select an option: ", lowBound, highBound);
		clean_stdin();
	}
	return userInput;
}

int get_option(int type, const char *msg)
{
	if (type == NUM)
	{
		int userInput = getBoundedInt(msg, 0, 6);
		return userInput;
	}
	else if (type == CHAR)
	{
		do
		{
			clean_stdin();
			char charInput;
			printf("%s", msg);
			scanf_s("%c", &charInput, 1);
			switch (charInput)
			{
			case 'n':
			case 'N':
				return 'N';
			case 'y':
			case 'Y':
				return 'Y';
			}
			printf("Please select Y or N\n");
			fflush(stdout);
		} while (1);
	}
	return NONE;
}

char getChar(const char *prompt)
{
	char charInput;
	do
	{
		int status;
		clean_stdin();
		printf("%s", prompt);
		status = scanf_s("%c", &charInput, 1);
		if (status == 1)
			break;
		printf("Invalid character, try again...\n");
		fflush(stdout);
	} while (1);
	return charInput;
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/*
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */
	menu_header(title);
	int counter = 0;
	char option;
	do
	{
		menu_header(title);
		printf("============================================================================================================\n");
		printf(": S. No : Name                            : Phone No                        : Email ID                     :\n");
		//printf(": %*s : %*s : %*s : %*s\n", -2, "S. No", -40, "Name", -40, "Phone No", -40, "Email Id");
		printf("============================================================================================================\n");
		for (int i = 0; i < mode; i++)
		{
			//print each section spaced out correctly
			//printf(": %*d : %*s : %*s : %*s\n", -5, address_book->list[counter].si_no, -40, address_book->list[counter].name[0], -40, address_book->list[counter].phone_numbers[0], -40, address_book->list[counter].email_addresses[0]);
			//print each section spaced out correctly
			// address_book->list[i].name[0],address_book->list[i].phone_numbers[0],address_book->list[i].email_addresses[0]);
			printf(": %d", address_book->list[counter].si_no);
			printf("\t: %s", address_book->list[counter].name[0]);
			printf("\t\t\t\t: %s", address_book->list[counter].phone_numbers[0]);
			printf("\t\t\t\t: %s\n", address_book->list[counter].email_addresses[0]);
			counter++;
		}
		printf("============================================================================================================\n");
		option = getChar(msg);
	} while (option == 'n' || option == 'p' && counter <= address_book->count); //while (toupper(option) != 'Q' && counter <= address_book->count);
	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	//system("cls");

	printf("#######  Address Book  #######\n");
	if (*str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void printList(AddressBook *address_book)
{
	printf("PRINTING LIST\n");
	for (int i = 0; i < address_book->count; i++)
	{
		printf("name: %s, number: %s, email: %s\n", address_book->list[i].name[0],
				 address_book->list[i].phone_numbers[0], address_book->list[i].email_addresses[0]);
	}
	printf("\nLIST COMPLETE");
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;

	do
	{
		main_menu();

		option = get_option(NUM, "");
		if ((address_book->count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
		case e_add_contact:
			/* Add your implementation to call add_contacts function here */
			add_contacts(address_book);
			break;
		case e_search_contact:
			search_contact(address_book);
			break;
		case e_edit_contact:
			edit_contact(address_book);
			break;
		case e_delete_contact:
			delete_contact(address_book);
			break;
		case e_list_contacts:
			break;
			/* Add your implementation to call list_contacts function here */
			list_contacts(address_book, "Search Result:\n", 0, "Press [q]-Cancel | [n]-Next Page | [p]-Previous Page: ", e_list);

		case e_save:
			save_file(address_book);
			break;
		case e_exit:
			break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
	int user_opt, tempIndex; //variable to store user option and tempIndex stores address book count
	ContactInfo newPerson;	 //Declare temp new contact

	//initialize each variable to empty string
	strcpy(newPerson.name[0], " ");
	strcpy(newPerson.phone_numbers[0], " ");
	strcpy(newPerson.email_addresses[0], " ");

	address_book->count = 0; //temporary assignment to check code works
	tempIndex = address_book->count;

	tempIndex++; //another contact added, increment address book size
	newPerson.si_no = tempIndex;

	menu_header("Add Contact:\n"); //Display header for "Add Contact"

	//Display options user can add to
	printf("0. Exit\n");
	printf("1. Name       :\n");
	printf("2. Phone No 1 :\n");
	printf("3. Email ID 1 :\n");

	do
	{
		user_opt = getBoundedInt("Please select an option: ", 0, 3);

		switch (user_opt)
		{
		case e_no_opt:
			break; //exit while loop
		case 1:
			printf("Enter the name: ");
			scanf("%s", newPerson.name[0]);
			break;
		case 2:
			printf("Enter Phone Number 1: [Please renter the same option of alternate Phone Number]: ");
			scanf("%s", newPerson.phone_numbers[0]);
			break;
		case 3:
			printf("Enter Email ID 1: [Please renter the same option of alternate Email ID]: ");
			scanf("%s", newPerson.email_addresses[0]);
			break;
		}

		/* Display option menu with new added info */
		menu_header("Add Contact:\n");

		printf("0. Exit\n");
		printf("1. Name       : %s\n", newPerson.name[0]);
		printf("2. Phone No 1 : %s\n", newPerson.phone_numbers[0]);
		printf("3. Email ID 1 : %s\n", newPerson.email_addresses[0]);

	} while (user_opt != 0);
	printf("THIS IS THE CURRENT COUNT: %d", address_book->count);

	newPerson.si_no = address_book->count;

	address_book->list[address_book->count] = newPerson; //update latest contact in list
	address_book->count += 1;									  //another contact added, increment address book size
	printList(address_book);
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
	int tempIndex;
	address_book->count = 0; //temporary assignment to check code works
	tempIndex = address_book->count;

	tempIndex++; //another contact added, increment address book size

	ContactInfo person;

	person.si_no = tempIndex;

	switch (field)
	{
	case 1:
		for (int i = 0; i < loop_count; i++)
		{
			for (int name = 0; name < NAME_COUNT; name++)
			{
				if (address_book->list[tempIndex].name[name] != NULL)
				{
					return e_success;
					//clean_stdin();
					printf("%c", address_book->fp, person.name[tempIndex]);
				}
			}
		}
		break;

	case 2:
		for (int i = 0; i < loop_count; i++)
		{
			for (int phone = 0; phone < PHONE_NUMBER_COUNT; phone++)
			{
				if (address_book->list[tempIndex].phone_numbers[phone] != NULL)
				{
					return e_success;
					clean_stdin();
					printf("%c", address_book->fp, person.phone_numbers);
				}
			}
		}
		break;

	case 3:
		for (int i = 0; i < loop_count; i++)
		{
			for (int email = 0; email < EMAIL_ID_COUNT; email++)
			{
				if (address_book->list[tempIndex].email_addresses[email] != NULL)
				{
					return e_success;
					clean_stdin();
					printf("%c", address_book->fp, person.email_addresses);
				}
			}
		}
		break;

	case 4:
		for (int i = 0; i < loop_count; i++)
		{
			for (int serial = 0; serial < NAME_COUNT; serial++)
			{
				if (address_book->list[LIST_MAX].si_no)
				{
					return e_success;
					clean_stdin();
					printf("%c", address_book->fp, person.si_no);
				}
			}
		}
		break;

	default:
		break;
	}
}

Status search_contact(AddressBook *address_book)
{
	// uses contact info struct to set person_found as a pointer
	ContactInfo *person_found = address_book->list;

	// input from user has length of 32
	char input[32];

	// declare user options
	int user_opt;

	// pointer for FILE (.CSV)
	FILE *fp;

	//want to shorten this instead of long print statement
	char *msg = ":======:==================================:==================================:==================================:\n:"
					": S.No : Name                             : Phone No                         : Email                            :\n:"
					":======:==================================:==================================:==================================:\n"
					":      :                                  :                                  :                                  :\n:"
					":      :                                  :                                  :                                  :\n:"
					":      :                                  :                                  :                                  :\n:";

	// Displays menu options
	menu_header("Search contact by: \n");

	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n");

	// do loop allows for user to search until case '0' (e_no_opt) is selected
	do
	{
		// user opt calls getbounded function to set options from 0 - 4, will return invalid response if out of bounds
		user_opt = getBoundedInt("\nPlease select an option: ", 0, 4);

		// switch statement based on bounds
		switch (user_opt)
		{

		// RETURN TO MAIN MENU
		case e_no_opt:
			break;
		// FIND NAME
		case 1:
			printf("Please enter the name: ");

			// clears input buffer
			clean_stdin();

			// reads input from user, must not exceed 32 characters
			// use %[^\n]%*c to allow user to use both spaces for first/last name, or just first name
			scanf("%[^\n]%*c", input);

			// NAME FOUND
			if (fp != NULL)
			{
				// input = input | address_book = store file, list, count | address_book->count = loopcount | 1 = field | msg = formatting of output | e_search =  mode | ==e_success = status
				if (search(input, address_book, address_book->count, 1, msg, e_search) == e_success)
				{
					// returns the search above if successful
					return search(input, address_book, address_book->count, 1, msg, e_search);
				}
				// NAME NOT FOUND
				else
				{

					printf("'%s' not found in this address book.\n", &input);
				}
			}
			break;

		// FIND PHONE NUMBER
		case 2:
			printf("Please enter the phone number: ");

			// clears input buffer
			clean_stdin();

			// reads input from user, must not exceed 32 characters
			scanf("%s", input);

			// PHONE NUMBER FOUND
			if (fp != NULL)
			{
				if (search(input, address_book, address_book->count, 1, msg, e_search) == e_success)
				{

					return search(input, address_book, address_book->count, 1, msg, e_search);
				}
				else
				{
					printf("'%s' not found in this address book.\n", &input);
				}
			}
			break;
		// FIND EMAIL
		case 3:
			printf("Please enter the email ID: ");

			// clears input buffer
			clean_stdin();

			// reads input from user, must not exceed 32 characters
			scanf("%s", input);

			// EMAIL FOUND
			if (fp != NULL)
			{
				if (search(input, address_book, address_book->count, 1, msg, e_search) == e_success)
				{
					return search(input, address_book, address_book->count, 1, msg, e_search);
				}
				// EMAIL NOT FOUND
				else
				{

					printf("'%s' not found in this address book.\n", &input);
				}
			}
			break;
		// FIND SERIAL NUMBER | refers to the index the contact info is stored at
		case 4:
			printf("Please enter the serial number: ");

			// clears input buffer
			clean_stdin();

			// reads input from user, must not exceed 32 characters
			scanf("%s", input);

			// SERIAL NUMBER FOUND
			if (fp != NULL)
			{
				if (search(input, address_book, address_book->count, 1, msg, e_search) == e_success)
				{
					return search(input, address_book, address_book->count, 1, msg, e_search);
				}
				// Serial NUMBER NOT FOUND
				else
				{
					printf("Serial Number '%s' not found in this address book.\n", &input);
				}
			}
			break;
		}
	} while (user_opt != e_exit);
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
	char valid, selection;
	//char input[32];
	int user_opt;

	//change deleperson into general input?
	ContactInfo deletePerson; //Declare temp new contact
	ContactInfo emptyPerson;

	//initialize each variable to empty string
	strcpy(deletePerson.name[0], " ");
	strcpy(deletePerson.phone_numbers[0], " ");
	strcpy(deletePerson.email_addresses[0], " ");

	strcpy(emptyPerson.name[0], " ");
	strcpy(emptyPerson.phone_numbers[0], " ");
	strcpy(emptyPerson.email_addresses[0], " ");

	char *msg = ":======:==================================:==================================:==================================:\n:"
					": S.No : Name                             : Phone No                         : Email                            :\n:"
					":======:==================================:==================================:==================================:\n"
					":      :                                  :                                  :                                  :\n:"
					":      :                                  :                                  :                                  :\n:"
					":      :                                  :                                  :                                  :\n:";

	menu_header("Search Contact to Delete By:\n");

	//Display options user can add to
	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n");

	user_opt = getBoundedInt("Please select an option: ", 0, 4);

	switch (user_opt)
	{
	case e_no_opt:
		return e_back;
	case 1:
		printf("Enter the Name: ");
		scanf("%s", deletePerson.name[0]); //take in user search parameter

		if (search(deletePerson.name[0], address_book, address_book->count, 1, msg, e_delete) == e_success)
			return search(deletePerson.name[0], address_book, address_book->count, 1, msg, e_delete);

		break;
	case 2:
		printf("Enter Phone Number: ");
		scanf("%s", deletePerson.phone_numbers[0]);

		if (search(deletePerson.phone_numbers[0], address_book, address_book->count, 1, msg, e_delete) == e_success)
			return search(deletePerson.phone_numbers[0], address_book, address_book->count, 1, msg, e_delete);

		break;
	case 3:
		printf("Enter Email ID: ");
		scanf("%s", deletePerson.email_addresses[0]);

		if (search(deletePerson.email_addresses[0], address_book, address_book->count, 1, msg, e_delete) == e_success)
			return search(deletePerson.email_addresses[0], address_book, address_book->count, 1, msg, e_delete);

		break;
	case 4:
		printf("Enter Serial Number: ");
		scanf("%d", deletePerson.si_no);

		/*  search for serial number hasnt been added yet to search()

		if (search(deletePerson.si_no, address_book, address_book->count, 1, msg, e_delete) == e_success)
			return search(deletePerson.si_no, address_book, address_book->count, 1, msg, e_delete);
*/
		break;
	}

	printf("Press: [s] = Select, [q] | Cancel: ");
	scanf("%c", selection);

	if (selection == 's')
	{
		int user_si_no;
		printf("Select a Serial Number (S.No) to Delete: ");
		scanf("%d", user_si_no);

		// assign deletePerson to corresponding serial number
		deletePerson = address_book->list[user_si_no];

		menu_header("Delete Contact:\n");
		printf("0. Exit\n");
		printf("1. Name       : %s\n", deletePerson.name[0]);
		printf("2. Phone No 1 : %s\n", deletePerson.phone_numbers[0]);
		printf("3. Email ID 1 : %s\n", deletePerson.email_addresses[0]);

		printf("\nEnter 'Y' to delete. [Press any key to ignore]: ");
		scanf("%c", valid);

		if (valid == 'Y')
		{
			address_book->list[user_si_no] = emptyPerson;
			address_book->count--; //might not display last contact??

			//double check file and list were reassigned or mutated correctly
		}

		//if anyother key entered, DONT delete selected contact
	}
	return e_success;
}