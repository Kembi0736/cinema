<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "film.h"
#include "users.h"
#include "favorites.h"
#include "ui.h"


User user;
Film* catalog = NULL;
Film* favorites = NULL;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    catalog = load_films("films.txt");
    login_screen();
    
    free_list(catalog);
    if (favorites != NULL) {
        free_list(favorites);
    }
    
    return 0;
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "film.h"
#include "users.h"
#include "favorites.h"
#include "ui.h"


User user;
Film* catalog = NULL;
Film* favorites = NULL;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    catalog = load_films("films.txt");
    login_screen();
    
    free_list(catalog);
    if (favorites != NULL) {
        free_list(favorites);
    }
    
    return 0;
>>>>>>> 936af0ee4e36cd8848f7c8a7a4ed5c483099b080
}