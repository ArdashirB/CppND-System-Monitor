#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
#include "format.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// Done: Return the system's CPU, fix processor.cpp
Processor& System::Cpu() { 
    return cpu_; 
}




// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    vector<int> pids = LinuxParser::Pids();
    processes_.clear();
    for(auto i: pids){
        // Process a(i);
        // a.pid_ = i;
        // a.user_ = a.User();
        // a.ram_ = a.Ram();
        // a.command_ = a.Command();
        // a.cpu_util_ = a.CpuUtilization();
        // a.uptime_ = a.UpTime();
        // processes_.push_back(a);
        processes_.push_back(Process(i));
    }
    //Sort them here
    std::sort(processes_.begin(), processes_.end(), WayToSort);

    return processes_; 
}

bool System::WayToSort(Process a, Process b){
    return a<b;
    // return std::stof(a.cpu_util_)>std::stof(b.cpu_util_);
    // return a.ram_>b.ram_;
}





// Done: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// Done: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// Done: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// Done: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// Done: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
// NOT DONE***************

long int System::UpTime() { 
    return LinuxParser::UpTime();
 }