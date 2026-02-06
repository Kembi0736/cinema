<<<<<<< HEAD
#ifndef UI_H
#define UI_H

#include "film.h"
#include "users.h"

extern User user;
extern Film* catalog;
extern Film* favorites;

void main_menu();
void catalog_menu();
void favorites_menu();
void profile_menu();
void admin_menu();
void login_screen();
void register_screen();
void view_film_details(Film* film, int is_catalog);
void add_film_admin();
void delete_film_admin(Film* film);
void center_text(char* output, char* text, int width);

=======
#ifndef UI_H
#define UI_H

#include "film.h"
#include "users.h"

extern User user;
extern Film* catalog;
extern Film* favorites;

void main_menu();
void catalog_menu();
void favorites_menu();
void profile_menu();
void admin_menu();
void login_screen();
void register_screen();
void view_film_details(Film* film, int is_catalog);
void add_film_admin();
void delete_film_admin(Film* film);
void center_text(char* output, char* text, int width);

>>>>>>> 936af0ee4e36cd8848f7c8a7a4ed5c483099b080
#endif