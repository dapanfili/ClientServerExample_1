#include <jsonrpccpp/server.h>
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Waypoint.hpp"
#include "waypointserverstub.h"

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include <vector>
#include <fstream>
#include <math.h>


/**
*  Copyright 2018 Danielle Panfili
*  
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*  
*  http://www.apache.org/license/LICENSE-2.0
*
*  Unless required by applicalbe law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*  Full permissions given to ASU for the download, transfer, copying
*  and use in my evaluation in this course SER 321.
*
*  Purpose: Json Remote Procedure Call in C++
*
*  Ser321 Priciples of Distributed Software Sytems
*  see http://pooh.poly.asu.edu/Ser321
*  @author 
*  	   Software Engineering Student
*  @version
* 
*  @author Danielle Panfili dpanfili@asu.edu
 *         Software Engineering, CIDSE, IAFSE, ASU Poly
 * @version January 2018
*/ 

using namespace jsonrpc;
using namespace std;



class WaypointServer : public waypointserverstub {
	public:
    vector<Waypoints> waypointVec;
	Json::Value::Members WayPointList;
		WaypointServer(AbstractServerConnector &connector, int port);
		//Virtual functions
  		virtual void notifyServer();
  		virtual std::string serviceInfo();
		virtual bool addWaypoint(double lat, double lon, double ele, const std::string& name);
        virtual bool removeWaypoint(const std::string& name);
		virtual void removeAllVec();
        virtual bool modifyWaypoint(double lat, double lon, double ele, const std::string& name);
        virtual void saveJsonFile(const std::string& jsonFileName);
        virtual std::string calcDistAndBear(const std::string& name1, const std::string& name2);
		virtual Json::Value getWaypoint(const std::string& name);
  		virtual Json::Value getList();
    int portNum;

    //Remove From Vector used in the remove process
    void removeFromVector(string selected){
      for (int i = 0; i < waypointVec.size(); i++){
        if(!selected.compare(waypointVec[i].name))
          waypointVec.erase(waypointVec.begin() + i);
      }
   }

    //Import library initially
    void importJson(){
        for (int i = 0; i < waypointVec.size(); i++){
            removeFromVector(waypointVec[i].name);   
        }
        Json::Value jsonLibRoot;
        Json::Reader reader;
        ifstream inFile("waypoints.json", ifstream::binary);
        reader.parse(inFile, jsonLibRoot);
        WayPointList = jsonLibRoot.getMemberNames();

        for (int i = 0; i < WayPointList.size(); i++){
                Json::Value wp = jsonLibRoot.get(WayPointList[i],"NULL");
                string name = WayPointList[i];

                double lat = wp.get("lat", "0").asDouble();
                double lon = wp.get("lon", "0").asDouble();
                double ele = wp.get("ele", "0").asDouble();

              waypointVec.push_back(*(new Waypoints(lat,lon,ele,name.c_str())));
        }
   }

     //convert degrees to radians
    double toRadians(double deg){
      return deg * 3.141592653589793 / 180.0;
    }
    
    //convert radians to degrees
    double toDegrees(double rad){
      return rad * 180.0 / 3.141592653589793;
    }


        
};

//Server Functions

WaypointServer::WaypointServer(AbstractServerConnector &connector, int port) : waypointserverstub(connector){
    portNum = port;
    cout << "server up and listening on port " << port << endl;
}

void WaypointServer::notifyServer(){
    cout << "Media server notified" << endl;
}

string WaypointServer::serviceInfo(){
    std::string msg = "Media Library";
  stringstream ss;
  ss << portNum;
    return  msg.append(ss.str());
}

//Initally had as void but then the java client would not work. Found that making a bool allowed the server to interact and add the waypoint
bool WaypointServer::addWaypoint(double lat, double lon, double ele, const std::string& name) {
  waypointVec.push_back(*(new Waypoints(lat,lon,ele,name.c_str())));
  return true;
  }
//Here but not used
void WaypointServer::removeAllVec(){
   for (int i = 0; i < waypointVec.size(); i++){
            waypointVec.erase(waypointVec.begin() + i);
        } 
   importJson();
}

///Initally had as void but then the java client would not work. Found that making a bool allowed the server to interact and remove the waypoint
bool WaypointServer::removeWaypoint(const std::string& name) {
    removeFromVector(name);
    return true;
}
//Having this as a void works because it is just saving the file and not doing anything differnt.
void WaypointServer::saveJsonFile(const std::string& jsonFileName) {
  Json::Value jsonUser;
   Json::StyledStreamWriter ssw("  ");
   std::ofstream jsonOutFile(jsonFileName.c_str(), std::ofstream::binary);
   for(int i=0;i<waypointVec.size(); i++){
      Waypoints wps = waypointVec[i];
      jsonUser[wps.name]["lat"] = wps.lat;
      jsonUser[wps.name]["lon"] = wps.lon;
      jsonUser[wps.name]["ele"] = wps.ele;
      jsonUser[wps.name]["name"] = wps.name;

   }
   ssw.write(jsonOutFile, jsonUser);
 

}
//Initally had as void but then the java client would not work. Found that making a bool allowed the server to interact and modify the waypoint
bool WaypointServer::modifyWaypoint(double lat, double lon, double ele, const std::string& name) {
    int index = 0;
  for (int i = 0; i < waypointVec.size(); i++){
          if(!name.compare(waypointVec[i].name))
            index = i;
        }
  waypointVec[index].lat = lat;
  waypointVec[index].lon = lon;
  waypointVec[index].ele = ele;
  return true;
}

//Calculates the dist and bear by taking in 2 strings of the waypoint names. 
std::string WaypointServer::calcDistAndBear(const std::string& name1, const std::string& name2){
   	
	int fromIndex = 0;
	int toIndex = 0;
	//waypoint indexes set
	for (int i = 0; i < waypointVec.size(); i++){
	      	if(!name1.compare(waypointVec[i].name))
	      		fromIndex = i;
		if(!name2.compare(waypointVec[i].name))
	      		toIndex = i;
        }
        
    //Calculations here
	double r = 6371;
   	double phi1 = toRadians(waypointVec[fromIndex].lat);
	double phi2 = toRadians(waypointVec[toIndex].lat);
	double lambda1 = toRadians(waypointVec[fromIndex].lon);
	double lambda2 = toRadians(waypointVec[toIndex].lon);
	double deltaPhi = phi2 - phi1;
	double deltaLambda = lambda1 - lambda2;
	double answer = sin(deltaPhi/2.0)*sin(deltaPhi/2) + cos(phi1)*cos(phi1) * sin(deltaLambda/2.0) * sin(deltaLambda/2.0);
	double c = 2 * atan2(sqrt(answer),sqrt(1-answer));
	double dist = r*c;
	double y = sin(lambda2-lambda1) * cos(phi2);
	double x = cos(phi1) * sin(phi2) - sin(phi1)*cos(phi2)*cos(lambda2-lambda1);
	double bear = fmod(((atan2(y, x)*180/3.141592) + 360), 360);
	char s[100];
	sprintf(s,"Dist: %.4f Bear: %.4f",dist,bear);
	//return the string value of the dist and bear for importing into the txt field
	return s;
}
//Get a list of the waypoints by name
Json::Value WaypointServer::getList() {
   	Json::Value ret(Json::arrayValue);
	for (int i = 0; i < waypointVec.size(); i++){
	      	ret.append(waypointVec[i].name);
        }
	return ret;
}

//Get a specific waypoint information 
Json::Value WaypointServer::getWaypoint(const std::string& name) {
	int index = 0;
	for (int i = 0; i < waypointVec.size(); i++){
	      	if(!name.compare(waypointVec[i].name))
	      		index = i;
        }
	Json::Value wp;
	//root["node"]["name"] = name1;
	wp[waypointVec[index].name]["name"] = waypointVec[index].name;
	wp[waypointVec[index].name]["lat"] = waypointVec[index].lat;
	wp[waypointVec[index].name]["lon"] = waypointVec[index].lon;
	wp[waypointVec[index].name]["ele"] = waypointVec[index].ele;	
	return wp;
}


//Main Function
int main(int argc, char * argv[]) {   
 int port = 8080;
   	if(argc > 1){
      		port = atoi(argv[1]);
   	}
   	HttpServer httpserver(port);
   	WaypointServer ws(httpserver, port);
	ws.importJson();
   	ws.StartListening();
   	int c = getchar();
   	ws.StopListening();
   	return 0;
}		




