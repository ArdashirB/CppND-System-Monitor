#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
using std::ifstream;


Process::Process(int pid) : pid_(pid) {
    // Process a(i);
    // pid_ = i;
    user_ = User();
    ram_ = Ram();
    command_ = Command();
    cpu_util_ = CpuUtilization();
    uptime_ = UpTime();
};

// TODO: Return this process's ID
int Process::Pid() { 
    return pid_; 
}

// TODO: Return this process's CPU utilization
string Process::CpuUtilization() { 
    return LinuxParser::CpuUtilization(Pid()); 
}

// TODO: Return the command that generated this process
string Process::Command() { 
    return LinuxParser::Command(Pid());
}

// TODO: Return this process's memory utilization
string Process::Ram() {
    return LinuxParser::Ram(Pid()); 
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
    return LinuxParser::Uid(Pid()); 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    return LinuxParser::UpTime(Pid());
    }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const &a) const { 
    // Why doesnt the line below work??
    // return stol(LinuxParser::CpuUtilization(pid_)) < stol(LinuxParser::CpuUtilization(a.pid_));
    return stol(LinuxParser::Ram(pid_)) > stol(LinuxParser::Ram(a.pid_));
}