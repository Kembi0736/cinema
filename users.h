#ifndef USERS_H
#define USERS_H

typedef struct User {
    char login[50];
    char password[50];
    char card_number[17];
    int favorites;
    int is_admin;
} User;

int validate_login(char* login);
int validate_password(char* password);
int validate_card_number(char* card_number);
int load_user(char* login, User* user);
int save_user(User* user);
int user_exists(char* login);
int registration(User* user);
int authentication(char* login, char* password, User* user);
void delete_favorites(char* login);
int count_users(char* filename);

#endif