#include "favorites.h"
#include "film.h"
#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Film* load_favorites(char* login) {
    char filename[100];
    sprintf(filename, "favorites_%s.txt", login);

    return load_films(filename);
}

int is_favorite(Film* head, char* name) {
    return find_film(head, name) != NULL;
}

Film* add_to_favorites(Film* head, Film* film) {
    if (is_favorite(head, film->name)) {
        return head;
    }

    Film* newFilm = create_film(film->name, film->year, film->country, film->genre, film->rating);

    return add_to_list(head, newFilm);
}

Film* remove_from_favorites(Film* head, char* name) {
    Film* film = find_film(head, name);

    if (film != NULL) {
        return remove_from_list(head, film);
    }

    return head;
}

void save_favorites(Film* head, char* login) {
    char filename[100];
    sprintf(filename, "favorites_%s.txt", login);

    if (head == NULL) {
        remove(filename);
        return;
    }

    save_films(head, filename);
}

void remove_from_all(char* name) {
    FILE* file = fopen("users.txt", "r");
    if (file == NULL) {
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        User temp;

        if (sscanf(line, "%s %s %s %d %d", temp.login, temp.password, temp.card_number, &temp.favorites, &temp.is_admin) == 5) {
            Film* head = load_favorites(temp.login);

            if (head != NULL) {
                head = remove_from_favorites(head, name);
                save_favorites(head, temp.login);
                temp.favorites = count_films(head);
                save_user(&temp);
                free_list(head);
            }
        }
    }
    
    fclose(file);
}