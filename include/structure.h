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
    int book_id;
    char book_name[50];
    int available; // availability of books show karne k liye 0/1
};

// issue/return data
struct issue {
    char member_id[11];
    int book_id;
    int status; // return status update karne k liye
};

#endif