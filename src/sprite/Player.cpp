#include <sprite/Player.hpp>
#include <allegro5/allegro.h>
#include <components/display.hpp>
#include <cmath>
#include <game/game.hpp>
#include <game/global.hpp>
#include <audio.hpp>

#define CURRENT_TILE bank::tileset::getBank(texInfo.bankID).getTile(texInfo.tileID)

#define DEFAULT_WALK_ANIM_RATE 200.

Player::Player() {
    texInfo.tileID = 0;
    animation.init(DEFAULT_WALK_ANIM_RATE);
    trailAnim.init(50.);
    crouchAnim.init(100.);
}

float d = 0.5f;

void Player::update(double ms) {
    // trail animation
    if (trailEnabled && trailAnim.update(ms)) {
        trailPositions.push_front({getWorldPosition(),texInfo});
        while (trailPositions.size()>TRAIL_INSTANCE_COUNT) trailPositions.pop_back();
    }
    // crouch animation
    if (crouching) {
        scale.x = fmaxf(fminf(scale.x+0.01f*ms*d, 2.0f),1.0f);
        scale.y = fminf(fmaxf(scale.y-0.01f*ms*d, 0.5f),1.0f);
        if (d>0 && scale.x>=1.999f && scale.y<=0.501f) d=-d;
        else if (d<0 && scale.x<=1.001f && scale.y>=0.999f) d=-d;
    } else {
        scale.x = fmaxf(scale.x-0.01f*ms, 1.0f);
        scale.y = fminf(scale.y+0.01f*ms, 1.0f);
    }
}

void Player::move(float dx, float dy, float ms, int roomID) {
    animation.rate = DEFAULT_WALK_ANIM_RATE/speedmul;
    worldPos += getFixedDisplacement(dx*ms,dy*ms,roomID);
    if (!(dx==0.0f && dy==0.0f) || (animation.frame&1)) {
        bool _tick = animation.update(ms);
        if (_tick && !(animation.frame&1)) {
            if (Game::getGame()->roomID == 2) {
                if (animation.frame%4==0) audio::playSound(audio::Sound::STEP02);
                else audio::playSound(audio::Sound::STEP01);
            } else 
                audio::playSound(audio::Sound::GRASS);
        }
    }
    
    // }
    // worldPos.x += dx;
    // worldPos.y += dy;
}

void Player::setWorldPosition(float2 pos) {
    worldPos.x = pos.x - CURRENT_TILE.size.x*scale.x*spriteScale.x/4.f;
    worldPos.y = pos.y - CURRENT_TILE.size.y*scale.y*spriteScale.y/2.f;
}
float2 Player::getWorldPosition() const {
    return worldPos;
}
float2 Player::getWorldCenter() const {
    Rectf hb = getHitbox();
    return hb.min + hb.size/2;
}
float Player::getWorldFeetY() const {
    // printf("%.1f\n",worldPos.y);
    return worldPos.y + (float)bank::tileset::getBank(texInfo.bankID).getTile(texInfo.tileID).size.y * spriteScale.y;
}


void Player::positionRoom(float2 roomPos) {
    setPosition(worldPos+roomPos);
}
float2 Player::getScreenPosition() const {
    return position+translate;
}
float Player::getScreenFeetY() const {
    return position.y+translate.y + (float)bank::tileset::getBank(texInfo.bankID).getTile(texInfo.tileID).size.y * spriteScale.y;
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
bool Player::isUsingNikes() const {
    return usingNikes;
}

void Player::setSpriteScale(float2 v) {
    spriteScale = v;
}
float2 Player::getSpriteScale() const {
    return spriteScale;
}

Rectf Player::getHitbox() const {
    float2 size = {(float) texInfo.tileRect.size.x,(float) texInfo.tileRect.size.y};
    if (texInfo.bankType == bank::TILESET){
        size.x = bank::tileset::getBank(texInfo.bankID).getTile(texInfo.tileID).size.x;
        size.y = bank::tileset::getBank(texInfo.bankID).getTile(texInfo.tileID).size.y;
    }
    size *= spriteScale;
    // size *= scale;       // buggy ass
    static const float xoffset = size.x/4.0f;
    Rectf hitbox = {
        getWorldPosition(),
        {size.x-2*xoffset, size.y/2.0f}
    };
    hitbox.min.x += xoffset;
    hitbox.min.y += size.y/2.0f;
    //printf("%f\n", (1.f-scale.y)*size.y);
    return hitbox;
}

Rectf Player::getScreenHitbox() const {
    float2 size = {(float) texInfo.tileRect.size.x,(float) texInfo.tileRect.size.y};
    if (texInfo.bankType == bank::TILESET){
        size.x = CURRENT_TILE.size.x;
        size.y = bank::tileset::getBank(texInfo.bankID).getTile(texInfo.tileID).size.y;
    }
    size *= spriteScale;
    // size *= scale;       // buggy ass
    Rectf hitbox = {
        getScreenPosition(),
        {size.x, size.y}
    };
    return hitbox;
}

#define JUST_A_NICE_COLLISION_DISTANCE 0.2f
#define JANCD JUST_A_NICE_COLLISION_DISTANCE

/**
 * if (abs(a)<abs(b)) return a;
 * else return b;
 */
float absmin(float a, float b) {
    if (abs(a)<abs(b)) return a;
    return b;
}

#define AXIS_CHECK(d,axis)  (d<0.0f? absmin(d,  drw.min.axis+drw.size.axis + JANCD - __playerHitbox.min.axis) : \
                                    absmin(d,  drw.min.axis - JANCD - (__playerHitbox.min.axis+__playerHitbox.size.axis)))
/*
JANCD = just a nice collision distance \
if (d<0.0f) \
                        rdx = absmin(d,  drw.min.x+drw.size.x + JANCD - __playerHitbox.min.x);\
                    else \
                        rdx = absmin(d,  drw.min.x - JANCD - (__playerHitbox.min.x+__playerHitbox.size.x));
*/
float2 Player:: getFixedDisplacement(float dx, float dy, int roomID) {
    if (invincible) return {dx,dy};
    
    if (roomID<0) roomID = Game::getGame()->roomID;
    const Room& room = global::get().rooms[roomID];

    float rdx = dx, rdy = dy;
    const Rectf __playerHitbox = getHitbox();
    for (const Drawable::DrawableData& data : room.objects) {
        if (!data[Drawable::COMP_SOLID]) continue;
        Rectf playerHitbox = __playerHitbox;
        Rectf drw = Drawable::createHitbox(data);
        playerHitbox.min.x += dx;
        if (playerHitbox.intersects(drw)){
            // printf("%.1f %.1f\n", __playerHitbox.min.x, drw.min.x);
            // newx = drw.max.x
            // newDx = newx - worldPos.x
            rdx = AXIS_CHECK(dx,x);
        }
        playerHitbox.min.x = __playerHitbox.min.x;
        playerHitbox.min.y += dy;
        if (playerHitbox.intersects(drw)) {
            rdy = AXIS_CHECK(dy,y);
        }
    }
    for (const StaticEntity::EntityData& ent : room.entities) {
        // assume da su svi solid
        Rectf playerHitbox = __playerHitbox;
        Rectf drw = StaticEntity::createHitbox(ent);
        playerHitbox.min.x += dx;
        if (playerHitbox.intersects(drw)){
            // printf("%.1f %.1f\n", __playerHitbox.min.x, drw.min.x);
            // newx = drw.max.x
            // newDx = newx - worldPos.x
            rdx = AXIS_CHECK(dx,x);
        }
        playerHitbox.min.x = __playerHitbox.min.x;
        playerHitbox.min.y += dy;
        if (playerHitbox.intersects(drw)) {
            rdy = AXIS_CHECK(dy,y);
        }
    }
    return {rdx, rdy};
}

void Player::orientate(float _dx, float _dy) {
    if (_dy>0.0f) setTileByDirection(DIR_DOWN);
    else if (_dy<0.0f) setTileByDirection(DIR_UP);
    else if (_dx>0.0f) setTileByDirection(DIR_RIGHT);
    else if (_dx<0.0f) setTileByDirection(DIR_LEFT);
}

void Player::setTileByDirection(directions dir) {
    texInfo.tileID = dir;
}
void Player::drawInstance(float2 pos, bank::TextureInfo ti, float2 scale, ALLEGRO_COLOR tint) {
    ALLEGRO_BITMAP* bitmap = bank::getTexture(ti).getAllegroBitmap();
    if (!bitmap) return;

    Rectu rect = bank::tileset::getBank(ti.bankID).getTile(ti.tileID);
    rect.min.x += (animation.frame%4)*rect.size.x;
    if (usingNikes) rect.min.y += rect.size.y*2;

    float2 posfix = {
        (1.f-scale.x)*(float)rect.size.x * spriteScale.x / 2.0f,
        (1.f-scale.y)*(float)rect.size.y * spriteScale.y
    };

    al_draw_tinted_scaled_rotated_bitmap_region(bitmap,
                                        (float)rect.min.x,(float)rect.min.y,
                                        (float)rect.size.x,(float)rect.size.y,
                                        tint,
                                        // al_map_rgb(100,100,100),
                                        0.0f, 0.0f,
                                        pos.x+posfix.x, pos.y+posfix.y,
                                        scale.x*spriteScale.x, scale.y*spriteScale.y,
                                        0.0f,
                                        0);
}
void Player::draw() {
    int opacity = 100;
    int dOpacity = -opacity/TRAIL_INSTANCE_COUNT;
    if (trailEnabled) for (const trail& tr : trailPositions) {
        drawInstance(tr.pos+position-worldPos, tr.texInfo, scale, al_map_rgba(100,100,100,opacity));
        opacity += dOpacity;
    }

    drawInstance(position+translate, texInfo, scale, al_map_rgb_f(1.f,1.f,1.f));
}


void Player::enableTrail(bool t) {
    trailEnabled = t;
}
bool Player::isTrailEnabled() const {
    return trailEnabled;
}

void Player::setCrouching(bool t) {
    crouching = t;
}
bool Player::isCrouching() const {
    return crouching;
}
