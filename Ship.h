#pragma once

#include <iostream>
#include <cmath>
#include <math.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Ship
{
public:
    ///OBJECT CONSTRUCTION
    Ship(Vector2f newPos)
    {
        ship.setPointCount(3);

        ship.setPoint(0, sf::Vector2f(0, 0));
        ship.setPoint(1, sf::Vector2f(-15, 40));
        ship.setPoint(2, sf::Vector2f(15, 40));

        ship.setOrigin(0,20);

        ship.setFillColor(Color(0,0,0,0));
        ship.setOutlineThickness(1);
        ship.setOutlineColor(Color::White);

        ship.setPosition(newPos);

    }

    ///FUNCTION SET POS AND GET POS
    void setPos(Vector2f newPos)
    {
        ship.setPosition(newPos);
    }
    Vector2f getPos()
    {
        Vector2f getPos(ship.getPosition().x,ship.getPosition().y);
        return getPos;
    }

    ///FUNCTION SET VELO X AND GET VELO X
    void setVeloX(int newVeloX)
    {
        veloX = newVeloX;
    }
    int getVeloX()
    {
        return veloX;
    }

    ///FUNCTION SET VELO Y AND GET VELO Y
    void setVeloY(int newVeloY)
    {
        veloY = newVeloY;
    }
    int getVeloY()
    {
        return veloY;
    }

    ///FUNCTION SET MOVE
    void setMove(Vector2f newMove)
    {
        ship.move(newMove);
    }

    ///FUNCTION SET HEADING AND GET HEADING
    void setHeading(float newHeading)
    {
        heading = newHeading;
        ship.rotate(heading);
    }
    float getHeading()
    {
        return ship.getRotation();
    }

    ///FUNCTION BOOST
    void Boost()
    {
        rotation = ship.getRotation()* atan(1)*4 / 180 - (atan(1)*4 / 2);

        Vector2f force = Vector2f(cos(rotation),sin(rotation));
        veloX += force.x;
        veloY += force.y;
    }

    ///FUNCTION SET TIMER AND GET TIMER
    void setTimer(int newTimer)
    {
        timer = newTimer;
    }
    int getTimer()
    {
        return timer;
    }

    ///FUNCTION GET LIMIT
    int getLimit()
    {
        return limit;
    }

    ///FUNCTION SET IS INVINCIBLE AND GET IS INVINCIBLE
    void setIsInvincible(bool newIsInvincible)
    {
        isInvincible = newIsInvincible;
    }
    bool getIsInvincible()
    {
        return isInvincible;
    }

    ///FUNCTION GET GLOBAL BOUNDS
    FloatRect getGlob()
    {
        return ship.getGlobalBounds();
    }

    ///FUNCTION SET LIVES AND GET LIVES
    void setLives(int newLives)
    {
        lives = newLives;
    }
    int getLives()
    {
        return lives;
    }

    ///FUNCTION DRAW
    void drawTo(RenderWindow &window)
    {
        window.draw(ship);
    }

    ///FUNCTION UPDATE
    void Update(int screen_width,int screen_height)
    {
        this->setMove({veloX,veloY});
        veloX *= friction;
        veloY *= friction;

        if(this->getPos().x >= screen_width)
        {
            this->setPos({0,this->getPos().y});
        }
        if(this->getPos().x < 0)
        {
            this->setPos({screen_width,this->getPos().y});
        }
        if(this->getPos().y >= screen_height)
        {
            this->setPos({this->getPos().x,0});
        }
        if(this->getPos().y < 0)
        {
            this->setPos({this->getPos().x,screen_height});
        }

        if(isInvincible == true)
        {
            invincibleTimer++;
            ship.setOutlineColor(Color::Red);
        }
        if(invincibleTimer >= invincibleLimit)
        {
            isInvincible = false;
            invincibleTimer = 0;
            ship.setOutlineColor(Color::White);
        }
    }
private:
    ConvexShape ship;

    float veloX = 0;
    float veloY = 0;

    float heading = 0;
    float rotation;
    float friction = 0.96;

    int timer = 0;
    int limit = 30;

    int invincibleTimer = 0;
    int invincibleLimit = 100;
    bool isInvincible = true;

    int lives = 3;
};
