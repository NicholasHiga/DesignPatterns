#pragma once
// The command pattern encapsulates a request as an object thereby letting 
// you parameterize other objects with different requests, queue or log requests
// and support undoable operations.

// Key players:
// Invoker (Remote), ICommand, Command, Receiver (Car)

#include <iostream>
#include <memory>
#include <stack>

class ICommand
{
public:
    virtual void execute() = 0;
    virtual void unexecute() = 0;
};

// Receiver
class Car
{
public:
    void turnEngineOn()
    {
        std::cout << "Car engine turned on." << std::endl;
    }

    void turnEngineOff()
    {
        std::cout << "Car turned off." << std::endl;
    }

    void moveLeft()
    {
        std::cout << "Car moved left." << std::endl;
    }

    void moveRight()
    {
        std::cout << "Car moved right." << std::endl;
    }

    void lockDoors()
    {
        std::cout << "Car doors locked." << std::endl;
    }

    void unlockDoors()
    {
        std::cout << "Car doors unlocked." << std::endl;
    }
};

class TurnCarOn : public ICommand
{
public:
    TurnCarOn(Car *car) : m_car(car) {}
    void execute() override
    {
        m_car->turnEngineOn();
    }

    void unexecute() override
    { 
        m_car->turnEngineOff();
    }

private:
    Car *m_car;
};

class MoveCarLeft : public ICommand
{
public:
    MoveCarLeft(Car *car) : m_car(car) {}
    void execute() override
    {
        m_car->moveLeft();
    }

    void unexecute() override
    {
        m_car->moveRight();
    }

private:
    Car *m_car;
};

class LockCarDoors : public ICommand
{
public:
    LockCarDoors(Car *car) : m_car(car) {}
    void execute() override
    {
        m_car->lockDoors();
    }

    void unexecute() override
    {
        m_car->unlockDoors();
    }

private:
    Car *m_car;
};

// The invoker
class RemoteControlA
{
public:
    void setButtonA(std::unique_ptr<ICommand> cmd) 
    { 
        buttonA = std::move(cmd);
    }

    void setButtonB(std::unique_ptr<ICommand> cmd)
    {
        buttonB = std::move(cmd);
    }

    void setButtonC(std::unique_ptr<ICommand> cmd)
    {
        buttonC = std::move(cmd);
    }

    void pressButtonA()
    {
        buttonA.get()->execute();
        commandStack.push(buttonA.get());
    }

    void pressButtonB()
    {
        buttonB.get()->execute();
        commandStack.push(buttonB.get());
    }

    void pressButtonC()
    {
        buttonC.get()->execute();
        commandStack.push(buttonC.get());
    }

    void undoLastCommand()
    {
        if (!commandStack.empty())
        {
            commandStack.top()->unexecute();
            commandStack.pop();
        }
        else
        {
            std::cout << "No commands left to unexecute." << std::endl;
        }
    }

private:
    std::unique_ptr<ICommand> buttonA, buttonB, buttonC;
    std::stack<ICommand*> commandStack;
};

// Not implementing the methods, since these are the same as RemoteControlA
// but has different buttons. This is simply to show how you decouple 
// the command from each invoker.
class RemoteControlB
{
public:
    // setLeftButton, setRightButton, setUpButton, setDownButton,
    // pressLeftButton... etc.
private:
    std::unique_ptr<ICommand> leftButton, rightButton, upButton, downButton;
    std::stack<ICommand*> commandStack;
};

// Pretty ridiculous example, since you can control the car using a remote,
// you can also move the car without turning the car on and various other 
// reasons. However, this is good enough to demonstrate the design pattern.
inline void CommandDemo()
{
    auto car = std::make_unique<Car>();
    RemoteControlA rc;
    auto turnCarOn = std::make_unique<TurnCarOn>(car.get());
    auto moveCarLeft = std::make_unique<MoveCarLeft>(car.get());
    auto lockCarDoors = std::make_unique<LockCarDoors>(car.get());

    rc.setButtonA(std::move(turnCarOn));
    rc.setButtonB(std::move(moveCarLeft));
    rc.setButtonC(std::move(lockCarDoors));

    std::cout << "Enter 0 to turn the engine on." << std::endl;
    std::cout << "Enter 1 to move the car left." << std::endl;
    std::cout << "Enter 2 to lock the car doors." << std::endl;
    std::cout << "Enter 3 to undo the last action." << std::endl;
    std::cout << "Enter -1 to exit." << std::endl;

    int temp = 0;
    do
    {
        std::cout << std::endl;
        std::cin >> temp;

        if (temp >= -1 && temp <= 3)
        {
            switch (temp)
            {
            case 0:
                rc.pressButtonA();
                break;
            case 1:
                rc.pressButtonB();
                break;
            case 2:
                rc.pressButtonC();
                break;
            case 3:
                rc.undoLastCommand();
                break;
            default:
                break;
            }
        }
        else
        {
            std::cout << "Invalid input. Try another option." << std::endl;
        }
    } while (temp != -1);
}