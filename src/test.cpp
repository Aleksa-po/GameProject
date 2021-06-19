#include "lib.hpp"
#include <catch.hpp>
#include <Windows.h>

int TestMap[16][32] = 
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

TEST_CASE("Checking coordinates over time_1") {
    int LM[16][32];
    Player test1("player.png", 0, 0, LM);
    test1.dir = 1; 
    test1.speed = 0.14;
    test1.update(200);
    REQUIRE(test1.px == 28);
    REQUIRE(test1.py == 0);
}


TEST_CASE("Checking coordinates over time_2") { 
    int LM[16][32];
    Player test2("player.png", 10, 5, LM);
    test2.dir = 3; 
    test2.speed = 0.14;
    test2.update(100);
    REQUIRE((test2.px, test2.py) == (400, 214));
}

/*
TEST_CASE("Checking player's move_2") {
    int LM[16][32];
    Player test4("player.png", 0, 0, LM);
    test4.speed = 0.14;
    test4.dir = 1;
    test4.live = true;
    while (test4.live) {
        Move(test4);
        keybd_event (VK_UP,0,0,0);
        keybd_event (VK_UP,0,KEYEVENTF_KEYUP,0);
        Sleep(50);
        test4.live = false;
    }
    REQUIRE(test4.speed == 0.14f);
    REQUIRE(test4.dir == 1);
}
*/

TEST_CASE("Checking collision_1") {
    Player test5("player.png", 6, 6, TestMap);
    bool A = true;
    bool StartMenu = false;
    bool WIN = false;
    test5.live = true;
    test5.score = 0;
    test5.speed = 0.14;
    test5.pvx = test5.speed;
    test5.pvy = 0;
    test5.height = 38;
    test5.width = 38;
    test5.px = 281;
    test5.collisionMap();
    REQUIRE(((A) && (test5.live)) == true);
    REQUIRE(((StartMenu) && (WIN)) == false );
    REQUIRE(test5.score == 1);
    REQUIRE(test5.pvx == 0.14f);
    REQUIRE(test5.speed == 0.14f);
    REQUIRE(test5.pvy == 0);
}
