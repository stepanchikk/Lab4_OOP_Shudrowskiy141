#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Структура для збереження пари "Ім'я - Код"
struct Pair {
    string fullName;
    int code;
};

// Власний асоціативний масив
class AssociativeArray {
private:
    Pair* data;
    int size;
    int capacity;
    int CodeError;

    void resize() { // Функція збільшення розміру масиву при заповненні
        capacity *= 2;
        Pair* newData = new Pair[capacity];
        for (int i = 0; i < size; i++) { // Копіюємо старі дані в новий масив
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    AssociativeArray(int initialCapacity = 10) {
        size = 0;
        capacity = initialCapacity;
        data = new Pair[capacity];
        CodeError = 0;
    }

    ~AssociativeArray() {
        delete[] data;
    }

    void add(const string& fullName, int code) { // Функція додавання нової пари
        for (int i = 0; i < size; i++) { // Перевіряємо, чи є вже таке ім'я
            if (data[i].fullName == fullName) {
                data[i].code = code;
                return;
            }
        }
        if (size == capacity) { // Якщо масив заповнений, розширюємо його
            resize();
        }
        data[size++] = {fullName, code};
    }

    int& operator[](const string& fullName) { 
        for (int i = 0; i < size; i++) { // Шукаємо ім'я в масиві
            if (data[i].fullName == fullName) {
                return data[i].code;
            }
        }
        CodeError = 1;
        throw runtime_error("Error: entity not found!");
    }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << "[ " << data[i].fullName << " ] -> [ " << data[i].code << " ]\n";
        }
    }
};

void addRandomEntries(AssociativeArray& aa, int count) {
    string firstNames[] = {"Ivan", "Maria", "Oleg", "Anna", "Dmytro", "Olena", "Serhii", "Nadia", "Yurii", "Kateryna"};
    string lastNames[] = {"Petrenko", "Koval", "Sydorenko", "Melnyk", "Tkachenko", "Bielov", "Shevchenko", "Kryvonos", "Havrylenko", "Bondarenko"};
    
    for (int i = 0; i < count; i++) { // Додаємо задану кількість записів
        string fullName = firstNames[rand() % 10] + " " + lastNames[rand() % 10];
        int code = rand() % 90000 + 10000;
        aa.add(fullName, code);
    }
}

int main() {
    srand(time(0));
    AssociativeArray aa;

    cout << "Choose input method: \n1 - Manual entry\n2 - Random data\nEnter your choice: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        int n;
        cout << "Enter number of entries: ";
        cin >> n;
        cin.ignore();
        for (int i = 0; i < n; i++) {
            string fullName;
            int code;
            cout << "Enter full name: ";
            getline(cin, fullName);
            cout << "Enter code (number): ";
            cin >> code;
            cin.ignore();
            aa.add(fullName, code);
        }
    } else {
        int n = rand() % 5 + 3;
        addRandomEntries(aa, n);
    }

    cout << "Stored data:" << endl;
    aa.display();

    while (true) {
        string searchName;
        cout << "\nEnter name to search (or type 'exit' to quit): ";
        getline(cin, searchName);
        if (searchName == "exit") break;
        try {
            cout << "Code: " << aa[searchName] << endl;
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}
