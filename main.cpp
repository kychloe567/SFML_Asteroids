#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Ship.h"
#include "Bullet.h"
#include "Asteroid.h"

using namespace std;
using namespace sf;

int screen_width = VideoMode::getDesktopMode().width;
int screen_height = VideoMode::getDesktopMode().height;

//int screen_width = 1024;
//int screen_height = 512;

Vector2f screen_center(screen_width/2,screen_height/2);
int maxAsteroids = 0;

int main()
{
    RenderWindow window(VideoMode(screen_width,screen_height), "Asteroids",Style::Close | Style::Titlebar | Style::Fullscreen);
    window.setFramerateLimit(60);

    Ship ship({screen_width/2,screen_height/2});

    Bullet bullet;
    vector<Bullet> bullets;

    Asteroid asteroid;
    vector<Asteroid> asteroids;

    srand((unsigned)time(0));
    window.clear();

    while(window.isOpen())
    {
        Event evnt;
        while(window.pollEvent(evnt))
        {
            switch(evnt.type)
            {
            case Event::Closed:
                window.close();
                break;
            }
        }

        ///SHIP KEYBOARD MOVING
        if(Keyboard::isKeyPressed(Keyboard::A))
        {
            ship.setHeading(-5);
        }
        if(Keyboard::isKeyPressed(Keyboard::D))
        {
            ship.setHeading(5);
        }
        if(Keyboard::isKeyPressed(Keyboard::W))
        {
            ship.Boost();
        }
        if(Keyboard::isKeyPressed(Keyboard::Space))
        {
            if(ship.getTimer() >= ship.getLimit())
            {
                bullets.push_back(bullet);
                bullets[bullets.size()-1].setPos({ship.getPos().x,ship.getPos().y});
                ship.setTimer(0);
            }
        }

        ///SPAWNING ASTEROIDS
        for(;maxAsteroids < 15 ; maxAsteroids++)
        {
            asteroids.push_back(asteroid);
            asteroids[asteroids.size()-1].Spawn(rand()%20 + (-10),rand()%20 + (-10),rand()%screen_width,rand()%screen_height);
        }

        ///SHIP UPDATE
        ship.Update(screen_width,screen_height);

        ///BULLETS UPDATE
        for(int i = 0; i < bullets.size(); i++)
        {
            bullets[i].Update(screen_width,screen_height,ship.getHeading());
            if(bullets[i].Delete() == 1)
            {
                bullets.erase(bullets.begin() + i);
            }
            int asteroidSize = asteroids.size();
            for(int j = 0; j < asteroidSize; j++)
            {
                if(bullets[i].getGlob().intersects(asteroids[j].getGlob()))
                {
                    if(asteroids[j].Split() == 0)
                    {
                        Vector2f tempPos = Vector2f(asteroids[j].getPos());
                        asteroids.erase(asteroids.begin() + j);

                        asteroids.push_back(asteroid);
                        asteroids[asteroids.size() - 1].setPos(tempPos);
                        asteroids[asteroids.size() - 1].setRad(20);
                        asteroids[asteroids.size() - 1].Spawn(rand()%20 + (-10),rand()%20 + (-10));
                        asteroids.push_back(asteroid);
                        asteroids[asteroids.size() - 1].setPos(tempPos);
                        asteroids[asteroids.size() - 1].setRad(20);
                        asteroids[asteroids.size() - 1].Spawn(rand()%20 + (-10),rand()%20 + (-10));
                    }
                    else if(asteroids[j].Split() == 1)
                    {
                        Vector2f tempPos = Vector2f(asteroids[j].getPos());
                        asteroids.erase(asteroids.begin() + j);

                        asteroids.push_back(asteroid);
                        asteroids[asteroids.size() - 1].setPos(tempPos);
                        asteroids[asteroids.size() - 1].setRad(10);
                        asteroids[asteroids.size() - 1].Spawn(rand()%20 + (-10),rand()%20 + (-10));
                        asteroids.push_back(asteroid);
                        asteroids[asteroids.size() - 1].setPos(tempPos);
                        asteroids[asteroids.size() - 1].setRad(10);
                        asteroids[asteroids.size() - 1].Spawn(rand()%20 + (-10),rand()%20 + (-10));
                    }
                    else if(asteroids[j].Split() == 2)
                    {
                        asteroids.erase(asteroids.begin() + j);
//                        asteroids.push_back(asteroid);
//                        asteroids[asteroids.size()-1].Spawn(rand()%20 + (-10),rand()%20 + (-10),rand()%screen_width,rand()%screen_height);
                    }
                    bullets.erase(bullets.begin() + i);
                }
            }
        }
        if(ship.getTimer() < ship.getLimit())
        {
            ship.setTimer(ship.getTimer() + 1);
        }

        ///ASTEROIDS UPDATE
        for(int i = 0 ; i < asteroids.size() ; i++)
        {
            asteroids[i].Update(screen_width,screen_height);

            if(asteroids[i].getGlob().intersects(ship.getGlob()) && ship.getIsInvincible() == false)
            {
                ship.setLives(ship.getLives() - 1);
                cout << "hit" << endl;
                ship.setPos(screen_center);
                ship.setIsInvincible(true);
                ///DEAD ->
//                if(ship.getLives() <= 0)
//                {
//                    system("pause");
//                }
            }
        }

        ///CLEARING, DRAWING, DISPLAYING
        window.clear();
        ship.drawTo(window);
        for(int i = 0; i < bullets.size(); i++)
        {
            bullets[i].drawTo(window);
        }
        for(int i = 0; i < asteroids.size() ; i++)
        {
            asteroids[i].drawTo(window);
        }
        window.display();

    }
    return 0;
}
