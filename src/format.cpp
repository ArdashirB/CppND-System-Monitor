#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    string formatted_time;
    int hour, min, sec, time;
    time = seconds;
    hour = time /3600;
	time = time % 3600;
	min = time/60;
	time = time %60;
	sec = time;
    formatted_time = std::to_string(hour) + ":" 
                    + std::to_string(min) +":"
                    + std::to_string(sec);
    // formatted_time = std::to_string(seconds/3600) + ":" 
    //                 + std::to_string((seconds%60)/60) +":"
    //                 + std::to_string((((seconds%60)/60))%60);
    // formatted_time = std::to_string((seconds/60)%60) + ":" 
    //                 + std::to_string(seconds%60) +":"
    //                 + std::to_string(seconds/60);
    return formatted_time;
}