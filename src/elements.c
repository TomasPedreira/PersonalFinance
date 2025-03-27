#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"
#include "elements.h"


element create_button( 
    Vector2 start,
    size_t width, 
    size_t height, 
    Color color, 
    Color text_color, 
    char* text, 
    size_t font_size,
    void (*action)(char* txt)
){
    button b = malloc(sizeof(struct _Button));
    if (b == NULL){
        return NULL;
    }
    b->start = start;
    b->width = width;
    b->height = height;
    b->color = color;
    b->text_color = text_color;
    strcpy(b->text, text);
    b->hovering = false;
    b->clicked = false;
    b->font_size = font_size;
    b->text_pos = (Vector2){
        b->start.x + b->width/2 - MeasureText(b->text, b->font_size )/2, 
        b->start.y + b->height/2 - b->font_size/2
    };
    b->action = action;
    element e = malloc(sizeof(struct _element));
    if (e == NULL){
        free(b);
        return NULL;
    }
    e->tag = BTN;
    e->page = MAIN_PAGE;
    e->btn = b;
    e->visible = true;
    e->enabled = true;
    return e;

}

element create_input(
    Vector2 start,
    size_t width, 
    size_t height,
    Color color1,
    Color color2,
    char* text,
    char * placeholder,
    size_t font_size

){
    input_form i = malloc(sizeof(struct _Input));
    if (i == NULL){
        return NULL;
    }
    i->start = start;
    i->width = width;
    i->height = height;
    i->color1 = color1;
    i->color2 = color2;
    strcpy(i->placeholder, placeholder);
    i->changed = false;
    i->clicked = false;
    i->font_size = font_size;   
    element e = malloc(sizeof(struct _element));
    if (e == NULL){
        free(i);
        return NULL;
    }
    e->tag = IN;
    e->page = MAIN_PAGE;
    e->in = i;
    e->visible = true;
    e->enabled = true;
    return e;
}

element create_panel(
    Vector2 start,
    size_t width, 
    size_t height,
    Color color
){
    panel p = malloc(sizeof(struct _Panel));
    if (p == NULL){
        return NULL;
    }
    p->start = start;
    p->width = width;
    p->height = height;
    p->color = color;
    element e = malloc(sizeof(struct _element));
    if (e == NULL){
        free(p);
        return NULL;
    }
    e->tag = PNL;
    e->page = MAIN_PAGE;
    e->pnl = p;
    e->visible = true;
    e->enabled = true;
    return e;
}


void destroy_drop_down(drop_down dd){
    for (size_t i = 0; i < dd->num_buttons; i++){
        destroy_button(dd->buttons[i]);
    }
    free(dd->buttons);
    free(dd);
}

void destroy_button(button b){
    free(b);
}
void destroy_input(input_form in){
    free(in);
}
void destroy_panel(panel p){
    free(p);
}
