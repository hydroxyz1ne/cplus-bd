#include <iostream>
#include <fstream>
#include<string.h>
#include<algorithm>
#include<vector>

struct Car {
	std::string brand;
	double cost;
	std::string country;
	std::string color;
	std::string showroom;

};


class CarDatabase {
private:
	std::vector<Car> cars;
	std::string filename;

	void loadDatabase() {
		std::ifstream inputFile(filename.c_str());
		if (inputFile.is_open()) {
			cars.clear();
			Car car;
			while (inputFile >> car.brand >> car.cost >> car.country >> car.color >> car.showroom) {
				cars.push_back(car);
			}
			inputFile.close();
		}
	}


public: 
	CarDatabase(const std::string& filename) : filename(filename) {
		loadDatabase();
	}

	void ViewDatabase() {
		for (const auto& car : cars) {
			std::cout << "Марка" << car.brand << "Стоимость" << car.cost << "Страна изготовитель" << car.country << "Цвет" << car.color << "Название салона продаж" << car.showroom;
		}
	}

};

int main() {
	CarDatabase carDB("");
	carDB.ViewDatabase();
}