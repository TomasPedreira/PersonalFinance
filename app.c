
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

void onClickMae(page cur_p){
    for (size_t i=0; i<cur_p->num_elements; i++){
        switch (cur_p->elements[i]->tag)
        {
            case BTN:
                free(cur_p->elements[i]->btn);
                break;
            case DD:
                free(cur_p->elements[i]->dd);
                break;
            case GRID:
                break;
            case IN:
                if (!strcmp(cur_p->elements[i]->in->text, "AVISO ENVIADO")){
                    printf("Aviso enviado\n");
                    return;
                }
            default:
                break;
        }
        
    }
    element in = create_input(
        (Vector2){SCREEN_WIDTH/2 - 200/2, 0},
        200,
        50,
        BLUE,
        BLACK,
        "AVISO ENVIADO",
        20
    );
    cur_p->elements[cur_p->num_elements] = in;
    cur_p->num_elements++;
    

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
    p->elements[p->num_elements] = create_button(
        (Vector2){SCREEN_WIDTH/2 - 200/2, SCREEN_HEIGHT/2 - 100/2},
        200,
        50,
        BLUE,
        BLACK,
        "MAE",
        20,
        onClickPrint
    );
    p->num_elements++;
    p->elements[p->num_elements] = create_button(
        (Vector2){SCREEN_WIDTH/2 - 200/2, SCREEN_HEIGHT/2 - 400/2},
        200,
        50,
        BLUE,
        BLACK,
        "TOMAS",
        20,
        onClickPrint
    );
    p->num_elements++;
    element in = create_input(
        (Vector2){SCREEN_WIDTH/2 - 200/2, 0},
        200,
        50,
        BLUE,
        BLACK,
        "AVISO ENVIADO",
        20
    );
    p->elements[p->num_elements] = in;
    p->num_elements++;
    p->elements[p->num_elements-1]->visible = false;
    p->elements[p->num_elements-1]->enabled = false;

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
                    free(a->pages[i]->elements[j]->btn);
                    break;
                case DD:
                    free(a->pages[i]->elements[j]->dd);
                    break;
                case GRID:
                    break;
                case IN:
                    free(a->pages[i]->elements[j]->in);
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

