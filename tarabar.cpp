#include "tarabar.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Функция для чтения файла
string readFileTar(const string& filename) {
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

// Функция для разбивки UTF-8 строки на символы
vector<string> splitUtf8Tar(const string& str) {
    vector<string> characters;
    string currentChar;
    
    for (unsigned char c : str) {
        if ((c & 0xC0) != 0x80) { // Начало нового UTF-8 символа
            if (!currentChar.empty()) {
                characters.push_back(currentChar);
            }
            currentChar.clear();
        }
        currentChar += c;
    }
    
    if (!currentChar.empty()) {
        characters.push_back(currentChar);
    }
    
    return characters;
}

// Английская тарабарская грамота - заменяем только согласные
map<char, char> TarabarEng = {
    // Заглавные согласные
    {'B', 'Z'}, {'Z', 'B'},
    {'C', 'Y'}, {'Y', 'C'},
    {'D', 'X'}, {'X', 'D'},
    {'F', 'W'}, {'W', 'F'},
    {'G', 'V'}, {'V', 'G'},
    {'H', 'T'}, {'T', 'H'},
    {'J', 'S'}, {'S', 'J'},
    {'K', 'R'}, {'R', 'K'},
    {'L', 'Q'}, {'Q', 'L'},
    {'M', 'P'}, {'P', 'M'},
    {'N', 'N'}, // N остается на месте (центральная буква)
    
    // Строчные согласные
    {'b', 'z'}, {'z', 'b'},
    {'c', 'y'}, {'y', 'c'},
    {'d', 'x'}, {'x', 'd'},
    {'f', 'w'}, {'w', 'f'},
    {'g', 'v'}, {'v', 'g'},
    {'h', 't'}, {'t', 'h'},
    {'j', 's'}, {'s', 'j'},
    {'k', 'r'}, {'r', 'k'},
    {'l', 'q'}, {'q', 'l'},
    {'m', 'p'}, {'p', 'm'},
    {'n', 'n'}  // n остается на месте
};

// Русская тарабарская грамота (заменяем только согласные)
map<string, string> TarabarRus = {
    // Заглавные согласные
    {"Б", "Щ"}, {"Щ", "Б"},
    {"В", "Ш"}, {"Ш", "В"},
    {"Г", "Ч"}, {"Ч", "Г"},
    {"Д", "Ц"}, {"Ц", "Д"},
    {"Ж", "Х"}, {"Х", "Ж"},
    {"З", "Ф"}, {"Ф", "З"},
    {"К", "Т"}, {"Т", "К"},
    {"Л", "С"}, {"С", "Л"},
    {"М", "Р"}, {"Р", "М"},
    {"Н", "П"}, {"П", "Н"},
    
    // Строчные согласные
    {"б", "щ"}, {"щ", "б"},
    {"в", "ш"}, {"ш", "в"},
    {"г", "ч"}, {"ч", "г"},
    {"д", "ц"}, {"ц", "д"},
    {"ж", "х"}, {"х", "ж"},
    {"з", "ф"}, {"ф", "з"},
    {"к", "т"}, {"т", "к"},
    {"л", "с"}, {"с", "л"},
    {"м", "р"}, {"р", "м"},
    {"н", "п"}, {"п", "н"}
};

void initConsoleTarabar() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
}

// Функция для проверки английской согласной буквы
bool isEnglishConsonant(char c) {
    char upperC = toupper(c);
    // Согласные английского алфавита
    return (upperC == 'B' || upperC == 'C' || upperC == 'D' || upperC == 'F' || 
            upperC == 'G' || upperC == 'H' || upperC == 'J' || upperC == 'K' ||
            upperC == 'L' || upperC == 'M' || upperC == 'N' || upperC == 'P' ||
            upperC == 'Q' || upperC == 'R' || upperC == 'S' || upperC == 'T' ||
            upperC == 'V' || upperC == 'W' || upperC == 'X' || upperC == 'Y' || 
            upperC == 'Z');
}

// Функция для проверки русской согласной буквы
bool isRussianConsonant(const string& utf8Char) {
    vector<string> consonants = {
        "Б", "В", "Г", "Д", "Ж", "З", "К", "Л", "М", "Н", "П", "Р", "С", "Т", "Ф", "Х", "Ц", "Ч", "Ш", "Щ",
        "б", "в", "г", "д", "ж", "з", "к", "л", "м", "н", "п", "р", "с", "т", "ф", "х", "ц", "ч", "ш", "щ"
    };
    
    for (const string& consonant : consonants) {
        if (utf8Char == consonant) {
            return true;
        }
    }
    return false;
}

// Шифрование для английского текста
string encryptEnglish(const string& text) {
    string encrypted;
    for (char c : text) {
        if (isEnglishConsonant(c) && TarabarEng.count(c)) {
            encrypted += TarabarEng[c];
        } else {
            encrypted += c; // Гласные и другие символы без изменений
        }
    }
    return encrypted;
}

// Дешифрование для английского текста
string decryptEnglish(const string& text) {
    string decrypted;
    for (char c : text) {
        if (isEnglishConsonant(c)) {
            bool found = false;
            for (const auto& pair : TarabarEng) {
                if (pair.second == c) {
                    decrypted += pair.first;
                    found = true;
                    break;
                }
            }
            if (!found) {
                decrypted += c;
            }
        } else {
            decrypted += c; // Гласные и другие символы без изменений
        }
    }
    return decrypted;
}

// Шифрование для русского текста (UTF-8)
string encryptRussian(const string& text) {
    vector<string> chars = splitUtf8Tar(text);
    string encrypted;
    
    for (const string& ch : chars) {
        if (isRussianConsonant(ch) && TarabarRus.count(ch)) {
            encrypted += TarabarRus[ch];
        } else {
            encrypted += ch; // Гласные и другие символы без изменений
        }
    }
    return encrypted;
}

// Дешифрование для русского текста (UTF-8)
string decryptRussian(const string& text) {
    vector<string> chars = splitUtf8Tar(text);
    string decrypted;
    
    for (const string& ch : chars) {
        if (isRussianConsonant(ch)) {
            bool found = false;
            for (const auto& pair : TarabarRus) {
                if (pair.second == ch) {
                    decrypted += pair.first;
                    found = true;
                    break;
                }
            }
            if (!found) {
                decrypted += ch;
            }
        } else {
            decrypted += ch; // Гласные и другие символы без изменений
        }
    }
    return decrypted;
}

// Запись в файл
void writeToFileTar(const string& filename, const string& content) {
    ofstream file(filename);
    if (file.is_open()) {
        file << content;
        file.close();
        cout << "Успешно записано в " << filename << endl;
    } else {
        cerr << "Ошибка при записи в файл " << filename << "!" << endl;
    }
}

void processRussian() {
    cout << "Введите имя файла с текстом: ";
    string filename;
    getline(cin, filename);

    string input;
    try {
        input = readFileTar(filename);
        cout << "Текст из файла: " << input << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
        cout << "Возврат в главное меню.\n";
        return;
    }

    string encrypted = encryptRussian(input);
    string decrypted = decryptRussian(encrypted);

    cout << "\nЗашифрованный текст: " << encrypted << endl;
    writeToFileTar("encryptedTarabar.txt", encrypted);

    cout << "\nРасшифрованный текст: " << decrypted << endl;
    writeToFileTar("decryptedTarabar.txt", decrypted);
}

void processEnglish() {
    cout << "Enter filename with text: ";
    string filename;
    getline(cin, filename);

    string input;
    try {
        input = readFileTar(filename);
        cout << "Text from file: " << input << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
        cout << "Returning to main menu.\n";
        return;
    }

    string encrypted = encryptEnglish(input);
    string decrypted = decryptEnglish(encrypted);

    cout << "\nEncrypted text: " << encrypted << endl;
    writeToFileTar("encryptedTarabar.txt", encrypted);

    cout << "\nDecrypted text: " << decrypted << endl;
    writeToFileTar("decryptedTarabar.txt", decrypted);
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
