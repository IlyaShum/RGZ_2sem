#include "atbash.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void initConsole() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
}

// Русский алфавит в UTF-8 (байтовое представление)
const string rusUpper = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
const string rusLower = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
const string engUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string engLower = "abcdefghijklmnopqrstuvwxyz";

// Функция для чтения файла
string readFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Ошибка: не удалось открыть файл " + filename);
    }
    
    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();
    file.close();
    
    if (content.empty()) {
        throw runtime_error("Ошибка: файл " + filename + " пустой");
    }
    
    return content;
}

// Функция для поиска UTF-8 символа в строке
size_t findUtf8Char(const string& str, const string& targetChar, size_t startPos = 0) {
    if (targetChar.empty()) return string::npos;
    
    for (size_t i = startPos; i < str.length(); ) {
        // Определяем длину текущего символа UTF-8
        unsigned char firstByte = str[i];
        size_t charLen = 1;
        if ((firstByte & 0xE0) == 0xC0) charLen = 2;
        else if ((firstByte & 0xF0) == 0xE0) charLen = 3;
        else if ((firstByte & 0xF8) == 0xF0) charLen = 4;
        
        if (i + charLen <= str.length()) {
            string currentChar = str.substr(i, charLen);
            if (currentChar == targetChar) {
                return i;
            }
        }
        i += charLen;
    }
    return string::npos;
}

// Функция для получения символа по индексу в UTF-8 строке
string getUtf8CharAt(const string& str, size_t index) {
    if (index >= str.length()) return "";
    
    unsigned char firstByte = str[index];
    size_t charLen = 1;
    if ((firstByte & 0xE0) == 0xC0) charLen = 2;
    else if ((firstByte & 0xF0) == 0xE0) charLen = 3;
    else if ((firstByte & 0xF8) == 0xF0) charLen = 4;
    
    if (index + charLen <= str.length()) {
        return str.substr(index, charLen);
    }
    return "";
}

// Функция для получения длины UTF-8 строки в символах
size_t utf8Length(const string& str) {
    size_t len = 0;
    for (size_t i = 0; i < str.length(); ) {
        unsigned char firstByte = str[i];
        if ((firstByte & 0x80) == 0) i += 1;
        else if ((firstByte & 0xE0) == 0xC0) i += 2;
        else if ((firstByte & 0xF0) == 0xE0) i += 3;
        else if ((firstByte & 0xF8) == 0xF0) i += 4;
        else i += 1;
        len++;
    }
    return len;
}

string atbashTransform(const string& text, bool isRussian) {
    string result;
    
    if (isRussian) {
        // Обработка русского текста
        for (size_t i = 0; i < text.length(); ) {
            string currentChar = getUtf8CharAt(text, i);
            
            if (!currentChar.empty()) {
                // Проверяем в верхнем регистре
                size_t pos = findUtf8Char(rusUpper, currentChar);
                if (pos != string::npos) {
                    size_t alphabetLen = utf8Length(rusUpper);
                    size_t mirrorPos = (alphabetLen - 1) - (pos / 2);
                    string mirroredChar = getUtf8CharAt(rusUpper, mirrorPos * 2);
                    result += mirroredChar;
                } 
                // Проверяем в нижнем регистре
                else {
                    pos = findUtf8Char(rusLower, currentChar);
                    if (pos != string::npos) {
                        size_t alphabetLen = utf8Length(rusLower);
                        size_t mirrorPos = (alphabetLen - 1) - (pos / 2);
                        string mirroredChar = getUtf8CharAt(rusLower, mirrorPos * 2);
                        result += mirroredChar;
                    } 
                    // Если не буква - оставляем как есть
                    else {
                        result += currentChar;
                    }
                }
                
                i += currentChar.length();
            } else {
                i++;
            }
        }
    } else {
        // Обработка английского текста
        for (char c : text) {
            if (c >= 'A' && c <= 'Z') {
                result += 'Z' - (c - 'A');
            } else if (c >= 'a' && c <= 'z') {
                result += 'z' - (c - 'a');
            } else {
                result += c;
            }
        }
    }
    
    return result;
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
    
    cout << "Введите имя файла с текстом: ";
string filename;
getline(cin, filename);

string message;
try {
    message = readFile(filename);
    cout << "Текст для шифрования: " << message << endl;
} catch (const exception& e) {
    cerr << e.what() << endl;
    cout << "Возврат в главное меню.\n";
    return;  // Возвращаемся в главное меню
}

    string encrypted = atbashTransform(message, isRussian);
    cout << "Зашифрованный текст: " << encrypted << endl;
    writeToFile("encryptedAtbash.txt", encrypted);

    string decrypted = atbashTransform(encrypted, isRussian);
    cout << "Расшифрованный текст: " << decrypted << endl;
    writeToFile("decryptedAtbash.txt", decrypted);
}
