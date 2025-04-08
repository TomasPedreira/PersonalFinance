
#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include "config.h"
#include "elements.h"
#include "app.h"




void onClickPrint(char* text){
    printf("Button pressed: %s\n",  text);
}

page create_main_page(){
    const size_t max_elements = 16;
    page p = malloc(sizeof(struct _Page));
    if (p == NULL){
        return NULL;
    }
    p->type = MAIN_PAGE;
    p->elements = malloc(max_elements*sizeof(element));
    if (p->elements == NULL){
        free(p);
        return NULL;
    }
    p->num_elements = 0;
    p->color = WHITE;    
    
    // task creation panelanel 
    p->elements[p->num_elements++] = create_panel(
        MAIN_PAGE_LEFT_PANEL_START,
        MAIN_PAGE_LEFT_PANEL_WIDTH,
        MAIN_PAGE_LEFT_PANEL_HEIGHT,
        MAIN_PAGE_LEFT_PANEL_COLOR
    );
    p->elements[p->num_elements++] = create_panel(
        MAIN_PAGE_RIGHT_PANEL_START,
        MAIN_PAGE_RIGHT_PANEL_WIDTH,
        MAIN_PAGE_RIGHT_PANEL_HEIGHT,
        MAIN_PAGE_RIGHT_PANEL_COLOR
    );
    p->elements[p->num_elements++] = create_button(
        MAIN_PAGE_ADD_TASK_BUTTON_START,
        MAIN_PAGE_ADD_TASK_BUTTON_WIDTH,
        MAIN_PAGE_ADD_TASK_BUTTON_HEIGHT,
        MAIN_PAGE_ADD_TASK_BUTTON_COLOR,
        WHITE,
        "Add Task",
        20,
        onClickPrint
    );
    p->elements[p->num_elements++] = create_input(
        MAIN_PAGE_TITLE_BOX_START,
        MAIN_PAGE_TITLE_BOX_WIDTH,
        MAIN_PAGE_TITLE_BOX_HEIGHT,
        MAIN_PAGE_TITLE_BOX_COLOR1,
        MAIN_PAGE_TITLE_BOX_COLOR2,
        "Title",
        "Title",
        20
    );
    p->elements[p->num_elements++] = create_input(
        MAIN_PAGE_DATE_BOX_START,
        MAIN_PAGE_DATE_BOX_WIDTH,
        MAIN_PAGE_DATE_BOX_HEIGHT,
        MAIN_PAGE_DATE_BOX_COLOR1,
        MAIN_PAGE_DATE_BOX_COLOR2,
        "Date",
        "Date",
        20
    );
    p->elements[p->num_elements++] = create_text_box(
        MAIN_PAGE_DESCRIPTION_BOX_START,
        MAIN_PAGE_DESCRIPTION_BOX_WIDTH,
        MAIN_PAGE_DESCRIPTION_BOX_HEIGHT,
        MAIN_PAGE_DESCRIPTION_BOX_COLOR1,
        MAIN_PAGE_DESCRIPTION_BOX_COLOR2,
        "This description might be the worst placeholder that has ever been written in the history of mankind, and therefore might be the biggest mistake ive ever made.",
        20
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

