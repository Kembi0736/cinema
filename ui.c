<<<<<<< HEAD
#include "ui.h"
#include "users.h"
#include "favorites.h"
#include "film.h"
#include <stdio.h>
#include <windows.h>

#define KNRM  "\x1b[0m"
#define KYLW  "\x1b[33m"
#define KBLK  "\x1B[90m"


void center_text(char* output, char* text, int width) {
    int len = strlen(text);
    
    if (len > width) {
        strncpy(output, text, width);
        output[width] = '\0';
        return;
    }

    int left = (width - len) / 2;
    int right = width - len - left;

    int pos = 0;
    for (int i = 0; i < left; i++) {
        output[pos++] = ' ';
    }
    for (int i = 0; i < len; i++) {
        output[pos++] = text[i];
    }
    for (int i = 0; i < right; i++) {
        output[pos++] = ' ';
    }
    output[pos] = '\0';
}

void login_screen() {
    int choice;

    while (1) {
        system("cls");
        printf("╔════════════════════════════════════╗\n");
        printf("║          КИНОТЕАТР - ВХОД          ║\n");
        printf("╚════════════════════════════════════╝\n\n");
        printf("1. Войти\n");
        printf("2. Регистрация\n");
        printf("3. Выход\n");
        printf("\nВыберите действие: ");

        if (scanf(" %d", &choice) != 1) {
            continue;
        }

        switch (choice) {
            case 1: {
                char login[20];
                char password[20];

                printf("\nВведите логин: ");
                scanf("%s", login);
                while(getchar() != '\n');
                printf("\nВведите пароль: ");
                scanf("%s", password);
                while(getchar() != '\n');

                if (authentication(login, password, &user)) {
                    printf("\nВход выполнен успешно!");
                    favorites = load_favorites(user.login);
                    main_menu();
                    return;
                }
                else {
                    printf("\nНеверный логин или пароль!");
                }
                break;
            }
            case 2:
                register_screen();
                break;
            case 3:
                return;
        }
    }
}

void register_screen() {
    User newUser;
    newUser.favorites = 0;
    newUser.is_admin = 0;

    system("cls");
    printf("╔════════════════════════════════════╗\n");
    printf("║            РЕГИСТРАЦИЯ             ║\n");
    printf("╚════════════════════════════════════╝\n\n");

    while (1) {
        printf("Логин (3-20 символов): ");
        scanf(" %s", newUser.login);
        if (!validate_login(newUser.login)) {
            printf("Некорректный логин!\n");
            continue;
        }
        if (user_exists(newUser.login)) {
            printf("Пользователь уже существует!\n");
            continue;
        }
        break;
    }

    while (1) {
        printf("Пароль (6-20 символов, буквы в разном регистре и цифры): ");
        scanf(" %s", newUser.password);
        if (!validate_password(newUser.password)) {
            printf("Некорректный пароль!\n");
            continue;
        }
        break;
    }

    while (1) {
        printf("Номер карты (16 цифр): ");
        scanf(" %s", newUser.card_number);
        if (!validate_card_number(newUser.card_number)) {
            printf("Некорректный номер карты!\n");
            continue;
        }
        break;
    }

    if (registration(&newUser)) {
        printf("\nРегистрация прошла успешно!\n");
    }
    else {
        printf("\nОшибка регистрации!\n");
    }
}

void main_menu() {
    int choice;

    while (1) {
        system("cls");
        printf("╔════════════════════════════════════╗\n");
        printf("║           ГЛАВНОЕ МЕНЮ             ║\n");
        printf("╚════════════════════════════════════╝\n\n");
        printf("Пользователь: %s %s\n\n", user.login, user.is_admin ? "(Администратор)" : "");
        printf("1. Каталог фильмов\n");
        printf("2. Избранное (%d)\n", user.favorites);
        printf("3. Личный кабинет\n");
        if(user.is_admin) {
            printf("4. Режим администратора\n");
        }
        printf("0. Выход\n");
        printf("\nВыберите действие: ");

        if (scanf(" %d", &choice) != 1) {
            continue;
        }

        switch (choice) {
            case 1:
                catalog_menu();
                break;
            case 2:
                favorites_menu();
                break;
            case 3:
                profile_menu();
                break;
            case 4:
                if (user.is_admin) {
                    admin_menu();
                }
                break;
            case 0:
                save_favorites(favorites, user.login);
                return;
        }
    }
}

void catalog_menu() {
    if (catalog == NULL) {
        printf("Каталог пуст!\n");
        return;
    }

    Film* current = catalog;
    int choice;

    while (1) {
        system("cls");
        printf("╔════════════════════════════════════╗\n");
        printf("║          КАТАЛОГ ФИЛЬМОВ           ║\n");
        printf("╚════════════════════════════════════╝\n\n");

        Film* left = current->prev;
        Film* right = current->next;

        char leftname[45], centername[45], rightname[45];

        center_text(leftname, left->name, 44);
        center_text(centername, current->name, 44);
        center_text(rightname, right->name, 44);

    printf("%s╔════════════════════════════════════════════╗%s  %s╔════════════════════════════════════════════╗%s  %s╔════════════════════════════════════════════╗%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s║                                            ║%s  %s║                                            ║%s  %s║                                            ║%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s║                                            ║%s  %s║                                            ║%s  %s║                                            ║%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s║                                            ║%s  %s║                                            ║%s  %s║                                            ║%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s║%s║%s  %s║%s║%s  %s║%s║%s\n", KBLK, leftname, KNRM, KYLW, centername, KNRM, KBLK, rightname, KNRM);
    printf("%s║                  ★ %4.1f ★                  ║%s  %s║                  ★ %4.1f ★                  ║%s  %s║                  ★ %4.1f ★                  ║%s\n", KBLK, left->rating, KNRM, KYLW, current->rating, KNRM, KBLK, right->rating, KNRM);
    printf("%s║                                            ║%s  %s║                                            ║%s  %s║                                            ║%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s║                                            ║%s  %s║                                            ║%s  %s║                                            ║%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s║                                            ║%s  %s║                                            ║%s  %s║                                            ║%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s╚════════════════════════════════════════════╝%s  %s╚════════════════════════════════════════════╝%s  %s╚════════════════════════════════════════════╝%s\n\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);

    printf("\n1. ← Влево\n");
    printf("2. → Вправо\n");
    printf("3. Подробнее о фильме\n");
    printf("4. Добавить в избранное\n");
    if(user.is_admin) {
        printf("5. Удалить фильм (Админ)\n");
    }
    printf("0. Назад\n");
    printf("\nВыберите действие: ");

    if (scanf(" %d", &choice) != 1) {
        continue;
    }

    switch (choice) {
        case 1:
            current = current->prev;
            break;
        case 2:
            current = current->next;
            break;
        case 3:
            view_film_details(current, 1);
            break;
        case 4:
            favorites = add_to_favorites(favorites, current);
            user.favorites++;
            save_user(&user);
            save_favorites(favorites, user.login);
            printf("Добавлено в избранное!\n");
            break;
        case 5:
            if (user.is_admin) {
                delete_film_admin(current);
                catalog = load_films("films.txt");
                current = catalog;
            }
            break;
        case 0:
            return;
        }
    }
}

void favorites_menu() {
    if (favorites == NULL) {
        printf("Список избранного пуст!\n");
        return;
    }

    Film* current = favorites;
    int choice;

    while (1) {
        system("cls");
        printf("╔════════════════════════════════════╗\n");
        printf("║             ИЗБРАННОЕ              ║\n");
        printf("╚════════════════════════════════════╝\n\n");

        Film* left = current->prev;
        Film* right = current->next;

    char leftname[45], centername[45], rightname[45];

    center_text(leftname, left->name, 44);
    center_text(centername, current->name, 44);
    center_text(rightname, right->name, 44);

    printf("%s╔════════════════════════════════════════════╗%s  %s╔════════════════════════════════════════════╗%s  %s╔════════════════════════════════════════════╗%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s║                                            ║%s  %s║                                            ║%s  %s║                                            ║%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s║                                            ║%s  %s║                                            ║%s  %s║                                            ║%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s║                                            ║%s  %s║                                            ║%s  %s║                                            ║%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s║%s║%s  %s║%s║%s  %s║%s║%s\n", KBLK, leftname, KNRM, KYLW, centername, KNRM, KBLK, rightname, KNRM);
    printf("%s║                  ★ %4.1f ★                  ║%s  %s║                  ★ %4.1f ★                  ║%s  %s║                  ★ %4.1f ★                  ║%s\n", KBLK, left->rating, KNRM, KYLW, current->rating, KNRM, KBLK, right->rating, KNRM);
    printf("%s║                                            ║%s  %s║                                            ║%s  %s║                                            ║%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s║                                            ║%s  %s║                                            ║%s  %s║                                            ║%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s║                                            ║%s  %s║                                            ║%s  %s║                                            ║%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s╚════════════════════════════════════════════╝%s  %s╚════════════════════════════════════════════╝%s  %s╚════════════════════════════════════════════╝%s\n\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);

    printf("\n1. ← Влево\n");
    printf("2. → Вправо\n");
    printf("3. Подробнее о фильме\n");
    printf("4. Удалить из избранного\n");
    printf("0. Назад\n");
    printf("\nВыберите действие: ");

    if(scanf(" %d", &choice) != 1) {
        continue;
    }

    switch(choice) {
        case 1:
            current = current->prev;
            break;
        case 2:
            current = current->next;
            break;
        case 3:
            view_film_details(current, 0);
            break;
        case 4: {
            char name[100];
            strcpy(name, current->name);
            if(current->next != current) {
                current = current->next;
            } else {
                current = NULL;
            }
            favorites = remove_from_favorites(favorites, name);
            user.favorites--;
            save_user(&user);
            save_favorites(favorites, user.login);
            printf("\nУдалено из избранного!");
            if(favorites == NULL) {
                return;
            }
            break;
        }
        case 0:
            return;
        }
    }
}

void view_film_details(Film* film, int is_catalog) {
    int choice;

    while (1) {
        system("cls");
        print_details(film);

        printf("\n1. Добавить в избранное\n");
        if(!is_catalog) {
            printf("2. Удалить из избранного\n");
        }
        if(user.is_admin && is_catalog) {
            printf("3. Удалить фильм (Админ)\n");
        }
        printf("0. Назад\n");
        printf("\nВыберите действие: ");
        
        if(scanf(" %d", &choice) != 1) {
            continue;
        }

        switch(choice) {
            case 1:
                favorites = add_to_favorites(favorites, film);
                user.favorites++;
                save_user(&user);
                save_favorites(favorites, user.login);
                printf("\nДобавлено в избранное!");
                break;
            case 2:
                if(!is_catalog) {
                    favorites = remove_from_favorites(favorites, film->name);
                    user.favorites--;
                    save_user(&user);
                    save_favorites(favorites, user.login);
                    printf("\nУдалено из избранного!");
                    return;
                }
                break;
            case 3:
                if(user.is_admin && is_catalog) {
                    delete_film_admin(film);
                    return;
                }
                break;
            case 0:
                return;
            }
    }
}

void profile_menu() {
    int choice;
    
    while (1) {
        system("cls");
        printf("╔════════════════════════════════════╗\n");
        printf("║           ЛИЧНЫЙ КАБИНЕТ           ║\n");
        printf("╚════════════════════════════════════╝\n\n");
        printf("Логин: %s\n", user.login);
        printf("Пароль: %s\n", user.password);
        printf("Номер карты: %s\n", user.card_number);
        printf("Избранных фильмов: %d\n", user.favorites);
        
        printf("\n1. Изменить пароль\n");
        printf("2. Изменить номер карты\n");
        printf("0. Назад\n");
        printf("\nВыберите действие: ");
        
        if (scanf(" %d", &choice) != 1) {
            continue;
        }
        
        switch (choice) {
            case 1: {
                char newPassword[20];
                printf("\nНовый пароль: ");
                scanf(" %s", newPassword);
                
                if (validate_password(newPassword)) {
                    strcpy(user.password, newPassword);
                    save_user(&user);
                    printf("\nПароль изменен!");
                } else {
                    printf("\nНекорректный пароль!");
                }
                break;
            }
            case 2: {
                char newCard[16];
                printf("\nНовый номер карты: ");
                scanf(" %s", newCard);
                
                if (validate_card_number(newCard)) {
                    strcpy(user.card_number, newCard);
                    save_user(&user);
                    printf("\nНомер карты изменен!");
                } 
                else {
                    printf("\nНекорректный номер карты!");
                }
                break;
            }
            case 0:
                return;
        }
    }
}

void admin_menu() {
    int choice;
    
    while(1) {
        system("cls");
        printf("╔════════════════════════════════════╗\n");
        printf("║        РЕЖИМ АДМИНИСТРАТОРА        ║\n");
        printf("╚════════════════════════════════════╝\n\n");
        printf("1. Добавить фильм в каталог\n");
        printf("2. Просмотр каталога (с удалением)\n");
        printf("0. Назад\n");
        printf("\nВыберите действие: ");
        
        if(scanf(" %d", &choice) != 1) {
            continue;
        }
        
        switch(choice) {
            case 1:
                add_film_admin();
                break;
            case 2:
                catalog_menu();
                break;
            case 0:
                return;
        }
    }
}

void add_film_admin() {
    system("cls");
    printf("╔════════════════════════════════════╗\n");
    printf("║         ДОБАВЛЕНИЕ ФИЛЬМА          ║\n");
    printf("╚════════════════════════════════════╝\n\n");
    
    char name[100];
    int year;
    char country[100];
    char genre[100];
    float rating;
    
    printf("Название: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    
    printf("Год: ");
    while(scanf(" %d", &year) != 1) {
        printf("Некорректный год! Введите снова: ");
    }
    
    printf("Страна: ");
    fgets(country, sizeof(country), stdin);
    country[strcspn(country, "\n")] = 0;
    
    printf("Жанр: ");
    fgets(genre, sizeof(genre), stdin);
    genre[strcspn(genre, "\n")] = 0;
    
    printf("Рейтинг (0.0-10.0): ");
    while(scanf(" %f", &rating) != 1) {
        printf("Некорректный рейтинг! Введите снова: ");
    }
    
    Film* newFilm = create_film(name, year, country, genre, rating);

    if(newFilm != NULL) {
        catalog = add_to_list(catalog, newFilm);
        save_films(catalog, "films.txt");
        printf("\nФильм добавлен в каталог!");
    }
    else {
        printf("\nОшибка добавления фильма!");
    }
}

void delete_film_admin(Film* film) {
    system("cls");
    printf("Удалить фильм '%s'? (1 - Да, 0 - Нет): ", film->name);
    
    int confirm;
    if(scanf("%d", &confirm) != 1) {
        return;
    }
    
    if(confirm == 1) {
        char name[100];
        strcpy(name, film->name);
        remove_from_all(name);
        catalog = remove_from_list(catalog, film);
        save_films(catalog, "films.txt");
        favorites = load_favorites(user.login);
        user.favorites--;
        save_user(&user);
        printf("\nФильм удален!");
    }
}
=======
#include "ui.h"
#include "users.h"
#include "favorites.h"
#include "film.h"
#include <stdio.h>
#include <windows.h>

#define KNRM  "\x1b[0m"
#define KYLW  "\x1b[33m"
#define KBLK  "\x1B[90m"


void center_text(char* output, char* text, int width) {
    int len = strlen(text);
    
    if (len > width) {
        strncpy(output, text, width);
        output[width] = '\0';
        return;
    }

    int left = (width - len) / 2;
    int right = width - len - left;

    int pos = 0;
    for (int i = 0; i < left; i++) {
        output[pos++] = ' ';
    }
    for (int i = 0; i < len; i++) {
        output[pos++] = text[i];
    }
    for (int i = 0; i < right; i++) {
        output[pos++] = ' ';
    }
    output[pos] = '\0';
}



void login_screen() {
    int choice;

    while (1) {
        system("cls");
        printf("╔════════════════════════════════════╗\n");
        printf("║          КИНОТЕАТР - ВХОД          ║\n");
        printf("╚════════════════════════════════════╝\n\n");
        printf("1. Войти\n");
        printf("2. Регистрация\n");
        printf("3. Выход\n");
        printf("\nВыберите действие: ");

        if (scanf(" %d", &choice) != 1) {
            continue;
        }

        switch (choice) {
            case 1: {
                char login[20];
                char password[20];

                printf("\nВведите логин: ");
                scanf("%s", login);
                while(getchar() != '\n');
                printf("\nВведите пароль: ");
                scanf("%s", password);
                while(getchar() != '\n');

                if (authentication(login, password, &user)) {
                    printf("\nВход выполнен успешно!");
                    favorites = load_favorites(user.login);
                    main_menu();
                    return;
                }
                else {
                    printf("\nНеверный логин или пароль!");
                }
                break;
            }
            case 2:
                register_screen();
                break;
            case 3:
                return;
        }
    }
}

void register_screen() {
    User newUser;
    newUser.favorites = 0;
    newUser.is_admin = 0;

    system("cls");
    printf("╔════════════════════════════════════╗\n");
    printf("║            РЕГИСТРАЦИЯ             ║\n");
    printf("╚════════════════════════════════════╝\n\n");

    while (1) {
        printf("Логин (3-20 символов): ");
        scanf(" %s", newUser.login);
        if (!validate_login(newUser.login)) {
            printf("Некорректный логин!\n");
            continue;
        }
        if (user_exists(newUser.login)) {
            printf("Пользователь уже существует!\n");
            continue;
        }
        break;
    }

    while (1) {
        printf("Пароль (6-20 символов, буквы в разном регистре и цифры): ");
        scanf(" %s", newUser.password);
        if (!validate_password(newUser.password)) {
            printf("Некорректный пароль!\n");
            continue;
        }
        break;
    }

    while (1) {
        printf("Номер карты (16 цифр): ");
        scanf(" %s", newUser.card_number);
        if (!validate_card_number(newUser.card_number)) {
            printf("Некорректный номер карты!\n");
            continue;
        }
        break;
    }

    if (registration(&newUser)) {
        printf("\nРегистрация прошла успешно!\n");
    }
    else {
        printf("\nОшибка регистрации!\n");
    }
}

void main_menu() {
    int choice;

    while (1) {
        system("cls");
        printf("╔════════════════════════════════════╗\n");
        printf("║           ГЛАВНОЕ МЕНЮ             ║\n");
        printf("╚════════════════════════════════════╝\n\n");
        printf("Пользователь: %s %s\n\n", user.login, user.is_admin ? "(Администратор)" : "");
        printf("1. Каталог фильмов\n");
        printf("2. Избранное (%d)\n", user.favorites);
        printf("3. Личный кабинет\n");
        if(user.is_admin) {
            printf("4. Режим администратора\n");
        }
        printf("0. Выход\n");
        printf("\nВыберите действие: ");

        if (scanf(" %d", &choice) != 1) {
            continue;
        }

        switch (choice) {
            case 1:
                catalog_menu();
                break;
            case 2:
                favorites_menu();
                break;
            case 3:
                profile_menu();
                break;
            case 4:
                if (user.is_admin) {
                    admin_menu();
                }
                break;
            case 0:
                save_favorites(favorites, user.login);
                return;
        }
    }
}

void catalog_menu() {
    if (catalog == NULL) {
        printf("Каталог пуст!\n");
        return;
    }

    Film* current = catalog;
    int choice;

    while (1) {
        system("cls");
        printf("╔════════════════════════════════════╗\n");
        printf("║          КАТАЛОГ ФИЛЬМОВ           ║\n");
        printf("╚════════════════════════════════════╝\n\n");

        Film* left = current->prev;
        Film* right = current->next;

        char leftname[45], centername[45], rightname[45];

        center_text(leftname, left->name, 44);
        center_text(centername, current->name, 44);
        center_text(rightname, right->name, 44);

    printf("%s╔════════════════════════════════════════════╗%s  %s╔════════════════════════════════════════════╗%s  %s╔════════════════════════════════════════════╗%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s║                                            ║%s  %s║                                            ║%s  %s║                                            ║%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s║                                            ║%s  %s║                                            ║%s  %s║                                            ║%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s║                                            ║%s  %s║                                            ║%s  %s║                                            ║%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s║%s║%s  %s║%s║%s  %s║%s║%s\n", KBLK, leftname, KNRM, KYLW, centername, KNRM, KBLK, rightname, KNRM);
    printf("%s║                  ★ %4.1f ★                  ║%s  %s║                  ★ %4.1f ★                  ║%s  %s║                  ★ %4.1f ★                  ║%s\n", KBLK, left->rating, KNRM, KYLW, current->rating, KNRM, KBLK, right->rating, KNRM);
    printf("%s║                                            ║%s  %s║                                            ║%s  %s║                                            ║%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s║                                            ║%s  %s║                                            ║%s  %s║                                            ║%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s║                                            ║%s  %s║                                            ║%s  %s║                                            ║%s\n", KBLK, KNRM, KYLW, KNRM, KBLK, KNRM);
    printf("%s╚════════════════════════════════════════════╝%s  %s╚════════════════════════════════════════════╝%s  %s╚════════════════════════════════════════════╝%s\n\n"), KBLK, KNRM, KYLW, KNRM, KBLK, KNRM;

    printf("\n1. ← Влево\n");
    printf("2. → Вправо\n");
    printf("3. Подробнее о фильме\n");
    printf("4. Добавить в избранное\n");
    if(user.is_admin) {
        printf("5. Удалить фильм (Админ)\n");
    }
    printf("0. Назад\n");
    printf("\nВыберите действие: ");

    if (scanf(" %d", &choice) != 1) {
        continue;
    }

    switch (choice) {
        case 1:
            current = current->prev;
            break;
        case 2:
            current = current->next;
            break;
        case 3:
            view_film_details(current, 1);
            break;
        case 4:
            favorites = add_to_favorites(favorites, current);
            user.favorites++;
            save_user(&user);
            save_favorites(favorites, user.login);
            printf("Добавлено в избранное!\n");
            break;
        case 5:
            if (user.is_admin) {
                delete_film_admin(current);
                catalog = load_films("films.txt");
                current = catalog;
            }
            break;
        case 0:
            return;
        }
    }
}

void favorites_menu() {
    if (favorites == NULL) {
        printf("Список избранного пуст!\n");
        return;
    }

    Film* current = favorites;
    int choice;

    while (1) {
        system("cls");
        printf("╔════════════════════════════════════╗\n");
        printf("║             ИЗБРАННОЕ              ║\n");
        printf("╚════════════════════════════════════╝\n\n");

        Film* left = current->prev;
        Film* right = current->next;

    printf("╔════════════════════════════════════════════╗  ╔════════════════════════════════════════════╗  ╔════════════════════════════════════════════╗\n");
    printf("║                                            ║  ║                                            ║  ║                                            ║\n");
    printf("║                                            ║  ║                                            ║  ║                                            ║\n");
    printf("║                                            ║  ║                                            ║  ║                                            ║\n");
    printf("║%44s║  ║%44s║  ║%44s║\n", left->name, current->name, right->name);
    printf("║                  ★ %2.1f ★                  ║  ║                  ★ %2.1f ★                  ║  ║                  ★ %2.1f ★                  ║\n", left->rating, current->rating, right->rating);
    printf("║                                            ║  ║                                            ║  ║                                            ║\n");
    printf("║                                            ║  ║                                            ║  ║                                            ║\n");
    printf("║                                            ║  ║                                            ║  ║                                            ║\n");
    printf("╚════════════════════════════════════════════╝  ╚════════════════════════════════════════════╝  ╚════════════════════════════════════════════╝\n\n");

    printf("\n1. ← Влево\n");
    printf("2. → Вправо\n");
    printf("3. Подробнее о фильме\n");
    printf("4. Удалить из избранного\n");
    printf("0. Назад\n");
    printf("\nВыберите действие: ");

    if(scanf(" %d", &choice) != 1) {
        continue;
    }

    switch(choice) {
        case 1:
            current = current->prev;
            break;
        case 2:
            current = current->next;
            break;
        case 3:
            view_film_details(current, 0);
            break;
        case 4: {
            char name[100];
            strcpy(name, current->name);
            if(current->next != current) {
                current = current->next;
            } else {
                current = NULL;
            }
            favorites = remove_from_favorites(favorites, name);
            user.favorites--;
            save_user(&user);
            save_favorites(favorites, user.login);
            printf("\nУдалено из избранного!");
            if(favorites == NULL) {
                return;
            }
            break;
        }
        case 0:
            return;
        }
    }
}

void view_film_details(Film* film, int is_catalog) {
    int choice;

    while (1) {
        system("cls");
        print_details(film);

        printf("\n1. Добавить в избранное\n");
        if(!is_catalog) {
            printf("2. Удалить из избранного\n");
        }
        if(user.is_admin && is_catalog) {
            printf("3. Удалить фильм (Админ)\n");
        }
        printf("0. Назад\n");
        printf("\nВыберите действие: ");
        
        if(scanf(" %d", &choice) != 1) {
            continue;
        }

        switch(choice) {
            case 1:
                favorites = add_to_favorites(favorites, film);
                user.favorites++;
                save_user(&user);
                save_favorites(favorites, user.login);
                printf("\nДобавлено в избранное!");
                break;
            case 2:
                if(!is_catalog) {
                    favorites = remove_from_favorites(favorites, film->name);
                    user.favorites--;
                    save_user(&user);
                    save_favorites(favorites, user.login);
                    printf("\nУдалено из избранного!");
                    return;
                }
                break;
            case 3:
                if(user.is_admin && is_catalog) {
                    delete_film_admin(film);
                    return;
                }
                break;
            case 0:
                return;
            }
    }
}

void profile_menu() {
    int choice;
    
    while (1) {
        system("cls");
        printf("╔════════════════════════════════════╗\n");
        printf("║           ЛИЧНЫЙ КАБИНЕТ           ║\n");
        printf("╚════════════════════════════════════╝\n\n");
        printf("Логин: %s\n", user.login);
        printf("Пароль: %s\n", user.password);
        printf("Номер карты: %s\n", user.card_number);
        printf("Избранных фильмов: %d\n", user.favorites);
        
        printf("\n1. Изменить пароль\n");
        printf("2. Изменить номер карты\n");
        printf("0. Назад\n");
        printf("\nВыберите действие: ");
        
        if (scanf(" %d", &choice) != 1) {
            continue;
        }
        
        switch (choice) {
            case 1: {
                char newPassword[20];
                printf("\nНовый пароль: ");
                scanf(" %s", newPassword);
                
                if (validate_password(newPassword)) {
                    strcpy(user.password, newPassword);
                    save_user(&user);
                    printf("\nПароль изменен!");
                } else {
                    printf("\nНекорректный пароль!");
                }
                break;
            }
            case 2: {
                char newCard[16];
                printf("\nНовый номер карты: ");
                scanf(" %s", newCard);
                
                if (validate_card_number(newCard)) {
                    strcpy(user.card_number, newCard);
                    save_user(&user);
                    printf("\nНомер карты изменен!");
                } 
                else {
                    printf("\nНекорректный номер карты!");
                }
                break;
            }
            case 0:
                return;
        }
    }
}

void admin_menu() {
    int choice;
    
    while(1) {
        system("cls");
        printf("╔════════════════════════════════════╗\n");
        printf("║        РЕЖИМ АДМИНИСТРАТОРА        ║\n");
        printf("╚════════════════════════════════════╝\n\n");
        printf("1. Добавить фильм в каталог\n");
        printf("2. Просмотр каталога (с удалением)\n");
        printf("0. Назад\n");
        printf("\nВыберите действие: ");
        
        if(scanf(" %d", &choice) != 1) {
            continue;
        }
        
        switch(choice) {
            case 1:
                add_film_admin();
                break;
            case 2:
                catalog_menu();
                break;
            case 0:
                return;
        }
    }
}

void add_film_admin() {
    system("cls");
    printf("╔════════════════════════════════════╗\n");
    printf("║         ДОБАВЛЕНИЕ ФИЛЬМА          ║\n");
    printf("╚════════════════════════════════════╝\n\n");
    
    char name[100];
    int year;
    char country[100];
    char genre[100];
    float rating;
    
    printf("Название: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    
    printf("Год: ");
    while(scanf(" %d", &year) != 1) {
        printf("Некорректный год! Введите снова: ");
    }
    
    printf("Страна: ");
    fgets(country, sizeof(country), stdin);
    country[strcspn(country, "\n")] = 0;
    
    printf("Жанр: ");
    fgets(genre, sizeof(genre), stdin);
    genre[strcspn(genre, "\n")] = 0;
    
    printf("Рейтинг (0.0-10.0): ");
    while(scanf(" %f", &rating) != 1) {
        printf("Некорректный рейтинг! Введите снова: ");
    }
    
    Film* newFilm = create_film(name, year, country, genre, rating);

    if(newFilm != NULL) {
        catalog = add_to_list(catalog, newFilm);
        save_films(catalog, "films.txt");
        printf("\nФильм добавлен в каталог!");
    }
    else {
        printf("\nОшибка добавления фильма!");
    }
}

void delete_film_admin(Film* film) {
    system("cls");
    printf("Удалить фильм '%s'? (1 - Да, 0 - Нет): ", film->name);
    
    int confirm;
    if(scanf("%d", &confirm) != 1) {
        return;
    }
    
    if(confirm == 1) {
        char name[100];
        strcpy(name, film->name);
        remove_from_all(name);
        catalog = remove_from_list(catalog, film);
        save_films(catalog, "films.txt");
        favorites = load_favorites(user.login);
        user.favorites--;
        save_user(&user);
        printf("\nФильм удален!");
    }
}
>>>>>>> 936af0ee4e36cd8848f7c8a7a4ed5c483099b080
