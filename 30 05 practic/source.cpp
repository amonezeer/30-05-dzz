#include <iostream>
#include <memory>
#include <string>
#include <random>

using namespace std;

class IRouteStrategy {
public:
    virtual ~IRouteStrategy() = default;
    virtual string buildRoute(const string& start, const string& end) const = 0;
};

class CarRouteStrategy : public IRouteStrategy {
public:
    string buildRoute(const string& start, const string& end) const override {
        return "Построение маршрута на автомобиле от " + start + " до " + end + " по дорогам.";
    }
};

class WalkRouteStrategy : public IRouteStrategy {
public:
    string buildRoute(const string& start, const string& end) const override {
        return "Построение маршрута пешком от " + start + " до " + end + " по пешеходным дорожкам.";
    }
};

class PublicTransportRouteStrategy : public IRouteStrategy {
public:
    string buildRoute(const string& start, const string& end) const override {
        return "Построение маршрута на общественном транспорте от " + start + " до " + end + " с использованием автобусов , тролейбусов , трамваев.";
    }
};

class Navigator {
private:
    unique_ptr<IRouteStrategy> strategy;

public:
    void setStrategy(unique_ptr<IRouteStrategy> newStrategy) {
        strategy = move(newStrategy);
    }

    string buildRoute(const string& start, const string& end) const {
        if (!strategy) {
            throw logic_error("Стратегия не установлена");
        }
        return strategy->buildRoute(start, end);
    }

    double getRandomDistance(double min, double max) const {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
};

int main() {
    system("chcp 1251");
    Navigator navigator;
    string start, end;
    int choice;

    cout << "Введите начальную точку: ";
    getline(cin, start);
    cout << "Введите пункт назначения: ";
    getline(cin, end);
    cout << "|-------------------------------------------------------|\n";
    cout << "Выберите способ передвижения:" << endl;
    cout << "1. Автомобиль" << endl;
    cout << "2. Пешком" << endl;
    cout << "3. Общественный транспорт" << endl;
    cout << "Введите ваш выбор: \n";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
    case 1:
        navigator.setStrategy(make_unique<CarRouteStrategy>());
        break;
    case 2:
        navigator.setStrategy(make_unique<WalkRouteStrategy>());
        break;
    case 3:
        navigator.setStrategy(make_unique<PublicTransportRouteStrategy>());
        break;
    default:
        cout << "Неверный выбор!" << endl;
        return 1;
    }

    string route = navigator.buildRoute(start, end);
    cout << "|-------------------------------------------------------|\n";
    cout << "Маршрут успешно построен!" << endl;
    cout << route << endl;
    cout << "Откуда: " << start << endl;
    cout << "Куда: " << end << endl;

    double distance = navigator.getRandomDistance(1.0, 50.0);
    cout << "Примерное расстояние: " << distance << " км" << endl;

    return 0;
}
