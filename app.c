
#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include "elements.h"
#include "app.h"



app create_app(){
    app a = malloc(sizeof(struct _app_sate));
    a->current_page = MAIN_PAGE;
    a->num_elements = 0;
    return a;
}
void destroy_app(app a){
    free(a);
}

void change_page(app a, ptype p){
    a->current_page = p;
}

ptype get_current_page(app a){
    return a->current_page;
}

void add_element(app a, element e){
    a->elements[a->num_elements] = e;
    a->num_elements++;
}

element get_element(app a, size_t i){
    return a->elements[i];
}


