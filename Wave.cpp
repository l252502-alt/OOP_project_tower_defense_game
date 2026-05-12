#include "Wave.h"
Wave::Wave() : totalEnemies(0), spawnedCount(0), timer(0.0f), started(false), finished(false)
{
    for (int i = 0; i < max_enemies_per_wave; i++)
    {
        spawnType[i] = 0;
        spawnDelay[i] = 0.0f;
    }
}
Wave::~Wave()
{}
void Wave::setup(int waveNumber)
{
    totalEnemies = 0;
    spawnedCount = 0;
    timer = 0.0f;
    started = false;
    finished = false;
    for (int i = 0; i < max_enemies_per_wave; i++)
    {
        spawnType[i] = 0;
        spawnDelay[i] = 0.0f;
    }
    float delay = 0.0f;
    float gap = 1.5f; 
    int idx = 0;    
    //wave 1: only basic enemies
    //wave 2: basics + fast
    //wave 3: basics + fast + tanks
    //wave 4: all types
    //wave 5: all types + boss
    int basics = 3 + waveNumber * 2;
    int fasts = waveNumber;
    int tanks = waveNumber / 2;
    int flying = waveNumber / 2;
    int bosses;
    if (waveNumber >= 4)
    {
        bosses = 1;
    }
    else
    {
        bosses = 0;
    }
    if (basics > max_enemies_per_wave)
    {
        basics = max_enemies_per_wave;
    }
    for (int i = 0; i < basics && idx < max_enemies_per_wave; i++)
    {
        spawnType[idx] = 0;      
        spawnDelay[idx] = delay;
        delay = delay + gap;
        idx++;
    }
    for (int i = 0; i < fasts && idx < max_enemies_per_wave; i++) 
    {
        spawnType[idx] = 1; 
        spawnDelay[idx] = delay;
        delay = delay + gap * 0.7f;       //faster spawning
        idx++;
    }
    for (int i = 0; i < tanks && idx < max_enemies_per_wave; i++)
    {
        spawnType[idx] = 2;       //tank enemy
        spawnDelay[idx] = delay;
        delay = delay + gap * 1.5f;       //slower spawning for tank enemy
        idx++;
    }
    for (int i = 0; i < flying && idx < max_enemies_per_wave; i++)
    {
        spawnType[idx] = 3;   
        spawnDelay[idx] = delay;
        delay = delay + gap;
        idx++;
    }
    for (int i = 0; i < bosses && idx < max_enemies_per_wave; i++)
    {
        spawnType[idx] = 4;
        spawnDelay[idx] = delay;
        delay = delay + gap * 2.0f;
        idx++;
    }
    totalEnemies = idx;
}
void Wave::start()
{
    started = true;
}
bool Wave::isFinished() const
{
    return finished;
}
bool Wave::isStarted() const 
{
    return started;
}
int Wave::getNextSpawn(float dt)
{
    if (!started || finished)               //if wave not started or already finished
    {
        return -1;
    }
    timer = timer + dt;
    if (spawnedCount >= totalEnemies)
    {
        finished = true;
        return -1;
    }
    if (timer >= spawnDelay[spawnedCount])
    {
        int type = spawnType[spawnedCount];
        spawnedCount++;
        return type;
    }
    return -1;
}