#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>          // Necesario para std::string
#include <sys/utsname.h>   // Necesario para uname() y struct utsname
#include <fstream>         // Necesario para std::ifstream
#include <iostream>        // Si usas std::cout o std::cerr para depuración


std::string getUpTimeFormatted();
std::string getOsName();
std::string getKernelVersion();
float getCpuUsage();
float getMemoryUsage();
int getTotalProcesses();
int getRunningProcesses();
std::string generateDynamicBar(float percentage, int width = 20);

#endif
