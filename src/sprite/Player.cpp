#include <sprite/Player.hpp>
#include <allegro5/allegro.h>
#include <components/display.hpp>
#include <cmath>

Player::Player() {
    texInfo.tileID = 0;
    animation.init(0.2);
}

void Player::move(float dx, float dy) {
    worldPos += getFixedDisplacement(dx,dy);
    // worldPos.x += dx;
    // worldPos.y += dy;
}

void Player::setWorldPosition(float2 pos) {
    worldPos = pos;
}
float2 Player::getWorldPosition() const {
    return worldPos;
}

void Player::positionRoom(float2 roomPos) {
    setPosition(worldPos+roomPos);
}
float2 Player::getScreenPosition() const {
    return position+translate;
}

float Player::getSpeed() const {
    return SPEED*speedmul;
}
void Player::setSpeedMul(float v) {
    speedmul = v;
}

void Player::useNikes(bool t) {
    usingNikes = t;
}

void Player::setRoom(Room* r) {
    room = r;
}
float Player::getFixedDisplacementX(float dx) {
    // if (dx==0.0f) return 0.0f;
    // bool dir_right = dx>0.0f;
    // float maxdx = dx;
    // const float playerPos = getWorldPosition().x;
    // static const float playerSize = 32.0f * scale;
    // static constexpr float tileSize = 16.0f; //tile = 16x16 (todo)
    // for (const Drawable::DrawableData& data : room->objects) {
    //     float xpos = (float) data[Drawable::COMP_X];
    //     if (dir_right) {
    //         if ((playerPos+playerSize + dx) > xpos) {
    //             float _maxdx = dx - xpos-(playerPos+playerSize);
    //             if (std::abs(_maxdx)<std::abs(maxdx)) maxdx = _maxdx;
    //             printf("right maxdx: %.1f; %.1f; %.1f\n",maxdx, xpos, (playerPos+playerSize));
    //         }
    //     } /*else {
    //         if (playerPos < (xpos+tileSize)) {
    //             maxdx = dx + (xpos+tileSize)-playerPos;
    //             printf("left maxdx: %.1f; %.1f; %.1f\n",maxdx, xpos+tileSize, playerPos);
    //         }
    //     }*/
    // }
    // return maxdx;
    const Rectf __playerHitbox = {getFullPosition(), {32.0f*scale, 48.0f*scale}};
    for (const Drawable::DrawableData& data : room->objects) {
        Rectf playerHitbox = __playerHitbox;
        Rectf drw = {
            {(float)data[Drawable::COMP_X],(float)data[Drawable::COMP_Y]},
            {16.0f, 16.0f}
        };
        drw.min = drw.min+room->getTranslate();
        playerHitbox.min.x += dx;
        if (playerHitbox.intersects(drw)){
            // printf("%.1f %.1f\n", playerHitbox.min.x, drw.min.x);
            return 0.0f;
        }    
    }
    return dx;
}
float Player::getFixedDisplacementY(float dy) {
    const Rectf __playerHitbox = {getWorldPosition(), {32.0f*scale, 48.0f*scale}};
    for (const Drawable::DrawableData& data : room->objects) {
        Rectf playerHitbox = __playerHitbox;
        Rectf drw = {
            {(float)data[Drawable::COMP_X],(float)data[Drawable::COMP_Y]},
            {16.0f, 16.0f}
        };
        playerHitbox.min.y += dy;
        if (playerHitbox.intersects(drw)) return 0.0f;
    }
    return dy;
}
template <typename T>
Rect<T> hitboxAdded(const Rect<T>& a, float2 delta) {
    Rect<T> c = a;
    c.min = c.min + delta;
    return c;
}

Rectf Player::getHitbox() const {
    float2 size = {(float) texInfo.tileRect.size.x,(float) texInfo.tileRect.size.y};
    if (texInfo.bankType == bank::TILESET){
        size.x = bank::tileset::getBank(texInfo.bankID).getTile(texInfo.tileID).size.x;
        size.y = bank::tileset::getBank(texInfo.bankID).getTile(texInfo.tileID).size.y;
    }
    size *= scale;
    static const float xoffset = 4*scale;
    Rectf hitbox = {
        getWorldPosition(),
        {size.x-2*xoffset, size.y/2.0f}
    };
    hitbox.min.x += xoffset;
    hitbox.min.y += size.y/2.0f;
    return hitbox;
}

float2 Player:: getFixedDisplacement(float dx, float dy) {
    /*  
        boolean canMoveX = true;
        boolean canMoveY = true;
        for (Drawable o : cos){
            if (o.getHitbox().intersects(getHitboxAt(reqx + dx, reqy))){ // X movement check
                canMoveX = false;
            }
            if (o.getHitbox().intersects(getHitboxAt(reqx, reqy + dy))){ // Y movement check
                canMoveY = false;
            }
        }
        for (Entity e : Main.getEntities().getNodeGroup()) {
            if (e.getHitbox().intersects(getHitboxAt(reqx + dx, reqy))) canMoveX = false;
            if (e.getHitbox().intersects(getHitboxAt(reqx, reqy + dy))) canMoveY = false;
        }

        if (canMoveX) reqx = (getRequestedX() + dx);
        if (canMoveY) reqy = (getRequestedY() + dy);
    */
    // return {getFixedDisplacementX(dx), getFixedDisplacementY(dy)};
    float rdx = dx, rdy = dy;
    const Rectf __playerHitbox = getHitbox();
    for (const Drawable::DrawableData& data : room->objects) {
        if (!data[Drawable::COMP_SOLID]) continue;
        Rectf playerHitbox = __playerHitbox;
        Rectf drw = Drawable::createHitbox(data);
        playerHitbox.min.x += dx;
        if (playerHitbox.intersects(drw)){
            // printf("%.1f %.1f\n", __playerHitbox.min.x, drw.min.x);
            rdx = 0.0f;
        }
        playerHitbox.min.x = __playerHitbox.min.x;
        playerHitbox.min.y += dy;
        if (playerHitbox.intersects(drw)) {
            rdy = 0.0f;
        }
    }
    return {rdx, rdy};
}

void Player::orientate(float _dx, float _dy) {
    if (_dy>0.0f) setTileByDirection(DIR_DOWN);
    else if (_dy<0.0f) setTileByDirection(DIR_UP);
    else if (_dx>0.0f) setTileByDirection(DIR_RIGHT);
    else if (_dx<0.0f) setTileByDirection(DIR_LEFT);
    animation.update();
}

void Player::setTileByDirection(directions dir) {
    texInfo.tileID = dir;
}
void Player::draw() {
    ALLEGRO_BITMAP* bitmap = bank::getTexture(texInfo).getAllegroBitmap();
    if (!bitmap) return;
    Rectu rect = bank::tileset::getBank(texInfo.bankID).getTile(texInfo.tileID);
    rect.min.x += (animation.frame%4)*rect.size.x;
    if (usingNikes) rect.min.y += rect.size.y*2;

    al_draw_tinted_scaled_rotated_bitmap_region(bitmap,
                                        (float)rect.min.x,(float)rect.min.y,
                                        (float)rect.size.x,(float)rect.size.y,
                                        al_map_rgb_f(1.0f,1.0f,1.0f),
                                        // al_map_rgb(100,100,100),
                                        0.0f, 0.0f,
                                        position.x+translate.x, position.y+translate.y,
                                        scale, scale,
                                        0.0f,
                                        0);
}