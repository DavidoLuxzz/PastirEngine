#include <components/Room.hpp>
#include <components/display.hpp>

void Room::setTranslate(float x, float y) {
    translate.x = x;
    translate.y = y;
}
float2 Room::getTranslate() const {
    return translate;
}
void Room::move(float dx, float dy) {
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
    if (newx>bounds.min.x) newx=bounds.min.x;
    if (newy>bounds.min.y) newy=bounds.min.y;

    float desna_strana = (bounds.min.x+bounds.size.x-winSize.x) / Display::getPixelScale();
    if (-newx > desna_strana) newx = -desna_strana;
    desna_strana = (bounds.min.y+bounds.size.y-winSize.y) / Display::getPixelScale();
    if (-newy > desna_strana) newy = -desna_strana;

    translate.x = newx;
    translate.y = newy;
}

void Room::draw() {
    al_hold_bitmap_drawing(true);
    for (Drawable::DrawableData& data : objects) {
        Drawable::drawData(data, translate);
    }
    al_hold_bitmap_drawing(false);
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