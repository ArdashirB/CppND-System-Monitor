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
    
    for(auto i: LinuxParser::Pids()){
        Process a(i);
        a.pid_ = i;
        a.user_ = a.User();
        a.ram_ = a.Ram();
        a.command_ = a.Command();
        a.cpu_util_ = a.CpuUtilization();
        processes_.push_back(a);
    }
    

    return processes_; 
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