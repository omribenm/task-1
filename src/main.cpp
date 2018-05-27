#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include "../include/cyberpc.h"
#include "../include/cyberdns.h"
#include "../include/cyberworm.h"
#include "../include/cyberexpert.h"

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;
//Updating daily data
void DailyRun(CyberDNS *dns,vector<CyberExpert*> exp){
	vector<string> list;
	int length=exp.size();
	int i=0;
	int Last_checked=0;
	//Update experts data
	for( i=0;i<length;i++){
		if (exp[i]->getWorkTime()>0){
			Last_checked=(exp[i])->dailyCheck(*dns ,Last_checked);
			exp[i]->setEfficiency();
			exp[i]->setWorkTime();

			if (Last_checked==-1)
				Last_checked++;
		}
		else if(exp[i]->getResTime()>0)
	 		exp[i]->setBrakeTime();

	 }

	if(length>0){
	 if (exp[i-1]->efficiency!= exp[i-1]->getEfficiency())
		 exp[i-1]->setEfficiency();
	}
	 list=dns->GetCyberPCList();
	 int size=list.size();
	 //Update all computers and their neighbors
	 for (int j=size-1 ;j>=0; j--)
	 	dns->GetCyberPC(list[j]).Run(*dns);
	 Last_checked=0;
}

int main (){
	CyberDNS *dns=new CyberDNS();
	boost::property_tree::ptree tree;
	int count_days=0;
	int end_time;
 	vector<CyberExpert*> exp;

 	//Adding the computers to network
	boost::property_tree::read_xml("./computers.xml",tree);
	BOOST_FOREACH(boost::property_tree::ptree::value_type &v,tree.get_child("")){
		CyberPC *pc=new CyberPC(v.second.get<std::string>("os"),v.second.get<std::string>("name"));
		dns->AddPC(*pc);
		cout<<"Adding to server: "<<pc->getName()<<" "<<std::endl;
		cout<<pc->getName()<<" connected to server"<<" "<<std::endl;
	};

	//Build the network
	boost::property_tree::read_xml("./network.xml",tree);
	BOOST_FOREACH(boost::property_tree::ptree::value_type &v,tree.get_child("")){

		cout<<"Connecting "<<v.second.get<std::string>("pointA")<<" to "<<v.second.get<std::string>("pointB")<<endl;
		(dns->GetCyberPC(v.second.get<std::string>("pointA"))).AddConnection(v.second.get<std::string>("pointB"));
		cout<<"    "<<v.second.get<std::string>("pointA")<<" now connected to "<<v.second.get<std::string>("pointB")<<endl;
		(dns->GetCyberPC(v.second.get<std::string>("pointB"))).AddConnection(v.second.get<std::string>("pointA"));
		(cout<<"    "<<v.second.get<std::string>("pointB"))<<" now connected to "<<v.second.get<std::string>("pointA")<<endl;
	};

	//Worms & experts are being created
	boost::property_tree::read_xml("./events.xml",tree);
	BOOST_FOREACH(boost::property_tree::ptree::value_type &v,tree.get_child("")){

			if(v.first=="hack"){
				//Update the date
				cout<<"Day : "<<count_days<<endl;
				count_days++;
				//Get worm data & create it
				string computer=v.second.get<string>("computer");
				string worm_name=v.second.get<string>("wormName");
				int worm_dormancy=v.second.get<int>("wormDormancy");
				string worm_os=v.second.get<string>("wormOs");
				CyberWorm *worm = new CyberWorm(worm_os, worm_name, worm_dormancy);
				cout<<"    "<<"Hack occurred on "<<computer<<endl;
				dns->GetCyberPC(computer).Infect(*worm);
				//Run the simulation of this day
				DailyRun(dns,exp);
				delete worm;
			}else if(v.first=="clock-in"){
				//Update the date
				cout<<"Day : "<<count_days<<endl;
				count_days++;
				//Get expert data & create it
				string name=v.second.get<string>("name");
				int work_time=v.second.get<int>("workTime");
				int rest_time=v.second.get<int>("restTime");
				int efficiency=v.second.get<int>("efficiency");
				CyberExpert *expert=new CyberExpert(name,work_time,rest_time,efficiency);
				exp.push_back(expert);
				//Print the result
				cout<<"    clocked in: "<<name<<" began working"<<endl;
				DailyRun(dns,exp);
			}else if(v.first=="termination")
				end_time=v.second.get<int>("time");

		};
		//Keep working the days remaining
		while(count_days<=end_time){
			cout<<"Day : "<<count_days<<"\n";
			DailyRun(dns,exp);
			count_days++;
		}
		//Delete experts
		for (int k=0;k<exp.size();k++)
			delete exp[k];
		delete dns;
}
