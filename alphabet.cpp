#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void initConsoleAlph() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
}

// Функция для чтения файла
string readFileAlph(const string& filename) {
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

// Функция для проверки, является ли байт началом UTF-8 символа
bool isUtf8StartByte(unsigned char c) {
    return (c & 0xC0) != 0x80;
}

// Функция для разбивки UTF-8 строки на символы
vector<string> splitUtf8(const string& str) {
    vector<string> characters;
    string currentChar;
    
    for (unsigned char c : str) {
        if (isUtf8StartByte(c) && !currentChar.empty()) {
            characters.push_back(currentChar);
            currentChar.clear();
        }
        currentChar += c;
    }
    
    if (!currentChar.empty()) {
        characters.push_back(currentChar);
    }
    
    return characters;
}

// Функция для поиска символа в векторе
size_t findInVector(const vector<string>& vec, const string& target) {
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i] == target) {
            return i;
        }
    }
    return vec.size(); // Возвращаем размер вектора если не нашли (аналог npos)
}

// Функция для преобразования UTF-8 символа в верхний регистр
string toUpperUtf8(const string& utf8Char) {
    // Простая замена для русских букв
    if (utf8Char == "а") return "А";
    if (utf8Char == "б") return "Б";
    if (utf8Char == "в") return "В";
    if (utf8Char == "г") return "Г";
    if (utf8Char == "д") return "Д";
    if (utf8Char == "е") return "Е";
    if (utf8Char == "ё") return "Ё";
    if (utf8Char == "ж") return "Ж";
    if (utf8Char == "з") return "З";
    if (utf8Char == "и") return "И";
    if (utf8Char == "й") return "Й";
    if (utf8Char == "к") return "К";
    if (utf8Char == "л") return "Л";
    if (utf8Char == "м") return "М";
    if (utf8Char == "н") return "Н";
    if (utf8Char == "о") return "О";
    if (utf8Char == "п") return "П";
    if (utf8Char == "р") return "Р";
    if (utf8Char == "с") return "С";
    if (utf8Char == "т") return "Т";
    if (utf8Char == "у") return "У";
    if (utf8Char == "ф") return "Ф";
    if (utf8Char == "х") return "Х";
    if (utf8Char == "ц") return "Ц";
    if (utf8Char == "ч") return "Ч";
    if (utf8Char == "ш") return "Ш";
    if (utf8Char == "щ") return "Щ";
    if (utf8Char == "ъ") return "Ъ";
    if (utf8Char == "ы") return "Ы";
    if (utf8Char == "ь") return "Ь";
    if (utf8Char == "э") return "Э";
    if (utf8Char == "ю") return "Ю";
    if (utf8Char == "я") return "Я";
    
    // Для английских букв
    if (utf8Char.size() == 1 && utf8Char[0] >= 'a' && utf8Char[0] <= 'z') {
        return string(1, utf8Char[0] - 'a' + 'A');
    }
    
    return utf8Char;
}

// Функция для преобразования UTF-8 символа в нижний регистр
string toLowerUtf8(const string& utf8Char) {
    // Простая замена для русских букв
    if (utf8Char == "А") return "а";
    if (utf8Char == "Б") return "б";
    if (utf8Char == "В") return "в";
    if (utf8Char == "Г") return "г";
    if (utf8Char == "Д") return "д";
    if (utf8Char == "Е") return "е";
    if (utf8Char == "Ё") return "ё";
    if (utf8Char == "Ж") return "ж";
    if (utf8Char == "З") return "з";
    if (utf8Char == "И") return "и";
    if (utf8Char == "Й") return "й";
    if (utf8Char == "К") return "к";
    if (utf8Char == "Л") return "л";
    if (utf8Char == "М") return "м";
    if (utf8Char == "Н") return "н";
    if (utf8Char == "О") return "о";
    if (utf8Char == "П") return "п";
    if (utf8Char == "Р") return "р";
    if (utf8Char == "С") return "с";
    if (utf8Char == "Т") return "т";
    if (utf8Char == "У") return "у";
    if (utf8Char == "Ф") return "ф";
    if (utf8Char == "Х") return "х";
    if (utf8Char == "Ц") return "ц";
    if (utf8Char == "Ч") return "ч";
    if (utf8Char == "Ш") return "ш";
    if (utf8Char == "Щ") return "щ";
    if (utf8Char == "Ъ") return "ъ";
    if (utf8Char == "Ы") return "ы";
    if (utf8Char == "Ь") return "ь";
    if (utf8Char == "Э") return "э";
    if (utf8Char == "Ю") return "ю";
    if (utf8Char == "Я") return "я";
    
    // Для английских букв
    if (utf8Char.size() == 1 && utf8Char[0] >= 'A' && utf8Char[0] <= 'Z') {
        return string(1, utf8Char[0] - 'A' + 'a');
    }
    
    return utf8Char;
}

string getAlphabet(bool isRussian) {
    return isRussian ? "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ" 
                    : "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}

bool isAlphaChar(const string& utf8Char, bool isRussian, const vector<string>& alphabetChars) {
    string upperChar = toUpperUtf8(utf8Char);
    
    for (size_t i = 0; i < alphabetChars.size(); i++) {
        if (alphabetChars[i] == upperChar) {
            return true;
        }
    }
    return false;
}

string buildCipherAlphabet(const string& keyword, const string& alphabet) {
    vector<string> alphabetChars = splitUtf8(alphabet);
    vector<string> remainingAlphabet = alphabetChars;
    vector<string> cipherAlphabet;
    
    vector<string> keywordChars = splitUtf8(keyword);
    
    // Добавляем уникальные буквы ключевого слова
    for (size_t i = 0; i < keywordChars.size(); i++) {
        string upperCh = toUpperUtf8(keywordChars[i]);
        size_t pos = findInVector(remainingAlphabet, upperCh);
        if (pos < remainingAlphabet.size()) {
            cipherAlphabet.push_back(upperCh);
            // Удаляем элемент из remainingAlphabet
            for (size_t j = pos; j < remainingAlphabet.size() - 1; j++) {
                remainingAlphabet[j] = remainingAlphabet[j + 1];
            }
            remainingAlphabet.pop_back();
        }
    }
    
    // Добавляем оставшиеся буквы алфавита
    for (size_t i = 0; i < remainingAlphabet.size(); i++) {
        cipherAlphabet.push_back(remainingAlphabet[i]);
    }
    
    // Собираем обратно в строку
    string result;
    for (size_t i = 0; i < cipherAlphabet.size(); i++) {
        result += cipherAlphabet[i];
    }
    return result;
}

string encrypt(const string& text, const string& cipherAlphabet, const string& alphabet) {
    vector<string> textChars = splitUtf8(text);
    vector<string> alphabetChars = splitUtf8(alphabet);
    vector<string> cipherChars = splitUtf8(cipherAlphabet);
    
    string result;
    
    for (size_t i = 0; i < textChars.size(); i++) {
        string upperCh = toUpperUtf8(textChars[i]);
        size_t pos = findInVector(alphabetChars, upperCh);
        if (pos < alphabetChars.size()) {
            string encrypted = cipherChars[pos];
            
            // Сохраняем регистр
            if (textChars[i] == toLowerUtf8(textChars[i])) {
                result += toLowerUtf8(encrypted);
            } else {
                result += encrypted;
            }
        } else {
            result += textChars[i];
        }
    }
    return result;
}

string decrypt(const string& text, const string& cipherAlphabet, const string& alphabet) {
    vector<string> textChars = splitUtf8(text);
    vector<string> alphabetChars = splitUtf8(alphabet);
    vector<string> cipherChars = splitUtf8(cipherAlphabet);
    
    string result;
    
    for (size_t i = 0; i < textChars.size(); i++) {
        string upperCh = toUpperUtf8(textChars[i]);
        size_t pos = findInVector(cipherChars, upperCh);
        if (pos < cipherChars.size()) {
            string decrypted = alphabetChars[pos];
            
            // Сохраняем регистр
            if (textChars[i] == toLowerUtf8(textChars[i])) {
                result += toLowerUtf8(decrypted);
            } else {
                result += decrypted;
            }
        } else {
            result += textChars[i];
        }
    }
    return result;
}

bool writeToFilealph(const string& filename, const string& content) {
    ofstream file(filename);
    if (file.is_open()) {
        file << content;
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
    string alphabet = getAlphabet(isRussian);
    vector<string> alphabetChars = splitUtf8(alphabet);
    
    string keyword;
    while (true) {
        cout << "Введите кодовое слово (" 
             << (isRussian ? "русские" : "английские") 
             << " буквы без повторений): ";
        
        getline(cin, keyword);
        
        if (keyword.empty()) {
            cout << "Кодовое слово не может быть пустым!\n";
            continue;
        }
        
        vector<string> keywordChars = splitUtf8(keyword);
        
        bool valid = true;
        vector<string> temp;
        
        for (size_t i = 0; i < keywordChars.size(); i++) {
            string upperCh = toUpperUtf8(keywordChars[i]);
            
            // Проверяем, что символ есть в алфавите
            bool foundInAlphabet = false;
            for (size_t j = 0; j < alphabetChars.size(); j++) {
                if (alphabetChars[j] == upperCh) {
                    foundInAlphabet = true;
                    break;
                }
            }
            
            if (!foundInAlphabet) {
                valid = false;
                break;
            }
            
            // Проверяем на повторения
            bool foundInTemp = false;
            for (size_t j = 0; j < temp.size(); j++) {
                if (temp[j] == upperCh) {
                    foundInTemp = true;
                    break;
                }
            }
            
            if (foundInTemp) {
                valid = false;
                break;
            }
            
            temp.push_back(upperCh);
        }
        
        if (valid) break;
        cout << "Некорректное слово! Используйте только уникальные "
             << (isRussian ? "русские" : "английские") << " буквы.\n";
    }
    
    string cipherAlphabet = buildCipherAlphabet(keyword, alphabet);
    
    
    
    cout << "Введите имя файла с текстом: ";
    string filename;
    getline(cin, filename);

    string message;
    try {
        message = readFileAlph(filename);
        cout << "Текст из файла: " << message << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
        cout << "Возврат в главное меню.\n";
        return;
    }

    string encrypted = encrypt(message, cipherAlphabet, alphabet);
    cout << "\nЗашифрованное сообщение: " << encrypted << endl;
    
    string decrypted = decrypt(encrypted, cipherAlphabet, alphabet);
    cout << "Расшифрованное сообщение: " << decrypted << endl;

    if (writeToFilealph("encryptedAlph.txt", encrypted)) {
        cout << "Зашифрованный текст сохранен в encryptedAlph.txt" << endl;
    } else {
        cerr << "Ошибка при записи в encryptedAlph.txt" << endl;
    }

    if (writeToFilealph("decryptedAlph.txt", decrypted)) {
        cout << "Расшифрованный текст сохранен в decryptedAlph.txt" << endl;
    } else {
        cerr << "Ошибка при записи в decryptedAlph.txt" << endl;
    }
}
