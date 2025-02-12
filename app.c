
#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include "app.h"

struct _app_sate {
    ptype current_page;
};



app create_app(){
    app a = malloc(sizeof(struct _app_sate));
    a->current_page = MAIN_PAGE;
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



