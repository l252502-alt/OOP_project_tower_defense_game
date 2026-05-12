#include "Game.h"
Game::Game()               //default constructor
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();    //full-screen mode
    screenWidth = desktop.width;
    screenHeight = desktop.height;
    mapAreaWidth = (int)(screenWidth * 0.75f);           //75% of screen will be occupied by map
    uiPanelX = mapAreaWidth - 20;                //rest of screen by UI panel
    window.create(desktop, "Tower Defense", sf::Style::Fullscreen);
    if (bgMusic.openFromFile("background_music.ogg"))         //loading music file
    {
        bgMusic.setLoop(true);
        bgMusic.setVolume(50);
        bgMusic.play();
    }
    enemyCount = 0;
    towerCount = 0;
    currentWave = 1;
    waveStartTimer = 3.0f;             //3 second countdown before wave 1
    waveStarting = true;               //start counting down immediately
    waveRunning = false;
    gold = 350;
    lives = 10;
    state = playing;
    fontLoaded = false;
    for (int i = 0; i < max_enemies; i++)                //initializing enemies array with nullptr
    {
        enemies[i] = nullptr;
    }
    for (int i = 0; i < max_towers; i++)                 //initializing towers array with nullptr
    { 
        towers[i] = nullptr;
    }
    fontLoaded = font.loadFromFile("C:/Windows/Fonts/arial.ttf");           //load font
    ui.loadFont("C:/Windows/Fonts/arial.ttf");
    ui.setGold(gold);
    ui.setLives(lives);
    ui.setWave(currentWave, total_waves);
    wave.setup(currentWave);
}
Game::~Game()                     //destructor
{
    for (int i = 0; i < max_enemies; i++)         //deleting dynamically allocated enemies array
    {
        delete enemies[i];
        enemies[i] = nullptr;
    }
    for (int i = 0; i < max_towers; i++)          //deleting dynamically allocated towers array
    {
        delete towers[i];
        towers[i] = nullptr;
    }
}
void Game::run() 
{
    while (window.isOpen()) 
    {
        float dt = clock.restart().asSeconds();
        if (dt > 0.05f)
        {
            dt = 0.05f;
        }
        handleEvents();
        if (state == playing)
        {
            update(dt);
        }
        render();
    }
}
void Game::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed)                //defining keyboard key operations
        {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
            if (event.key.code == sf::Keyboard::Num1)
                ui.setSelectedTower(0);
            if (event.key.code == sf::Keyboard::Num2)
                ui.setSelectedTower(1);
            if (event.key.code == sf::Keyboard::Num3)
                ui.setSelectedTower(2);
            if (event.key.code == sf::Keyboard::Num4) 
                ui.setSelectedTower(3);
            if (event.key.code == sf::Keyboard::Num5) 
                ui.setSelectedTower(4);
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            handleClick(event.mouseButton.x, event.mouseButton.y);      
        }
    }
}
void Game::handleClick(int mouseX, int mouseY) 
{
    int btnX = uiPanelX;
    int btnWidth = screenWidth - uiPanelX - 60;
    int btnHeight = 60;
    int btnStartY = 260;
    for (int i = 0; i < 5; i++)
    {
        int btnY = btnStartY + i * (btnHeight + 10);
        sf::FloatRect btnRect((float)btnX, (float)btnY, (float)btnWidth, (float)btnHeight);
        if (btnRect.contains((float)mouseX, (float)mouseY))  //if mouse has selected the position of a button, select that tower
        {
            ui.setSelectedTower(i);
            return;
        }
    }
    if (mouseX >= mapAreaWidth)
    {
        return;
    }
    int sel = ui.getSelectedTower();
    if (sel < 0)             //if no tower selected
    {
        return;
    }
    int col = map.pixelToCol((float)mouseX);
    int row = map.pixelToRow((float)mouseY);
    if (row < 0 || row >= map_rows)          //selected position not map
    {
        return;
    }
    if (col < 0 || col >= map_cols)          //selected position not map
    {
        return;
    }
    if (!map.is_placeable(row, col))          //if selected area not a grass tile, then do nothing
    {
        return;
    }
    if (towerCount >= max_towers)             //if number of maximum towers exceeded
    {
        return;
    }
    int cost = ui.getSelectedTowerCost();
    if (gold < cost)                         //if cost is greater than gold present, cannot place tower
    {
        return;
    }
    float tx = map.tileCenterX(col);
    float ty = map.tileCenterY(row);
    Tower* newTower = nullptr;              //pointer for a new tower to place
    switch (sel)                    //checking for selected tower
    {
    case 0:
        newTower = new CannonTower(tx, ty, row, col);
        break;
    case 1:
        newTower = new SniperTower(tx, ty, row, col);
        break;
    case 2:
        newTower = new MachineGunTower(tx, ty, row, col); 
        break;
    case 3: 
        newTower = new SlowTower(tx, ty, row, col);  
        break;
    case 4:
        newTower = new FreezeTower(tx, ty, row, col);   
        break;
    }
    if (newTower)                          //if new tower not nullptr (invalid)
    {
        towers[towerCount] = newTower;     //increase a tower
        towerCount++;                      
        map.setOccupied(row, col);         //set the tile on which tower is placed as occupied
        gold = gold - cost;                //decrease the cost of selected tower from the gold present
        ui.setGold(gold);
    }
}
void Game::spawnEnemy(int type)
{
    if (enemyCount >= max_enemies)         //if maximum enemies reached then cannot spawn new enemies
    {
        return;
    }
    float startX = map.get_PathX(0);       //starting position of enemies
    float startY = map.get_PathY(0);
    float exitX = map.get_PathX(map.get_PathCount() - 1);         //exit position of enemies
    float exitY = map.get_PathY(map.get_PathCount() - 1);
    Enemy* e = nullptr;                 //pointer to store a new spawned enemy 
    switch (type)
    {
    case 0: 
        e = new BasicEnemy(startX, startY); 
        break;
    case 1:
        e = new FastEnemy(startX, startY);    
        break;
    case 2: 
        e = new TankEnemy(startX, startY);   
        break;
    case 3:
        e = new FlyingEnemy(startX, startY, exitX, exitY);   //it directly goes to exit without moving on path
        break;
    case 4:
        e = new BossEnemy(startX, startY); 
        break;
    }
    if (e) 
    {
        if (type != 3)             //if not flying enemy, then place checkpoints 
        {
            e->setTarget(map.get_PathX(1), map.get_PathY(1));
            e->advanceWaypoint();
        }
        enemies[enemyCount] = e;
        enemyCount++;
    }
}
void Game::cleanDeadEnemies()           //remove enemies from screen once dead
{
    for (int i = 0; i < enemyCount; i++)
    {
        if (!enemies[i])          //if nullptr (no enemies)
        {
            continue;
        }
        if (!enemies[i]->is_alive()) 
        {
            if (!enemies[i]->hasReachedEnd())
            {
                gold = gold + enemies[i]->getGoldReward(); //if enemy did not reach end then give the allocated gold to player
                ui.setGold(gold);
            }
            delete enemies[i];                //delete dead enemy
            enemies[i] = nullptr;
            for (int j = i; j < enemyCount - 1; j++)
            {
                enemies[j] = enemies[j + 1];          //move every element of array one position behind
            }
            enemies[enemyCount - 1] = nullptr;        //last positiojn nullptr
            enemyCount--;                             //an enemy number removed
            i--;
        }
    }
}
void Game::checkWaveComplete()
{
    if (!waveRunning)                   //a wave not started
    {
        return;
    }
    if (wave.isFinished() && enemyCount == 0)    //prev. wave finished and no enemy left from that wave
    {
        waveRunning = false;
        if (currentWave >= total_waves)
        {
            state = win;
        }
        else 
        {
            currentWave++;
            wave.setup(currentWave);
            ui.setWave(currentWave, total_waves);
            waveStartTimer = 3.0f;                 //3 second timer before starting next wave
            waveStarting = true;
        }
    }
}
void Game::update(float dt) 
{
    if (waveStarting)
    {
        waveStartTimer = waveStartTimer - dt;
        if (waveStartTimer <= 0.0f)               //if countdown finished start the wave
        {
            waveStarting = false;
            waveRunning = true;
            waveStartTimer = 0.0f;  
            wave.start();
        }
        return;
    }
    if (!waveRunning && !waveStarting && state == playing)
    {
        // this is handled in checkWaveComplete now
    }
    if (waveRunning)
    {
        int type = wave.getNextSpawn(dt);          //spawn new enemies till wave is running
        if (type >= 0)
        {
            spawnEnemy(type);
        }
    }
    for (int i = 0; i < enemyCount; i++)
    {
        if (!enemies[i] || !enemies[i]->is_alive())        //if enemy not alive or enemy not present
        {
            continue;
        }
        int wpIdx = enemies[i]->getWaypointIndex();   
        int totalWP = map.get_PathCount();
        float ex = enemies[i]->getX();                 //postion of enemy along x
        float ey = enemies[i]->getY();                 //postion of enemy along x
        if (wpIdx < totalWP)
        {
            float tx = map.get_PathX(wpIdx);
            float ty = map.get_PathY(wpIdx);
            float dx = tx - ex;
            float dy = ty - ey;
            float dist = dx * dx + dy * dy;
            if (dist < 100.0f)
            {
                if (wpIdx + 1 < totalWP)          //if next waypoint is less than total, can move to next
                {
                    enemies[i]->advanceWaypoint();
                    enemies[i]->setTarget(map.get_PathX(wpIdx + 1), map.get_PathY(wpIdx + 1));   //next checkpoint becomes target
                }
                else
                {
                    lives--;                       //decrease lives when an enemy reaches end
                    ui.setLives(lives);
                    enemies[i]->set_hp(0);         //that enemy's power set to 0
                    if (lives <= 0)                //if lives finished, then game over
                    {
                        state = game_over;
                    }
                }
            }
        }
        enemies[i]->update(dt);
    }
    for (int i = 0; i < towerCount; i++)
    {
        if (!towers[i])
        {
            continue;
        }
        towers[i]->attack(enemies, enemyCount, dt);             //attack on enemies
        towers[i]->updateBullets(dt);
    }
    cleanDeadEnemies();
    checkWaveComplete();
}
void Game::render() 
{
    window.clear(sf::Color::Black);
    map.render(window);
    for (int i = 0; i < towerCount; i++)
    {
        if (towers[i])
        {
            towers[i]->render(window);
            towers[i]->renderBullets(window);
        }
    }
    for (int i = 0; i < enemyCount; i++)
    {
        if (enemies[i] && enemies[i]->is_alive())
        {
            enemies[i]->render(window);
        }
    }
    renderUIPanel();
    if (waveStarting)
    {
        renderWaveCountdown();
    }
    if (state == game_over)
    {
        renderGameOver();
    }
    if (state == win)
    {
        renderWin();
    }
    window.display();
}
void Game::renderUIPanel() 
{
    if (!fontLoaded)
    {
        return;
    }
    sf::Text title;
    title.setFont(font);
    title.setCharacterSize(26);
    title.setFillColor(sf::Color(210, 200, 230));
    title.setString("TOWER DEFENSE GAME");
    title.setPosition(uiPanelX, 22);
    window.draw(title);

    sf::RectangleShape line1(sf::Vector2f(screenWidth - uiPanelX - 50, 2));
    line1.setPosition(uiPanelX, 65);
    line1.setFillColor(sf::Color(210, 200, 230));
    window.draw(line1);

    sf::Text goldText;
    goldText.setFont(font);
    goldText.setCharacterSize(20);
    goldText.setFillColor(sf::Color(220, 220, 220));
    goldText.setString("Gold: " + std::to_string(gold));
    goldText.setPosition(uiPanelX, 80);
    window.draw(goldText);

    sf::Text livesText;
    livesText.setFont(font);
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color(220, 220, 220));
    livesText.setString("Lives: " + std::to_string(lives));
    livesText.setPosition(uiPanelX, 115);
    window.draw(livesText);

    sf::Text waveText;
    waveText.setFont(font);
    waveText.setCharacterSize(20);
    waveText.setFillColor(sf::Color(220, 220, 220));
    waveText.setString("Wave: " + std::to_string(currentWave) + " / " + std::to_string(total_waves));
    waveText.setPosition(uiPanelX, 150);
    window.draw(waveText);

    sf::RectangleShape line2(sf::Vector2f(screenWidth - uiPanelX - 50, 2));
    line2.setPosition(uiPanelX, 195);
    line2.setFillColor(sf::Color(210, 200, 230));
    window.draw(line2);

    sf::Text selectLabel;
    selectLabel.setFont(font);
    selectLabel.setCharacterSize(18);
    selectLabel.setFillColor(sf::Color(220, 220, 220));
    selectLabel.setString("Select Tower (1-5):");
    selectLabel.setPosition(uiPanelX, 215);
    window.draw(selectLabel);

    const char* towerNames[] = {"1. Cannon Rs.150", "2. Sniper Rs.200", "3. MachineGun Rs.125", "4. Slow Rs.100", "5. Freeze Rs.175"};
    int btnX = uiPanelX;
    int btnWidth = screenWidth - uiPanelX - 60;
    int btnHeight = 60;
    int btnStartY = 260;

    for (int i = 0; i < 5; i++)
    {
        int btnY = btnStartY + i * (btnHeight + 10);
        sf::RectangleShape btn(sf::Vector2f(btnWidth, btnHeight));
        btn.setPosition(btnX, btnY);
        btn.setOutlineColor(sf::Color(220, 220, 220));
        btn.setOutlineThickness(3);
        btn.setFillColor(sf::Color::Transparent);
        if (ui.getSelectedTower() == i)
        {
            btn.setOutlineColor(sf::Color::Green);
            btn.setOutlineThickness(3);
        }
        else
        {
            btn.setOutlineColor(sf::Color(80, 80, 80));
            btn.setOutlineThickness(2);
        }
        window.draw(btn);

        sf::Text btnText;
        btnText.setFont(font);
        btnText.setCharacterSize(18);
        btnText.setFillColor(sf::Color(220, 220, 220));
        btnText.setString(towerNames[i]);
        btnText.setPosition(btnX + 10, btnY + 20);
        window.draw(btnText);
    }

    int instrY = btnStartY + 5 * (btnHeight + 10) + 15;

    sf::RectangleShape line3(sf::Vector2f(screenWidth - uiPanelX - 50, 2));
    line3.setPosition(uiPanelX, instrY - 5);
    line3.setFillColor(sf::Color(210, 200, 230));
    window.draw(line3);

    sf::Text instr;
    instr.setFont(font);
    instr.setCharacterSize(16);
    instr.setFillColor(sf::Color(220, 220, 220));
    instr.setString("Click green tile to place tower\n" 
        "ESC - Exit");
    instr.setPosition(uiPanelX, instrY + 5);
    window.draw(instr);
}
void Game::renderWaveCountdown()
{
    if (!fontLoaded)
    {
        return;
    }
    sf::RectangleShape bg(sf::Vector2f(445, 80));
    bg.setPosition(mapAreaWidth / 2 - 250, screenHeight / 2 - 40);
    bg.setFillColor(sf::Color(0, 0, 0, 200));
    bg.setOutlineColor(sf::Color(180, 200, 230));
    bg.setOutlineThickness(2);
    window.draw(bg);

    sf::Text waveTxt;
    waveTxt.setFont(font);
    waveTxt.setCharacterSize(26);
    waveTxt.setFillColor(sf::Color(200, 200, 200));
    waveTxt.setString("Wave " + std::to_string(currentWave) + " incoming!");
    waveTxt.setPosition(mapAreaWidth / 2 - 140, screenHeight / 2 - 35);
    window.draw(waveTxt);

    int secondsLeft = (int)waveStartTimer + 1;
    sf::Text countTxt;
    countTxt.setFont(font);
    countTxt.setCharacterSize(26);
    countTxt.setFillColor(sf::Color::Red);
    countTxt.setString("Starting in: " + std::to_string(secondsLeft));
    countTxt.setPosition(mapAreaWidth / 2 - 120, screenHeight / 2 + 5);
    window.draw(countTxt);
}
void Game::renderGameOver()
{
    bgMusic.stop();
    sf::RectangleShape overlay(sf::Vector2f(screenWidth, screenHeight));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);
    if (!fontLoaded)
    {
        return;
    }
    sf::Text txt;
    txt.setFont(font);
    txt.setCharacterSize(80);
    txt.setFillColor(sf::Color::Red);
    txt.setString("GAME OVER");
    txt.setPosition(screenWidth / 2 - 280, screenHeight / 2 - 80);
    window.draw(txt);

    sf::Text sub;
    sub.setFont(font);
    sub.setCharacterSize(26);
    sub.setFillColor(sf::Color::White);
    sub.setString("Press ESC to exit");
    sub.setPosition(screenWidth / 2 - 120, screenHeight / 2 + 30);
    window.draw(sub);
}
void Game::renderWin() 
{
    bgMusic.stop();
    sf::RectangleShape overlay(sf::Vector2f(screenWidth, screenHeight));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);
    if (!fontLoaded)
    {
        return;
    }
    sf::Text txt;
    txt.setFont(font);
    txt.setCharacterSize(80);
    txt.setFillColor(sf::Color::Green);
    txt.setString("CONGRATS YOU WIN!");
    txt.setPosition(screenWidth / 2 - 500, screenHeight / 2 - 80);
    window.draw(txt);

    sf::Text sub;
    sub.setFont(font);
    sub.setCharacterSize(26);
    sub.setFillColor(sf::Color::White);
    sub.setString("All waves defeated! Press ESC to exit.");
    sub.setPosition(screenWidth / 2 - 260, screenHeight / 2 + 30);
    window.draw(sub);
}