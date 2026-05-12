#pragma once
#ifndef WAVE_H
#define WAVE_H
const int max_enemies_per_wave = 30;
class Wave
{
private:
    int spawnType[max_enemies_per_wave];
    float spawnDelay[max_enemies_per_wave];
    int totalEnemies;
    int spawnedCount;
    float timer;
    bool started;
    bool finished;
public:
    Wave();
    ~Wave();
    void setup(int waveNumber);
    void start();
    bool isFinished() const;
    bool isStarted() const;
    int getNextSpawn(float dt);
};
#endif