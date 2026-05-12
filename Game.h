#ifndef GAME_H
#define GAME_H
#include <SFML/Audio.hpp> 
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Wave.h"
#include "UI.h"
#include "Enemy.h"
#include "Tower.h"
#include "BasicEnemy.h"
#include "FastEnemy.h"
#include "TankEnemy.h"
#include "FlyingEnemy.h"
#include "BossEnemy.h"
#include "CannonTower.h"
#include "SniperTower.h"
#include "MachineGunTower.h"
#include "SlowTower.h"
#include "FreezeTower.h"

const int max_enemies = 150;
const int max_towers = 50;
const int total_waves = 5;
const int playing = 0;
const int game_over = 1;
const int win = 2;

class Game 
{
private:
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Music bgMusic;
    int screenWidth;
    int screenHeight;
    int mapAreaWidth;
    int uiPanelX;
    Map  map;
    Wave wave;
    UI   ui;
    Enemy* enemies[max_enemies];
    Tower* towers[max_towers];
    int enemyCount;
    int towerCount;
    int currentWave;
    int gold;
    int lives;
    int state;
    bool waveRunning;
    float waveStartTimer; 
    bool  waveStarting;
    sf::Font font;
    bool fontLoaded;
    void handleEvents();
    void handleClick(int mouseX, int mouseY);
    void update(float dt);
    void render();
    void spawnEnemy(int type);
    void cleanDeadEnemies();
    void checkWaveComplete();
    void renderGameOver();
    void renderWin();
    void renderWaveCountdown();
    void renderUIPanel();
public:
    Game();
    ~Game();
    void run();
};
#endif