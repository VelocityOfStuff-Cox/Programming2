#include <algorithm>  
#include <vector>  
#include <iostream>  
#include <set>

using std::cout, std::endl;

class Car {
public:
	Car() = delete;
	Car(int newMaxPassengers);
	void removePassenger();
	void addPassenger();
	int getNumPassengers() const;
	int -()
	{
		passengers--;
	};
private:
	int passengers{ 0 };
	const int maxPassengers{ 0 };
};

int main()
{
	Car car(2);
	cout << car.getNumPassengers() << endl;
	car.removePassenger();
	cout << car.getNumPassengers() << endl;
	car.addPassenger();
	car.addPassenger();
	cout << car.getNumPassengers() << endl;
	car.addPassenger();
	cout << car.getNumPassengers() << endl;
	car.removePassenger();
	cout << car.getNumPassengers() << endl;
}

Car::Car(int newMaxPassengers)
{
	int& MaxPassengersPtr = maxPassengers;
	int& newMaxPassengersPtr = newMaxPassengers;
	MaxPassengersPtr = newMaxPassengersPtr;
}

void Car::removePassenger()
{
	passengers--;
}

void Car::addPassenger()
{
	if (passengers < maxPassengers)
	{
		passengers++;
	}
}

int Car::getNumPassengers() const
{
	return passengers;
}
