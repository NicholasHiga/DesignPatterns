#pragma once
// The singleton pattern ensures a class has only one instance and provides
// a global point of access to it.
#include <iostream>:
#include <memory>

class Singleton
{
public:
    static Singleton* getInstance()
    {
        if (!instance)
            instance = std::make_unique<Singleton>();
        return instance.get();
    }

    void printAddress()
    {
        std::cout << "The address of this instance is. " << instance.get()
            << std::endl;
    }

private:
    Singleton();
    static std::unique_ptr<Singleton> instance;
};

// Very basic pattern, so no example.
