#pragma once
// The adapter pattern converts the interface of a class to another interface
// the client expects. Adapter lets classes work together that couldn't
// otherwise because of incompatible interfaces.

#include <iostream>

class ITarget
{
public:
    virtual void request() = 0;
};

class Adaptee
{
public:
    void someRequestWeNeed()
    {
        std::cout << "Doing the request we need." << std::endl;
    }
};

class Adapter : public ITarget
{
public:
    Adapter(Adaptee adaptee) : m_adaptee(adaptee){}

    void request() override
    {
        // Do some conversion to make it work for client
        m_adaptee.someRequestWeNeed();
    }
private:
    Adaptee m_adaptee;
};

void someMethodWhereClientNeedsITarget(ITarget &target)
{
    target.request();
}

void AdapterExample()
{
    Adaptee adaptee;
    Adapter adapter = { adaptee };
    someMethodWhereClientNeedsITarget(adapter);
}
