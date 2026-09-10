#pragma once
#ifndef __FIGHT_HPP
#define __FIGHT_HPP

#include <audio.hpp>
#include <vector>
#include <data_types.hpp>
#include <fight/blast.hpp>
#include <fight/orb.hpp>

/**
 * Klasa sadrzi podatke o fightu:
 *  - tok radne (timeline)
 *  - koje muzike i sound effects se koriste
 *  - koje teksture se koriste
 * 
 * i treba da ima implementiranu update() funkciju,
 * koja ce da kontrolise sva desavanja kako je napisano
 * u Portable Fight Fajlu (PFF :D)
 */
class Fight {
    /**
     * Svi sound efekti stoje ovde.
     */
    std::vector<audio::Sound> sounds;
    /**
     * Sve muzike stoje ovde. Ih nece biti puno
     */
    std::vector<audio::Sound> music;
    /**
     * Room/arena gde ce se desavati fight.
     */
    unsigned int fightRoomID;
    /**
     * Mesto gde ce player da bude kada bude poceo fight.
     */
    float2 playerSpawn;

    // drawable Fight komponente

    /**
     * TODO: napraviti posebnu klasu za ove entities.
     * Kandidati:
     *  - DynamicEntity
     *  - Enemy
     * 
     * Ideja: visualna animacija (entity sprite change) da ide u poseban fajl.
     *        Taj fajl ce da sadrzi sve animacije tog entitija (npr. udari, hodaj,...)
     *        Taj fajl nece da sadrzi kretanje, vec samo animacije za kretanje.
     * 
     */
    // std::vector<Sprite> enemies;

    std::vector<Orb> orbs;
    std::vector<Blast> blasts;
public:

    /**
     * Pripremi sve tako da fight moze da pocne.
     *  - promeni sobu u fightRoomID
     *  - teleporta playera na playerSpawn
     */
    void prepare();

    /**
     * Update funkcija. Kontrolise tok fighta.
     */
    void update(double ms);

    /**
     * Nacrta sve.
     */
    void draw();
};


#endif