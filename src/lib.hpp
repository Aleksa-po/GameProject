#pragma once

#include <SFML/Graphics.hpp>
#include <ostream>
#include <sstream>
#include <xmemory>
 
using namespace sf;
///Класс Map
/**
* Создание класса, загружающего текстуры и создающего срайты для отрисовки карт уровней игры 
*/
class Map { 
public:
    /// Переменные для спрайтов блоков карты
    Image bl1i, bl2i, bl3i, bl5i; 
    Texture bl1t, bl2t, bl3t, bl5t; 
    Sprite bl1s, bl2s, bl3s, bl5s;  
    RectangleShape bg, bw; 
    /// Конструктор класса Map
    Map(); 
};

/// Класс Bonus
/**
* Создание класса, загружающего текстуры и создающего срайты для отрисовки бонусов 
*/
class Bonus {
public:
    /// Переменные для спрайтов бонуса
    Image bi; 
    Texture bt; 
    Sprite bs; 
    /// Конструктор класса Bonus
    Bonus();
};

/// Класс Player
/** Класс подгружающий изобажение игрока, хранящий и изменяющий его характеристики 
* (такие, как координата, скорость и тд). Также, отвечающий за логическую составляющую движения
* игрока и его взаимодействие со всеми другими объектами, присутствующими в игре
*/
class Player {
public:
    /// Определяет состояние игрока (жив/мерв)
    bool live; 
    /// Отвечаюn за координаты игрока 
    float px, py;
    /// Отвечают за скорость, размеры игрока 
    float pvx, pvy;
    float width, height;
    float speed = 0; 
    /// Отвечает за направление
    int dir;
    /// Отвечает за количество очков
    int score; 
    /// Файл для изображение игрока
    String picture; 
    /// Переменные для создания спрайта
    Image pi; 
    Texture pt; 
    Sprite ps; 

    /// Конструктор класса Player
    Player(String P, float X, float Y, int LM[16][32]); 
    /// Функция, определяющая как будет двигаться игрок и, в соответствии с этим, изменяющая его координаты
    void update(float time); 
    /// Функция, определяющая характеристику взаимодействия спрайта игрока с спрайтами других объектов
    void collisionMap();
};

/// Класс Menud
/**
* Загружает изображения для меню 
*/
class Menud {
public:
    /// Переменные для спрайтов меню 
    Texture menuT, But1, But2, But3; 
    Sprite M, B1, B2, B3; 
    /// Конструктор класса Menud
    Menud ();
};

/// Функция уровня
/**
*\brief задаёт выбранную карту, а также начальные координаты игрока на конкретной карте
*\param NumBut номер уровня
*/
void Level (int NumBut); 

/// Функция движений
/**
*\brief отвечает за изменение направления, скорости и текстурки игрока при нажатии клавиш движения
*\param Ghost игрок
*/
void Move(Player & Ghost);

/// Функция отрисовки 
/**
*\brief занимается отрисовкой карты, игрока, его колличества очков и, в кончном итоге, обновляет экран 
*\param window окно игры
*\param MapL карта уровня
*\param Crystal бонус на уровне
*\param Ghost игрок
*\param time время
*\param TScore - очки 
*/
void Draw(RenderWindow & window, Map & MapL, Bonus & Crystal, Player & Ghost, float time, Text TScore);

/// Функция меню
/**
*\brief отвечает за взаимодействие пользователя с глывным меню (нажатие и анимации кнопок выбора уровня)
* и экраном после успешного завершения уровня 
*\param window окно
*\param WS количество бонусов при успешном завершении уровня
*/
void menu (RenderWindow & window, int WS);

/// Функция для старта и рестарта игры
/**
*\brief отвечает за создание объктов классов, контролирует рестарт уровней и возвращение обратно в меню
*\param window окно
*/  
bool StartGame (RenderWindow & window);

/// Функция для рестарта игры
/**
*\brief отвечает за реализацию рестарта
*\param window окно
 */
void gameRunning (RenderWindow & window);
