#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Bullet
{
public:
    ///OBJECT CONSTRUCTION
    Bullet()
    {
        bullet.setRadius(2);
        bullet.setOrigin(bullet.getRadius(),bullet.getRadius());

        bullet.setFillColor(Color(0,0,0,0));
        bullet.setOutlineThickness(1);
        bullet.setOutlineColor(Color::White);
    }

    ///FUNCTION SET POS AND GET POS
    void setPos(Vector2f newPos)
    {
        bullet.setPosition(newPos);
    }
    Vector2f getPos()
    {
        Vector2f getPos(bullet.getPosition().x,bullet.getPosition().y);
        return getPos;
    }

    ///FUNCTION SET MOVE
    void setMove(Vector2f newMove)
    {
        bullet.move(newMove);
    }

    ///FUNCTION DELETE
    int Delete()
    {
        if(toDelete == true) return 1;
    }

    ///FUNCTION GET GLOBAL BOUNDS
    FloatRect getGlob()
    {
        return bullet.getGlobalBounds();
    }

    ///FUNCTION DRAW
    void drawTo(RenderWindow &window)
    {
        window.draw(bullet);
    }

    ///FUNCTION UPDATE
    int Update(int screen_width, int screen_height, int heading)
    {
        if(isDirSet == false)
        {
            rotation = heading* atan(1)*4 / 180 - (atan(1)*4 / 2);
            Vector2f force = Vector2f(cos(rotation),sin(rotation));
            veloX = force.x * magnitude;
            veloY = force.y * magnitude;
            isDirSet = true;
        }

        this->setMove({veloX,veloY});

        if(this->getPos().x >= screen_width || this->getPos().x < 0 || this->getPos().y >= screen_height || this->getPos().y < 0)
        {
            toDelete = true;
        }
    }

private:
    CircleShape bullet;

    float veloX = 0;
    float veloY = 0;
    int magnitude = 4;
    float rotation;

    bool isDirSet = false;
    bool toDelete = false;

};
