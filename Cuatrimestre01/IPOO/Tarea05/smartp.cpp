#include <iostream>
#include <memory>

class Punto
{
public:
    Punto(double x, double y) : x(x), y(y){};

    void print()
    {
        std::cout << "(" << x << ", " << y << ")\n";
    }

private:
    double x{}, y{};
};

/**
 * Ejemplo de punteros inteligentes
 *
 * Programa que muestra como utilizar punteros inteligentes para el manejo de memoria dinamica.
 * Se incluye el uso de std::unique_ptr
 *
 * Salida:
 * 100, Hola
 * 0x263a89a12b0, 0x263a89a6f9
 * (3, 7)
 */
int main()
{
    // Ejemplos de punteros inteligentes
    std::unique_ptr<int> num{new int(100)};
    std::unique_ptr<std::string> cad{new std::string("Hola")};
    std::unique_ptr<Punto> punto{new Punto(3, 7)};

    // 100, Hola
    std::cout << *num << ", " << *cad << "\n";           
    // 0x263a89a12b0, 0x263a89a6f9
    std::cout << num.get() << ", " << cad.get() << "\n"; 
    // (3, 7)
    punto->print();                                      

    return 0;
}
