#include <game.hpp>
#include <iostream>
#include <display.hpp>
#include <logger.hpp>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 640

Display display;

int game::run(){

    return 0;
}

int game::init(){
    if (!display.create(WINDOW_WIDTH, WINDOW_HEIGHT)) return -1;

    return 0;
}
void game::clean(){
    logger::info("Cleaning game components...");
    display.destroy();
}
