#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <vector>
#include <fstream>
using std::string;
using std::stof;
using std::stoi;
using std::to_string;
using std::vector;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    float totaltime;
    string line, key, value;
    string user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice; 
    float usertime, nicetime, systemalltime, idlealltime, iowaittime, irqtime, softirqtime,
         stealtime, guesttime, guest_nicetime, virtalltime;
    std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> user >> nice >> system >> idle >> iowait >>
                    irq >> softirq >> steal >> guest >> guest_nice) {
                if (key == "cpu") {
                    usertime = stoi(user) - stoi(guest);
                    nicetime = stoi(nice) - stoi(guest_nice);
                    idlealltime = stoi(idle) + stoi(iowait);
                    systemalltime = stoi(system) + stoi(irq) + stoi(softirq);
                    virtalltime = stoi(guest) + stoi(guest_nice);
                    totaltime = usertime + nicetime + idlealltime + systemalltime +
                                 stoi(steal) + virtalltime;
                    return totaltime;
                }
            }
        }
    }
//   return std::stoi(value);
  return totaltime; 
}