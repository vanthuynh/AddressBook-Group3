# Project 3 - Address Book (cs2600)

### Group Members
- Andre Nalbandian
- Christopher Tcherkezian
- Moina Vernon
- Paola Barrera
- Van Huynh

### Contribution
| Name                   |      Task        |
| --------------------   | --------------   |
| Van Huynh              | implement get_option(), list_contact() |
| Christopher Tcherkezian| implement search_contacts |
| Andre Nalbandian       | implement load_file(), save_file(), design extra phone number and email feature|
| Moina Vernon           | implement add_contact(), edit_contact, and delete_contact |
| Paola Barrera          |                  |    
- We all helped each other with debugging, gave feedbacks and did our best perfecting the application

### Resources
- The project can be found online -->  [***CLICK HERE***](https://www.emertxe.com/embedded-systems/c-programming/c-projects/address-book-c/?gclid=Cj0KCQjwtMCKBhDAARIsAG-2Eu84R-w7MbNt3VoLKUZqFHlCUHNjOJsFUfUcYHbp0vF25jS9aVlS66YaAn6gEALw_wcB)

### Get Started
1. Create new folder & Move into the newly created folder
```
mkdir <folder_name>
cd <folder_name>
```
2. clone this repo
```
git clone https/SSH
```
3. Move into the directory
```
cd AddressBook-Group3
```
4. Make new branch and start working on the part
```
git switch -c <your_name_branch>
```
5. When ready(or need help), push your branch up
```
git add .
git commit -m "I need help on this/I just finished the part"
git push -u origin <your_name_branch>
```
6. Compile command line
```
gcc .\main.c .\address_book_fops.c .\address_book_menu.c
```
### Project Overview

```
#######  Address Book  #######
#######  Features:
0. Exit
1. Add Contact
2. Search Contact
3. Edit Contact
4. Delete Contact
5. List All Contacts
6. Save

Please select an option: 4

#######  Address Book  #######
#######  Search Contact to Delete By:

0. Back
1. Name
2. Phone No.
3. Email ID
4. Serial No.

Please select an option: 1
Enter the Name: 
```