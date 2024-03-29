﻿#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

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
    CarDatabase() = default;  // Добавлен конструктор по умолчанию

    CarDatabase(const std::string& filePath) : filename(filePath) {
        loadDatabase(filename);
    }

    void loadDatabase(const std::string& filename) {
        std::ifstream inputFile(filename);

        if (!inputFile.is_open()) {
            std::cerr << "Ошибка. Невозможно открыть файл " << filename << std::endl;
            return;
        }

        Car car;
        while (inputFile >> car.brand >> car.cost >> car.country >> car.color >> car.showroom) {
            cars.push_back(car);
        }

        inputFile.close();
    }

    void newDataBase() {
        std::cout << "Введите название файла: ";
        std::string fileName;
        std::cin >> fileName;

        fileName += ".txt";

        std::ofstream outputFile(fileName);

        if (outputFile.is_open()) {
            std::cout << "Файл успешно создан: " << fileName << "\n";
            cars.clear();  // Очистить текущие данные при создании новой базы данных
            filename = fileName;  // Установить новое имя файла для текущей базы данных
        }
        else {
            std::cerr << "Не удалось создать файл.\n";
        }
    }

    void openExistingDatabase() {
        std::cout << "Введите путь к существующему файлу базы данных: ";
        std::cin >> filename;

        loadDatabase(filename);

        std::cout << "База данных успешно открыта: " << filename << "\n";
    }

    std::string getFileName() const {
        return filename;
    }

    void saveDatabase() {
        std::ofstream outputFile(filename);

        if (!outputFile.is_open()) {
            std::cerr << "Невозможно сохранить файл: " << filename << std::endl;
            return;
        }

        for (const auto& car : cars) {
            outputFile << car.brand << ' ' << car.cost << ' ' << car.country << ' ' << car.color << ' ' << car.showroom << '\n';
        }

        outputFile.close();
        std::cout << "База данных сохранена в файл: " << filename << std::endl;
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
            std::cout << "Введите значение действия, которое хотите выполнить: ";
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

            std::cout << "Нажмите Enter для продолжения...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        } while (choice != 0);
    }

    // Sort the database based on user input
    void sortDatabase() {
        int sortChoice;
        std::cout << "\n----- Сортировка -----\n";
        std::cout << "1. Сортировка по марке\n";
        std::cout << "2. Сортировка по цене\n";
        std::cout << "3. Сортировка по стране изготовителе\n";
        std::cout << "4. Сортировка по цвету\n";
        std::cout << "5. Сортировка по салонам\n";
        std::cout << "Введите значение сортировки, которую вы хотите выполнить: ";
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
            std::cout << "Неизвестный вариант. Попробуйте что-то другое.\n";
        }
    }

    // Add a new record to the database
    void addRecord() {
        Car newCar;
        std::cout << "Введите бренд: ";
        std::cin >> newCar.brand;
        std::cout << "Введите стоимость: ";
        std::cin >> newCar.cost;
        std::cout << "Введите страну производителя: ";
        std::cin >> newCar.country;
        std::cout << "Введите цвет авто: ";
        std::cin >> newCar.color;
        std::cout << "Введите салон, где авто есть в наличии: ";
        std::cin >> newCar.showroom;

        cars.push_back(newCar);
        std::cout << "Запись добавлена в базу данных.\n";
        saveDatabase();
    }

    void deleteRecord() {
        std::string brandToDelete, colorToDelete, countryToDelete;
        std::cout << "Введите бренд для удаления: ";
        std::cin >> brandToDelete;
        std::cout << "Введите цвет для удаления: ";
        std::cin >> colorToDelete;
        std::cout << "Введите страну для удаления: ";
        std::cin >> countryToDelete;

        auto it = std::remove_if(cars.begin(), cars.end(), [brandToDelete, colorToDelete, countryToDelete](const Car& car) {
            return car.brand == brandToDelete && car.color == colorToDelete && car.country == countryToDelete;
            });

        if (it != cars.end()) {
            cars.erase(it, cars.end());
            std::cout << "Записи с брендом " << brandToDelete << ", цветом " << colorToDelete << " и производителем " << countryToDelete << " удалены.\n";
        }
        else {
            std::cout << "Записи с брендом " << brandToDelete << ", цветом " << colorToDelete << " и производителем " << countryToDelete << " не найдены.\n";
        }

        saveDatabase();
    }

    void viewDatabase() {
        for (const auto& car : cars) {
            std::cout << "Марка: " << car.brand << ", Стоимость: " << car.cost << ", Страна: " << car.country
                << ", Цвет: " << car.color << ", Салон: " << car.showroom << std::endl;
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

    std::string filePath;
    CarDatabase carDB;

    int choice;
    do {
        std::cout << "\n----- Меню базы данных -----\n";
        std::cout << "(1) Посмотреть/изменить базу данных\n";
        std::cout << "(2) Создать новую базу данных\n";
        std::cout << "(0) Выход\n";
        std::cout << "Введите значение действия, которое хотите выполнить: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            if (!filePath.empty()) {
                carDB.loadDatabase(filePath);  // Загрузить текущую базу данных перед открытием меню
                carDB.mainMenu();
            }
            else {
                std::cout << "База данных не выбрана.\n";
                std::cout << "(1) Открыть существующую базу данных\n";
                std::cout << "(2) Создать новую базу данных\n";
                std::cout << "Введите значение действия: ";
                std::cin >> choice;

                switch (choice) {
                case 1:
                    carDB.openExistingDatabase();
                    filePath = carDB.getFileName();
                    break;
                case 2:
                    carDB.newDataBase();
                    filePath = carDB.getFileName();
                    break;
                default:
                    std::cout << "Неизвестный вариант. Попробуйте что-то другое.\n";
                }
            }
            break;
        case 2:
            carDB.newDataBase();
            filePath = carDB.getFileName();  // Получить имя файла текущей базы данных
            break;
        case 0:
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Неизвестный вариант. Попробуйте что-то другое.\n";
        }

        std::cout << "Нажмите Enter для продолжения...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (choice != 0);

    return 0;

    carDB.saveDatabase();
}
