#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<vector>

struct Datos {
    std::string name;
    int age;
    std::string dead;
};

int main() {
    // Nombre del archivo CSV
    const char* nombreArchivo = "ejemplo.csv";

    // Crear un objeto ofstream para abrir el archivo (crear si no existe)
    /*
    std::ofstream archivoSalida(nombreArchivo, std::ios::app);

    // Verificar si se pudo abrir correctamente el archivo
    if (!archivoSalida.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return 1; // Salir con código de error
    }

    // Escribir datos en el archivo CSV
    archivoSalida << "name,age,dead" << std::endl;
    archivoSalida << "bau,23,false" << std::endl;
    archivoSalida << "fede,17,false" << std::endl;

    // Cerrar el archivo después de escribir en él
    archivoSalida.close();
    */

    std::ifstream archivoEntrada(nombreArchivo);
    if (!archivoEntrada.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return 1; // Salir con código de error
    }

    std::vector<Datos> datos;
    std::string linea;
    bool firstLine = true;
    while (std::getline(archivoEntrada, linea)) {
        if (firstLine) {
            firstLine = false;
        } else {
            std::istringstream ss(linea);
            //pasamos linea como si fuese un flujo de entrada, para poder separar por campos
            std::string campo;

            // Crear una persona para almacenar los datos de la línea
            Datos dato;

            // Procesar cada campo de la línea
            std::getline(ss, dato.name, ',');
            //acá agarramos una línea de ss hasta que llegue a la coma y la guardamos en dato.name

            std::getline(ss, campo, ',');
            //acá agarramos una línea de ss hasta que llegue a la coma y la guardamos en campo

            dato.age = std::stoi(campo);
            //string to int stoi

            std::getline(ss, dato.dead, ',');

            // Almacenar la persona en el vector
            datos.push_back(dato);
        }
    }

    // Cerrar el archivo después de leerlo
    archivoEntrada.close();

    for (const auto& d : datos) {
        std::cout << "Nombre: " << d.name << ", Edad: " << d.age << ", Muerto: " << d.dead << std::endl;
    }


    return 0; // Salir sin errores
}