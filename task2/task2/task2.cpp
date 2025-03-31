#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Клас асоціативного масиву між двома сутностями
class AssociativeArray {
private:
    map<string, string> data; // Асоціативний масив
    int CodeError; // Код помилки

public:
    // Конструктор
    AssociativeArray() : CodeError(0) {
        srand(time(0)); // Ініціалізація випадкового числа
    }

    // Функція додавання сутностей
    void add(const string& fullName, const string& code) {
        data[fullName] = code;
    }

    // Перевантаження операції []
    string& operator[](const string& fullName) {
        if (data.find(fullName) == data.end()) {
            CodeError = 1;
            throw runtime_error("Помилка: сутність не знайдена!");
        }
        return data[fullName];
    }

    // Перевантаження операції виклику функції
    string operator()(const string& fullName) const {
        if (data.find(fullName) == data.end()) {
            return "Помилка: сутність не знайдена!";
        }
        return data.at(fullName);
    }

    // Генерація випадкових даних (від 3 до 10 пар)
    void generateRandomData() {
        string firstNames[] = { "Ivan", "Petro", "Maria", "Oksana", "Dmytro", "Anna", "Serhii", "Olena", "Yurii", "Nadia" };
        string lastNames[] = { "Shevchenko", "Kovalenko", "Boyko", "Tkachenko", "Kozak", "Melnyk", "Kharchenko", "Dovzhenko", "Zinchenko", "Hrytsenko" };
        int count = rand() % 8 + 3; // Випадкове число від 3 до 10
        for (int i = 0; i < count; i++) {
            string fullName = firstNames[rand() % 10] + " " + lastNames[rand() % 10];
            string code = to_string(rand() % 90000 + 10000);
            add(fullName, code);
        }
    }

    // Дружня функція введення
    friend istream& operator>>(istream& in, AssociativeArray& aa) {
        string firstName, lastName, code;
        cout << "Введіть ім'я, прізвище і код: ";
        in >> firstName >> lastName >> code;
        string fullName = firstName + " " + lastName;
        aa.add(fullName, code);
        return in;
    }

    // Дружня функція виведення у вигляді таблиці
    friend ostream& operator<<(ostream& out, const AssociativeArray& aa) {
        out << "+-------------------------+----------------+" << endl;
        out << "|         Ім'я           |      Код       |" << endl;
        out << "+-------------------------+----------------+" << endl;
        for (const auto& pair : aa.data) {
            out << "| " << setw(23) << left << pair.first
                << " | " << setw(14) << left << pair.second << " |" << endl;
        }
        out << "+-------------------------+----------------+" << endl;
        return out;
    }
};

int main() {
    setlocale(LC_ALL, "ukr");
    AssociativeArray aa;
    int choice;

    cout << "Оберіть режим: 1 - Ввести вручну, 2 - Згенерувати випадково: ";
    cin >> choice;

    if (choice == 1) {
        int n;
        cout << "Скільки пар ви хочете ввести? ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> aa;
        }
    }
    else if (choice == 2) {
        aa.generateRandomData();
    }

    // Вивід даних у вигляді таблиці
    cout << "Асоціативний масив: " << endl;
    cout << aa;

    // Пошук за ключем (дозволяє багаторазовий пошук)
    string firstName, lastName;
    while (true) {
        cout << "Введіть ім'я та прізвище для пошуку (або 'exit' для виходу): ";
        cin >> firstName;
        if (firstName == "exit") break;
        cin >> lastName;
        string fullName = firstName + " " + lastName;
        try {
            cout << "Код: " << aa[fullName] << endl;
        }
        catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}
