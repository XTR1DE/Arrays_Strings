#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>


void findAnomalies(double arr[], int size, double threshold = 3.0) {
    if (size <= 1) {
        throw std::runtime_error("Размер массива должен быть больше 1");
    }

    // среднее арифм. элементов массива
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    double mean = sum / size;

    // Сумма (Xi - mean)^2
    double sumSqDiff = 0.0;
    for (int i = 0; i < size; ++i) {
        double diff = arr[i] - mean;
        sumSqDiff += diff * diff;
    }
    
    // Отклонение
    double sigma = sqrt(sumSqDiff / (size - 1));

    // Поиск аномалий
    std::cout << "Аномальные выбросы (порог = " << threshold << "):\n";
    bool found = false;
    for (int i = 0; i < size; ++i) {
        double z = (arr[i] - mean) / sigma;
        if (std::abs(z) > threshold) {
            std::cout << "  " << arr[i] << " (Z = " << z << ")\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "  Аномалий не обнаружено.\n";
    }
}


int split(const std::string& text, std::string words[], int maxWords) {
    int count = 0;
    std::string word = "";

    for (int i = 0; i <= text.length(); i++) {
        // Если пробел или конец строки – добавляем слово
        if (i == text.length() || text[i] == ' ') {
            if (word != "") {
                words[count] = word;
                count++;
                word = "";
            }
        }
        else {
            word = word + text[i]; // ищем дальше
        }
    }
    return count;
}


void findCommonWords(std::string words1[], int size1, std::string words2[], int size2) {
    std::string printedWords[100];
    int printedCount = 0;

    std::cout << "Общие слова:\n";

    for (int i = 0; i < size1; ++i) {
        bool alreadyPrinted = false;
        for (int p = 0; p < printedCount; ++p) {
            if (printedWords[p] == words1[i]) {
                alreadyPrinted = true;
                break;
            }
        }
        if (alreadyPrinted) 
            continue;

        for (int j = 0; j < size2; ++j) {
            if (words1[i] == words2[j]) {
                std::cout << "  " << words1[i] << "\n";
                printedWords[printedCount] = words1[i];
                ++printedCount;
                break;
            }
        }
    }

    if (printedCount == 0) {
        std::cout << "  Нет общих слов.\n";
    }
}


int main() {
    setlocale(LC_ALL, "");

    // Тесты

    std::cout << "Задача 1:\n";

    double data[] = { 100, 105, 98, 102, 200, 95, 101, 500, 103 };
    int size = 9;

    // Тест 1
    std::cout << "\n--- Тест 1: порог = 0.3 ---\n";
    findAnomalies(data, size, 0.3);

    // Тест 2
    std::cout << "\n--- Тест 2: порог = 0.4 ---\n";
    findAnomalies(data, size, 0.4);

    // Тест 3
    std::cout << "\n--- Тест 3: порог = 1.0 ---\n";
    findAnomalies(data, size, 1.0);

    std::cout << "\nЗадача 2:\n";

    // Тест 1
    std::cout << "\n--- Тест 1:\n";
    std::string t1_1 = "the quick brown fox jumps over the lazy dog";
    std::string t2_1 = "the lazy dog sleeps under the brown fox";
    const int MAX = 100;
    std::string w1[MAX], w2[MAX];
    int s1 = split(t1_1, w1, MAX);
    int s2 = split(t2_1, w2, MAX);
    findCommonWords(w1, s1, w2, s2);

    // Тест 2
    std::cout << "\n--- Тест 2\n";
    std::string t1_2 = "hello world from C++";
    std::string t2_2 = "goodbye world from Python";
    s1 = split(t1_2, w1, MAX);
    s2 = split(t2_2, w2, MAX);
    findCommonWords(w1, s1, w2, s2);

    // Тест 3
    std::cout << "\n--- Тест 3\n";
    std::string t1_3 = "apple banana cherry";
    std::string t2_3 = "dog cat mouse";
    s1 = split(t1_3, w1, MAX);
    s2 = split(t2_3, w2, MAX);
    findCommonWords(w1, s1, w2, s2);

    return 0;


}
