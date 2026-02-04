#ifndef FILM_H
#define FILM_H

#include <stdio.h>

typedef struct Film {
    char name[100];
    int year;
    char country[100];
    char genre[100];
    float rating;

    struct Film* next;
    struct Film* prev;
} Film;

Film* create_film(char* name, int year, char* country, char* genre, float rating);
Film* load_films(char* filename);
Film* add_to_list(Film* head, Film* film);
Film* remove_from_list(Film* head, Film* film);
Film* find_film(Film* head, char* name);
void save_films(Film* head, char* filename);
void free_list(Film* head);
int count_films(Film* head);
void print_details(Film* film);

#endif