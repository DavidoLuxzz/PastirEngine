#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <game/game.hpp>
#include <game/main_menu.hpp>
#include <asset_manager.hpp>
#include <game/global.hpp>

global::vars _state = {
    .running = true
};

global::vars& global::get() {
    return _state;
}

#define LOG_MAIN_LOADING false


enum ScreenType {
    GAME,
    MAIN_MENU,
    FIGHT,

    NUM_SCREEN_TYPES
};
ScreenType currentScreen = GAME;
Display display;
ALLEGRO_FONT* font;
MainMenu mainMenu;
Game game; // da ne trosi stack


void setupAssman();
int initDisplay();


void assertInit(int ret, const char* name){
    if (!ret){
        std::cerr << name << " nece da radi >:c\n";
        exit(EXIT_FAILURE);
    }
    if (LOG_MAIN_LOADING)
        std::cout << "Ucitao " << name << std::endl;
}

void init(){
    assertInit(al_init(), "allegro");
    assertInit(al_init_primitives_addon(), "primitives addon");
    assertInit(al_init_image_addon(), "image addon");
    assertInit(al_init_font_addon(), "font addon");
    assertInit(al_init_acodec_addon(), "font addon");
    assertInit(al_install_keyboard(), "keyboard");
    assertInit(al_install_mouse(), "mouse");
    assertInit(al_install_audio(), "audio addon");
    assertInit(al_init_acodec_addon(), "acodec addon");

    setupAssman();
    assertInit(!initDisplay(), "display");

}

void uninstall(){
    std::cout << "Shutting down allegro addons\n";
    display.destroy();
    al_uninstall_mouse();
    al_uninstall_keyboard();
    al_uninstall_audio();
    al_shutdown_font_addon();
    al_shutdown_image_addon();
    al_shutdown_primitives_addon();
    al_uninstall_system();
}

int run();
/**
 * ovo allegro sranje ne da mi da prdnem bez ovih parametara. jebiga.
 * napravljeno samo za Mac tako da postujem.
 * mislio sam da cu da ga odradim na majmuna tako sto stavim @code{#define ALLEGRO_NO_MAGIC_MAIN},
 * medjutim on meni vrati sa greskom. mangup
 */
int main(int argc, char** argv) {
    putchar(0xa);
    init();

    std::cout << "--> game::init()\n";
    Game::makeCurrent(&game);
    if (game.init()) {
        std::cerr << "Ne moze da ucita gejm >:(\n";
        game.clean();
        uninstall();
        return 0;
    }
    std::cout << "--> run()\n";
    run();
    std::cout << "--> game::clean()\n";
    game.clean();

    uninstall();

    return 0;
}

int run(){
    Display* display = Display::getCurrentDisplay();
    // unsigned int frames = 0;
    double lastTime = 0.0;
    while (_state.running) {
        double deltaTime = al_get_time() - lastTime; // seconds?
        lastTime = al_get_time();

        // sve je ovde jasno
        if (currentScreen == ScreenType::GAME) {
            game.handleEvents();
            game.update(deltaTime);
            game.draw();
        } // todo: else if (currentScreen == ScreenType::FIGHT) { ... }
        // ja bi prvo napravio neki fight. cisto onako da se nahajpujem.
        // da dobijem malo motivacije da nastavim da pravim igricu.
        // a nadam se da ce Ivana tog pastira nacrtati.

        display->setTitle(  (std::string("DEMO FPS: ")+std::to_string((int)round(1.0/deltaTime)) + 
                            " Sprites: "+std::to_string(game.rooms[game.roomID].objects.size())).c_str()  );
    }

    return 0;
}

#define LUKA_ASSERT0(x) if (x) return -1;
#define LUKA_ASSERT1(x) if (x<0) return -1;

void setupAssman() {
    int __assets_path_err = 0;
    std::string __assets_path;
    __assets_path = assman::getallegropathstr(ALLEGRO_RESOURCES_PATH, &__assets_path_err);
    //__assets_path = std::getenv("HOME");
    __assets_path += "assets";
    printf("> Setting resources path to %s [errors=%d, %d]\n", __assets_path.c_str(), __assets_path_err, assman::setcwd(__assets_path));
}


int initDisplay() {
    Display::setupPixelScale(1.0f);
    LUKA_ASSERT0(display.create(WINDOW_WIDTH, WINDOW_HEIGHT, "DEMO", true));
    display.getEventQueue().registerKeyboardEventSource();

    // int dpi = al_get_monitor_dpi(al_get_display_adapter(display.getAllegroDisplay()));
    return 0;
}
