#include "lib.hpp"

#include <SFML/Graphics.hpp>
#include <ostream>
#include <sstream>
#include <string>
#include <xmemory>

using namespace std;
using namespace sf;

/// "Масштаб" 
int markup = 40; 
/// Единичный размер по горизонтали 
int horizontalLine = 32; 
/// Единичный размер по вертикали
int verticalLine = 16; 
/// Началые координаты игрока
int x, y; 
/// Номер уровня, количество очков игрока
int NumBut = 0, point = 0; 
/// Отвечают за работу меню и необходимость рестарта соответственно
bool StartMenu = 1, A = 1; 
/// Выиграл игрок уровень или нет
bool WIN = 0; 
/// Карта, выбранного игроком уровня
int LM[16][32]; 

/** Карты уровней игры
* 0 - игровое поле c поинтами, 1 - черный фон, 2 - бонусы, 3 - стенки, 
* 4 - игровое поле без поинтов, 5 - Смертельные блоки, 6 - конец уровня 
*/
int GameMap1[16][32] = 
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,3,0,0,0,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,3,0,4,0,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,3,0,2,0,0,0,0,0,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,3,3,3,0,3,3,3,0,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,3,0,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,3,0,3,0,0,0,3,0,0,0,0,3,3,0,0,0,3,3,1,1,1,1,1,1,
    1,1,1,1,1,1,1,3,3,0,3,0,3,3,3,0,4,4,0,3,3,0,0,0,0,3,1,1,1,1,1,1,
    1,1,1,3,3,3,3,3,0,0,3,0,3,1,3,2,0,0,0,0,0,0,3,3,0,3,3,3,3,1,1,1,
    1,1,1,3,0,0,2,3,0,3,3,0,3,3,3,3,3,3,0,3,3,3,3,3,2,0,0,6,3,1,1,1,
    1,1,1,3,0,0,0,3,0,3,3,0,0,0,0,0,0,0,0,3,1,1,1,3,3,3,3,3,3,1,1,1,
    1,1,1,3,0,0,0,3,0,0,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,3,0,4,0,0,0,0,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

int GameMap2[16][32] = 
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,3,0,0,0,0,0,3,3,0,0,0,0,3,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,3,0,4,4,3,0,3,3,0,3,2,0,3,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,5,0,0,0,0,0,0,0,0,3,0,0,3,3,3,1,1,1,1,1,
    1,1,1,1,1,3,3,3,3,1,1,1,3,3,3,3,3,0,3,3,3,3,0,0,0,0,3,1,1,1,1,1,
    1,1,1,1,1,3,4,0,3,1,1,1,1,1,1,1,3,0,0,0,3,3,3,3,3,0,3,1,1,1,1,1,
    1,1,1,1,1,3,2,0,3,1,1,1,1,3,3,3,3,3,3,0,3,1,1,1,3,0,3,1,1,1,1,1,
    1,1,1,1,1,3,3,0,3,1,1,1,1,3,0,0,0,0,0,0,3,1,3,5,3,0,3,1,1,1,1,1,
    1,1,1,1,1,3,0,0,5,1,1,1,1,3,0,3,3,3,3,3,3,1,3,0,0,0,3,1,1,1,1,1,
    1,1,1,1,1,3,0,3,3,1,1,1,1,3,0,0,0,0,0,0,3,1,3,0,3,3,3,1,1,1,1,1,
    1,1,1,1,1,3,0,3,3,3,3,3,3,3,3,3,3,4,4,0,3,1,3,0,2,0,3,1,1,1,1,1,
    1,1,1,1,1,3,0,3,3,5,0,0,0,0,3,3,3,4,4,0,3,1,3,0,0,0,3,1,1,1,1,1,
    1,1,1,1,1,3,0,0,0,0,0,3,2,0,0,0,0,0,0,0,3,1,3,3,3,6,3,1,1,1,1,1,
    1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,3,3,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

int GameMap3[16][32] = 
{
    3,3,3,3,3,3,5,3,3,3,3,5,3,3,3,3,3,3,5,3,3,3,3,3,3,3,3,3,3,3,3,3,
    3,3,0,0,0,0,0,0,0,2,3,0,0,0,0,0,3,3,0,0,0,3,3,3,3,3,3,3,3,3,6,3,
    3,0,0,0,0,3,0,0,0,0,3,0,3,0,4,0,3,3,0,4,0,3,3,3,3,3,3,3,3,3,0,3,
    3,0,3,3,3,3,3,3,3,3,3,0,3,0,0,0,0,0,0,3,0,2,0,0,0,0,3,0,0,3,0,3,
    3,0,3,3,3,0,0,0,0,0,0,0,3,0,4,3,4,4,0,4,0,3,3,3,0,0,0,0,0,3,0,3,
    3,0,0,0,3,0,0,4,0,3,3,0,4,0,4,3,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,3,
    3,0,4,0,3,0,0,3,0,0,0,0,0,0,3,3,0,4,0,4,3,0,3,0,0,0,3,0,0,0,3,3,
    3,0,0,0,0,0,0,3,0,0,3,3,3,3,3,4,0,4,0,3,3,0,3,3,0,3,3,0,0,3,3,3,
    3,3,3,0,3,0,0,4,0,0,3,0,0,0,0,0,2,0,0,0,0,0,3,0,0,3,3,0,3,3,3,3,
    3,0,0,0,3,0,0,0,0,0,3,0,4,0,4,4,0,3,0,4,3,3,0,0,0,0,0,0,0,0,0,3,
    3,0,4,4,3,3,3,3,0,0,3,0,4,0,4,4,0,3,0,0,0,0,0,0,3,4,0,0,3,4,0,3,
    3,0,0,0,0,0,0,0,0,0,3,0,4,0,4,4,0,3,0,0,2,0,0,0,0,0,0,0,0,0,0,3,
    3,0,0,2,0,0,0,3,3,3,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,
    3,3,3,4,4,0,3,3,3,3,0,0,3,0,0,0,0,3,3,3,0,4,0,0,0,4,0,3,0,4,4,3,
    3,4,0,0,0,0,3,2,0,0,0,0,3,4,4,4,3,3,3,3,0,0,0,0,0,3,0,0,0,4,4,5,
    3,3,3,5,3,3,3,3,3,3,3,3,3,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
};

Map::Map() {
    bl1i.loadFromFile("images/bl1.png");
    bl1t.loadFromImage(bl1i);
    bl1s.setTexture(bl1t);

    bl2i.loadFromFile("images/bl2.png");
    bl2t.loadFromImage(bl2i);
    bl2s.setTexture(bl2t);

    bl3i.loadFromFile("images/bl3.png");
    bl3t.loadFromImage(bl3i);
    bl3s.setTexture(bl3t);

    bl5i.loadFromFile("images/bl5.png");
    bl5t.loadFromImage(bl5i);
    bl5s.setTexture(bl5t);

    bg.setSize(Vector2f(markup, markup));
    bg.setFillColor(Color::Black);

    bw.setSize(Vector2f(markup, markup));
    bw.setFillColor(Color(0, 255, 0, 70));
}

Bonus::Bonus() {
    bi.loadFromFile("images/bonus.png");
    bt.loadFromImage(bi);
    bs.setTexture(bt);
}

Player::Player(String P, float X, float Y, int LM[16][32]) {
    speed = 0;
    live = true;
    dir = 0;
    score = 0;
    width = 38;
    height = 38;
    picture = P;
    pi.loadFromFile("images/" + picture);
    pt.loadFromImage(pi);
    ps.setTexture(pt);
    px = X*markup;
    py = Y*markup;
    ps.setTextureRect(IntRect(0, 0, width, height));
}
    
void Player::update(float time) {
    switch (dir) 
    {
        /// Движение влево
        case 0: pvx = -speed; pvy = 0; break; 
        /// Движение вправо
        case 1: pvx = speed; pvy = 0; break; 
        /// Движение вверх
        case 2: pvx = 0; pvy = -speed; break; 
        /// Движение вниз
        case 3: pvx = 0; pvy = speed; break; 
    }

    px += pvx*time;
    py += pvy*time;
    ps.setPosition(px, py);
    collisionMap();
}

void Player::collisionMap() {
    for (int i = py/40; i < (py + height)/40; i++) {
        for (int j = px/40; j < (px + width)/40; j++) {
            /// Условие, отвечающее за взаимодейстие игрока со стенкой
            if (LM[i][j] == 3 ) { 
                if (pvx < 0) {
                    px = (j+1)*markup;
                    speed = 0;
                }
                if (pvx > 0) {
                    px = (j*markup)-width;
                    speed = 0;
                }
                if (pvy < 0) {
                    py = (i+1)*markup;
                    speed = 0;
                }
                if (pvy > 0) {
                    py = (i*markup)-height; 
                    speed = 0;
                }
            }
            /// Прибавление очков при взаимодействии с бонусом
            if (LM[i][j] == 2 ) { 
                score+=10;
                LM[i][j] = 4;
            }
            /// Прибавление очков при взаимодействии с поинтомм
            if (LM[i][j] == 0 ) { 
                score++;
                LM[i][j] = 4;
            }
            /// Условие, отвечающее за рестарт при вз-ии с "плохим" блоком
            if (LM[i][j] == 5 ) { 
                live = false;
                speed = 0;
                A = false;
            }
            /// Условие, отвечающее за победу игрока
            if (LM[i][j] == 6 ) {  
                StartMenu = true;
                live = 0;
                WIN = true;
                speed = 0;
            }
        }
    }

}

Menud::Menud() {
    menuT.loadFromFile("images/menu.png");
    But1.loadFromFile("images/1.png");
    But2.loadFromFile("images/2.png");
    But3.loadFromFile("images/3.png");

    M.setTexture(menuT);
    B1.setTexture(But1);
    B2.setTexture(But2);
    B3.setTexture(But3);
}

void menu (RenderWindow & window, int WS) {

    Font FInfo;
    FInfo.loadFromFile("font/Abaddon Bold.ttf");
    Text TInfo ("Go to menu - Esc   Restart - Space", FInfo, 20);
    
    int Score = WS;
    Text WinScore("", FInfo, 100);
    ostringstream SWin;
    SWin << Score;
    WinScore.setString("Score: " + SWin.str());
    WinScore.setPosition (440, 320);
    TInfo.setPosition(470, 555);
    TInfo.setColor(Color::White); 
    WinScore.setColor(Color::White);

    Menud MenuD;

    while (StartMenu) {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                {StartMenu = false; window.close();}
        }

        window.clear();
        window.draw(MenuD.M);
        window.draw(TInfo);

        ///Действия, выполняющиеся на экране меню, если это не экран победы
        if (!WIN) { 
            NumBut = 0;

            /// Кординаты кнопок и заднего фона в главном меню
            MenuD.M.setPosition(0,0);
            MenuD.B1.setPosition(300,400);
            MenuD.B2.setPosition(540,400);
            MenuD.B3.setPosition(780,400);
        
            /// Условия, создающие анимацию для кнопок при наведении на них кусора
            if (IntRect(300, 400, 200, 80).contains(Mouse::getPosition(window))) { MenuD.B1.setPosition(304,396); NumBut = 1; }
            if (IntRect(540, 400, 200, 80).contains(Mouse::getPosition(window))) { MenuD.B2.setPosition(544,396); NumBut = 2; }
            if (IntRect(780, 400, 200, 80).contains(Mouse::getPosition(window))) { MenuD.B3.setPosition(784,396); NumBut = 3; }

            /// Условие, отвечающее за нажатие на кнопки выборауровня и дальнейшее зарытие меню
            if (Mouse::isButtonPressed(Mouse::Left)) {
                switch (NumBut) {
                case 1: {StartMenu = false;}
                case 2: {StartMenu = false;}
                case 3: {StartMenu = false;}
                }
            } 
            
            window.draw(MenuD.B1);
            window.draw(MenuD.B2);
            window.draw(MenuD.B3);
            window.display();
        } else { 
            /// Действия, выполняющиеся в меню при прохождени игроком уровня
            window.draw(WinScore);
            WIN = false;
            window.display();
            while (StartMenu) {
                /// Переход из экрана победы, на экан выбора уровня
                if (Keyboard::isKeyPressed(Keyboard::Escape)) {menu(window, 0);} 
                /// Позволяет сдлелать рестарт игры и снова пройти, уже пройденный уровень
                if (Keyboard::isKeyPressed(Keyboard::Space)) {StartMenu = false;}
            }
        }
            
    }
    
}

void Level (int NumBut) {
    if (NumBut == 1) { 
        x = 5;
        y = 13;
        for (int i = 0; i < verticalLine; i++) {
            for (int j = 0; j < horizontalLine; j++) {
                LM[i][j] = GameMap1[i][j];
            }
        }
    } else if (NumBut == 2) {
        x = 6;
        y = 6;
        for (int i = 0; i < verticalLine; i++) {
            for (int j = 0; j < horizontalLine; j++) {
                LM[i][j] = GameMap2[i][j];
            }
        }
    } else {
        x = 1;
        y = 14;
        for (int i = 0; i < verticalLine; i++) {
            for (int j = 0; j < horizontalLine; j++) {
                LM[i][j] = GameMap3[i][j];
            }
        }
    }
}

void Move(Player & Ghost) {

    if ((Keyboard::isKeyPressed(Keyboard::Left))&&(Ghost.speed == 0)) {
        Ghost.dir = 0; 
        Ghost.speed = 0.14;
        Ghost.ps.setTextureRect(IntRect(38, 38, 38, 38)); 
    } 
    if ((Keyboard::isKeyPressed(Keyboard::Right))&&(Ghost.speed == 0)) {
        Ghost.dir = 1; 
        Ghost.speed = 0.14;
        Ghost.ps.setTextureRect(IntRect(38, 0, 38, 38));  
    } 
    if ((Keyboard::isKeyPressed(Keyboard::Up))&&(Ghost.speed == 0)) {
        Ghost.dir = 2; 
        Ghost.speed = 0.14;
    }
    if ((Keyboard::isKeyPressed(Keyboard::Down))&&(Ghost.speed == 0)) {
        Ghost.dir = 3;
        Ghost.speed = 0.14;
    }
}

void Draw(RenderWindow & window, Map & MapL, Bonus & Crystal, Player & Ghost, float time, Text TScore) {
    for (int i = 0; i < verticalLine; i++) {
        for (int j = 0; j < horizontalLine; j++) {
            if (LM[i][j] == 0 ) {
                MapL.bl3s.setPosition(j * markup, i * markup);
                window.draw(MapL.bl3s);
            } else if (LM[i][j] == 3 ) {
                MapL.bl2s.setPosition(j * markup, i * markup);
                window.draw(MapL.bl2s);
            } else if (LM[i][j] == 1 ) {
                MapL.bg.setPosition(j * markup, i * markup);
                window.draw(MapL.bg);
            } else if (LM[i][j] == 4 ) {
                MapL.bl1s.setPosition(j * markup, i * markup);
                window.draw(MapL.bl1s);
            } else if (LM[i][j] == 5 ) {
                MapL.bl5s.setPosition(j * markup, i * markup);
                window.draw(MapL.bl5s);
            } else if (LM[i][j] == 2 ) {
                MapL.bl1s.setPosition(j * markup, i * markup);
                window.draw(MapL.bl1s);
                Crystal.bs.setPosition(j * markup, i * markup);
                window.draw(Crystal.bs);
            } else {
                MapL.bw.setPosition(j * markup, i * markup);
                MapL.bl1s.setPosition(j * markup, i * markup);
                window.draw(MapL.bl1s);
                window.draw(MapL.bw);
            }
        }
    }
    Ghost.update(time);
    window.draw(Ghost.ps);
    window.draw(TScore);
    window.display();
}

bool StartGame (RenderWindow & window) {
    menu(window, point);
    Clock clock;
    Level (NumBut);

    Player Ghost("player.png", x, y, LM);
    Bonus Crystal;
    Map MapL;

    Font FScore;
    FScore.loadFromFile("font/Abaddon Bold.ttf");
    Text TScore("", FScore, 45);
    TScore.setColor(Color::White); 
    
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds(); 
        clock.restart(); 
        time = time/500;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {window.close(); }
        }

        if (Ghost.live) {
            
            ostringstream SScore;
            SScore << Ghost.score;
            point = Ghost.score;
            TScore.setString("Score: " + SScore.str());
            TScore.setPosition(10, -6);
            Move(Ghost);
        }

        /// Условие, отвечающее за возвращение в меню при нажатии Esc или поподании на экран победы
        if ((Keyboard::isKeyPressed(Keyboard::Escape))||(StartMenu)) {A = false; StartMenu = true; }

        /// Условие, отвечающее за рестарт игры при нажатии на пробел
        if ((Keyboard::isKeyPressed(Keyboard::Space))||(!A)) { return true; }
        
        window.clear();
        Draw(window, MapL, Crystal, Ghost, time, TScore);
    }
    return 0;
}

void gameRunning (RenderWindow & window) { 
    if (StartGame(window)) {
        A = true; gameRunning(window); 
    } 
}