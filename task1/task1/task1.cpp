#include <iostream>
#include <locale>
#include <cmath>
#include <initializer_list>
#include <cstdlib>
#include <ctime>

class Vector3D {
private:
    double x, y, z;
    static int objectCount;
public:
    mutable int State;

    // Конструктори
    Vector3D() : x(0), y(0), z(0), State(0) { objectCount++; }
    Vector3D(double val) : x(val), y(val), z(val), State(0) { objectCount++; }
    Vector3D(std::initializer_list<double> list) {
        auto it = list.begin();
        x = (list.size() > 0) ? *it++ : 0;
        y = (list.size() > 1) ? *it++ : 0;
        z = (list.size() > 2) ? *it++ : 0;
        State = 0;
        objectCount++;
    }
    Vector3D(double* arr) {
        if (arr == nullptr) {
            State = -1; // Код помилки
            x = y = z = 0;
        }
        else {
            x = arr[0]; y = arr[1]; z = arr[2];
            State = 0;
        }
        objectCount++;
    }
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
    Vector3D operator+(const Vector3D& v) const { return Vector3D{ x + v.x, y + v.y, z + v.z }; }
    Vector3D operator-(const Vector3D& v) const { return Vector3D{ x - v.x, y - v.y, z - v.z }; }
    Vector3D operator*(double scalar) const { return Vector3D{ x * scalar, y * scalar, z * scalar }; }
    Vector3D operator/(double scalar) const {
        if (scalar == 0) { return Vector3D(*this); }
        return Vector3D{ x / scalar, y / scalar, z / scalar };
    }
    Vector3D operator%(int scalar) const { return Vector3D{ fmod(x, scalar), fmod(y, scalar), fmod(z, scalar) }; }

    // Унарні оператори
    Vector3D operator-() const { return Vector3D{ -x, -y, -z }; }
    bool operator!() const { return (x == 0 && y == 0 && z == 0); }
    Vector3D& operator++() { x++; y++; z++; return *this; }
    Vector3D operator++(int) { Vector3D temp = *this; ++(*this); return temp; }

    // Оператори порівняння
    bool operator==(const Vector3D& v) const { return (x == v.x && y == v.y && z == v.z); }
    bool operator!=(const Vector3D& v) const { return !(*this == v); }
    bool operator>(const Vector3D& v) const { return (x > v.x && y > v.y && z > v.z); }
    bool operator<(const Vector3D& v) const { return (x < v.x && y < v.y && z < v.z); }

    // Оператор доступу за індексом
    double& operator[](int index) {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        State = -3; return z;
    }

    // Оператор виклику
    void operator()() { std::cout << "Вектор: (" << x << ", " << y << ", " << z << ")\n"; }

    // Оператор виводу та вводу
    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Vector3D& v) {
        is >> v.x >> v.y >> v.z;
        return is;
    }

    // Заповнення випадковими числами
    void randomize() {
        x = (rand() % 200 - 100) / 10.0;
        y = (rand() % 200 - 100) / 10.0;
        z = (rand() % 200 - 100) / 10.0;
    }
};

int Vector3D::objectCount = 0;

// Головна функція для перевірки
int main() {
    setlocale(LC_ALL, "ukr");
    srand(time(0));

    Vector3D v1;
    char choice;
    std::cout << "Ви хочете ввести вектор вручну (h) чи використовувати випадкові значення (r)? ";
    std::cin >> choice;

    if (choice == 'h' || choice == 'H') {
        std::cout << "Введіть координати вектора v1 (x, y, z): ";
        std::cin >> v1;
    }
    else {
        v1.randomize();
        std::cout << "Згенерований випадковий вектор v1: " << v1 << std::endl;
    }

    Vector3D v2;
    v2.randomize();
    std::cout << "Рандомний вектор v2: " << v2 << std::endl;

    Vector3D v3 = v1 + v2;
    Vector3D v4 = v3 * 2;
    v4++;

    std::cout << "Результат v4: " << v4 << std::endl;
    return 0;
}
