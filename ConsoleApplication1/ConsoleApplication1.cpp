#include <iostream>
#include <fstream>
#include<string.h>
#include<algorithm>
#include<vector>

struct Car {
	std::string brand;
	double cost = 0.0;
	std::string country;
	std::string color;
    std::string showroom;

};


class CarDatabase {
private:
    std::vector<Car> cars;
    std::string filename;

public:

    CarDatabase(const std::string& filename) : filename(filename) {
        loadDatabase();
    }

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


    void mainMenu() {
        int choice;
        do {
            std::cout << "\n----- Меню базы данных -----\n";
            std::cout << "(1) Посмотреть базу данных\n";
            std::cout << "(2) Добавить запись\n";
            std::cout << "(3) Удалить запись\n";
            std::cout << "(4) Поиск по базе данных\n";
            std::cout << "(5) Сортировка базы данных\n";
            std::cout << "(0) Выход\n";
            std::cout << "Введите значение действия, которое хотите выполнить ";
            std::cin >> choice;

            switch (choice) {
            case 1:
                viewDatabase();
                break;
            case 2:
                addRecord();
                break;
            case 3:
                deleteRecord();
                break;
            case 4:
                searchDatabase();
                break;
            case 5:
                sortDatabase();
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                exit(0);
                break;
            default:
                std::cout << "Неизвестный вариант. Попробуйте что-то другое.\n";
            }
            system("cls");
        } while (choice != 6);
    }

    void sortDatabase() {
        int sortChoice;
        std::cout << "\n----- Sort Options -----\n";
        std::cout << "1. Sort by Brand\n";
        std::cout << "2. Sort by Cost\n";
        std::cout << "3. Sort by Country\n";
        std::cout << "4. Sort by Color\n";
        std::cout << "5. Sort by Showroom\n";
        std::cout << "Enter your choice: ";
        std::cin >> sortChoice;

        switch (sortChoice) {
        case 1:
            sortRecordsByBrand();
            break;
        case 2:
            sortRecordsByCost();
            break;
        case 3:
            sortRecordsByCountry();
            break;
        case 4:
            sortRecordsByColor();
            break;
        case 5:
            sortRecordsByShowroom();
            break;
        default:
            std::cout << "Invalid choice. Returning to main menu.\n";
        }
        system("cls");
    }

    void addRecord() {
        Car newCar;
        std::cout << "Введите бренд:";
        std::cin >> newCar.brand;
        std::cout << "Введите стоимость:";
        std::cin >> newCar.cost;
        std::cout << "Введите страну производителя: ";
        std::cin >> newCar.country;
        std::cout << "Введите цвет авто: ";
        std::cin >> newCar.color;
        std::cout << "Введите салон, где авто есть в наличии: ";
        std::cin >> newCar.showroom;

        cars.push_back(newCar);
        std::cout << "Запись добавлена в базу данных.\n";
    }

    void deleteRecord() {
        std::string brandToDelete;
        std::cout << "Введите бренд, чтобы удалить: ";
        std::cin >> brandToDelete;

        auto it = std::remove_if(cars.begin(), cars.end(),
            [brandToDelete](const Car& car) { return car.brand == brandToDelete; });
        cars.erase(it, cars.end());

        std::cout << "Запись с брендом " << brandToDelete << " удалена.\n";
    }

    void viewDatabase() {
        for (const auto& car : cars) {
            std::cout << "Марка" << car.brand << "Стоимость" << car.cost << "Страна изготовитель" << car.country << "Цвет" << car.color << "Название салона продаж" << car.showroom;
        }
    }

    void searchDatabase() {
        int searchChoice;
        std::cout << "\n----- Поиск -----\n";
        std::cout << "(1) Поиск по бренду\n";
        std::cout << "(2) Поиск по стране происхождения\n";
        std::cout << "Введите категорию поиска: ";
        std::cin >> searchChoice;

        switch (searchChoice) {
        case 1:
            searchByBrand();
            break;
        case 2:
            searchByCountry();
            break;
        default:
            std::cout << "Неверная команда. Вернитесь в меню и попробуйте снова.\n";
        }
    }

    void searchByBrand() {
        std::string searchBrand;
        std::cout << "Введите бренд для поиска: ";
        std::cin >> searchBrand;

        bool found = false;
        for (const auto& car : cars) {
            if (car.brand == searchBrand) {
                std::cout << "Марка: " << car.brand << ", Цена: " << car.cost << ", Страна: " << car.country
                    << ", Цвет: " << car.color << ", Салон: " << car.showroom << std::endl;
                found = true;
            }
        }

        if (!found) {
            std::cout << "В наличии нет авто данного бренда.\n";
        }
    }

    void searchByCountry() {
        std::string searchCountry;
        std::cout << "Введите страну по которой хотите выполнить поиск: ";
        std::cin >> searchCountry;

        bool found = false;
        for (const auto& car : cars) {
            if (car.country == searchCountry) {
                std::cout << "Марка: " << car.brand << ", Цена: " << car.cost << ", Страна: " << car.country
                    << ", Цвет: " << car.color << ", Салон: " << car.showroom << std::endl;
                found = true;
            }
        }

        if (!found) {
            std::cout << "В наличии нет авто выбранной страны происхождения.\n";
        }
    }

    void sortRecordsByBrand() {
        std::sort(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
            return a.brand < b.brand;
            });
        std::cout << "База данных отсортирована по маркам.\n";
        viewDatabase();
    }

    void sortRecordsByCost() {
        std::sort(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
            return a.cost < b.cost;
            });
        std::cout << "База данных отсортирована по цене.\n";
        viewDatabase();
    }

    void sortRecordsByCountry() {
        std::sort(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
            return a.country < b.country;
            });
        std::cout << "База данных отсортирована по стране происхождения.\n";
        viewDatabase();
    }

    void sortRecordsByColor() {
        std::sort(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
            return a.color < b.color;
            });
        std::cout << "База данных отсортирована по цветам.\n";
        viewDatabase();
    }

    void sortRecordsByShowroom() {
        std::sort(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
            return a.showroom < b.showroom;
            });
        std::cout << "База данных отсортирована по наличию в салонах.\n";
        viewDatabase();
    }
};




int main() {
    setlocale(0, "rus");
    CarDatabase carDB("car_database.txt");
    carDB.mainMenu();
    return 0;
}