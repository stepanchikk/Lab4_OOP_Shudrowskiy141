#include <iostream>   
#include <map>        // Підключення бібліотеки для роботи з асоціативними масивами (map)
#include <string>     // Підключення бібліотеки для роботи зі строками (string)
#include <cstdlib>    // Підключення для функцій генерації випадкових чисел (rand)
#include <ctime>      // Підключення для роботи з часом (time)
#include <iomanip>    // Підключення для форматування виведення (setw)
using namespace std;  

// Клас асоціативного масиву між двома сутностями
class AssociativeArray {
private:
    map<string, string> data; // Визначення асоціативного масиву (ключ - значення, тип string)
    int CodeError;  // Змінна для збереження коду помилки

public:
    // Конструктор
    AssociativeArray() : CodeError(0) {   // Ініціалізація конструктора. Код помилки за замовчуванням = 0
        srand(time(0)); // Ініціалізація генератора випадкових чисел з поточного часу
    }

    // Функція додавання сутностей у асоціативний масив
    void add(const string& fullName, const string& code) {
        data[fullName] = code;  // Додаємо пару ключ-значення в масив
    }

    // Перевантаження операції [] для доступу до елементів масиву
    string& operator[](const string& fullName) {
        if (data.find(fullName) == data.end()) {  // Перевірка чи є ключ у масиві
            CodeError = 1;  // Якщо ні, встановлюємо код помилки
            throw runtime_error("Помилка: сутність не знайдена!");  // Викидаємо помилку
        }
        return data[fullName];  // Повертаємо значення по ключу
    }

    // Перевантаження операції виклику функції для доступу до елементів масиву
    string operator()(const string& fullName) const {
        if (data.find(fullName) == data.end()) {  // Перевірка чи є ключ у масиві
            return "Помилка: сутність не знайдена!";  // Якщо немає, повертаємо повідомлення про помилку
        }
        return data.at(fullName);  // Повертаємо значення по ключу
    }

    // Генерація випадкових даних (від 3 до 10 пар)
    void generateRandomData() {
        string firstNames[] = {"Ivan", "Petro", "Maria", "Oksana", "Dmytro", "Anna", "Serhii", "Olena", "Yurii", "Nadia"};  // Массив імен
        string lastNames[] = {"Shevchenko", "Kovalenko", "Boyko", "Tkachenko", "Kozak", "Melnyk", "Kharchenko", "Dovzhenko", "Zinchenko", "Hrytsenko"};  // Массив прізвищ
        int count = rand() % 8 + 3; // Випадкове число від 3 до 10 для кількості пар
        for (int i = 0; i < count; i++) {
            string fullName = firstNames[rand() % 10] + " " + lastNames[rand() % 10];  // Створення випадкового повного імені
            string code = to_string(rand() % 90000 + 10000);  // Генерація випадкового коду
            add(fullName, code);  // Додавання в асоціативний масив
        }
    }

    // Дружня функція для введення даних в асоціативний масив
    friend istream& operator>>(istream& in, AssociativeArray& aa) {
        string firstName, lastName, code;  // Змінні для введення даних
        cout << "Введіть ім'я, прізвище і код: ";  // Запит користувача
        in >> firstName >> lastName >> code;  // Зчитування введених даних
        string fullName = firstName + " " + lastName;  // Формуємо повне ім'я
        aa.add(fullName, code);  // Додаємо пару ім'я-код в масив
        return in;  // Повертаємо потік
    }

    // Дружня функція для виведення асоціативного масиву у вигляді таблиці
    friend ostream& operator<<(ostream& out, const AssociativeArray& aa) {
        out << "+-------------------------+----------------+" << endl;  // Заголовок таблиці
        out << "|         Ім'я           |      Код       |" << endl;  // Імена колонок
        out << "+-------------------------+----------------+" << endl;
        for (const auto& pair : aa.data) {  // Перебір всіх пар у масиві
            out << "| " << setw(23) << left << pair.first  // Виведення імені
                << " | " << setw(14) << left << pair.second << " |" << endl;  // Виведення коду
        }
        out << "+-------------------------+----------------+" << endl;  // Закриття таблиці
        return out;  // Повертаємо потік
    }
};

// Головна функція
int main() {
    AssociativeArray aa;  // Створення об'єкта класу
    int choice;  // Змінна для вибору режиму

    cout << "Оберіть режим: 1 - Ввести вручну, 2 - Згенерувати випадково: ";  // Запит режиму
    cin >> choice;  // Зчитування вибору

    if (choice == 1) {  // Якщо вибрано введення вручну
        int n;  // Кількість пар
        cout << "Скільки пар ви хочете ввести? ";  // Запит кількості
        cin >> n;  // Зчитування кількості
        for (int i = 0; i < n; i++) {
            cin >> aa;  // Викликаємо функцію введення для кожної пари
        }
    } else if (choice == 2) {  // Якщо вибрано генерацію випадкових даних
        aa.generateRandomData();  // Генерація випадкових даних
    }

    // Виведення асоціативного масиву
    cout << "Асоціативний масив: " << endl;
    cout << aa;  // Використовуємо перевантажену функцію виведення

    // Пошук за ключем (дозволяє багаторазовий пошук)
    string firstName, lastName;  // Змінні для введення імені та прізвища
    while (true) {
        cout << "Введіть ім'я та прізвище для пошуку (або 'exit' для виходу): ";  // Запит на введення
        cin >> firstName;  // Введення імені
        if (firstName == "exit") break;  // Якщо введено "exit", виходимо з циклу
        cin >> lastName;  // Введення прізвища
        string fullName = firstName + " " + lastName;  // Формуємо повне ім'я
        try {
            cout << "Код: " << aa[fullName] << endl;  // Пошук і виведення коду по імені
        } catch (const runtime_error& e) {  // Якщо виникає помилка
            cout << e.what() << endl;  // Виводимо повідомлення про помилку
        }
    }

    return 0;  // Завершення програми
}
