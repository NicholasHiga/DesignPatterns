#pragma once
// The observer pattern defines a one to many dependancy between objects so that
// when one object changes state, all its dependants are updated and notified
// automatically.

#include <vector>
#include <functional>
#include <iostream>

class IObserver
{
public:
	virtual void update() const = 0;
};

class IObservable
{
public:
	virtual void add(IObserver &obs) = 0;
	virtual void remove(IObserver &obs) = 0;
	virtual void notify() = 0;
};

class WeatherStationObservable : public IObservable
{
public:
	void add(IObserver &obs) override { observers.push_back(obs); }
	void remove(IObserver &obs) override {}//remove the right observer
	void notify() override
	{
		for (auto const i : observers)
			i.get().update();
	}

	void setTemperature(int &temp)
	{
		if (temperature != temp)
		{
			temperature = temp;
			notify();
		}
		else
		{
			std::cout << "Temperature still the same, observers not notified."
				<< std::endl;
		}
	}

	int getTemperature()
	{
		return temperature;
	}

private:
	int temperature = 10;
	std::vector<std::reference_wrapper<IObserver>> observers;
};

class PhoneDisplayObserver : public IObserver
{
public:
	PhoneDisplayObserver(WeatherStationObservable &wso) : wso(wso) {}

	void update() const override
	{
		std::cout << "Phone got new temperature of " << wso.getTemperature()
			<< std::endl;
	}

private:
	WeatherStationObservable &wso;
};

class TVDisplayObserver : public IObserver
{
public:
	TVDisplayObserver(WeatherStationObservable &wso) : wso(wso) {}

	void update() const override
	{
		std::cout << "TV got new temperature of " << wso.getTemperature()
			<< std::endl;
	}

private:
	WeatherStationObservable & wso;
};

inline void ObserverDemo()
{
	WeatherStationObservable wsObservable;
	PhoneDisplayObserver phoneDisplayObserver(wsObservable);
	TVDisplayObserver tvDisplayObserver(wsObservable);
	wsObservable.add(phoneDisplayObserver);
	wsObservable.add(tvDisplayObserver);

	std::cout << "Current temperature: " << wsObservable.getTemperature()
		<< std::endl;

	int temp;
	do
	{
		std::cout << "Enter a temperature to update to. Enter -1 to exit."
			<< std::endl;
		std::cin >> temp;
		wsObservable.setTemperature(temp);
		std::cout << std::endl;
	} while (temp != -1);
}