#ifndef __APP_H__
#define __APP_H__
#include "elements.h"

typedef struct _app_sate* app;
struct _app_sate {
    ptype current_page;
    element elements[1024];
    size_t num_elements;
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
* @return ptype
*/
ptype get_current_page(app a);

/*
* @brief Add an element to the app
* @param a app
* @param e element
*/
void add_element(app a, element e);

/*
* @brief Get an element from the app
* @param a app
* @param i index of the element
* @return element*
*/
element get_element(app a, size_t i);

#endif // __APP_H__