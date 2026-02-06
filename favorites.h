<<<<<<< HEAD
#ifndef FAVORITES_H
#define FAVORITES_H

#include "film.h"

Film* load_favorites(char* login);
Film* add_to_favorites(Film* head, Film* film);
Film* remove_from_favorites(Film* head, char* name);
int is_favorite(Film* head, char* name);
void save_favorites(Film* head, char* login);
void remove_from_all(char* name);

=======
#ifndef FAVORITES_H
#define FAVORITES_H

#include "film.h"

Film* load_favorites(char* login);
Film* add_to_favorites(Film* head, Film* film);
Film* remove_from_favorites(Film* head, char* name);
int is_favorite(Film* head, char* name);
void save_favorites(Film* head, char* login);
void remove_from_all(char* name);

>>>>>>> 936af0ee4e36cd8848f7c8a7a4ed5c483099b080
#endif