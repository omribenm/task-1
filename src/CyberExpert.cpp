#include "../include/cyberexpert.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

CyberExpert::CyberExpert(std::string cyber_expert_name_, int cyber_expert_work_time_, int cyber_expert_rest_time_, int cyber_expert_efficiency_):cyber_expert_name_(cyber_expert_name_),cyber_expert_work_time_(cyber_expert_work_time_),cyber_expert_rest_time_(cyber_expert_rest_time_), cyber_expert_efficiency_(cyber_expert_efficiency_){
	work_time=cyber_expert_work_time_;
	break_time=cyber_expert_rest_time_;
	efficiency=cyber_expert_efficiency_;
}
void CyberExpert:: Clean(CyberPC & cyber_pc){
	cyber_pc.Disinfect();
}
const int  CyberExpert::getWorkTime(){
	return work_time;
}

const int  CyberExpert::getEfficiency(){
	 return cyber_expert_efficiency_;
}

const int  CyberExpert::getResTime(){
	return break_time;
}
string CyberExpert::getName(){
	return cyber_expert_name_;
}
//
int CyberExpert:: dailyCheck(CyberDNS & dns,int Last_checked){
   vector <string> pcList;
   pcList=dns.GetCyberPCList();
   int i=0;
   int length= pcList.size();
   for (i=length-1-Last_checked;i>=0 && efficiency>0;i--){
	   cout<<"    "<<cyber_expert_name_<<" examining "<<pcList[i]<<"\n";
	   Clean(dns.GetCyberPC(pcList[i]));
	   setEfficiency();
   }
  return (length-1-i);
}
void CyberExpert:: setWorkTime(){
   if (work_time>0  && cyber_expert_rest_time_!=0)
	   work_time--;
   if(work_time==0 && cyber_expert_rest_time_!=0){
	  break_time=cyber_expert_rest_time_;
	  cout<<"	"<<cyber_expert_name_<<" is taking a break"<<"\n";
   }
}
void CyberExpert:: setBrakeTime(){
   if (break_time>0)
	   break_time--;
   if (break_time==0){
	   work_time=cyber_expert_work_time_;
	   cout<<"	"<<cyber_expert_name_<<" is back to work"<<"\n";}
}
void CyberExpert::setEfficiency(){
	if (efficiency==0)
		efficiency=cyber_expert_efficiency_;
	else
		efficiency--;
}


