//
// Created by Shumskiy Ilya on 12.05.2025
//
#include "password.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const string PASSWORD_FILE = "password.txt";

// Записывает зашифрованный пароль в файл при первом запуске
void initializePasswordFile() {
    ifstream test(PASSWORD_FILE);
    if (!test.good()) {
        ofstream out(PASSWORD_FILE);
        vector<int> passwordParts = {0x53, 0x68, 0x75, 0x6d, 0x32, 0x30, 0x30, 0x35};
        for (int part : passwordParts) {
            out << part << " ";
        }
    }
}

// Чтение пароля из файла
string getPassword() {
    initializePasswordFile(); // Убедимся, что файл существует
    
    ifstream in(PASSWORD_FILE);
    vector<int> passwordParts;
    int num;
    
    while (in >> num) {
        passwordParts.push_back(num);
    }
    
    string password;
    for (int part : passwordParts) {
        password += static_cast<char>(part);
    }
    
    return password;
}

// Проверка введённого пароля
bool checkPassword() {
    string storedPassword = getPassword();
    string input;
    
    cout << "[Меню] Введите пароль для доступа к программе: ";
    getline(cin, input);
    
    if (input != storedPassword) {
        cout << "[Меню] Неверный пароль! Доступ запрещен.\n";
        return false;
    }
    
    return true;
}
