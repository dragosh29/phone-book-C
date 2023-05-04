#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

int c=0;

typedef struct{
    char name[35];
    char address[50];
    char father_name[35];
    char mother_name[30];
    char number[15];
    char gender[8];
    char mail[100];
}Contact;

Contact contacts[101];

void read() {
    "Reads the input file and stores the data in an array of struct contacts.";

    FILE *fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    char current_line[1001];
    while (fgets(current_line, 100, fp)) {
        printf("%s", current_line);
    }
    fclose(fp);
}

void exit_prog();
void add_contact();
void contact_list();
void search_contact();
void modify_contact();
void delete_contact();

void menu() {
    "Displays the menu.";

    c++;
    if(c==1)printf("\n\t\t\t\t   Opened the Phonebook \t\t\t\t\t\t\n\n");

    printf("\t\t\t\t\t  MENU\t\t\n\n");
    printf("\t1.Add New Contact   \t2.Contact List   \t3.Search Contact  \n\t4.Modify Contact \t5.Delete Contact \t6.Exit");
    printf("\n\n\t Enter 1 to 6: \n");
    switch(getch()){
        case '1': add_contact();
            break;
        case '2': contact_list();
            break;
        case '3': search_contact();
            break;
        case '4': modify_contact();
            break;
        case '5': delete_contact();
            break;
        case '6': exit_prog();
            break;
        default:
            getch();
            menu();
    }
}

void add_contact()
{
    system("cls");
    // add a new contact
    Contact new_contact;
    printf("Enter name: ");
    scanf("%34s", new_contact.name);
    printf("Enter address: ");
    scanf("%49s", new_contact.address);
    printf("Enter father's name: ");
    scanf("%34s", new_contact.father_name);
    printf("Enter mother's name: ");
    scanf("%29s", new_contact.mother_name);
    printf("Enter telephone number: ");
    scanf("%14s", new_contact.number);
    printf("Enter gender: ");
    scanf("%7s", new_contact.gender);
    printf("Enter email address: ");
    scanf("%99s", new_contact.mail);

    FILE *fp = fopen("input.txt", "a");

    fprintf(fp, "%s %s %s %s %s %s %s ", new_contact.name, new_contact.address,
            new_contact.father_name, new_contact.mother_name, new_contact.number,
            new_contact.gender, new_contact.mail);
    fclose(fp);
    menu();
}

void search_contact()
{
    // search a contact by telephone number

    system("cls");
    char number[15];
    printf("Enter the telephone number of the contact: ");
    scanf("%s", number);

    FILE *fp = fopen("input.txt", "r");
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    Contact contact;
    int i = 0, found = 0;
    while(fscanf(fp, "%34s %49s %34s %29s %14s %7s %99s", contact.name, contact.address,
                 contact.father_name, contact.mother_name, contact.number,
                 contact.gender, contact.mail) == 7)
    {
        if(strcmp(contact.number, number) == 0)
        {
            printf("Contact found:\n");
            printf("Name: %s\n", contact.name);
            printf("Address: %s\n", contact.address);
            printf("Father's name: %s\n", contact.father_name);
            printf("Mother's name: %s\n", contact.mother_name);
            printf("Telephone number: %s\n", contact.number);
            printf("Gender: %s\n", contact.gender);
            printf("Email address: %s\n\n", contact.mail);
            found = 1;
            break;
        }
        i++;
    }

    if(!found)
    {
        printf("Contact not found\n");
    }

    fclose(fp);
    menu();
}

void delete_contact() {

    // delete a contact found by telephone number
    system("cls");
    char tel_number[15];
    printf("Enter the telephone number of the contact you want to delete: ");
    scanf("%14s", tel_number);

    FILE *fp = fopen("input.txt", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if(temp == NULL) {
        printf("Error creating temporary file\n");
        fclose(fp);
        return;
    }

    Contact contact;
    int deleted = 0;
    while(fscanf(fp, "%34s %49s %34s %29s %14s %7s %99s", contact.name, contact.address,
                 contact.father_name, contact.mother_name, contact.number,
                 contact.gender, contact.mail) == 7)
    {
        if(strcmp(contact.number, tel_number) == 0) {
            deleted = 1;
        } else {
            fprintf(temp, "%s %s %s %s %s %s %s\n", contact.name, contact.address,
                    contact.father_name, contact.mother_name, contact.number,
                    contact.gender, contact.mail);
        }
    }
    fclose(fp);
    fclose(temp);

    if(!deleted) {
        printf("Contact not found\n");
        remove("temp.txt");
    } else {
        remove("input.txt");
        rename("temp.txt", "input.txt");
        printf("Contact deleted successfully\n");
    }

    menu();
}

void contact_list()
{
    system("cls");
    // display the list of contacts
    FILE *fp = fopen("input.txt", "r");
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    Contact contact;
    int i = 0;
    while(fscanf(fp, "%34s %49s %34s %29s %14s %7s %99s", contact.name, contact.address,
                 contact.father_name, contact.mother_name, contact.number,
                 contact.gender, contact.mail) == 7)
    {
        printf("Contact %d:\n", i+1);
        printf("Name: %s\n", contact.name);
        printf("Address: %s\n", contact.address);
        printf("Father's name: %s\n", contact.father_name);
        printf("Mother's name: %s\n", contact.mother_name);
        printf("Telephone number: %s\n", contact.number);
        printf("Gender: %s\n", contact.gender);
        printf("Email address: %s\n\n", contact.mail);
        i++;
    }
    fclose(fp);
    menu();
}

void modify_contact()
{
    //searches for a contact by phone number then allows it to be modified in file
    system("cls");
    // modify a contact
    char number[14];
    printf("Enter the telephone number of the contact to be modified: ");
    scanf("%14s", number);

    FILE *fp = fopen("input.txt", "r");
    FILE *fp_temp = fopen("f_temp.txt", "w"); // temporary file

    if(fp == NULL || fp_temp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    Contact contact;
    int found = 0;
    while(fscanf(fp, "%34s %49s %34s %29s %14s %7s %99s", contact.name, contact.address,
                 contact.father_name, contact.mother_name, contact.number,
                 contact.gender, contact.mail) == 7)
    {
        if(strcmp(contact.number, number) == 0)
        {
            found = 1;
            printf("Contact found:\n");
            printf("Name: %s\n", contact.name);
            printf("Address: %s\n", contact.address);
            printf("Father's name: %s\n", contact.father_name);
            printf("Mother's name: %s\n", contact.mother_name);
            printf("Telephone number: %s\n", contact.number);
            printf("Gender: %s\n", contact.gender);
            printf("Email address: %s\n", contact.mail);

            // modify the contact
            printf("\nEnter the new details:\n");
            printf("Enter address: ");
            scanf("%49s", contact.address);
            printf("Enter father's name: ");
            scanf("%34s", contact.father_name);
            printf("Enter mother's name: ");
            scanf("%29s", contact.mother_name);
            printf("Enter telephone number: ");
            scanf("%14s", contact.number);
            printf("Enter gender: ");
            scanf("%7s", contact.gender);
            printf("Enter email address: ");
            scanf("%99s", contact.mail);
        }
        // write the contact to the temporary file
        fprintf(fp_temp, "%s %s %s %s %s %s %s ", contact.name, contact.address,
                contact.father_name, contact.mother_name, contact.number,
                contact.gender, contact.mail);
    }

    fclose(fp);
    fclose(fp_temp);

    // delete the old file and rename the temporary file to the original name
    remove("input.txt");
    rename("f_temp.txt", "input.txt");

    if(!found)
    {
        printf("Contact not found\n");
    }
    else
    {
        printf("Contact modified successfully\n");
    }

    menu();
}

void exit_prog(){
    system("cls");
"Exits the program.";
    system("cls");
    printf("\n\n\t\t\t\t Are you sure you want to exit? (Y/N): \n");
    if(getch()==89 || getch()==121){
        printf("\n\n\t\t\t\t Closing phonebook. Have a nice day!");
        exit(0);
    }
    else{
        menu();
    }
}

void start(){
    "Starts the program.";

    menu();
}

int main(){

    system("color 09");
    start();
    return 0;
}