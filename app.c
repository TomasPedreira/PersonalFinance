#include "app.h"
#include <stdlib.h>

struct _app_sate {
    enum pages current_page;
};

app create_app(){
    app a = malloc(sizeof(struct _app_sate));
    a->current_page = MAIN_PAGE;
    return a;
}
void destroy_app(app a){
    free(a);
}

void change_page(app a, enum pages p){
    a->current_page = p;
}

enum pages get_current_page(app a){
    return a->current_page;
}