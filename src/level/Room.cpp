#include <level/Room.hpp>
#include <components/display.hpp>
#include <sprite/Player.hpp>

void Room::setTranslate(float x, float y) {
    translate.x = x;
    translate.y = y;
}
float2 Room::getTranslate() const {
    return translate;
}
void Room::move(float _dx, float _dy, void* _player) {
    Player* player = (Player*) _player;
    float2 delta = {_dx,_dy};
    float dx = _dx, dy = _dy;
    if (player) delta = player->getFixedDisplacement(_dx,_dy);
    dx = delta.x;
    dy = delta.y;
    /*
    // camera coordinates
    double x = player.getRequestedX()-root.getWidth()/2;
    double y = player.getRequestedY()-root.getHeight()/2;
    // Fix x coords
    if ((x+root.getWidth())>LEVEL_WIDTH) x=LEVEL_WIDTH-root.getWidth();
    if (x<=0) x=0;
    // Fix y coords
    if ((y+root.getHeight())>LEVEL_HEIGHT) y=LEVEL_HEIGHT-root.getHeight();
    if (y<=0) y=0;
    
    camX = x;
    camY = y;
    player.setCameraPos(x, y);
    player.relocate(player.getRequestedX() - x, player.getRequestedY() - y);
    for (DynamicObject o : dynamicObjects) o.updatePos(-x, -y);
    DialogBox.updatePos(this, 0, 0);*/
    vec2<int> winSize;
    winSize.x = Display::getCurrentDisplay()->getWidth();
    winSize.y = Display::getCurrentDisplay()->getHeight();
    float newx = translate.x + dx; // new translate x
    float newy = translate.y + dy; // -||-

    float desna_strana = (bounds.min.x+bounds.size.x-winSize.x) / Display::getPixelScale();

    if (newx>bounds.min.x) {
        newx=bounds.min.x;
        if (player) player->move(-dx,0.0f);
    } else if (player && player->getTranslate().x<0.0f) {
        player->move(-dx,0.0f);
        newx = translate.x;
    } else if (-newx > desna_strana) {
        newx = -desna_strana;
        if (player) player->move(-dx,0.0f);
    } else if (player && player->getTranslate().x>0.0f) {
        player->move(-dx,0.0f);
        newx = translate.x;
    }
    desna_strana = (bounds.min.y+bounds.size.y-winSize.y) / Display::getPixelScale();
    if (newy>bounds.min.y) {
        newy=bounds.min.y;
        if (player) player->move(0.0f,-dy);
    } else if (player && player->getTranslate().y<0.0f) {
        player->move(0.0f,-dy);
        newy = translate.y;
    } else if (-newy > desna_strana) {
        newy = -desna_strana;
        if (player) player->move(0.0f, -dy);
    } else if (player && player->getTranslate().y>0.0f) {
        player->move(0.0f, -dy);
        newy = translate.y;
    }

    translate.x = newx;
    translate.y = newy;
    // if (player) player->move(ptrans.x,ptrans.y);
}

void Room::draw() {
    al_hold_bitmap_drawing(true);
    for (Drawable::DrawableData& data : objects) {
        Drawable::drawData(data, translate);
    }
    al_hold_bitmap_drawing(false);
}

#include <game.hpp>
void Room::position(float2 playerPos) {
    vec2<int> winSize;
    // window size. no scale (1.0f)
    winSize.x = Display::getCurrentDisplay()->getWidth();
    winSize.y = Display::getCurrentDisplay()->getHeight();
    // uses default pixel scale (4.0f)
    float newx = bounds.min.x + (winSize.x/2.0f)/Display::getPixelScale() - playerPos.x;
    float newy = bounds.min.y + (winSize.y/2.0f)/Display::getPixelScale() - playerPos.y;
    //printf("1: %f\n", newx-translate.x);

    float desna_strana = (bounds.min.x+bounds.size.x) / DEFAULT_PIXEL_SCALE - winSize.x/Display::getPixelScale();

    if (newx>bounds.min.x)
        newx=bounds.min.x;
    if (-newx > desna_strana)
        newx = -desna_strana;
    desna_strana = (bounds.min.y+bounds.size.y) / DEFAULT_PIXEL_SCALE - winSize.y/Display::getPixelScale();
    if (newy>bounds.min.y)
        newy=bounds.min.y;
    if (-newy > desna_strana)
        newy = -desna_strana;

    translate.x = newx;
    translate.y = newy;

    // printf("2: %f %f\n", newx, newy);
}

#define __KILOBYTE 1024
#define __MEGABYTE 1048576
#define __GIGABYTE 1073741824
#define __TERABYTE 1099511627776
#include <cmath>
std::string __memsizeToString(uint64_t a){
    static const std::string units[] = {"B", "kB", "MB", "GB", "TB", "inf"};
    int sizeid=0;
    if (a > __KILOBYTE) ++sizeid;
    if (a > __MEGABYTE) ++sizeid;
    if (a > __GIGABYTE) ++sizeid;
    if (a > __TERABYTE) ++sizeid;
    
    long double ad = (long double)a / powl(1024.0, 1.0*sizeid);
    uint64_t adi64 = (uint64_t)round(ad);
    uint64_t addecimals = fmod(round(ad*100)/100.0, 1.0) * 100;
    std::string str = std::to_string(adi64) + "." + std::to_string(addecimals) + " " + units[sizeid];
    return str;
}
uint64_t Room::getMemoryUsage() const {
    size_t szof = sizeof(Room);
    size_t vecsz = objects.capacity()*sizeof(Drawable::DrawableData);
    return szof+vecsz;
}