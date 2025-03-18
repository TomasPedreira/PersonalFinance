#ifndef __APP_H__
#define __APP_H__
#include "elements.h"

typedef struct _app_sate* app;
struct _app_sate {
    ptype current_page;
    page pages[16];
    size_t num_pages;
    int width;
    int height;	
};


/*
* @brief Create a new app
* @return app
*/
app create_app();
/*
* @brief Destroy the app
* @param a app
*/
void destroy_app(app a);

/*
* @brief Change the current page
* @param a app
* @param p page to change to: enum pages
*/
void change_page(app a, ptype p);

/*
* @brief Get the current page
* @param a app
* @return page
*/
page get_current_page(app a);

#endif // __APP_H__