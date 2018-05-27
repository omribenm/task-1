#ifndef CYBER_EXPERT
#define CYBER_EXPERT
#include <iostream>
#include <string>
#include <vector>
#include "../include/cyberpc.h"
#include "../include/cyberexpert.h"
using namespace std;
class CyberExpert
{
private:
	const std::string cyber_expert_name_;
    const int cyber_expert_work_time_;
    const int cyber_expert_rest_time_;
    const int cyber_expert_efficiency_;
    CyberExpert(); // Prevent the use of an empty constructor
    int  break_time;
    int work_time;

public:
    CyberExpert(std::string cyber_expert_name_, int cyber_expert_work_time_, int cyber_expert_rest_time_, int cyber_expert_efficiency_);
 	void Clean(CyberPC & cyber_pc);
 	const int  getWorkTime();
 	const int  getEfficiency();
 	const int  getResTime();
 	string getName();
 	void setWorkTime();
 	void  setBrakeTime();
 	void setEfficiency();
	int dailyCheck( CyberDNS & dns,int Last_checked);
	int efficiency;
};

#endif

