#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Done: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float mem_utilization{0.0};
  float mem_total, mem_free, mem_avail, buffers;
  string key, value, line;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()){
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      while(linestream >> key >> value){
        if(key == "MemTotal:")
          mem_total = std::stof(value);
        if(key == "MemFree:")
          mem_free = std::stof(value);
        if(key == "MemAvailable:")
          mem_avail = std::stof(value);
        if(key == "Buffers:")
          buffers = std::stof(value);
      }
    }
  }
  mem_utilization = (mem_total - mem_free)/mem_total;
  return mem_utilization;
 }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string up_time1, up_time2;
  int uptime{0};
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream filestream(line);
    filestream >> up_time1 >>up_time2;
    // uptime = std::stoi(up_time1);
    long int time{stol(up_time1)};
    // time /= sysconf(_SC_CLK_TCK);
    return time;
  }
  return 0;
 }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization for a process
string LinuxParser::CpuUtilization(int pid) { 
    long up_time = LinuxParser::UpTime();
    string line, token;
    string utime, stime, cutime, cstime, starttime;
    vector<string> value;
    float total_time, seconds, cpu_usage;
    std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) 
                            + LinuxParser::kStatFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> token) {
                value.push_back(token);
            }
            utime = value[13];
            stime = value[14];
            cutime = value[15];
            cstime = value[16];
            starttime = value[21]; 
        }
    }
    total_time = stoi(utime) + stoi(stime);
    seconds = float(up_time) - (stoi(starttime) / sysconf(_SC_CLK_TCK));//up_time in long seconds
    cpu_usage = (total_time / (sysconf(_SC_CLK_TCK))/seconds);
  return to_string(cpu_usage); 
}



// Done: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  return LinuxParser::Pids().size(); 
 }



// Done: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  int running{0};
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          return std::stoi(value);
        }
      }
    }
  }
  return std::stoi(value);
 }

// Done: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
    string line;
    string key;
    string value;
    int kb;
    std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid)
                             + LinuxParser::kCmdlineFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            return line;
        }
    }    
    return string(); 
}

// Done: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line;
    string key;
    string value;
    int kb;
    std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid)
                             + LinuxParser::kStatusFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "VmSize:") {
                    kb = stoi(value);
                    return to_string(kb/1024);
                }
            }
        }
    }        
  return string("0"); 
}

// Done: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
    string line;
    string key;
    string value1, value2, value3, value4;
    std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) 
                            + LinuxParser::kStatusFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            // std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value1 >> value2 >>value3>> value4) {
                
                if (key == "Uid:") {
                    return LinuxParser::UserforUid(value1);
                    // return value1;
                }
            }
        }
    }
  return string(); 
}

string LinuxParser::UserforUid(string uid){
  string line;
    string key;
    string value1, value2, value3, value4;
    std::ifstream filestream(LinuxParser::kPasswordPath );
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value1 >> value2 >>value3>> value4) {
                if (value2 == uid) {
                    return key;
                }
            }
        }
    }
  return string();
}

// TODO: Read and return the user associated with a process
// NOT USED, created another functtion befor I saw this one
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }