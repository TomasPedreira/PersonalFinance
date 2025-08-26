#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include "config.h"
#include "app.h"
#include "elements.h"

void run_headless(int argc, char *argv[]);
void run_gui();



void render(app a);
void input(app a);
void update(app a);

void render_page(page p);
void render_panel(panel pnl);
void render_input(input_form in);
void render_text_box(text_box tb);

void render_button(button b, size_t offset);
void render_drop_down(drop_down dd);


void resize_element(element e, Vector2 start, Vector2 end);
void resize_button(button b, Vector2 start, Vector2 end);
void resize_drop_down(drop_down dd, Vector2 start, Vector2 end);
void resize_input(input_form in, Vector2 start, Vector2 end);


// Main loop
int main(int argc, char *argv[]) {
    if (argc > 1) {
        run_headless(argc, argv);
    }else{
        run_gui();
    }
    return 0;
}
void run_headless(int argc, char *argv[]){
    
}
void run_gui(){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "todo app");
    SetTargetFPS(60);
    SetExitKey(0);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    app a = create_app();

    if (a == NULL){
        printf("Error creating app\n");
        return;
    }

    while (!WindowShouldClose()) {
        input(a);
        update(a);
        render(a);
    }
    destroy_app(a);
    printf("Exiting\n");

    CloseWindow();
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
        if (!p->elements[i]->enabled){
            continue;
        }
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
                if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){in->start.x, in->start.y, in->width, in->height}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    in->clicked = true;
                } 
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !CheckCollisionPointRec(GetMousePosition(), (Rectangle){in->start.x, in->start.y, in->width, in->height})){
                    in->clicked = false;
                }
                if (in->clicked){
                    int len = strlen(in->text);
                    if (IsKeyPressed(KEY_BACKSPACE) && len > 0){
                        in->text[len-1] = '\0';
                        if (len == 1){
                            in->changed = false;
                        }
                    } 
                    char c = GetCharPressed();
                    if (c != 0 && len < 1023){
                        in->changed = true;
                        in->text[len] = c;
                        in->text[len+1] = '\0';
                    }
                }
                break;
            default:
                break;
        }
    }
}
void update(app a){
    ptype p = get_current_page(a)->type;
    if (IsWindowResized()){
        printf("Resizing\n");
        Vector2 start = {a->width, a->height};
        Vector2 end = {GetScreenWidth(), GetScreenHeight()};
        for (size_t i=0; i < a->pages[p]->num_elements; i++){
            resize_element(a->pages[p]->elements[i], start, end);
        }
        a->width = end.x;
        a->height = end.y;
    }
    
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

// Rendering functions
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
        if (!p->elements[i]->visible){
            continue;
        }
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
            case PNL:
                render_panel(p->elements[i]->pnl);
                break;
            case TB:
                render_text_box(p->elements[i]->tb);
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
    int num_of_lines = 0;
    char buffer[1024][1024];
    size_t buffer_index = 0;
    int len = strlen(in->text);
    bool centered = true;
    if (in->changed){
        if (len > 0){
            for (size_t i = 0 ; i < len && num_of_lines < 1024; i++){
                
                buffer[num_of_lines][buffer_index] = in->text[i];
                buffer[num_of_lines][buffer_index+1] = '\0';
                if (MeasureText(buffer[num_of_lines], in->font_size) > (in->width*(1 - INBOX_PADDING * 2))){
                    centered = false;
                    buffer[num_of_lines++][buffer_index] = '\0';
                    buffer_index = 0;
                    buffer[num_of_lines][buffer_index] = in->text[i];
                    buffer[num_of_lines][buffer_index+1] = '\0';
                }
                buffer_index++;
            }
            const int max_lines = (in->height*(1 - INBOX_PADDING * 2)) / in->font_size;            
            int starting_index = 0;
            if (num_of_lines >= max_lines){
                starting_index = num_of_lines+1 - max_lines;
            }
            for (int i = starting_index; i < num_of_lines + 1  ; i++){
                Vector2 start_pos = (Vector2){
                    in->start.x + in->width  * INBOX_PADDING + centered * ((in->width  * (1-INBOX_PADDING*2)) - MeasureText(buffer[i], in->font_size))/2,
                    in->start.y + in->height * INBOX_PADDING + centered * ((in->height * (1-INBOX_PADDING*2)) - in->font_size)/2 + i*in->font_size 
                };
                if (num_of_lines >= max_lines ){
                    start_pos.y = in->start.y + in->height * INBOX_PADDING + centered * ((in->height * (1-INBOX_PADDING*2)) - in->font_size)/2 + (i-starting_index)*in->font_size;
                }
                DrawText(
                    buffer[i],
                    start_pos.x,
                    start_pos.y,
                    in->font_size,
                    in->color2
                );
                if (i == num_of_lines){
                    DrawLine(
                        start_pos.x + MeasureText(buffer[i], in->font_size),
                        start_pos.y,
                        start_pos.x + MeasureText(buffer[i], in->font_size),
                        start_pos.y + in->font_size,
                        in->color2
                    );
                }
            }
            
        }

    }else{
        DrawText(
            in->placeholder,
            in->start.x + in->width * INBOX_PADDING  +  ((in->width  * (1-INBOX_PADDING*2)) - MeasureText(in->placeholder, in->font_size))/2,
            in->start.y + in->height * INBOX_PADDING +  ((in->height * (1-INBOX_PADDING*2)) - in->font_size)/2,
            in->font_size,
            in->color2
        );
    }
    
    
    // drawing outline and cursor
    if (in->clicked){
        Rectangle outline = {
            in->start.x,
            in->start.y,
            in->width,
            in->height
        };
        DrawRectangleLinesEx(outline, 2, in->color2);
        Vector2 cursor_pos = {
            in->start.x + in->width * INBOX_PADDING +  ((in->width * (1-INBOX_PADDING*2)) - MeasureText(in->placeholder, in->font_size))/2 + MeasureText(in->placeholder, in->font_size),
            in->start.y + in->height * INBOX_PADDING +  ((in->height * (1-INBOX_PADDING*2)) - in->font_size)/2, 
        };
        
        int index = -1;
        char last_line[1024];
        
            
            

    }

}
void render_text_box(text_box tb){
    DrawRectangle(
        tb->start.x,
        tb->start.y,
        tb->width,
        tb->height,
        tb->color1
    );
    int num_of_lines = 0;
    char buffer[1024][1024];
    size_t buffer_index = 0;
    int len = strlen(tb->text);
    if (len > 0){
        for (size_t i = 0 ; i < len && num_of_lines < 1024; i++){
            
            buffer[num_of_lines][buffer_index] = tb->text[i];
            buffer[num_of_lines][buffer_index+1] = '\0';
            if (MeasureText(buffer[num_of_lines], tb->font_size) > (tb->width*(1 - INBOX_PADDING * 2))){
                buffer[num_of_lines++][buffer_index] = '\0';
                buffer_index = 0;
                buffer[num_of_lines][buffer_index] = tb->text[i];
                buffer[num_of_lines][buffer_index+1] = '\0';
            }
            buffer_index++;
        }
        const int max_lines = (tb->height*(1 - INBOX_PADDING * 2)) / tb->font_size;            
        int starting_index = 0;
        if (num_of_lines >= max_lines){
            starting_index = num_of_lines+1 - max_lines;
        }
        for (int i = starting_index; i < num_of_lines + 1  ; i++){
            Vector2 start_pos = (Vector2){
                tb->start.x + tb->width  * INBOX_PADDING,
                tb->start.y + tb->height * INBOX_PADDING + (i)*tb->font_size 
            };
            if (num_of_lines >= max_lines ){
                start_pos.y = tb->start.y + tb->height * INBOX_PADDING + (i-starting_index)*tb->font_size;
            }
            DrawText(
                buffer[i],
                start_pos.x,
                start_pos.y,
                tb->font_size,
                tb->color2
            );
        }        
    }

   
}
void render_panel(panel pnl){
    DrawRectangle(
        pnl->start.x,
        pnl->start.y,
        pnl->width,
        pnl->height,
        pnl->color
    );
}

// Resizing functions
void resize_drop_down(drop_down dd, Vector2 start, Vector2 end){
    dd->start = (Vector2){dd->start.x*end.x/start.x, dd->start.y*end.y/start.y};
    dd->width = dd->width*end.x/start.x;
    dd->height = dd->height*end.y/start.y;
    size_t new_button_padding = dd->button_padding*end.y/start.y;
    dd->button_padding = new_button_padding;
    for (size_t i = 0; i < dd->num_buttons; i++){
        button b = dd->buttons[i];
        b->start = (Vector2){b->start.x*end.x/start.x, b->start.y*end.y/start.y};
        b->width = b->width*end.x/start.x;
        b->height = b->height*end.y/start.y;
        b->text_pos = (Vector2){b->start.x + b->width/2 - MeasureText(b->text, b->font_size)/2, b->start.y + b->height/2 - b->font_size/2};
    }
}
void resize_button(button b, Vector2 start, Vector2 end){
    size_t new_width = end.x*b->width/start.x;
    size_t new_height = end.y*b->height/start.y;
    b->width = new_width;
    b->height = new_height;
    size_t new_x = end.x*b->start.x/start.x;
    size_t new_y = end.y*b->start.y/start.y;
    b->start = (Vector2){new_x, new_y};
    size_t new_font = end.y*b->font_size/start.y;
    size_t text_size = MeasureText(b->text, b->font_size);
    b->text_pos = (Vector2){b->start.x + b->width/2 - text_size/2, b->start.y + b->height/2 - b->font_size/2};

}
void resize_input(input_form in, Vector2 start, Vector2 end){
    size_t new_width = end.x*in->width/start.x;
    size_t new_height = end.y*in->height/start.y;
    in->width = new_width;
    in->height = new_height;
    size_t new_x = end.x*in->start.x/start.x;
    size_t new_y = end.y*in->start.y/start.y;
    in->start = (Vector2){new_x, new_y};
    size_t new_font = end.y*in->font_size/start.y;
}
void resize_text_box(text_box tb, Vector2 start, Vector2 end){
    size_t new_width = end.x*tb->width/start.x;
    size_t new_height = end.y*tb->height/start.y;
    tb->width = new_width;
    tb->height = new_height;
    size_t new_x = end.x*tb->start.x/start.x;
    size_t new_y = end.y*tb->start.y/start.y;
    tb->start = (Vector2){new_x, new_y};
    size_t new_font = end.y*tb->font_size/start.y;
}
void resize_panel(panel pnl, Vector2 start, Vector2 end){
    size_t new_width = end.x*pnl->width/start.x;
    size_t new_height = end.y*pnl->height/start.y;
    pnl->width = new_width;
    pnl->height = new_height;
    size_t new_x = end.x*pnl->start.x/start.x;
    size_t new_y = end.y*pnl->start.y/start.y;
    pnl->start = (Vector2){new_x, new_y};
}

void resize_element(element e,Vector2 start, Vector2 end){
    switch (e->tag)
    {
        case DD:
            resize_drop_down(e->dd, start, end);
            break;
        case BTN:
            resize_button(e->btn, start, end);
            break;
        case IN:
            resize_input(e->in, start, end);
            break;
        case PNL:
            resize_panel(e->pnl, start, end);
            break;
        default:
            break;
    }
}

