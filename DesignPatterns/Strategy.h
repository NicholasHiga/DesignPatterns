#pragma once
#include <iostream>

class IQuackStrategy
{
public:
	virtual ~IQuackStrategy() {};
	virtual void quack() = 0;
};

class IFlyStrategy
{
public:
	virtual ~IFlyStrategy() {};
	virtual void fly() = 0;
};

class Duck
{
public:
	Duck(IQuackStrategy &qs, IFlyStrategy &fs) : qs(qs), fs(fs) {}
	void quack() { qs.quack(); }
	void fly() { fs.fly(); }

protected:
	IQuackStrategy &qs;
	IFlyStrategy &fs;
};

class SimpleQuack : public IQuackStrategy
{
public:
	void quack() override { std::cout << "quack"; }
};

class NoQuack : public IQuackStrategy
{
public:
	void quack() override { std::cout << "..."; }
};

class SimpleFly : public IFlyStrategy
{
public:
	void fly() override { std::cout << "flying"; }
};

class NoFly : public IFlyStrategy
{
public:
	void fly() override { std::cout << "not flying"; }
};

/* Is there a possible way to do something like the following?
class NewDuck : public Duck
{
public: 
	NewDuck()
	{
		qs = SimpleQuack();
		fs = SimpleFly();
	}
};*/

inline void StrategyDemo()
{
	SimpleQuack sq;
	NoQuack nq;

	SimpleFly sf;
	NoFly nf;

	Duck typicalDuck(sq, sf);
	Duck rubberDuck(nq, nf);

	std::cout << "Typical duck is ";
	typicalDuck.fly();
	std::cout << "\n" << "Typical duck says ";
	typicalDuck.quack();
	std::cout << "\n";

	std::cout << "Rubber duck is ";
	rubberDuck.fly();
	std::cout << "\n" << "Rubber duck says ";
	rubberDuck.quack();
	std::cout << "\n";
	std::cin.get();
}

