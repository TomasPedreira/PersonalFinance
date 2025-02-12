#ifndef __ELEMENTS_H__
#define __ELEMENTS_H__

#include <raylib.h>
#include <raymath.h>

typedef struct _Button {
    Vector2 start;
    size_t width;
    size_t height;
    Color color;
    Color text_color;
    Vector2 text_pos;
    char* text;
    bool hovering;
    bool clicked;
    size_t font_size;
} button;

typedef struct _Drop_drown {
    Vector2 start;
    size_t width;
    size_t height;
    Color color1;
    Color color2;
    Vector2 text_pos;
    char* text;
    bool hovering;
    bool clicked;
    size_t font_size;
    button* buttons;
    size_t num_buttons;
} drop_down;

typedef enum {DD, BTN} elem_tag;

typedef struct _element {
    elem_tag tag;
    union {
        button btn;
        drop_down dd;
    };
} element;

#endif // __ELEMENTS_H__