#include "maze.h"
#include "genitem.h"
#include "mrhuggz.h"

#include <math.h>
#include <iostream>

#define MAX_BOMBS 1
#define MAX_DYNAMITES 1
#define INIT_AMMO 10

#define WALL_CHANCE 10
#define WEB_CHANCE 10

#define WEB_TIME 5

#define MINIMUM_GEN_DISTANCE 10
#define TILES_PER_ORB_STEP 30

#define WALL_UP "Wall_Up.png"
#define WALL_RIGHT "Wall_Right.png"
#define WALL_LEFT "Wall_Left.png"
#define WALL_DOWN "Wall_Down.png"
#define PLAYER_UP "Character_Back.png"
#define PLAYER_RIGHT "Character_Right.png"
#define PLAYER_LEFT "Character_Left.png"
#define PLAYER_DOWN "Character_Front.png"
#define KPLAYER_UP "Character_Back.png"
#define KPLAYER_DOWN "Character_Front_Key.png"
#define KPLAYER_LEFT "Character_Left_Key.png"
#define KPLAYER_RIGHT "Character_Right_Key.png"
#define FPLAYER_UP "Character_Fem_Back.png"
#define FPLAYER_RIGHT "Character_Fem_Right.png"
#define FPLAYER_LEFT "Character_Fem_Left.png"
#define FPLAYER_DOWN "Character_Fem_Front.png"
#define FKPLAYER_UP "Character_Fem_Back.png"
#define FKPLAYER_DOWN "Character_Fem_Front_Key.png"
#define FKPLAYER_LEFT "Character_Fem_Left_Key.png"
#define FKPLAYER_RIGHT "Character_Fem_Right_Key.png"
#define TILE_SPRITE "tile.png"
#define TILEH_SPRITE "tile_hidden.png"
#define TILE_SPRITE2 "tile2.png"
#define TILEH_SPRITE2 "tile_hidden2.png"
#define TILE_SPRITE3 "tile3.png"
#define TILEH_SPRITE3 "tile_hidden3.png"
#define TILE_SPRITE4 "tile4.png"
#define TILEH_SPRITE4 "tile_hidden4.png"
#define TILE_SPRITE5 "tile5.png"
#define TILEH_SPRITE5 "tile_hidden5.png"
#define TILE_SPRITE6 "tile6.png"
#define TILEH_SPRITE6 "tile_hidden6.png"
#define TILE_SPRITE7 "tile7.png"
#define TILEH_SPRITE7 "tile_hidden7.png"
#define ENEMY_UP "Enemy_Back.png"
#define ENEMY_DOWN "Enemy_Front.png"
#define ENEMY_LEFT "Enemy_Left.png"
#define ENEMY_RIGHT "Enemy_Right.png"
#define WENEMY_UP "Wall_Monster_Back.png"
#define WENEMY_DOWN "Wall_Monster_Friend.png"
#define WENEMY_LEFT "Wall_Monster_Left.png"
#define WENEMY_RIGHT "Wall_Monster_Right.png"
#define WEBENEMY_UP "Spider_Monster_Back.png"
#define WEBENEMY_DOWN "Spider_Monster_Front.png"
#define WEBENEMY_LEFT "Spider_Monster_Left.png"
#define WEBENEMY_RIGHT "Spider_Monster_Right.png"
#define BOMB_SPRITE "bomb.png"
#define DOWN_FIRE "Up_Fire.png"
#define UP_FIRE "Down_Fire.png"
#define MID_FIRE "Middle_Fire.png"
#define LEFT_FIRE "Left_Explosion.png"
#define RIGHT_FIRE "Right_Explosion.png"
#define HOR_FIRE "Middle_Horizontal_Explosion.png"
#define ORB_SPRITE "Orb_Monster.png"
#define KEY_SPRITE "key.png"
#define EXIT_SPRITE "End_Gate.png"
#define DYNAMITE_SPRITE "Dynamite.png"
#define TORCH_SPRITE "Torch_Add_Health.png"
#define AMMO_SPRITE "Explosives_Counter.png"
#define WEB_SPRITE "Web.png"
#define WEBBED0 "Web5.png"
#define WEBBED1 "Web4.png"
#define WEBBED2 "Web3.png"
#define WEBBED3 "Web2.png"
#define WEBBED4 "Web1.png"

#define PORTAL_1 "High_Health_Aperture.png"
#define PORTAL_2 "Middle_Health_Aperture.png"
#define PORTAL_3 "Low_Health_Aperture.png"

#define SOUND_EXPL "Explosion.wav"
#define SOUND_HIT "Hit_Hurt.wav"
#define SOUND_PICKUP "Pickup_Coin.wav"
#define SOUND_WEB "web.wav"
#define SOUND_DEAD "death.wav"
#define SOUND_PORTAL "portal.wav"
#define SOUND_TORCH "torch.wav"

#include <cstdlib>
#include <time.h>
#include "mazegen.h"

int Maze::getX(int x) {
    return (x-player_x)*TILE_SIZE+(WIDTH-TILE_SIZE)/2;
}

int Maze::getY(int y) {
    return (y-player_y)*TILE_SIZE+(HEIGHT-TILE_SIZE)/2;
}

bool Maze::are_opposite(int a, int b)
{
    return (a == 0 && b == 2 ||
            a == 1 && b == 3 ||
            a == 2 && b == 0 ||
            a == 3 && b == 1);
}

Maze::Maze(int w, int h, float d, int e, int l) :
    MAZE_HEIGHT(h),
    MAZE_WIDTH(w),
    MAZE_DENSITY(d),
    player({Sprite(PLAYER_UP),Sprite(PLAYER_RIGHT),Sprite(PLAYER_DOWN),Sprite(PLAYER_LEFT)}),
    key_player({Sprite(KPLAYER_UP),Sprite(KPLAYER_RIGHT),Sprite(KPLAYER_DOWN),Sprite(KPLAYER_LEFT)}),
    fplayer({Sprite(FPLAYER_UP),Sprite(FPLAYER_RIGHT),Sprite(FPLAYER_DOWN),Sprite(FPLAYER_LEFT)}),
    fkey_player({Sprite(FKPLAYER_UP),Sprite(FKPLAYER_RIGHT),Sprite(FKPLAYER_DOWN),Sprite(FKPLAYER_LEFT)}),
    wall_s({Sprite(WALL_UP),Sprite(WALL_RIGHT),Sprite(WALL_DOWN),Sprite(WALL_LEFT)}),
    enemy_s({Sprite(ENEMY_UP),Sprite(ENEMY_RIGHT),Sprite(ENEMY_DOWN),Sprite(ENEMY_LEFT)}),
    wenemy_s({Sprite(WENEMY_UP),Sprite(WENEMY_RIGHT),Sprite(WENEMY_DOWN),Sprite(WENEMY_LEFT)}),
    webenemy_s({Sprite(WEBENEMY_UP),Sprite(WEBENEMY_RIGHT),Sprite(WEBENEMY_DOWN),Sprite(WEBENEMY_LEFT)}),
    bomb(BOMB_SPRITE),
    expl(SOUND_EXPL),
    hit(SOUND_HIT),
    pickup(SOUND_PICKUP),
    sound_web(SOUND_WEB),
    dead_sound(SOUND_DEAD),
    portal_sound(SOUND_PORTAL),
    torch_sound(SOUND_TORCH),
    web(WEB_SPRITE),
    dynamite(DYNAMITE_SPRITE),
    upfire(UP_FIRE),
    downfire(DOWN_FIRE),
    midfire(MID_FIRE),
    leftfire(LEFT_FIRE),
    rightfire(RIGHT_FIRE),
    horfire(HOR_FIRE),
    portal({Sprite(PORTAL_3),Sprite(PORTAL_2),Sprite(PORTAL_1)}),
    orb_s(ORB_SPRITE),
    key(KEY_SPRITE),
    exit(EXIT_SPRITE),
    torch_s(TORCH_SPRITE),
    ammo_s(AMMO_SPRITE),
    webbed({Sprite(WEBBED0),Sprite(WEBBED1),Sprite(WEBBED2),Sprite(WEBBED3),Sprite(WEBBED4)}),
    tileh({Sprite(TILEH_SPRITE),Sprite(TILEH_SPRITE2),Sprite(TILEH_SPRITE3),Sprite(TILEH_SPRITE4),Sprite(TILEH_SPRITE5),Sprite(TILEH_SPRITE6),Sprite(TILEH_SPRITE7)}),
    tile({Sprite(TILE_SPRITE),Sprite(TILE_SPRITE2),Sprite(TILE_SPRITE3),Sprite(TILE_SPRITE4),Sprite(TILE_SPRITE5),Sprite(TILE_SPRITE6),Sprite(TILE_SPRITE7)}) {
    srand(time(NULL));
    std::cout<<"Tile size: "<<TILE_SIZE<<std::endl;
    ismale = true;
    reset(w,h,d,e,l);
}

void Maze::reset(int w, int h, float d, int e, int l) 
{
    std::cout<<"Reset("<<w<<","<<h<<","<<d<<","<<e<<","<<l<<")"<<std::endl;
    MAZE_HEIGHT = h;
    MAZE_WIDTH = w;
    MAZE_DENSITY = d;
    for (auto &row : grid) {
        row.clear();
    }
    grid.clear();
    webs.clear();

    for (int y = 0; y < h; ++y) {
        std::vector<Tile> row;
        for (int x = 0; x < w; ++x) {
            row.push_back({
                    !(y>0),
                    !(x>0),
                    !(y<(h-1)),
                    !(x<(w-1)),false});
        }
        grid.push_back(row);
    }

    std::cout<<"Generating "<<w<<"x"<<h<<" ("<<d<<")"<<std::endl;
    std::vector<wall> m = genMaze(w,h,d);
    std::cout<<"Generated!"<<std::endl;
    for (wall &w : m) {
        if (w.dir == "right") {
            grid[w.y][w.x].right = true;
            grid[w.y][w.x+1].left = true;
        }
        if (w.dir == "down") {
            grid[w.y][w.x].down = true;
            grid[w.y+1][w.x].up = true;
        }
    }

    player_x = 0; 
    player_y = 0;
    prev_player_x = 0;
    prev_player_y = 0;
    player_dir = 1;
    game_over = 0;
    health = 2;
    has_key = false;
    ammo = INIT_AMMO;
    win = false;
    enemycount = e;
    level = l;
    stucktime = 0;

    std::vector<int> keyloc = generateThing(player_x,player_y,w,h,MINIMUM_GEN_DISTANCE);
    key_or_exit = {keyloc[0], keyloc[1]};

    std::vector<int> torchloc = generateThing(player_x,player_y,w,h,MINIMUM_GEN_DISTANCE);
    torch = {torchloc[0], torchloc[1]};

    orb.x = (MAZE_WIDTH-1) * TILE_SIZE;
    orb.y = (MAZE_HEIGHT-1) * TILE_SIZE;

    enemies.clear();
    bombs.clear();
    dynamites.clear();
    blown_columns.clear();
    blown_rows.clear();
}

void Maze::collision_check()
{
    for (int i=0; i < enemies.size(); ++i) {

        if (enemies[i].x == player_x && enemies[i].y == player_y) {
            health--;
            hit.play();
            if (health < 0) {
                health = 0;
                game_over = enemies[i].type+1;
            }
            enemies.erase(enemies.begin() + i);
            continue;
        }
    }

    for (int i=0; i < webs.size(); ++i) {
        if (webs[i].x == player_x && webs[i].y == player_y) {
            stucktime += WEB_TIME;
            webs.erase(webs.begin() + i);
            sound_web.play();
            break;
        }
    }

    if (collision(TILE_SIZE/2, 
                  orb.x + TILE_SIZE/2,
                  orb.y + TILE_SIZE/2,
                  player_x * TILE_SIZE,
                  player_y * TILE_SIZE + TILE_SIZE/3,
                  (player_x+1)*TILE_SIZE,
                  (player_y+1)*TILE_SIZE - TILE_SIZE/3)) {
        dead_sound.play();
        game_over=-1;
    }
    //if (sqrt((orb.x-player_x*TILE_SIZE)*(orb.x-player_x*TILE_SIZE)+(orb.y-player_y*TILE_SIZE)*(orb.y-player_y*TILE_SIZE)) < TILE_SIZE/2)
    
    if (key_or_exit.x == player_x && key_or_exit.y == player_y) {
        if (!has_key) {
            has_key = true;
            pickup.play();
            std::vector<int> exitloc = generateThing(player_x,player_y,MAZE_WIDTH,MAZE_HEIGHT,MINIMUM_GEN_DISTANCE);
            key_or_exit = {exitloc[0], exitloc[1]};
        } else { 
            win = true; 
            portal_sound.play();
        }
    }

    if (torch.x == player_x && torch.y == player_y) {
        if (health < 2) ++health;
        std::vector<int> torchloc = generateThing(player_x,player_y,MAZE_WIDTH,MAZE_HEIGHT,MINIMUM_GEN_DISTANCE);
        torch = {torchloc[0], torchloc[1]};
        torch_sound.play();
    }
}

void Maze::onStep() {
    if (game_over) return;
    for (int i=0; i < enemies.size(); ++i) {

        if (enemies[i].x == player_x && enemies[i].y == player_y) {
            health--;
            if (health < 0) {
                health = 0;
                game_over = enemies[i].type + 1;
            }
            enemies.erase(enemies.begin() + i);
            continue;
        }

        if (rand() % 3 == 0) {
            enemies[i].move();
            for (int ii=0; ii < enemies.size(); ++ii) {
                if (i != ii && enemies[ii].x == enemies[i].x && 
                               enemies[ii].y == enemies[i].y &&
                               enemies[ii].dir == enemies[i].dir)
                    enemies[i].unmove();
            }
            if (enemies[i].y > MAZE_HEIGHT+1 ||
                enemies[i].y < -1 ||
                enemies[i].x > MAZE_WIDTH+1 ||
                enemies[i].x < -1) enemies.erase(enemies.begin() + i);
        }

        if (enemies[i].type == 1 && rand()%WALL_CHANCE == 0) {
            if (enemies[i].y >= 0 && enemies[i].x >= 0 &&
                enemies[i].y < MAZE_HEIGHT && enemies[i].x < MAZE_WIDTH) {
                switch (rand() % 4) {
                    case 0: grid[enemies[i].y][enemies[i].x].up = true; break;
                    case 1: grid[enemies[i].y][enemies[i].x].right = true; break;
                    case 2: grid[enemies[i].y][enemies[i].x].down = true; break;
                    case 3: grid[enemies[i].y][enemies[i].x].left = true; break;
                }
            }
        }

        if (enemies[i].type == 2 && rand()%WEB_CHANCE == 0) {
            webs.push_back({enemies[i].x, enemies[i].y});
        }

        for (int b=0; b < bombs.size(); ++b) {
            if (bombs[b].x == enemies[i].x && bombs[b].y == enemies[i].y) {
                blow_column(bombs[b].x);
                bombs.erase(bombs.begin()+b);
                expl.play();
                break;
            }
        }

        for (int d=0; d < dynamites.size(); ++d) {
            if (dynamites[d].x == enemies[i].x && dynamites[d].y == enemies[i].y) {
                blow_row(dynamites[d].y);
                dynamites.erase(dynamites.begin()+d);
                break;
            }
        }
    }

    collision_check();

    for (int i=0; i < enemycount; ++i) {
        if (rand() % 2) enemies.push_back(Enemy(MAZE_WIDTH,MAZE_HEIGHT));
    }


    grid[player_y][player_x].revealed = true;
}

void Maze::onDraw(Graphics &g) {
    if (game_over) return;

    //move orb
    int rpx = player_x * TILE_SIZE + TILE_SIZE/2;
    int rpy = player_y * TILE_SIZE + TILE_SIZE/2;
    Orb dorb = {rpx - orb.x,
                rpy - orb.y};
    dorb.x -= TILE_SIZE/2;
    dorb.y -= TILE_SIZE/2;
    float len = sqrt((double)(dorb.x*dorb.x + dorb.y*dorb.y));
    dorb.x *= (TILE_SIZE/TILES_PER_ORB_STEP)/len;
    dorb.y *= (TILE_SIZE/TILES_PER_ORB_STEP)/len;
    orb.x += dorb.x;
    orb.y += dorb.y;

    for (int y = 0; y < MAZE_HEIGHT; ++y) {
        for (int x = 0; x < MAZE_WIDTH; ++x) {
            int left = getX(x);
            int top = getY(y);
            if (grid[y][x].revealed) 
                tile[level%7].draw(g,left, top, TILE_SIZE,TILE_SIZE);
            else 
                tileh[level%7].draw(g,left,top, TILE_SIZE,TILE_SIZE);
            if (grid[y][x].up) wall_s[0].draw(g,left,top,TILE_SIZE,TILE_SIZE);
            if (grid[y][x].down) wall_s[2].draw(g,left,top,TILE_SIZE,TILE_SIZE);
            if (grid[y][x].right) wall_s[1].draw(g,left,top,TILE_SIZE,TILE_SIZE);
            if (grid[y][x].left) wall_s[3].draw(g,left,top,TILE_SIZE,TILE_SIZE);
        }
    }

    if (!has_key) {
        key.draw(g,getX(key_or_exit.x),getY(key_or_exit.y),TILE_SIZE,TILE_SIZE);
        if (ismale)
            player[player_dir].draw(g,getX(player_x),getY(player_y),TILE_SIZE,TILE_SIZE);
        else
            fplayer[player_dir].draw(g,getX(player_x),getY(player_y),TILE_SIZE,TILE_SIZE);
    } else {
        exit.draw(g,getX(key_or_exit.x),getY(key_or_exit.y),TILE_SIZE,TILE_SIZE);
        if (ismale)
            key_player[player_dir].draw(g,getX(player_x),getY(player_y),TILE_SIZE,TILE_SIZE);
        else
            fkey_player[player_dir].draw(g,getX(player_x),getY(player_y),TILE_SIZE,TILE_SIZE);
    }


    for (auto &enemy : enemies) {
        switch (enemy.type) { 
            case 0: 
                enemy_s[enemy.dir].draw(g,getX(enemy.x), 
                       getY(enemy.y),
                       TILE_SIZE, TILE_SIZE);
                break;
            case 1: 
                wenemy_s[enemy.dir].draw(g,getX(enemy.x),
                        getY(enemy.y), TILE_SIZE, TILE_SIZE);
                break;
            case 2:
                webenemy_s[enemy.dir].draw(g,getX(enemy.x),
                        getY(enemy.y), TILE_SIZE, TILE_SIZE);
                break;
        }
    }

    for (auto &w : webs) {
        web.draw(g,getX(w.x),getY(w.y),TILE_SIZE,TILE_SIZE);
    }

    for (auto &b : bombs) {
        bomb.draw(g,getX(b.x),
                    getY(b.y),
                    TILE_SIZE, TILE_SIZE);
    }
    for (auto &d : dynamites) {
        dynamite.draw(g,getX(d.x),getY(d.y),TILE_SIZE,TILE_SIZE);
    }
    prev_player_x = player_x;
    prev_player_y = player_y;

    for (int i=0; i < blown_columns.size(); ++i) {
        downfire.draw(g,getX(blown_columns[i]),getY(0),TILE_SIZE,TILE_SIZE);
        for (int y = 1; y < MAZE_HEIGHT-1; ++y)
            midfire.draw(g,getX(blown_columns[i]),getY(y),TILE_SIZE,TILE_SIZE);
        upfire.draw(g,getX(blown_columns[i]),getY(MAZE_HEIGHT-1),TILE_SIZE,TILE_SIZE);
    }
    blown_columns.clear();

    for (int i=0; i < blown_rows.size(); ++i) {
        leftfire.draw(g,getX(0),getY(blown_rows[i]),TILE_SIZE,TILE_SIZE);
        for (int x = 1; x < MAZE_WIDTH-1; ++x)
            horfire.draw(g,getX(x),getY(blown_rows[i]),TILE_SIZE,TILE_SIZE);
        rightfire.draw(g,getX(MAZE_WIDTH-1),getY(blown_rows[i]),TILE_SIZE,TILE_SIZE);
    }
    blown_rows.clear();

    portal[health].draw(g,0,0,WIDTH,HEIGHT);

    if (stucktime) {
        webbed[stucktime-1].draw(g,0,0,WIDTH,HEIGHT);
    } 
    torch_s.draw(g,getX(torch.x),getY(torch.y),TILE_SIZE,TILE_SIZE);
    orb_s.draw(g,orb.x+getX(0),orb.y+getY(0),TILE_SIZE,TILE_SIZE);

    if (bombs.size() > 0) {
        bomb.draw(g,0,0,TILE_SIZE,TILE_SIZE);
    }

    if (dynamites.size() > 0) {
        dynamite.draw(g,TILE_SIZE,0,TILE_SIZE,TILE_SIZE);
    }

    if (has_key) {
        key.draw(g,0, HEIGHT - TILE_SIZE, TILE_SIZE, TILE_SIZE);
    }

    for (int i=0; i < ammo; ++i) {
        ammo_s.draw(g,WIDTH-(i*TILE_SIZE),0,TILE_SIZE,TILE_SIZE);
    }
}

void Maze::onUp() {
    if (stucktime) { stucktime--; return; }
    grid[player_y][player_x].revealed = true;
    if (!grid[player_y][player_x].up) {
        player_y--;
        collision_check();
    }
    player_dir = 0;
}

void Maze::onDown() {
    if (stucktime) { stucktime--; return; }
    grid[player_y][player_x].revealed = true;
    if (!grid[player_y][player_x].down) {
        player_y++;
        collision_check();
    }
    player_dir = 2;
}

void Maze::onRight() {
    if (stucktime) { stucktime--; return; }
    grid[player_y][player_x].revealed = true;
    if (!grid[player_y][player_x].right) {
        player_x++;
        collision_check();
    }
    player_dir = 1;
}

void Maze::onLeft() {
    if (stucktime) { stucktime--; return; }
    grid[player_y][player_x].revealed = true;
    if (!grid[player_y][player_x].left) {
        player_x--;
        collision_check();
    }
    player_dir = 3;
}

void Maze::onA() {
    if (ammo > 0 && bombs.size() < MAX_BOMBS) {
        bombs.push_back({player_x,player_y});
        ammo--;
    }
}

void Maze::onB() {
    if (ammo > 0 && dynamites.size() < MAX_DYNAMITES) {
        dynamites.push_back({player_x,player_y});
        ammo--;
    }
}

void Maze::blow_column(int x) {
    for (auto i = enemies.begin(); i != enemies.end(); ++i) {
        if (i->x == x) { enemies.erase(i); blow_column(x); return; }
    }
    for (auto i = webs.begin(); i != webs.end(); ++i) {
        if (i->x == x) { webs.erase(i); blow_column(x); return; }
    }
    grid[0][x].down = false;
    for (int y = 1; y < MAZE_HEIGHT - 1; ++y) {
        grid[y][x].up = false;
        grid[y][x].down = false;
    }
    grid[MAZE_HEIGHT-1][x].up = false;

    blown_columns.push_back(x);
}

void Maze::blow_row(int y) {
    for (auto i = enemies.begin(); i != enemies.end(); ++i) {
        if (i->y == y) { enemies.erase(i); blow_row(y); return; }
    }
    for (auto i = webs.begin(); i != webs.end(); ++i) {
        if (i->y == y) { webs.erase(i); blow_row(y); return; }
    }
    grid[y][0].right = false;
    for (int x = 1; x < MAZE_WIDTH - 1; ++x) {
        grid[y][x].right = false;
        grid[y][x].left = false;
    }
    grid[y][MAZE_WIDTH-1].left = false;

    blown_rows.push_back(y);
}
