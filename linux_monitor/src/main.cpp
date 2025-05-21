#include <sstream> // Necesario para std::ostringstream
#include <iostream>
#include <iomanip>
#include <unistd.h> // Para la función sleep
#include "system.h"

// Colores ANSI
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define MAGENTA "\033[35m"

// Función para mostrar las métricas
void displayMetrics()
{
    std::string osName = getOsName();
    std::string kernelVersion = getKernelVersion();
    float cpuUsage = getCpuUsage();
    std::string dynamicBarCpu = generateDynamicBar(cpuUsage, 30);
    float memoryUsage = getMemoryUsage();
    std::string dynamicBarMemory = generateDynamicBar(memoryUsage, 30);
    int totalProcesses = getTotalProcesses();
    int runningProcesses = getRunningProcesses();
    std::string upTimeFormatted = getUpTimeFormatted();

    system("clear");

    std::cout << CYAN << "============================== SYSTEM MONITOR ==============================" << RESET << "\n\n";

    std::cout << CYAN << std::left << std::setw(18) << "OS:" << RESET << osName << "\n";
    std::cout << CYAN << std::left << std::setw(18) << "Kernel Version:" << RESET << kernelVersion << "\n\n";

    std::cout << YELLOW << std::left << std::setw(18) << "CPU Usage:" << RESET
              << std::fixed << std::setprecision(1) << std::setw(5) << cpuUsage << "% "
              << GREEN << dynamicBarCpu << RESET << "\n";

    std::cout << YELLOW << std::left << std::setw(18) << "Memory Usage:" << RESET
              << std::fixed << std::setprecision(1) << std::setw(5) << memoryUsage << "% "
              << BLUE << dynamicBarMemory << RESET << "\n\n";

    std::cout << MAGENTA << std::left << std::setw(18) << "Total Processes:" << RESET << totalProcesses << "\n";
    std::cout << MAGENTA << std::left << std::setw(18) << "Running Processes:" << RESET << runningProcesses << "\n";
    std::cout << CYAN << std::left << std::setw(18) << "Uptime:" << RESET << upTimeFormatted << "\n";

    std::cout << "\n"
              << CYAN << "===========================================================================" << RESET << "\n";
    std::cout << "Press Ctrl+C to exit.\n";
}

int main()
{
    while (true)
    {                     // Bucle infinito para la actualización en tiempo real
        displayMetrics(); // Mostrar las métricas actualizadas
        sleep(1);         // Esperar 1 segundo antes de la siguiente actualización
    }
    return 0;
}
