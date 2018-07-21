#pragma once
// Definition:
// The factory method pattern defines an interface for creating a object, but
// lets sub classes decide which class to instantiate. Factory method lets a
// class defer instantiation to sub classes.

// You want an object, but you don't necessarily know how you want to construct
// that object, why you want to construct that object and what parameters to 
// pass to create that object.

#include <iostream>
#include <memory>

struct vec2
{
    int x, y;
};

void printVec2(vec2 v)
{
    std::cout << "(" << v.x << ", " << v.y << ")";
}

class IObstacle
{
public:
    virtual void printContents() = 0;
protected:
    IObstacle(vec2 speed, vec2 size) : m_speed(speed), m_size(size) {}

    vec2 m_speed{ 0, 0 };
    vec2 m_size{ 1, 1 };
};

class Asteroid : public IObstacle
{
public:
    Asteroid(vec2 speed, vec2 size) : IObstacle(speed, size) {}
    void printContents() override
    {
        std::cout << "Asteroid with speed: ";
        printVec2(m_speed);
        std::cout << std::endl;
        std::cout << "Asteroid with size: ";
        printVec2(m_size);
        std::cout << std::endl;
    }
};

class SpaceDebris : public IObstacle
{
public:
    SpaceDebris(vec2 speed, vec2 size) : IObstacle(speed, size) {}
    void printContents() override
    {
        std::cout << "SpaceDebris with speed: ";
        printVec2(m_speed);
        std::cout << std::endl;
        std::cout << "SpaceDebris with size: ";
        printVec2(m_size);
        std::cout << std::endl;
    }
};

class ObstacleFactory
{
public:
    std::unique_ptr<IObstacle> createObstacle(int level)
    {
        if (level == 0)
        {
            return std::make_unique<Asteroid>(vec2{ 1, 1 }, vec2{1, 1});
        }
        else if (level == 1)
        {
            return std::make_unique<SpaceDebris>(vec2{ 2, 2 }, vec2{ 1, 1 });
        }
        else if (level == 2)
        {
            return std::make_unique<Asteroid>(vec2{ 5, 5 }, vec2{ 3, 3 });
        }
        else if (level == 3)
        {
            return std::make_unique<SpaceDebris>(vec2{ 4, 4 }, vec2{ 10, 10 });
        }
    }
};

inline void FactoryDemo()
{
    ObstacleFactory of;

    int temp = 0;
    do 
    {
        std::cout << "Select a level to load [0 - 3]. Enter -1 to exit." <<
            std::endl;
        std::cin >> temp;
        if (temp >= 0 && temp <= 3)
        {
            std::unique_ptr<IObstacle> obj = of.createObstacle(temp);
            std::cout << "The following has been loaded." << std::endl;
            obj->printContents();
            std::cout << std::endl;
        }
        else if (temp != -1)
        {
            std::cout << "Invalid input.\n" << std::endl;
        }
    } while (temp != -1);
}