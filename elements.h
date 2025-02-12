#ifndef __ELEMENTS_H__
#define __ELEMENTS_H__

#include <raylib.h>
#include <raymath.h>

typedef enum page_type ptype;
enum page_type {MAIN_PAGE, GAME, GAME_OVER};
typedef struct _Button * button;
struct _Button {
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
};

typedef struct _Drop_drown * drop_down;
struct _Drop_drown {
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
    size_t button_padding;
    button* buttons;
    size_t num_buttons;
};

typedef enum {DD, BTN, GRID} elem_tag;

typedef struct _element * element;

struct _element {
    elem_tag tag;
    ptype page;
    union {
        button btn;
        drop_down dd;
    };
};
#endif // __ELEMENTS_H__