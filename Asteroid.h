#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Asteroid
{
public:
    ///OBJECT CONSTRUCTION
    Asteroid()
    {
        asteroid.setPointCount(8);
        asteroid.setRadius(40);
        asteroid.setOrigin(asteroid.getRadius(),asteroid.getRadius());

        asteroid.setFillColor(Color(0,0,0,0));
        asteroid.setOutlineThickness(1);
        asteroid.setOutlineColor(Color::White);
    }

    ///FUNCTION SET POS AND GET POS
    void setPos(Vector2f newPos)
    {
        asteroid.setPosition(newPos);
    }
    Vector2f getPos()
    {
        Vector2f getPos(asteroid.getPosition().x,asteroid.getPosition().y);
        return getPos;
    }

    ///FUNCTION SET RAD
    void setRad(int newRad)
    {
        asteroid.setRadius(newRad);
        asteroid.setOrigin(asteroid.getRadius(),asteroid.getRadius());
    }

    ///FUNCTION SET MOVE
    Vector2f setMove(Vector2f newMove)
    {
        asteroid.move(newMove);
    }

    ///FUNCTION SPAWN
    void Spawn(float veloX,float veloY,int posX,int posY)
    {
        asteroid.setPosition(posX,posY);
        velo = Vector2f(veloX/10,veloY/10);
    }

    ///FUNCTION SPAWNSPLIT
    void Spawn(float veloX,float veloY)
    {
        velo = Vector2f(veloX/10,veloY/10);
    }

    ///FUNCTION GET GLOBAL BOUNDS
    FloatRect getGlob()
    {
        return asteroid.getGlobalBounds();
    }

    ///FUNCTION SPLIT
    int Split()
    {
        if(asteroid.getRadius() == 40)
        {
            return 0;
        }
        if(asteroid.getRadius() == 20)
        {
            return 1;
        }
        if(asteroid.getRadius() == 10)
        {
            return 2;
        }
    }

    ///FUNCTION DRAW
    void drawTo(RenderWindow &window)
    {
        window.draw(asteroid);
    }

    ///FUNCTION UPDATE
    void Update(int screen_width, int screen_height)
    {
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

        asteroid.move(velo);
    }
private:
    CircleShape asteroid;

    Vector2f velo = Vector2f(0,0);

};
