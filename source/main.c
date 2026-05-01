// Phase1
#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../include/structure.h"
void registerUser();
void loginUser();

int choice;
int main() {
    srand(time(0));
    while(1) {
        printf("\nWelcome To My Little Library\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");

        printf("What would you like to do? ");
        scanf("%d", &choice);
        printf("\n");

        switch(choice) {
        case 1:
        printf("Login to My Little Library\n"); 
        printf(" Your Cozy Little Corner! \n");
        loginUser();
        break;
        
        case 2:
        printf("Register to My Little Library\n");
        registerUser();
        break;

        case 3:
        printf("See You Again! Happy Reading!!\n");
        return 0;

        default:
        printf("Opps! Choice not found!! Please try again\n");
        break;
    }
    }
}