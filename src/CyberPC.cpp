#include "../include/cyberpc.h"
#include <iostream>
#include <string>

using namespace std;

CyberPC::CyberPC(std::string cyber_pc_os, std::string cyber_pc_name):cyber_pc_os_(cyber_pc_os),cyber_pc_name_(cyber_pc_name){
	cyber_pc_time_to_infect_=-1;
}

void CyberPC::AddConnection(std::string  second_pc){

    cyber_pc_connections_.push_back(second_pc);

}
void CyberPC::Infect(CyberWorm & worm){
	if(cyber_pc_os_==worm.getOs()){
		delete cyber_worm_;
		cyber_pc_time_to_infect_=worm.getTime();
		cyber_worm_= new CyberWorm(worm);
		cout<<" 	"<<cyber_pc_name_<< " infected by "<<worm.getName()<<endl;
	}
	else
		cout<<"        "<<"Worm "<<worm.getName()<< " is incompatible with "<<cyber_pc_name_<<endl;
}

void CyberPC:: Run(const CyberDNS & server){
	if(cyber_worm_!= NULL){
		if(cyber_pc_time_to_infect_==0){
			cout<<"    "<< cyber_pc_name_ << " infecting..." <<endl;
		    int length=cyber_pc_connections_.size();
			for(int i=0;i<length;i++){
				server.GetCyberPC(cyber_pc_connections_[i]).Infect(*cyber_worm_);
				//if(server.GetCyberPC(cyber_pc_connections_[i]).getOs()==cyber_worm_->getOs())
				//	cout<<" 	"<< server.GetCyberPC(cyber_pc_connections_[i]).getName() << " infected by "<<cyber_worm_->getName()<<endl;
			//	else
			//cout<<"        "<<"Worm "<<cyber_worm_->getName()<< " is incompatible with "<<server.GetCyberPC(cyber_pc_connections_[i]).getName()<<endl;
			}
		}
		else{
			cout<<"    "<<cyber_pc_name_<< ": Worm "<< (*cyber_worm_).getName()<<" is dormant"<<endl;
			cyber_pc_time_to_infect_--;
		}
    }
}

void CyberPC::Disinfect(){
	if (cyber_worm_!=NULL){
	string s=cyber_worm_->getName();
	delete cyber_worm_;
	cyber_worm_= NULL;
	cout<<"        "<<"Worm "<<s<<" successfully removed from "<< getName()<<endl;}

}

const std::string CyberPC::getName(){
	return  cyber_pc_name_;
}
const std::string CyberPC::getOs(){
	return  cyber_pc_os_;
}

CyberPC::~ CyberPC(){

   delete cyber_worm_;
 }

