#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <string.h>

#include "app.h"
#include "elements.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCALING_FACTOR 200

#define MAX_EXPENSES 1024

void render(app a);
void input(app a);
void update(app a);

void render_page(page p);
void render_input(input_form in);

drop_down create_drop_down(Vector2 start, Vector2 sizes, Color color1, Color color2, char* text, size_t font_size, size_t button_padding, char** buttons_text, size_t num_buttons){
    drop_down dd = malloc(sizeof(struct _Drop_drown));
    printf("Creating drop down\n");
    if(dd == NULL){
        printf("Error creating drop down inside creation\n");
        return NULL;
    }
    dd->start = start;
    dd->width = sizes.x;
    dd->height = sizes.y;
    dd->color1 = color1;
    dd->color2 = color2;
    dd->selected = 0;
    size_t text_size = MeasureText(text, font_size);
    Vector2 text_pos = {start.x + sizes.x/2 - text_size/2, start.y + sizes.y/2 - font_size/2};
    dd->text = text;
    dd->hovering = false;
    dd->clicked = false;
    dd->button_padding = button_padding;
    dd->num_buttons = num_buttons;

    button* buttons;
    buttons = malloc(num_buttons*sizeof(button));
    printf("Creating buttons\n");
    if (buttons == NULL){
        printf("Error creating buttons inside creation\n");
        return NULL;
    }
    for (size_t i = 0; i < num_buttons; i++){
        button b = malloc(sizeof(struct _Button));
        printf("Creating button %zu\n", i);
        if (b == NULL){
            printf("Error creating button %zu\n", i);
            return NULL;
        }
        b->start = (Vector2){start.x+button_padding/2, start.y + button_padding/2};
        b->width = sizes.x - button_padding;
        b->height = sizes.y - button_padding;
        b->color = color2;
        b->text = buttons_text[i];
        b->text_color = RAYWHITE;
        text_size = MeasureText(b->text, font_size);
        b->text_pos = (Vector2){b->start.x + b->width/2 - text_size/2, b->start.y + b->height/2 - font_size/2};
        
        b->hovering = false;
        b->clicked = false;
        b->font_size = font_size;
        buttons[i] = b;
    }
    dd->buttons = buttons;
    return dd;
}


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Finance app");
    SetTargetFPS(60);
    SetExitKey(0);
    app a = create_app();

    if (a == NULL){
        printf("Error creating app\n");
        return 1;
    }

    while (!WindowShouldClose()) {
        input(a);
        update(a);
        render(a);
    }
    destroy_app(a);
    printf("Exiting\n");

    CloseWindow();


    return 0;
}

void render(app a){
    BeginDrawing();
        page p = get_current_page(a);
        render_page(p);
    EndDrawing();
}
void input(app a){
    page p = get_current_page(a);
    for (size_t i = 0; i < p->num_elements; i++){
        switch (p->elements[i]->tag)
        {
            case DD:
                drop_down dd = p->elements[i]->dd;
                if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){dd->start.x, dd->start.y, dd->width, dd->height})){
                    dd->hovering = true;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        dd->clicked = !dd->clicked;
                    }
                } else {
                    dd->hovering = false;
                }
                if (dd->clicked){
                    for (size_t j = 0; j < dd->num_buttons; j++){
                        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){dd->buttons[j]->start.x, dd->buttons[j]->start.y, dd->buttons[j]->width, dd->buttons[j]->height})){
                            dd->buttons[j]->hovering = true;
                            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                                dd->selected = j;
                                dd->clicked = false;
                            }
                        } else {
                            dd->buttons[j]->hovering = false;
                        }
                    }
                }
                break;
            case BTN:
                button b = p->elements[i]->btn;
                if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){b->start.x, b->start.y, b->width, b->height})){
                    b->hovering = true;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        b->clicked = true;
                        b->action(b->text);
                    }
                } else {
                    b->hovering = false;
                    b->clicked  = false;
                }
                break;
            case IN:
                input_form in = p->elements[i]->in;
                if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){in->start.x, in->start.y, in->width, in->height})){
                    in->clicked = true;
                } else {
                    in->clicked = false;
                }
                if (in->clicked){
                    if (IsKeyPressed(KEY_BACKSPACE)){
                        in->text[strlen(in->text)-1] = '\0';
                    } else {
                        char c = GetCharPressed();
                        if (c != 0 && strlen(in->text) < 1023){
                            in->text[strlen(in->text)] = c;
                            in->text[strlen(in->text)+1] = '\0';
                        }
                    }
                }
                break;
            default:
                break;
        }
    }
}
void update(app a){
    switch (get_current_page(a)->type)
    {
        case MAIN_PAGE:
            break;
        case GAME:
            break;
        case GAME_OVER:
            break;
    }
}
void render_button(button b, size_t offset){
    DrawRectangle(
        b->start.x,
        b->start.y + offset,
        b->width,
        b->height,
        b->color
    );
    DrawText(
        b->text,
        b->text_pos.x,
        b->text_pos.y + offset,
        b->font_size,
        b->text_color
    );
}
void render_drop_down(drop_down dd){

    if (dd->clicked){
        DrawRectangle(
            dd->start.x,
            dd->start.y,
            dd->width,
            dd->height + dd->num_buttons*dd->height + dd->button_padding/2,
            dd->color1
        );
        render_button(dd->buttons[dd->selected], 0);
        for (size_t i = 0; i < dd->num_buttons; i++){
            render_button(dd->buttons[i], (i+1) * dd->height + dd->button_padding/2);
        }
    } else {
        DrawRectangle(
            dd->start.x,
            dd->start.y,
            dd->width,
            dd->height,
            dd->color1
        );
        render_button(dd->buttons[dd->selected], 0);
    }
    
        
}


void render_page(page p){
    ClearBackground(p->color);
    for (size_t i = 0; i < p->num_elements; i++){
        switch (p->elements[i]->tag)
        {
            case DD:
                render_drop_down(p->elements[i]->dd);
                break;
            case BTN:
                render_button(p->elements[i]->btn, 0);
                break;
            case IN:
                render_input(p->elements[i]->in);
                break;
            default:
                break;
        }
    }
}
void render_input(input_form in){
    DrawRectangle(
        in->start.x,
        in->start.y,
        in->width,
        in->height,
        in->color1
    );
    DrawText(
        in->text,
        in->start.x + in->width/2 - MeasureText(in->text, in->font_size),
        in->start.y + in->height/2 - in->font_size/2,
        in->font_size,
        in->color2
    );
}