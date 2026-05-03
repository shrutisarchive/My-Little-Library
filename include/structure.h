// Phase1
#ifndef STRUCTURE_H
#define STRUCTURE_H

// user data
struct user {
    char member_id[7];
    char name[50];
    char contact[15];
    char password[20];

};

// books data
struct books {
    char book_id[10];
    char book_name[50];
    int available; // availability of books show karne k liye 0/1 aur issue k baad update karne k liye
};

// issue/return data
struct returnBook {
    char member_id[11];
    char book_id[10];
};

void generateMemberID(char member_id[]);
void registerUser();
void initializeBooks();
void viewBooks();
void issueBook(char member_id[]);
void returnBook(char member_id[]);

#endif