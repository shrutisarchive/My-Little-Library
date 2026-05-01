// Phase2
#include<stdio.h>
#include <stdlib.h>
#include "../include/structure.h"
#include <string.h>
void generateMemberID(char member_id[]);
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
    printf("Enter your password: ");
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

            printf("What would you like to do? ");
            scanf("%d", &choice);

            switch(choice) {
                case 1:
                printf("BOOKS\n");
                break;

                case 2:
                printf("RETURN\n");
                break;

                case 3:
                printf("MY RECORD\n");
                break;

                case 4:
                printf("Logged Out Successfully!! Happy Reading~~\n");
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
