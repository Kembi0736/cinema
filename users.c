<<<<<<< HEAD
#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>


int validate_login(char* login){
    int len = strlen(login);

    if (len < 3 || len > 20) {
        return 0;
    }

    for (int i = 0; i < len; i++) {
        if (!isalnum(login[i])) {
            return 0;
        }
    }

    return 1;
}

int validate_password(char* password) {
    int len = strlen(password);

    if (len < 6 || len > 20) {
        return 0;
    }

    int has_upper = 0, has_lower = 0, has_digit = 0;

    for (int i = 0; i < len; i++) {
        if (!isalnum(password[i])) {
            return 0;
        }
        if (isupper(password[i])) {
            has_upper = 1;
        }
        if (islower(password[i])) {
            has_lower = 1;
        }
        if (isdigit(password[i])) {
            has_digit = 1;
        }
    }

    return has_upper && has_lower && has_digit;
}

int validate_card_number(char* card_number) {
    if (strlen(card_number) != 16) {
        return 0;
    }

    for (int i = 0; i < 16; i++) {
        if (!isdigit(card_number[i])) {
            return 0;
        }
    }

    return 1;
}

int load_user(char* login, User* user) {
    FILE* file = fopen("users.txt", "r");
    if (file == NULL) {
        return 0;
    }

    char line[100];
    while(fgets(line, sizeof(line), file)) {
        User temp;
        // line[strcspn(line, "\n")] = 0;

        if (sscanf(line, "%s %s %s %d %d", temp.login, temp.password, temp.card_number, &temp.favorites, &temp.is_admin) == 5) {
            if (strcmp(temp.login, login) == 0) {
                *user = temp;
                fclose(file);

                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}

int save_user(User* user) {
    FILE* file = fopen("users.txt", "r");
    FILE* tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        return 0;
    }

    int flag = 0;
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        User temp;

        if (sscanf(line, "%s %s %s %d %d", temp.login, temp.password, temp.card_number, &temp.favorites, &temp.is_admin) == 5) {
            if (strcmp(temp.login, user->login) == 0) {
                fprintf(tempFile, "%s %s %s %d %d\n", user->login, user->password, user->card_number, user->favorites, user->is_admin);
                flag = 1;
            }
            else {
                fprintf(tempFile, "%s", line);
            }
        }
    }
    fclose(file);

    if (!flag) {
        fprintf(tempFile, "%s %s %s %d %d\n", user->login, user->password, user->card_number, user->favorites, user->is_admin);
    }

    fclose(tempFile);
    remove("users.txt");
    rename("temp.txt", "users.txt");

    return 1;
}

int user_exists(char* login) {
    User temp;
    return load_user(login, &temp);
}

int registration(User* user) {
    if (user_exists(user->login)) {
        return 0;
    }

    FILE* file = fopen("users.txt", "a");
    if (file == NULL) {
        return 0;
    }

    fprintf(file, "\n%s %s %s %d %d\n", user->login, user->password, user->card_number, user->favorites, user->is_admin);
    fclose(file);

    return 1;
}

int authentication(char* login, char* password, User* user) {
    if (!load_user(login, user)) {
        return 0;
    }

    if ( strcmp(user->password, password) == 0) {
        return 1;
    }

    return 0;
}

void delete_favorites(char* login) {
    char filename[100];
    sprintf(filename, "favorites_%s.txt", login);
    remove(filename);
}

int count_users(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    int count = 0;
    char buffer[256];    
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
    }
    
    fclose(file);
    return count;
=======
#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>


int validate_login(char* login){
    int len = strlen(login);

    if (len < 3 || len > 20) {
        return 0;
    }

    for (int i = 0; i < len; i++) {
        if (!isalnum(login[i])) {
            return 0;
        }
    }

    return 1;
}

int validate_password(char* password) {
    int len = strlen(password);

    if (len < 6 || len > 20) {
        return 0;
    }

    int has_upper = 0, has_lower = 0, has_digit = 0;

    for (int i = 0; i < len; i++) {
        if (!isalnum(password[i])) {
            return 0;
        }
        if (isupper(password[i])) {
            has_upper = 1;
        }
        if (islower(password[i])) {
            has_lower = 1;
        }
        if (isdigit(password[i])) {
            has_digit = 1;
        }
    }

    return has_upper && has_lower && has_digit;
}

int validate_card_number(char* card_number) {
    if (strlen(card_number) != 16) {
        return 0;
    }

    for (int i = 0; i < 16; i++) {
        if (!isdigit(card_number[i])) {
            return 0;
        }
    }

    return 1;
}

int load_user(char* login, User* user) {
    FILE* file = fopen("users.txt", "r");
    if (file == NULL) {
        return 0;
    }

    char line[100];
    while(fgets(line, sizeof(line), file)) {
        User temp;
        // line[strcspn(line, "\n")] = 0;

        if (sscanf(line, "%s %s %s %d %d", temp.login, temp.password, temp.card_number, &temp.favorites, &temp.is_admin) == 5) {
            if (strcmp(temp.login, login) == 0) {
                *user = temp;
                fclose(file);

                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}

int save_user(User* user) {
    FILE* file = fopen("users.txt", "r");
    FILE* tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        return 0;
    }

    int flag = 0;
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        User temp;

        if (sscanf(line, "%s %s %s %d %d", temp.login, temp.password, temp.card_number, &temp.favorites, &temp.is_admin) == 5) {
            if (strcmp(temp.login, user->login) == 0) {
                fprintf(tempFile, "%s %s %s %d %d\n", user->login, user->password, user->card_number, user->favorites, user->is_admin);
                flag = 1;
            }
            else {
                fprintf(tempFile, "%s", line);
            }
        }
    }
    fclose(file);

    if (!flag) {
        fprintf(tempFile, "%s %s %s %d %d\n", user->login, user->password, user->card_number, user->favorites, user->is_admin);
    }

    fclose(tempFile);
    remove("users.txt");
    rename("temp.txt", "users.txt");

    return 1;
}

int user_exists(char* login) {
    User temp;
    return load_user(login, &temp);
}

int registration(User* user) {
    if (user_exists(user->login)) {
        return 0;
    }

    FILE* file = fopen("users.txt", "a");
    if (file == NULL) {
        return 0;
    }

    fprintf(file, "%s %s %s %d %d\n", user->login, user->password, user->card_number, user->favorites, user->is_admin);
    fclose(file);

    return 1;
}

int authentication(char* login, char* password, User* user) {
    if (!load_user(login, user)) {
        return 0;
    }

    if ( strcmp(user->password, password) == 0) {
        return 1;
    }

    return 0;
}

void delete_favorites(char* login) {
    char filename[100];
    sprintf(filename, "favorites_%s.txt", login);
    remove(filename);
}

int count_users(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    int count = 0;
    char buffer[256];    
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
    }
    
    fclose(file);
    return count;
>>>>>>> 936af0ee4e36cd8848f7c8a7a4ed5c483099b080
}