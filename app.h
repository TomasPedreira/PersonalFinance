#ifndef __APP_H__
#define __APP_H__

typedef struct _app_sate* app;
typedef enum page_type ptype;
enum page_type {MAIN_PAGE, GAME, GAME_OVER};



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




#endif // __APP_H__