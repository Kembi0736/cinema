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
}