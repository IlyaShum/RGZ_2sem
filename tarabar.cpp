//
// Created by Shumskiy Ilya on 12.05.2025
//
#include "tarabar.h"
#include <iostream>
#include <fstream>
#include <map>
#include <locale>
#include <codecvt>

using namespace std;

// Полная русская тарабарская грамота
const map<wchar_t, wchar_t> russianMap = {
    {L'Б', L'Щ'}, {L'В', L'Ш'}, {L'Г', L'Ч'}, {L'Д', L'Ц'}, {L'Ж', L'Х'},
    {L'З', L'Ф'}, {L'К', L'Т'}, {L'Л', L'С'}, {L'М', L'Р'}, {L'Н', L'П'},
    {L'П', L'Н'}, {L'Р', L'М'}, {L'С', L'Л'}, {L'Т', L'К'}, {L'Ф', L'З'},
    {L'Х', L'Ж'}, {L'Ц', L'Д'}, {L'Ч', L'Г'}, {L'Ш', L'В'}, {L'Щ', L'Б'},
    {L'Й', L'Ы'}, {L'Ы', L'Й'}  // Добавили Й и Ы
};

// Английская тарабарская грамота
const map<char, char> englishMap = {
    {'B', 'Z'}, {'C', 'Y'}, {'D', 'X'}, {'F', 'W'}, {'G', 'V'},
    {'H', 'T'}, {'J', 'S'}, {'K', 'R'}, {'L', 'Q'}, {'M', 'P'},
    {'N', 'M'}, {'P', 'L'}, {'Q', 'K'}, {'R', 'J'}, {'S', 'H'},
    {'T', 'G'}, {'V', 'F'}, {'W', 'D'}, {'X', 'C'}, {'Y', 'B'},
    {'Z', 'B'}
};

void initConsoleTarabar() {
    setlocale(LC_ALL, "ru_RU.utf8");
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif
}

wstring transformRussian(const wstring& input) {
    wstring result;
    for (wchar_t c : input) {
        wchar_t upperC = towupper(c);
        bool isLower = (c != upperC);
        
        if (russianMap.count(upperC)) {
            wchar_t transformed = russianMap.at(upperC);
            result += isLower ? towlower(transformed) : transformed;
        } else {
            result += c;  // Гласные и другие символы без изменений
        }
    }
    return result;
}

string transformEnglish(const string& input) {
    string result;
    for (char c : input) {
        char upperC = toupper(c);
        bool isLower = (c != upperC);
        
        if (englishMap.count(upperC)) {
            char transformed = englishMap.at(upperC);
            result += isLower ? tolower(transformed) : transformed;
        } else {
            result += c;
        }
    }
    return result;
}

void writeToFileTarab(const string& filename, const string& content) {
    ofstream file(filename);
    if (file.is_open()) {
        file << content;
        file.close();
    }
}

void writeToFileTarabar(const string& filename, const wstring& content) {
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    ofstream file(filename);
    if (file.is_open()) {
        file << converter.to_bytes(content);
        file.close();
    }
}

void processRussian() {
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    
    cout << "Введите текст на русском: ";
    string input;
    getline(cin, input);
    wstring winput = converter.from_bytes(input);

    wstring encrypted = transformRussian(winput);
    wstring decrypted = transformRussian(encrypted);

    cout << "\nЗашифрованный текст: " << converter.to_bytes(encrypted) << endl;
    writeToFileTarabar("encryptedTarabar.txt", encrypted);
    cout << "Сохранено в encryptedTarabar.txt\n";

    cout << "\nРасшифрованный текст: " << converter.to_bytes(decrypted) << endl;
    writeToFileTarabar("decryptedTarabar.txt", decrypted);
    cout << "Сохранено в decryptedTarabar.txt\n";
}
void processEnglish() {
    cout << "Enter English text: ";
    string input;
    getline(cin, input);

    string encrypted = transformEnglish(input);
    string decrypted = transformEnglish(encrypted);

    cout << "\nEncrypted text: " << encrypted << endl;
    writeToFileTarab("encryptedTarabar.txt", encrypted);
    cout << "Saved to encryptedTarabar.txt\n";

    cout << "\nDecrypted text: " << decrypted << endl;
    writeToFileTarab("decryptedTarabar.txt", decrypted);
    cout << "Saved to decryptedTarabar.txt\n";
}

void runTarabar() {
    initConsoleTarabar();

    cout << "\nТарабарская грамота\n";
    cout << "1. Русский язык\n";
    cout << "2. English\n";
    cout << "3. Назад\n";
    cout << "Ваш выбор: ";
    
    int choice;
    cin >> choice;
    cin.ignore();
    
    if (choice == 1) {
        processRussian();
    } else if (choice == 2) {
        processEnglish();
    } else if (choice == 3) {
        return;
    } else {
        cout << "Неверный выбор!\n";
    }
}
