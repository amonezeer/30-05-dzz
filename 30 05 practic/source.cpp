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
        return "���������� �������� �� ���������� �� " + start + " �� " + end + " �� �������.";
    }
};

class WalkRouteStrategy : public IRouteStrategy {
public:
    string buildRoute(const string& start, const string& end) const override {
        return "���������� �������� ������ �� " + start + " �� " + end + " �� ���������� ��������.";
    }
};

class PublicTransportRouteStrategy : public IRouteStrategy {
public:
    string buildRoute(const string& start, const string& end) const override {
        return "���������� �������� �� ������������ ���������� �� " + start + " �� " + end + " � �������������� ��������� , ����������� , ��������.";
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
            throw logic_error("��������� �� �����������");
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

    cout << "������� ��������� �����: ";
    getline(cin, start);
    cout << "������� ����� ����������: ";
    getline(cin, end);
    cout << "|-------------------------------------------------------|\n";
    cout << "�������� ������ ������������:" << endl;
    cout << "1. ����������" << endl;
    cout << "2. ������" << endl;
    cout << "3. ������������ ���������" << endl;
    cout << "������� ��� �����: \n";
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
        cout << "�������� �����!" << endl;
        return 1;
    }

    string route = navigator.buildRoute(start, end);
    cout << "|-------------------------------------------------------|\n";
    cout << "������� ������� ��������!" << endl;
    cout << route << endl;
    cout << "������: " << start << endl;
    cout << "����: " << end << endl;

    double distance = navigator.getRandomDistance(1.0, 50.0);
    cout << "��������� ����������: " << distance << " ��" << endl;

    return 0;
}
