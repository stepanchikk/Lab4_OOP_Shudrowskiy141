#include <iostream>          
#include <locale>            
#include <cmath>           
#include <initializer_list>  // Для використання списку ініціалізаці
#include <cstdlib>           // Для використання функції rand() для генерації випадкових чисел
#include <ctime>             // Для ініціалізації випадкових чисел на основі часу

// Клас вектора у тривимірному просторі
class Vector3D {
private:
    double x, y, z;           // Координати вектора
    static int objectCount;    // Лічильник кількості створених об'єктів класу

public:
    mutable int State;        // Змінна стану для відстеження помилок або інших станів вектора
    
    // Конструктори
    Vector3D() : x(0), y(0), z(0), State(0) { objectCount++; }  // Конструктор за замовчуванням (всі координати = 0)
    Vector3D(double val) : x(val), y(val), z(val), State(0) { objectCount++; }  // Конструктор з одним числом для ініціалізації всіх координат
    Vector3D(std::initializer_list<double> list) {  // Конструктор зі списком ініціалізації
        auto it = list.begin();
        x = (list.size() > 0) ? *it++ : 0;
        y = (list.size() > 1) ? *it++ : 0;
        z = (list.size() > 2) ? *it++ : 0;
        State = 0;
        objectCount++;
    }
    Vector3D(double* arr) {  // Конструктор з вказівником на масив
        if (arr == nullptr) {
            State = -1;  // Код помилки, якщо вказівник на масив null
            x = y = z = 0;
        } else {
            x = arr[0]; y = arr[1]; z = arr[2];
            State = 0;
        }
        objectCount++;
    }

    // Деструктор
    ~Vector3D() { 
        std::cout << "Вектор знищено. Стан вектора: (" << x << ", " << y << ", " << z << ")\n";
        objectCount--; 
    }

    // Оператор присвоєння
    Vector3D& operator=(const Vector3D& v) {
        if (this != &v) {
            x = v.x; y = v.y; z = v.z;
        }
        return *this;
    }
    
    // Арифметичні оператори
    Vector3D operator+(const Vector3D& v) const { return Vector3D{x + v.x, y + v.y, z + v.z}; }  // Додавання векторів
    Vector3D operator-(const Vector3D& v) const { return Vector3D{x - v.x, y - v.y, z - v.z}; }  // Віднімання векторів
    Vector3D operator*(double scalar) const { return Vector3D{x * scalar, y * scalar, z * scalar}; }  // Множення вектора на число
    Vector3D operator/(double scalar) const {
        if (scalar == 0) { return Vector3D(*this); }  // Перевірка ділення на нуль
        return Vector3D{x / scalar, y / scalar, z / scalar};  // Ділення вектора на число
    }
    Vector3D operator%(int scalar) const { return Vector3D{fmod(x, scalar), fmod(y, scalar), fmod(z, scalar)}; }  // Операція остачі для векторів
    
    // Унарні оператори
    Vector3D operator-() const { return Vector3D{-x, -y, -z}; }  // Зворотній вектор
    bool operator!() const { return (x == 0 && y == 0 && z == 0); }  // Логічне заперечення (перевірка на нульовий вектор)
    Vector3D& operator++() { x++; y++; z++; return *this; }  // Префіксний інкремент (збільшення всіх координат на 1)
    Vector3D operator++(int) { Vector3D temp = *this; ++(*this); return temp; }  // Постфіксний інкремент
    
    // Оператори порівняння
    bool operator==(const Vector3D& v) const { return (x == v.x && y == v.y && z == v.z); }  // Перевірка на рівність векторів
    bool operator!=(const Vector3D& v) const { return !(*this == v); }  // Перевірка на нерівність векторів
    bool operator>(const Vector3D& v) const { return (x > v.x && y > v.y && z > v.z); }  // Порівняння на більшість
    bool operator<(const Vector3D& v) const { return (x < v.x && y < v.y && z < v.z); }  // Порівняння на меншість
    
    // Оператор доступу за індексом (для координат x, y, z)
    double& operator[](int index) {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        State = -3; return z;  // Якщо індекс невірний, встановлюємо помилку і повертаємо координату z
    }
    
    // Оператор виклику
    void operator()() { std::cout << "Вектор: (" << x << ", " << y << ", " << z << ")\n"; }  // Виведення вектора на екран
    
    // Оператори виводу та вводу
    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;  // Оператор виведення вектора
    }
    friend std::istream& operator>>(std::istream& is, Vector3D& v) {
        is >> v.x >> v.y >> v.z;  // Оператор вводу координат вектора
        return is;
    }
    
    // Заповнення випадковими числами
    void randomize() {
        x = (rand() % 200 - 100) / 10.0;  // Випадкове значення для x
        y = (rand() % 200 - 100) / 10.0;  // Випадкове значення для y
        z = (rand() % 200 - 100) / 10.0;  // Випадкове значення для z
    }
};

// Статична змінна для підрахунку кількості об'єктів класу
int Vector3D::objectCount = 0;

// Головна функція для перевірки
int main() {
    std::locale::global(std::locale("uk_UA.utf8")); // Встановлення української локалі для підтримки кирилиці
    srand(time(0));  // Ініціалізація генератора випадкових чисел на основі поточного часу
    
    Vector3D v1;  // Створення об'єкта вектора v1
    char choice;
    std::cout << "Ви хочете ввести вектор вручну (h) чи використовувати випадкові значення (r)? ";
    std::cin >> choice;  // Користувач вибирає, чи вводити вручну чи використовувати рандомні значення
    
    if (choice == 'h' || choice == 'H') {
        std::cout << "Введіть координати вектора v1 (x, y, z): ";
        std::cin >> v1;  // Введення координат вручну
    } else {
        v1.randomize();  // Генерація випадкових значень для v1
        std::cout << "Згенерований випадковий вектор v1: " << v1 << std::endl;
    }
    
    Vector3D v2;  // Створення другого випадкового вектора v2
    v2.randomize();
    std::cout << "Рандомний вектор v2: " << v2 << std::endl;
    
    Vector3D v3 = v1 + v2;  // Додавання двох векторів
    Vector3D v4 = v3 * 2;   // Множення вектора на скаляр
    v4++;  // Префіксне збільшення всіх координат вектора
    
    std::cout << "Результат v4: " << v4 << std::endl;  // Виведення результату
    
    return 0;
}
