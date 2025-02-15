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

typedef enum {JOGO, SNACK, REFEICAO, LIVRO} expense_t;
typedef struct {
    size_t id;
    float amount;
    char* description;
    expense_t type;
} expense;
typedef struct {
    expense* expenses;
    size_t num_expenses;
    size_t max_expenses;
} expenses;


int init_expenses(expenses* expenses);
void destroy_expenses(expenses* expenses);
void print_list_of_expenses(expenses expenses);

void render(app a, expenses expenses);
void input(app a, expenses expenses);
void update(app a, expenses expenses);

void render_main_page(app a);
void render_main_page_graph(app a);
void render_main_page_nav_left(app a);

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
    size_t text_size = MeasureText(text, font_size);
    Vector2 text_pos = {start.x + sizes.x/2 - text_size/2, start.y + sizes.y/2 - font_size/2};
    dd->text_pos = text_pos;
    dd->text = text;
    dd->hovering = false;
    dd->clicked = false;
    dd->font_size = font_size;
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


void read_list_of_expenses(char* filename, expenses* expenses);

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Finance app");
    SetTargetFPS(60);
    SetExitKey(0);
    app a = create_app();
    if (a == NULL){
        printf("Error creating app\n");
        return 1;
    }
    expenses expenses;
    if (init_expenses(&expenses) != 0){
        printf("Error initializing expenses\n");
        return 1;
    }
    // erase after
    const float graph_ratio = 0.6;
    const size_t initx = 0;
    const size_t inity = 0;
    const size_t sizex = SCREEN_WIDTH*(1 - graph_ratio)-1;
    const size_t sizey = SCREEN_HEIGHT;
    // create a dropdown with 3 buttons

    drop_down dd = create_drop_down((Vector2){initx + sizex/2 - 100, inity + 100}, (Vector2){200, 50}, BLACK, BLUE, "Options", 20, 10, (char*[]){"Option 1", "Option 2", "Option 3"}, 3);
    if (dd == NULL){
        printf("Error creating drop down\n");
        return 1;
    }
    element e = malloc(sizeof(struct _element));
    if (e == NULL){
        printf("Error creating element\n");
        return 1;
    }
    e->tag = DD;
    e->page = MAIN_PAGE;
    e->dd = dd;
    printf("Adding element\n");
    add_element(a, e);
    printf("Element added\n");

    while (!WindowShouldClose()) {
        input(a, expenses);
        update(a, expenses);
        render(a, expenses);
    }
    printf("Number of butons: %d\n", dd->num_buttons);
    for (size_t i = 0; i < dd->num_buttons; i++){
        printf("Freeing button %zu\n", dd->buttons[i]->font_size);
        free(dd->buttons[i]);
    }
    free(dd->buttons);
    free(dd);
    free(e);
    
    destroy_app(a);
    destroy_expenses(&expenses);
    printf("Exiting\n");

    CloseWindow();


    return 0;
}

void render(app a, expenses expenses){
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
void input(app a, expenses expenses){
    if (IsKeyPressed(KEY_ONE)){
        element e = get_element(a, 0);
        e->dd->clicked = true;
    }
    if (IsKeyPressed(KEY_TWO)){
        element e = get_element(a, 0);
        e->dd->clicked = false;
    }
}
void update(app a, expenses expenses){
    switch (get_current_page(a))
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
    DrawRectangle(
        dd->start.x,
        dd->start.y,
        dd->width,
        dd->height,
        dd->color1
    );
    DrawText(
        dd->text,
        dd->text_pos.x,
        dd->text_pos.y,
        dd->font_size,
        dd->color2
    );
    if (dd->clicked)
        for (size_t i = 0; i < dd->num_buttons; i++){
            render_button(dd->buttons[i], (i+1) * dd->height + dd->button_padding/2);
        }
}

void render_main_page(app a){
    Color color = {0, 96, 138, 255}; // lighter dark blue
    ClearBackground(color);
    render_main_page_graph(a);
    render_main_page_nav_left(a);
}

void render_main_page_nav_left(app a){
    const float graph_ratio = 0.6;
    const size_t initx = 0;
    const size_t inity = 0;
    const size_t sizex = SCREEN_WIDTH*(1 - graph_ratio)-1;
    const size_t sizey = SCREEN_HEIGHT;
    const char* nav_left[] = {"Funds", "Stocks", "Crypto", "Settings"};
    size_t funds_size = MeasureText(nav_left[0], 20);
    DrawText(nav_left[0], initx + sizex/2 - funds_size/2, inity + 20, 20, RAYWHITE);

    element e = get_element(a, 0);
    render_drop_down(e->dd);
}

void render_main_page_graph(app a){
    const size_t num_divs = 10;
    const float graph_ratio = 0.60000;
    const size_t initx = round((float)SCREEN_WIDTH*(1.0000 - graph_ratio));
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
void read_list_of_expenses(char* filename, expenses* expenses){
    FILE* f = fopen(filename, "r");
    if (f == NULL){
        printf("Error opening file\n");
        return;
    }
    expense e;
    size_t id;
    while (fscanf(f, "%d;", &id) != EOF){
        e.id = id;
        char aux[1024];
        char car = ' ';
        fscanf(f, "%f;", &e.amount);
        size_t i;
        for (i = 0; (car = fgetc(f)) != ';'; i++)
            {
                aux[i] = car;                               //captura do nome do k navio
            }
        aux[i] = '\0';
        fscanf(f, "%d;", &e.type);
        e.description = malloc(sizeof(char)*(strlen(aux)+1));
        strcpy(e.description, aux);
        if (expenses->num_expenses == expenses->max_expenses){
            printf("Max number of expenses reached, ignoring every expense now\n");
            fclose(f);
            return;
        }
        expenses->expenses[id] = e;
        expenses->num_expenses++;

    }
    fclose(f);
}

int init_expenses(expenses* expenses){
    expenses->expenses = malloc(MAX_EXPENSES*sizeof(expense));
    if (expenses->expenses == NULL){
        return 1;
    }
    expenses->num_expenses = 0;
    expenses->max_expenses = MAX_EXPENSES;
    read_list_of_expenses("expenses.txt", expenses);
    print_list_of_expenses(*expenses);
    return 0;
}

void destroy_expenses(expenses* expenses){
    for (size_t i = 0; i < expenses->num_expenses; i++){
        free(expenses->expenses[i].description);
    }
    free(expenses->expenses);
}

void print_list_of_expenses(expenses expenses){
    for (size_t i = 0; i < expenses.num_expenses; i++){
        printf("id: %d, amount: %f, description: %s, type: %d\n", expenses.expenses[i].id, expenses.expenses[i].amount, expenses.expenses[i].description, expenses.expenses[i].type);
    }
}