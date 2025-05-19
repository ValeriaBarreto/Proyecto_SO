#include <sys/utsname.h>
#include <dirent.h>
#include "system.h"
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>


std::string getOsName() {
    std::ifstream os_release("/etc/os-release");
    std::string line;
    while (getline(os_release, line)) {
        if (line.find("PRETTY_NAME=") != std::string::npos) {
            size_t start = line.find('"') + 1;
            size_t end = line.rfind('"');
            return line.substr(start, end - start);
        }
    }
    return "Linux";
}

std::string getKernelVersion() {
    struct utsname buf;
    if (uname(&buf) == 0) {
        return buf.release;
    }
    return "unknown";
}

float getSystemUptime() {
    std::ifstream file("/proc/uptime");
    float uptime = 0.0f;
    if (file.is_open()) {
        file >> uptime;
    }
    return uptime;
}

std::string getUpTimeFormatted() {
    float uptime_seconds = getSystemUptime();
    unsigned hours = uptime_seconds / 3600;
    unsigned minutes = ((unsigned)uptime_seconds % 3600) / 60;
    unsigned seconds = (unsigned)uptime_seconds % 60;

    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%02u:%02u:%02u", hours, minutes, seconds);
    return std::string(buffer);
}


float getCpuUsage() {
    std::ifstream file("/proc/stat");
    std::string line;
    std::getline(file, line);
    std::istringstream ss(line);

    std::string cpu;
    long user, nice, system, idle, iowait, irq, softirq;
    ss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq;

    long idle_time = idle + iowait;
    long non_idle = user + nice + system + irq + softirq;
    long total = idle_time + non_idle;

    sleep(1); // Esperamos 1 segundo para ver el cambio

    file.clear(); // Reiniciar el estado del archivo
    file.seekg(0); // Volver al inicio
    std::getline(file, line);
    std::istringstream ss2(line);
    ss2 >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq;

    long idle_time2 = idle + iowait;
    long non_idle2 = user + nice + system + irq + softirq;
    long total2 = idle_time2 + non_idle2;

    float totald = total2 - total;
    float idled = idle_time2 - idle_time;

    return (totald - idled) / totald * 100.0;
}
float getMemoryUsage() {
    std::ifstream file("/proc/meminfo");
    std::string line;
    float memTotal = 0, memAvailable = 0;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string key;
        float value;
        std::string unit;

        ss >> key >> value >> unit;

        if (key == "MemTotal:") memTotal = value;
        else if (key == "MemAvailable:") memAvailable = value;

        if (memTotal > 0 && memAvailable > 0) break;
    }

    float memUsed = memTotal - memAvailable;
    return (memUsed / memTotal) * 100.0;  // Porcentaje
}

int getTotalProcesses() {
    int count = 0;
    DIR* proc_dir = opendir("/proc");
    if (!proc_dir) return 0;

    struct dirent* entry;
    while ((entry = readdir(proc_dir))) {
        if (entry->d_type == DT_DIR && atoi(entry->d_name) > 0)
            count++;
    }

    closedir(proc_dir);
    return count;
}


int getRunningProcesses() {
    int running = 0;
    DIR* proc_dir = opendir("/proc");
    if (!proc_dir) return 0;

    struct dirent* entry;
    while ((entry = readdir(proc_dir))) {
        if (entry->d_type != DT_DIR) continue;

        int pid = atoi(entry->d_name);
        if (pid <= 0) continue;

        std::string stat_path = "/proc/" + std::to_string(pid) + "/stat";
        std::ifstream stat_file(stat_path);
        if (!stat_file.is_open()) continue;

        std::string line;
        getline(stat_file, line);
        char state = '\0';
        sscanf(line.c_str(), "%*d %*s %c", &state);

        if (state == 'R') running++;
    }

    closedir(proc_dir);
    return running;
}

std::string generateDynamicBar(float percentage, int width) {
    int filled = static_cast<int>(percentage * width / 100.0f);
    std::string bar;

    // Siempre mostrar al menos un bloque si el porcentaje > 0
    if (percentage > 0 && filled == 0) {
        filled = 1;
    }

    for (int i = 0; i < width; ++i) {
        if (i < filled) {
            bar += "█";
        } else {
            bar += " ";
        }
    }

    return bar;
}
