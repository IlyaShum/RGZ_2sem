#include <iostream>
#include <string>
#include "atbash.h"
#include "tarabar.h"  
#include "alphabet.h"
#include "password.h"

using namespace std;

void displayMenu() {
    cout << "\n[Меню]. Выберите шифр:\n";
    cout << "1. Шифр Атбаш\n";
    cout << "2. Тарабарская грамота\n";  
    cout << "3. Алфавитный шифр\n";
    cout << "4. Выход\n";
    cout << "Ваш выбор: ";
}

void clearInputBuffer() {
    // Очистка буфера ввода без limits
    cin.clear();
    while (cin.get() != '\n') {
        continue; // Пропускаем все символы до конца строки
    }
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
            cout << "[Меню]. Ошибка: введите число от 1 до 4!\n";
            clearInputBuffer();
            continue;
        }
        
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                runAtbash();
                break;
            case 2:
                runTarabar();
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
