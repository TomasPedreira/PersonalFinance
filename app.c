
#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include "elements.h"
#include "app.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCALING_FACTOR 200

void onClickPrint(char* text){
    printf("%s\n",  text);
}

page create_main_page(){
    const size_t max_pages = 10;
    page p = malloc(sizeof(struct _Page));
    if (p == NULL){
        return NULL;
    }
    p->type = MAIN_PAGE;
    p->elements = malloc(max_pages*sizeof(element));
    if (p->elements == NULL){
        free(p);
        return NULL;
    }
    p->num_elements = 0;
    p->color = WHITE;    
    
    // task creation panelanel 
    p->elements[p->num_elements++] = create_panel(
        (Vector2){0,0},
        SCREEN_WIDTH*0.2,
        SCREEN_HEIGHT,
        (Color){24,28,79,255}
        );

    

    return p;
}
app create_app(){
    app a = malloc(sizeof(struct _app_sate));
    a->current_page = MAIN_PAGE;
    page p = create_main_page();
    a->pages[0] = p;
    a->num_pages = 1;
    a->width = SCREEN_WIDTH;
    a->height = SCREEN_HEIGHT;
    return a;
}
void destroy_app(app a){
    for (size_t i; i< a->num_pages; i++){
        for (size_t j = 0; j < a->pages[i]->num_elements; j++){
            switch (a->pages[i]->elements[j]->tag)
            {
                case BTN:
                    destroy_button(a->pages[i]->elements[j]->btn);
                    break;
                case DD:
                    destroy_drop_down(a->pages[i]->elements[j]->dd);
                    break;
                case PNL:
                    destroy_panel(a->pages[i]->elements[j]->pnl);
                    break;
                case IN:
                    destroy_input(a->pages[i]->elements[j]->in);
                    break;
                default:
                    break;
            }
            free(a->pages[i]->elements[j]);

        }
        free(a->pages[i]->elements);
        free(a->pages[i]);

    }
    free(a);
}

void change_page(app a, ptype p){
    a->current_page = p;
}

page get_current_page(app a){
    return a->pages[a->current_page];
}

