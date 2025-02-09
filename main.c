#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

#include "app.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCALING_FACTOR 200

void render(app a);
void input(app a);
void update(app a);

void render_main_page(app a);
void render_main_graph(app a);
void render_main_nav_left(app a);



int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Finance app");
    SetTargetFPS(60);
    SetExitKey(0); 
    app a = create_app();
    while (!WindowShouldClose()) {
        input(a);
        update(a);
        render(a);
    }
    destroy_app(a);

    return 0;
}

void render(app a){
    BeginDrawing();
        switch (get_current_page(a))
        {
            case MAIN_PAGE:
                render_main_page(a);    
                break;
            case GAME:

                break;
            case GAME_OVER:

                break;
        }  
    EndDrawing();
}
void input(app a){
    if (IsKeyPressed(KEY_ONE)){
        change_page(a, MAIN_PAGE);
    }
}
void update(app a){
}

void render_main_page(app a){
    Color color = {0, 96, 138, 255}; // lighter dark blue 
    ClearBackground(color);
    render_main_graph(a);
    render_main_nav_left(a);
}

void render_main_nav_left(app a){
    const float graph_ratio = 0.6;
    const size_t initx = 0;
    const size_t inity = 0;
    const size_t sizex = SCREEN_WIDTH*(1 - graph_ratio)-1;
    const size_t sizey = SCREEN_HEIGHT;
    const char* nav_left[] = {"Funds", "Stocks", "Crypto", "Settings"};
    size_t funds_size = MeasureText(nav_left[0], 20);
    DrawText(nav_left[0], initx + sizex/2 - funds_size/2, inity + 20, 20, RAYWHITE);
    
}

void render_main_graph(app a){
    const size_t num_divs = 10;
    const float graph_ratio = 0.6;
    const size_t initx = SCREEN_WIDTH*(1 - graph_ratio);
    const size_t inity = 0;
    const size_t sizex = SCREEN_WIDTH*graph_ratio;
    const size_t sizey = sizex;

    Rectangle rec = {initx, 0, sizex, sizey};
    Color color = {10, 0, 38, 255}; // dark blue
    DrawRectangleRec(rec, color);
    // draw grid
    const size_t xstep = sizex/num_divs;
    const size_t ystep = sizey/num_divs;
    for (size_t i = 0; i < num_divs+1; i++){
        DrawLine(initx + i*xstep, inity, initx + i*xstep, inity + sizey, RAYWHITE);
        DrawLine(initx, inity + i*ystep, initx + sizex, inity + i * ystep, RAYWHITE);
    }
}