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
    void (*action)(char* txt);
};

typedef struct _Drop_drown * drop_down;
struct _Drop_drown {
    Vector2 start;
    size_t width;
    size_t height;
    Color color1;
    Color color2;
    char* text;
    bool hovering;
    bool clicked;
    size_t selected;
    size_t button_padding;
    button* buttons;
    size_t num_buttons;
};

typedef struct _Input * input_form;
struct _Input {
    Vector2 start;
    size_t width;
    size_t height;
    Color color1;
    Color color2;
    char text[1024];
    size_t font_size;
    bool clicked;
};
typedef struct _Text_box * text_box;
struct _Text_box {
    Vector2 start;
    size_t width;
    size_t height;
    Color color1;
    Color color2;
    char text[1024];
    size_t font_size;
    bool clicked;
};

typedef enum {DD, BTN, GRID, IN} elem_tag;

typedef struct _element * element;

struct _element {
    elem_tag tag;
    ptype page;
    union {
        button btn;
        drop_down dd;
        input_form in;
    };
    bool visible;
    bool enabled;
};

typedef struct _Page * page;

struct _Page {
    ptype type;
    Color color;
    element* elements;
    size_t num_elements;
    size_t max_elements;
};


element create_button( 
    Vector2 start,
    size_t width, 
    size_t height, 
    Color color, 
    Color text_color, 
    char* text, 
    size_t font_size,
    void (*action)(char* txt)
);

element create_input(
    Vector2 start,
    size_t width, 
    size_t height,
    Color color1,
    Color color2,
    char* text,
    size_t font_size
);

#endif // __ELEMENTS_H__