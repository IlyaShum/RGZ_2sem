//
// Created by Shumskiy Ilya on 12.05.2025
//
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <locale>
#include <clocale>
#include <codecvt>
#include <cwctype>

using namespace std;

void initConsoleAlph() {
    setlocale(LC_ALL, "ru_RU.utf8");
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif
}

string getAlphabet(bool isRussian) {
    return isRussian ? "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ" 
                    : "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}

bool isAlphaChar(wchar_t c, bool isRussian) {
    if (isRussian) {
        return (c >= L'А' && c <= L'Я')  c == L'Ё' || c == L'ё';
    } else {
        return iswalpha(c);
    }
}

wchar_t toUpperW(wchar_t c, bool isRussian) {
    if (isRussian) {
        if (c >= L'а' && c <= L'я') return c - L'а' + L'А';
        if (c == L'ё') return L'Ё';
        return c;
    }
    return towupper(c);
}

wstring buildCipherAlphabet(const wstring& keyword, const wstring& alphabet, bool isRussian) {
    wstring cipherAlphabet;
    wstring remainingAlphabet = alphabet;
    
    // Добавляем уникальные буквы ключевого слова
    for (wchar_t c : keyword) {
        wchar_t upperC = toUpperW(c, isRussian);
        size_t pos = remainingAlphabet.find(upperC);
        if (pos != wstring::npos) {
            cipherAlphabet += upperC;
            remainingAlphabet.erase(pos, 1); // Удаляем использованную букву
        }
    }
    
    // Добавляем оставшиеся буквы алфавита
    cipherAlphabet += remainingAlphabet;
    
    return cipherAlphabet;
}

wstring encrypt(const wstring& text, const wstring& cipherAlphabet, const wstring& alphabet, bool isRussian) {
    wstring result;
    for (wchar_t c : text) {
        if (isAlphaChar(c, isRussian)) {
            bool isLower = isRussian ? ((c >= L'а' && c <= L'я') || c == L'ё') : iswlower(c);
            wchar_t upperC = toUpperW(c, isRussian);
            size_t pos = alphabet.find(upperC);
            if (pos != wstring::npos) {
                wchar_t encrypted = cipherAlphabet[pos];
                result += isLower ? towlower(encrypted) : encrypted;
            } else {
                result += c;
            }
        } else {
            result += c;
        }
    }
    return result;
}
wstring decrypt(const wstring& text, const wstring& cipherAlphabet, const wstring& alphabet, bool isRussian) {
    wstring result;
    for (wchar_t c : text) {
        if (isAlphaChar(c, isRussian)) {
            bool isLower = isRussian ? ((c >= L'а' && c <= L'я') || c == L'ё') : iswlower(c);
            wchar_t upperC = toUpperW(c, isRussian);
            size_t pos = cipherAlphabet.find(upperC);
            if (pos != wstring::npos) {
                wchar_t decrypted = alphabet[pos];
                result += isLower ? towlower(decrypted) : decrypted;
            } else {
                result += c;
            }
        } else {
            result += c;
        }
    }
    return result;
}

bool writeToFile(const string& filename, const wstring& content) {
    ofstream file(filename, ios::binary);
    if (file.is_open()) {
        wstring_convert<codecvt_utf8<wchar_t>> converter;
        string utf8_content = converter.to_bytes(content);
        file << utf8_content;
        file.close();
        return true;
    }
    return false;
}

void runAlphabetCipher() {
    initConsoleAlph();
    
    int langChoice;
    while (true) {
        cout << "\nВыберите язык:\n1. Русский\n2. Английский\n3. Назад\nВаш выбор: ";
        cin >> langChoice;
        cin.ignore();
        
        if (langChoice == 3) return;
        if (langChoice == 1 || langChoice == 2) break;
        cout << "Некорректный выбор! Попробуйте снова.\n";
    }
    
    bool isRussian = (langChoice == 1);
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    string alphabetStr = getAlphabet(isRussian);
    wstring alphabet = converter.from_bytes(alphabetStr);
    
    wstring keyword;
    while (true) {
        cout << "Введите кодовое слово (" 
             << (isRussian ? "русские" : "английские") 
             << " буквы без повторений): ";
        
        string input;
        getline(cin, input);
        keyword = converter.from_bytes(input);
        
        bool valid = true;
        wstring temp;
        for (wchar_t c : keyword) {
            if (!isAlphaChar(c, isRussian)) {
                valid = false;
                break;
            }
            wchar_t upperC = toUpperW(c, isRussian);
            if (temp.find(upperC) != wstring::npos) {
                valid = false;
                break;
            }
            temp += upperC;
        }
        
        if (valid && !temp.empty()) break;
        cout << "Некорректное слово! Используйте только уникальные "
             << (isRussian ? "русские" : "английские") << " буквы.\n";
    }
    
    wstring cipherAlphabet = buildCipherAlphabet(keyword, alphabet, isRussian);
    
    cout << "\nИсходный алфавит: " << alphabetStr << endl;
    cout << "Алфавит замены:  " << converter.to_bytes(cipherAlphabet) << endl;
    
    cout << "\nВведите сообщение для шифрования: ";
    string message;
    getline(cin, message);
    wstring wmessage = converter.from_bytes(message);

    wstring encrypted = encrypt(wmessage, cipherAlphabet, alphabet, isRussian);
    cout << "\nЗашифрованное сообщение: " << converter.to_bytes(encrypted) << endl;
    
    wstring decrypted = decrypt(encrypted, cipherAlphabet, alphabet, isRussian);
    cout << "Расшифрованное сообщение: " << converter.to_bytes(decrypted) << endl;

    if (writeToFile("encryptedAlph.txt", encrypted)) {
        cout << "Зашифрованный текст сохранен в encryptedAlph.txt" << endl;
    } else {
        cerr << "Ошибка при записи в encryptedAlph.txt" << endl;
    }

    if (writeToFile("decryptedAlph.txt", decrypted)) {
        cout << "Расшифрованный текст сохранен в decryptedAlph.txt" << endl;
    } else {
        cerr << "Ошибка при записи в decryptedAlph.txt" << endl;
    }
}
