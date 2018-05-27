#include "../include/cyberdns.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

CyberDNS::CyberDNS(){}

void CyberDNS::AddPC(CyberPC & cyber_pc_){

cyber_DNS_.insert(std::pair<const string, CyberPC&>(cyber_pc_.getName(),cyber_pc_));
}

CyberPC& CyberDNS::GetCyberPC( const std::string & cyber_pc_name) const{
	std::map<const std::string, CyberPC &>::const_iterator it=cyber_DNS_.find(cyber_pc_name);
	return (it->second);
}

vector <std::string> CyberDNS:: GetCyberPCList(){
std::map<const std::string, CyberPC &>::iterator it;
vector<string> a;
	for (it=cyber_DNS_.begin(); it!=cyber_DNS_.end(); it++){
		a.push_back(it->first);
	}
	return a;
}
CyberDNS::~CyberDNS(){
	std::map<const std::string, CyberPC &>::iterator it;
		for (it=cyber_DNS_.begin(); it!=cyber_DNS_.end(); it++)
			 delete&(it->second);


}
