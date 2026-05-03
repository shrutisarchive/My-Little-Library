// Phase2
#include<stdio.h>
#include <stdlib.h>
#include "../include/structure.h"
#include <string.h>

// user register karne k time call hoga
void registerUser() {
    struct user u;
    printf("     Register     \n");
    printf("Enter your name: ");
    scanf("%s", u.name);
    printf("Enter contact details: ");
    scanf("%s", u.contact);
    printf("Create a password: ");
    scanf("%s", u.password);
    generateMemberID(u.member_id); // member_id generate function ko call kiya
    printf("   Registration Successful   \n");
    printf("Name: %s\n", u.name);
    printf("Your Member ID: %s\n", u.member_id);

    // file handling part
    FILE *fp;
    
    fp = fopen("../data/user.txt", "a");
    if(fp == NULL) {
        printf("Error in opening file!\n");
        return;
    }
    
    fprintf(fp, "%s %s %s %s\n", u.name, u.contact, u.member_id, u.password);
    
    fclose(fp);
}

// Member ID joki hum generate karke denge user ko
void generateMemberID(char member_id[]) {
    for(int i = 0; i < 2; i++) {
        member_id[i] = 'A' + (rand() % 26);
    }
    for(int i = 2; i < 6; i++) {
        member_id[i] = '0' + (rand() % 10);
    }
    member_id[6] = '\0';
}

// login karne time call hoga
void loginUser() {
    char input_id[11];
    char input_pass[20];

    printf("\n");
    printf("         LOGIN       \n");
    printf("\n");
    printf("Enter your Member ID: ");
    scanf("%s", input_id);
    printf("Enter your Password: ");
    scanf("%s", input_pass);

    FILE *fp;
    fp = fopen("../data/user.txt", "r");

    if (fp == NULL) {
        printf("\n------------------------------\n");
        printf("No registered users yet!!\n");
        return;
    }

    // check if file empty
    char ch = fgetc(fp);
    if (ch == EOF) {
        printf("\n------------------------------\n");
        printf("No registered users yet!!\n");
        fclose(fp);
        return;
}

// pointer wapas start pe le ja
rewind(fp);
    // temporary variables user.txt file ko read karne k liye
    char name[50], contact[15], member_id[7], password[20];
    int found = 0; // check karne k liye file hai ki nai
    
    while(fscanf(fp, "%s %s %s %s", name, contact, member_id, password) != EOF) {
        if(strcmp(input_id, member_id) == 0 && strcmp(input_pass, password) == 0) {
            found = 1;
            printf("\nLogin Successful!! Welcome %s\n", name);
            printf("\n");
            break;
        }
    }
    // login menu jab user mil jaye uske baad appear hoga 
    int choice;
    if(found == 1) {
        while(1) {
            printf("1. Issue\n");
            printf("2. Return\n");
            printf("3. My Record\n");
            printf("4. Logout\n");

            printf("\n");
            printf("What would you like to do? ");
            scanf("%d", &choice);

            switch(choice) {
                case 1:
                viewBooks();
                issueBook(member_id);
                break;

                case 2:
                printf("\n");
                returnBook(member_id);
                break;

                case 3:
                printf("\n");
                myRecord(member_id);
                break;

                case 4:
                printf("\nLogged Out Successfully!! Happy Reading~~\n");
                return;

                default:
                printf("Invalid Choice\n");
                break;
            }
        } 
    }

    if(found == 0) {
        printf("Invalid Credentials! Please try again!!");
    }

    fclose(fp);
}

// books ka data joki system ka hai
void initializeBooks() {
    FILE *fp = fopen("../data/books.txt", "w");
    fprintf(fp, "B001 The_Alchemist 1\n");
    fprintf(fp, "B002 The_Midnight_Library 1\n");
    fprintf(fp, "B003 Namesake 1\n");
    fprintf(fp, "B004 Secret_History 1\n");
    fprintf(fp, "B005 Better_Than_The_Movies 1\n");
    fprintf(fp, "B006 Human_Acts 1\n");
    fprintf(fp, "B007 Welcome_To_The_Hyunam_Dong_Bookshop 1\n");
    fprintf(fp, "B008 The_Cat_Who_Saved_The_Library 1\n");
    fprintf(fp, "B009 The_Book_Theif 1\n");
    fprintf(fp, "B010 All_The_Light_We_Cannot_See 1\n");
    fprintf(fp, "B011 A_Novel_Love_Story 1\n");
    fprintf(fp, "B012 Kafka_On_The_Shore 1\n");
    fprintf(fp, "B013 The_Dead_Romantics 1\n");
    fprintf(fp, "B014 The_Colour_Purple 1\n");
    fprintf(fp, "B015 Tuesdays_With_Moorie 1\n");

    fclose(fp);
}

// books ko terminal pr print karne k liye
void viewBooks() {
    FILE *fp = fopen("../data/books.txt", "r");

    if (fp == NULL) {
        printf("No books available!\n");
        return;
    }

    struct books b;

    printf("\n                  AVAILABLE BOOKS                  \n");
    printf("%-10s %-35s %-10s\n", "ID", "Name", "Status");
    printf("------------------------------------------------------------\n");

    while (fscanf(fp, "%s %s %d", b.book_id, b.book_name, &b.available) != EOF) {

        printf("%-10s %-35s ", b.book_id, b.book_name);

        if (b.available == 1)
            printf("Available\n");
        else
            printf("Issued\n");
    }

    printf("\n");

    fclose(fp);
}

// issue karne time
void issueBook(char member_id[]) {
    char book_id[10];
    printf("Enter Book ID: ");
    scanf("%s", book_id);
    printf("\n");

    FILE *fp = fopen("../data/books.txt", "r");
    FILE *temp = fopen("../data/temp.txt", "w");

    if(fp == NULL || temp == NULL) {
        printf("Error opening file!");
        return;
    }

    struct books b;
    int found = 0;

    while(fscanf(fp, "%s %s %d", b.book_id, b.book_name, &b.available) != EOF) {
        
        // book match
        if(strcmp(b.book_id, book_id) == 0) {
            found = 1;
            // book match hone k baad availability check kar rahe
            if(b.available == 1) {
                printf("%s Book Issued\n", b.book_id);
                printf("--------------------\n");

                b.available = 0; // availability update

                // issued.txt mei entry
                FILE *issued = fopen("../data/issued.txt", "a");
                fprintf(issued, "%s %s\n", member_id, book_id);
                fclose(issued);
            } else {
                printf("Book Already Issued!!\n");
            }
        }

        // temp file mei likh rahe ab

        fprintf(temp, "%s %s %d\n", b.book_id, b.book_name, b.available);
    }
    fclose(fp);
    fclose(temp);

    // replace original file (books.txt)

    remove("../data/books.txt");
    rename("../data/temp.txt", "../data/books.txt");

    if(!found) {
        printf("Book Not Found!!");
    }
}

// return book 
void returnBook(char member_id[]) {
    char book_id[10];
    printf("Enter the Book ID to return: ");
    scanf("%s", book_id);

    FILE *issued = fopen("../data/issued.txt", "r");
    FILE *tempIssued = fopen("../data/tempIssued.txt", "w");

    if(issued == NULL || tempIssued == NULL) {
        printf("Error Opening Issued File!!\n");
        return;
    }

    struct returnBook r;
    int found = 0;

    // issued.txt check karenge pehle

    while(fscanf(issued, "%s %s", r.member_id, r.book_id) != EOF) {
        if(strcmp(r.member_id, member_id) == 0 && strcmp(r.book_id, book_id) == 0) {
            found = 1;
            continue; // entry delete ho jaega
        }

        fprintf(tempIssued, "%s %s\n", r.member_id, r.book_id);
    }

    fclose(issued);
    fclose(tempIssued);

    remove("../data/issued.txt");
    rename("../data/tempIssued.txt", "../data/issued.txt");

    if(!found) {
        printf("\n");
        printf("No such book Issued by You!\n");
        printf("\n");
        return;
    }

    // books.txt update hoga ab

    FILE *fp = fopen("../data/books.txt", "r");
    FILE *temp = fopen("../data/temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening books file!\n");
        return;
    }

    struct books b;

    while(fscanf(fp, "%s %s %d", b.book_id, b.book_name, &b.available) != EOF) {
        if(strcmp(b.book_id, book_id) == 0) {
            b.available = 1;
        }
        fprintf(temp, "%s %s %d\n", b.book_id, b.book_name, b.available);
    }

    fclose(fp);
    fclose(temp);

    remove("../data/books.txt");
    rename("../data/temp.txt", "../data/books.txt");

    printf("\n");
    printf("Book Returned Successfully!\n");
    printf("\n");
}

void myRecord(char member_id[]) {

    printf("\n");
    printf("    MY LITTLE LIBRARY\n");
    printf("  Your Cozy Little Corner\n");
    printf("\n");
    printf("       MEMBER CARD   \n");
    printf("\n");

    // getting member name
    FILE *user = fopen("../data/user.txt", "r");
    char name[50], contact[15], mem_id[11], pass[20];
    int userFound = 0;

    while (fscanf(user, "%s %s %s %s", name, contact, mem_id, pass) != EOF) {
        if (strcmp(mem_id, member_id) == 0) {
            printf("\nName      : %s\n", name);
            printf("Member ID : %s\n", member_id);
            userFound = 1;
            break;
        }
    }
    fclose(user);

    if (!userFound) {
        printf("User not found!\n");
        return;
    }

    // books issued data
    FILE *fp = fopen("../data/issued.txt", "r");

    if(fp == NULL) {
        printf("No records found!");
        return;
    }

    char m_id[11];
    char b_id[10];
    int found = 0;

    printf("\n~~Your Issued Books~~\n");
    printf("\n");

    while(fscanf(fp, "%s %s", m_id, b_id) != EOF) {

        if(strcmp(m_id, member_id) == 0) {
            printf("%s\n", b_id);
            found = 1;
        }

        
    }

    printf("\n");

    if(!found) {
        printf("\nNo books issued by you!\n");
        printf("\n");
    }

    fclose(fp);
}