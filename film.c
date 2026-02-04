#include "film.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Film* create_film(char* name, int year, char* country, char* genre, float rating) {
    Film* film = (Film*)malloc(sizeof(Film));
    if (film == NULL) {
        return NULL;
    }

    strncpy(film->name, name, sizeof(film->name) - 1);
    film->name[sizeof(film->name) - 1] = '\0';
    
    film->year = year;
    
    strncpy(film->country, country, sizeof(film->country) - 1);
    film->country[sizeof(film->country) - 1] = '\0';
    
    strncpy(film->genre, genre, sizeof(film->genre) - 1);
    film->genre[sizeof(film->genre) - 1] = '\0';
    
    film->rating = rating;
    film->next = film;
    film->prev = film;

    return film;
}

Film* load_films(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка: не могу открыть файл %s\n", filename);
        return NULL;
    }

    Film* head = NULL;
    char name[100];
    int year;
    char country[100];
    char genre[100];
    float rating;
    char buffer[100];

    while (1) {
        // Читаем название
        if (fgets(name, sizeof(name), file) == NULL) {
            break; // Конец файла
        }
        name[strcspn(name, "\n")] = '\0';
        
        // Пропускаем пустые строки
        if (strlen(name) == 0) {
            continue;
        }

        // Читаем год
        if (fscanf(file, "%d", &year) != 1) {
            break;
        }
        fgets(buffer, sizeof(buffer), file); // Считываем оставшуюся часть строки

        // Читаем страну
        if (fgets(country, sizeof(country), file) == NULL) {
            break;
        }
        country[strcspn(country, "\n")] = '\0';

        // Читаем жанр
        if (fgets(genre, sizeof(genre), file) == NULL) {
            break;
        }
        genre[strcspn(genre, "\n")] = '\0';

        // Читаем рейтинг
        if (fscanf(file, "%f", &rating) != 1) {
            break;
        }
        fgets(buffer, sizeof(buffer), file); // Считываем оставшуюся часть строки

        printf("Загружаю фильм: %s\n", name); // Отладочный вывод
        
        Film* newFilm = create_film(name, year, country, genre, rating);
        if (newFilm != NULL) {
            head = add_to_list(head, newFilm);
        }
    }

    fclose(file);
    printf("Загружено фильмов: %d\n", count_films(head)); // Отладочный вывод
    return head;
}

Film* add_to_list(Film* head, Film* film) {
    if (head == NULL) {
        film->next = film;
        film->prev = film;

        return film;
    }

    Film* tail = head->prev;
    film->next = head;
    film->prev = tail;
    tail->next = film;
    head->prev = film;

    return head;
}

Film* remove_from_list(Film* head, Film* film) {
    if (head->next == head) {
        free(film);
        return NULL;
    }

    Film* prev = film->prev;
    Film* next = film->next;
    prev->next = next;
    next->prev = prev;

    Film* newHead = film == head ? next : head;

    free(film);
    return newHead;
}

Film* find_film(Film* head, char* name) {
    Film* temp = head;

    if (strcmp(temp->name, name) == 0) {
        return temp;
    }
    temp = temp->next;

    while (temp != head) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

void save_films(Film* head, char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return;
    }

    Film* temp = head;
    do {
        fprintf(file, "%s\n", temp->name);
        fprintf(file, "%d\n", temp->year);
        fprintf(file, "%s\n", temp->country);
        fprintf(file, "%s\n", temp->genre);
        fprintf(file, "%f\n", temp->rating);
        temp = temp->next;
    } while (temp != head);

    fclose(file);
}

void free_list(Film* head) {
    Film* temp = head;
    Film* next = NULL;

    do {
        next = temp->next;
        free(temp);
        temp = next;
    } while (temp != head);
}

int count_films(Film* head) {
    if (head == NULL) {
        return 0;
    }

    int count = 0;
    Film* temp = head;

    do {
        count++;
        temp = temp->next;
    } while (temp != head);

    return count;
}

void print_details(Film* film) {
    printf("\nПодробная информация\n");
    printf("Название: %s\n", film->name);
    printf("Год: %d\n", film->year);
    printf("Страна: %s\n", film->country);
    printf("Жанр: %s\n", film->genre);
    printf("Рейтинг: %f\n", film->rating);
}