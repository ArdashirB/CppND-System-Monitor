#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include <unistd.h>

using std::string;
using std::stof;
using std::stoi;
using std::to_string;
using std::vector;


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    string line, key;
    float totald, idled, total, prev_total;
    float prev_idle, curr_idle;
    float prev_non_idle, curr_non_idle;
    float curr_total;
    string user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice; 

    std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> user >> nice >> system >> idle >> iowait >>
                    irq >> softirq >> steal >> guest >> guest_nice) {
                if (key == "cpu") {
                    prev_idle = stoi(idle) + stoi(iowait);
                    prev_non_idle = stoi(user) + stoi(nice)+ stoi(system) + 
                                    stoi(irq) + stoi(softirq) + stoi(steal);
                    
                }
            }
        }
    }
    usleep(100000);

    std::ifstream filestream2(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
    if (filestream2.is_open()) {
        while (std::getline(filestream2, line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> user >> nice >> system >> idle >> iowait >>
                    irq >> softirq >> steal >> guest >> guest_nice) {
                if (key == "cpu") {
                    curr_idle = stoi(idle) + stoi(iowait);
                    curr_non_idle = stoi(user) + stoi(nice)+ stoi(system) + 
                                    stoi(irq) + stoi(softirq) + stoi(steal);
                }
            }
        }
    }

    prev_total = prev_idle + prev_non_idle;
    curr_total = curr_idle + curr_non_idle;
    totald = curr_total - prev_total;
    idled = curr_idle - prev_idle;

    return (totald - idled) / totald ; 
}