#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <chrono>

using namespace std;

// Функция для загрузки словаря из файла
vector<string> loadDictionary(const string& filename) {
    vector<string> dictionary;
    ifstream file(filename);
    string word;
    while (file >> word) {
        dictionary.push_back(word);
    }
    return dictionary;
}

// Функция для проверки, можно ли составить слово из заданных букв
bool canFormWord(const string& word, const unordered_map<char, int>& charCount) {
    unordered_map<char, int> wordCount;
    for (char c : word) {
        wordCount[c]++;
    }
    for (const auto& kv : wordCount) {
        if (charCount.find(kv.first) == charCount.end() || charCount.at(kv.first) < kv.second) {
            return false;
        }
    }
    return true;
}

int main() {
    // Загрузка словаря
    vector<string> dictionary = loadDictionary("RussianNouns.txt");

    // Сортировка словаря по убыванию длины слов
    sort(dictionary.begin(), dictionary.end(), [](const string& a, const string& b{
        return a.size() > b.size();
        });

    // Инициализация хэш-таблицы для подсчёта букв в слове
    unordered_map<char, int> charCount;
    string inputWord;
    cout << "Введите слово: ";
    cin >> inputWord;
    for (char c : inputWord) {
        charCount[c]++;
    }

    // Поиск слов, которые можно составить из букв заданного слова
    vector<string> result;
    auto start = chrono::high_resolution_clock::now();
    for (const string& word : dictionary) {
        if (canFormWord(word, charCount)) {
            result.push_back(word);
        }
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Найденные слова:" << endl;
    for (const string& word : result) {
        cout << word << endl;
    }
    cout << "Время выполнения: " << elapsed.count() << " секунд" << endl;

    return 0;
}