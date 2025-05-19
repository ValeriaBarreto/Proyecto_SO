#include <sstream>  // Necesario para std::ostringstream
#include <iostream>
#include <iomanip>
#include <unistd.h>  // Para la función sleep
#include "system.h"

// Colores ANSI
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"


// Función para mostrar las métricas
void displayMetrics() {

    system("clear");  // Limpiar la pantalla
    std::ostringstream output;

    // Información del sistema
    std::cout  << "OS: " << getOsName() << RESET << "\n";
    std::cout  << "Kernel: " << getKernelVersion() << RESET << "\n\n";

    // Uso de CPU con barra dinámica
    std::cout << "CPU: " << std::fixed << std::setprecision(1) << getCpuUsage() << "% ";
    std::cout << generateDynamicBar(getCpuUsage(),20) << "\n\n";

    // Uso de memoria con barra dinámica más ancha
    std::cout << "Memory: " << std::fixed << std::setprecision(1) << getMemoryUsage() << "% ";
    std::cout << generateDynamicBar(getMemoryUsage(), 20) << "\n\n";

    // Resto de la información
    std::cout << "Total Processes: " << getTotalProcesses() << "\n";
    std::cout << "Running Processes: " << getRunningProcesses() << "\n";
    std::cout << "Up Time: " << getUpTimeFormatted() << "\n\n";
   
   std::cout << output.str();    

}

int main() {
    while (true) {  // Bucle infinito para la actualización en tiempo real
        displayMetrics();  // Mostrar las métricas actualizadas
        sleep(1);  // Esperar 1 segundo antes de la siguiente actualización
    }
    return 0;
}
