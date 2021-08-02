#include <iostream>
#include <vector>

#include "Application.hpp"
#include "Apps/TestApp.hpp"
#include "Apps/LifeGame.hpp"
#include "Apps/AStar/AStar.hpp"
#include "Apps/DiamondSquare.hpp"

using namespace std;

constexpr int NUMBER_PARAMS = 4;

class GenericApp;

bool isValidChoice(int choice) {
    return choice > 0 && choice <= NUMBER_PARAMS + 1;
}

template<typename T>
void run() {
    cout << "Running app ..." << endl;
    Application app(1280, 960, "Test");
    app.init<T>();
    app.run();
}

void print(const vector<int> &vector);


int main() {
    bool exit = false;
    while (!exit) {
        cout << "Which program do you want to run ?" << endl
             << "1. Test Program" << endl
             << "2. Life Game Program" << endl
             << "3. AStar Program" << endl
             << "4. DiamondSquare Program" << endl
             << (NUMBER_PARAMS + 1) << ". Exit" << endl;
        int option = 0;
        cin >> option;
        cin.ignore();
        while (!isValidChoice(option)) {
            cout << "Please enter a number between 1 and " << (NUMBER_PARAMS + 1) << endl;
            cin >> option;
            cin.ignore();
        }
        switch (option) {
            case 1:
                run<TestApp>();
                break;
            case 2:
                run<LifeGame>();
                break;
            case 3:
                run<AStar>();
                break;
            case 4:
                run<DiamondSquare>();
                break;
            default:
                exit = true;
                break;
        }
    }


    cout << "Hello, World!" << endl;
    return 0;
}
