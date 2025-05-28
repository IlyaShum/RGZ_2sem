//
// Created by Shumskiy Ilya on 12.05.2025
//
#include "atbash.h"
#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <codecvt>

using namespace std;

// Функция для корректного отображения русских символов
void initConsole() {
    setlocale(LC_ALL, "ru_RU.utf8");
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif
}

string atbashTransform(const string& text, bool isRussian) {
    // Полные алфавиты с правильным порядком букв
    const wstring rusUpper = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    const wstring rusLower = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    const string engUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string engLower = "abcdefghijklmnopqrstuvwxyz";

    // Конвертируем входную строку в wide string для корректной обработки русских символов
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    wstring wtext = converter.from_bytes(text);

    wstring result;

    for (wchar_t c : wtext) {
        if (isRussian) {
            if (iswupper(c)) {
                size_t pos = rusUpper.find(c);
                if (pos != wstring::npos) {
                    wchar_t mirrored = rusUpper[rusUpper.length() - 1 - pos];
                    result += mirrored;
                } else {
                    result += c;
                }
            } else {
                size_t pos = rusLower.find(c);
                if (pos != wstring::npos) {
                    wchar_t mirrored = rusLower[rusLower.length() - 1 - pos];
                    result += mirrored;
                } else {
                    result += c;
                }
            }
        } else {
            if (iswupper(c)) {
                result += 'Z' - (c - 'A');
            } else if (iswlower(c)) {
                result += 'z' - (c - 'a');
            } else {
                result += c;
            }
        }
    }

    // Конвертируем результат обратно в UTF-8
    return converter.to_bytes(result);
}

void writeToFile(const string& filename, const string& content) {
    ofstream file(filename);
    if (file.is_open()) {
        file << content;
        file.close();
        cout << "Успешно записано в " << filename << endl;
    } else {
        cerr << "Ошибка при записи в файл " << filename << "!" << endl;
    }
}

void runAtbash() {
    initConsole();

    cout << "Выберите язык:\n";
    cout << "1. Русский\n";
    cout << "2. Английский\n";
    cout << "3. Назад\n";
    cout << "Ваш выбор: ";
    
    int languageChoice;
    cin >> languageChoice;
    cin.ignore();
    
    bool isRussian = (languageChoice == 1);
    if (languageChoice == 3){
        return;
    }
    cout << "Введите сообщение: ";
    string message;
    getline(cin, message);

    string encrypted = atbashTransform(message, isRussian);
    cout << "Зашифрованное: " << encrypted << endl;
    writeToFile("encryptedATBASH.txt", encrypted);

    string decrypted = atbashTransform(encrypted, isRussian);
    cout << "Расшифрованное: " << decrypted << endl;
    writeToFile("decryptedATBASH.txt", decrypted);
}
