//
// Created by Shumskiy Ilya on 12.05.2025
//
#include <iostream>
#include <limits>
#include <string>
#include "atbash.h"
#include "tarabar.h"  // Добавлен include
#include "alphabet.h"
#include "password.h"

using namespace std;

void displayMenu() {
    cout << "\n[Меню]. Выберите шифр:\n";
    cout << "1. Шифр Атбаш\n";
    cout << "2. Тарабарская грамота\n";  // Изменено с DisplayGramota на пункт меню
    cout << "3. Алфавитный шифр\n";
    cout << "4. Выход\n";
    cout << "Ваш выбор: ";
}

int main() {
    // Проверка пароля
    if (!checkPassword()) {
        return 1;
    }

    int choice;

    do {
        displayMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[Меню]. Ошибка: введите число от 1 до 4!\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            runAtbash();
            break;
        case 2:
            runTarabar();  // Изменено с DisplayGramota
            break;
        case 3:
            runAlphabetCipher();
            break;
        case 4:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "[Меню]. Ошибка: введите число от 1 до 4!\n";
        }
    } while (choice != 4);

    return 0;
}

