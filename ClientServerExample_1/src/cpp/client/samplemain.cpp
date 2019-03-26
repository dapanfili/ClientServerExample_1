#include "WaypointGUI.cpp"
#include <cmath>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Multiline_Input.H>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <json/json.h>
#include <jsonrpccpp/server.h>
#include "waypointclientstub.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
using namespace std;
using namespace jsonrpc;



/**
 * Copyright (c) 2014 Tim Lindquist,
 * Software Engineering,
 * Arizona State University at the Polytechnic campus
 * <p/>
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation version 2
 * of the License.
 * <p/>
 * This program is distributed in the hope that it will be useful,
 * but without any warranty or fitness for a particular purpose.
 * <p/>
 * Please review the GNU General Public License at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 * see also: https://www.gnu.org/licenses/gpl-faq.html
 * so you are aware of the terms and your rights with regard to this software.
 * Or, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,USA
 * <p/>
 * Purpose: C++ FLTK client UI for Waypoint management.
 * This class extends the Gui component class WaypointGUI and demonstrates
 * sample control functions that respond to button clicks drop-down selects.
 * This software is meant to run on OSX, and Windows Cygwin using g++.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Cst420
 * @author Tim Lindquist (Tim.Lindquist@asu.edu) CIDSE - Software Engineering,
 *                       IAFSE, ASU at the Polytechnic campus
 * @file    samplemain.cpp
 * @date    September, 2014
 * 
 * 
 * 
 * 
/*
 * @author Danielle Panfili dpanfili@asu.edu
 *         Software Engineering, CIDSE, IAFSE, ASU Poly
 * @version January 2018 
 
 */





using namespace std;
using namespace jsonrpc;


class SampleStudentClient : public WaypointGUI {
    //Global Variables
    Json::Value::Members WayPointList;
    static constexpr double pi = 3.14159265;
    
    /** ClickedX is one of the callbacks for GUI controls.
    * Callbacks need to be static functions. But, static functions
    * cannot directly access instance data. This program uses "userdata"
    * to get around that by passing the instance to the callback
    * function. The callback then accesses whatever GUI control object
    * that it needs for implementing its functionality.
    */

   static void ClickedX(Fl_Widget * w, void * userdata) {
      std::cout << "You clicked Exit" << std::endl;
      exit(1);
   }

   static void ClickedRemoveWP(Fl_Widget * w, void * userdata) {

      
      SampleStudentClient* anInstance = (SampleStudentClient*)userdata;
      Fl_Input_Choice * frWps = anInstance->frWps;
      std::string selected(frWps->value());
      Fl_Input * theName = anInstance->nameIn;
      Json::Value way = anInstance->ws->getWaypoint(selected)[selected];
      std::string nameOfObj(theName->value());
      //call ws here to actually remove wayoint using the server
      //basically a server call
      anInstance->ws->removeWaypoint(nameOfObj);
      //call server to save the file
      anInstance->ws->saveJsonFile("waypoints.json");
      for (int i=0; i < frWps->menubutton()->size(); i++ ) {
         const Fl_Menu_Item &item = frWps->menubutton()->menu()[i];
         if(!selected.compare(item.label())){  // if they are equal
            frWps->menubutton()->remove(i);
            cout << "removed " << selected << endl;
            break;
         }
      }
      if(frWps->menubutton()->size()>0){
         frWps->value(frWps->menubutton()->menu()[0].label());
      }else{
         frWps->value("");
      }
      //refresh gui re initalizes the drop downs with the new value
	anInstance->removeAllFromGui();
    anInstance->refresh();

  }

   static void ClickedAddWP(Fl_Widget * w, void * userdata) {
    
      SampleStudentClient* anInstance = (SampleStudentClient*)userdata;
      Fl_Input_Choice * fromWPChoice = anInstance->frWps;
      Fl_Input_Choice * toWPChoice = anInstance->toWps;
      Fl_Input * theLat = anInstance->latIn;
      Fl_Input * theLon = anInstance->lonIn;
      Fl_Input * theEle = anInstance->eleIn;
      Fl_Input * theName = anInstance->nameIn;
      std::string lat(theLat->value());
      // what follows is not expedient, but shows how to convert to/from
      // double and formatted C and C++ strings.
      double latNum = atof(lat.c_str()); //convert from string to double
      char latFormat[10];
      sprintf(latFormat,"%4.4f",latNum);  //format the double into a C string
      std::string latCppStr(latFormat);   //convert formatted C str to C++ str
      std::string lon(theLon->value());
      std::string ele(theEle->value());
      double lonNum = atof(lon.c_str()); 
      double eleNum = atof(ele.c_str()); 
      std::string name(theName->value());
      std::cout << "You clicked the add waypoint button lat: "<< latCppStr
                << " lon: " << lon << " ele: " << ele << " name: "
                << name << std::endl;
      fromWPChoice->add(name.c_str());
      toWPChoice->add(name.c_str());
      fromWPChoice->value(name.c_str());
      //Server call here 
      //Drop down updated
      anInstance->ws->addWaypoint(latNum,lonNum,eleNum,name.c_str());
   } 
   static void ModifyWP(Fl_Widget * w, void * userdata){
    
      SampleStudentClient* anInstance = (SampleStudentClient*)userdata;
      Fl_Input_Choice * fromWPChoice = anInstance->frWps;
      Fl_Input_Choice * toWPChoice = anInstance->toWps;
      
      Fl_Input * theLat = anInstance->latIn;
      Fl_Input * theLon = anInstance->lonIn;
      Fl_Input * theEle = anInstance->eleIn;
      Fl_Input * theName = anInstance->nameIn;
      std::string lat(theLat->value());
      // what follows is not expedient, but shows how to convert to/from
      // double and formatted C and C++ strings.
      double latNum = atof(lat.c_str()); //convert from string to double
      char latFormat[10];
      sprintf(latFormat,"%4.4f",latNum);  //format the double into a C string
      std::string latCppStr(latFormat);   //convert formatted C str to C++ str
      std::string lon(theLon->value());
      std::string ele(theEle->value());
      double lonNum = atof(lon.c_str()); 
      double eleNum = atof(ele.c_str()); 
      std::string name(theName->value());

      //Server calls
      anInstance->ws->modifyWaypoint(latNum,lonNum,eleNum,name.c_str());
      anInstance->ws->saveJsonFile("waypoints.json");
      fromWPChoice->clear();
      //refresh gui with new values
      anInstance->removeAllFromGui();
      anInstance->refresh();
   }
   
   static void ClickedDistBear(Fl_Widget * w, void * userdata){
     
      SampleStudentClient* anInstance = (SampleStudentClient*)userdata;
      Fl_Input_Choice * frWps = anInstance->frWps;
      Fl_Input_Choice * toWps = anInstance-> toWps;
      Fl_Input * theLat = anInstance->latIn;
      Fl_Input * theLon = anInstance->lonIn;
      Fl_Input * theEle = anInstance->eleIn;
      Fl_Input * theName = anInstance->nameIn;
      std::string selected(frWps->value());
      std::string selectedTo(toWps->value());

      
      
      string distbear(anInstance->ws->calcDistAndBear(selected,selectedTo));
      //Server call to get dist and bear info into the text value box
       anInstance->distBearIn->value(distbear.c_str());
       
   }
   static void SelectedFromWP(Fl_Widget * w, void * userdata) {
    
      SampleStudentClient* anInstance = (SampleStudentClient*)userdata;
      Fl_Input_Choice * frWps = anInstance->frWps;
      Fl_Input_Choice * toWps = anInstance-> toWps;
      std::string selected(frWps->value());
      std::string selectedTo(toWps->value());
      std::cout << "You selected from waypoint "
                << selected
              <<"To: "<< selectedTo
                << std::endl;
        //Server call to get Waypoint
       	Json::Value ret = anInstance->ws->getWaypoint(selected)[selected];
        //Updates txt boxes at the right
        anInstance->latIn->value(ret["lat"].asString().c_str());
        anInstance->lonIn->value(ret["lon"].asString().c_str());
        anInstance->eleIn->value(ret["ele"].asString().c_str());
        anInstance->nameIn->value(ret["name"].asString().c_str());
   }

   static void SelectedToWP(Fl_Widget * w, void * userdata){
	SampleStudentClient* anInstance = (SampleStudentClient*)userdata;
	Fl_Input_Choice * toWps = anInstance-> toWps;
	std::string selected(toWps->value());
	//Server call to get Waypoint
	Json::Value ret = anInstance->ws->getWaypoint(selected)[selected];
	anInstance->latIn->value(ret["lat"].asString().c_str());
        anInstance->lonIn->value(ret["lon"].asString().c_str());
        anInstance->eleIn->value(ret["ele"].asString().c_str());
        anInstance->nameIn->value(ret["name"].asString().c_str());
  }
   static void ClickedExport(Fl_Widget * w, void * userdata){
    
       SampleStudentClient* anInstance = (SampleStudentClient*)userdata;
       //Server call
       anInstance-> ws->saveJsonFile("waypoints.json");
       cout<< "You clicked Export!";
   }
   
static void ClickedRefresh(Fl_Widget * w, void * userdata){
     
       SampleStudentClient* anInstance = (SampleStudentClient*)userdata;
        cout<< "You clicked Refresh!";
        //calls functions below to refresh
       anInstance->removeAllFromGui();
       anInstance->refresh();
       cout<< "You clicked Refresh!";
   
   }
   
public:
  //Create pointer to the stub
      waypointclientstub * ws;
      SampleStudentClient(const char * name = 0, waypointclientstub* ws = NULL) : WaypointGUI(name) {
    //Set stub
      this->ws = ws;
      refresh();
      removeWPButt->callback(ClickedRemoveWP, (void*)this);
      addWPButt->callback(ClickedAddWP, (void*)this);
      frWps->callback(SelectedFromWP, (void*)this);
      saveButt->callback(ClickedExport, (void*)this);
      modWPButt->callback(ModifyWP, (void*)this);
      distBearButt->callback(ClickedDistBear, (void*)this);
      refreshButt->callback(ClickedRefresh, (void*)this);
      callback(ClickedX);
      
   }

//Other functions that do not interact with server

void refresh(){
	//Call to get the full list of waypoints
	Json::Value wayList = ws->getList();
    cout<<wayList.size();
	for(int i = 0; i< wayList.size(); i++){
		string str = wayList[i].asString();
        cout<< str;
        //Add to the drop downs
		frWps->add(str.c_str());
		toWps->add(str.c_str());
		}
	}

//Clear the gui - doesn't get used.
 void removeFromGui(){
   frWps->clear();
   toWps->clear();
}
//Loop through list and clear for each name
void removeAllFromGui(){
    Json::Value wayList = ws->getList();
    for(int i = 0; i< wayList.size(); i++){
        frWps->clear();
        toWps->clear();
        }
}

//End class
};
//run client
int main(int argc, char*argv[]) {

	string host = "http://127.0.0.1:8080";
   	if(argc>1){
      	host = "http://"+ string(argv[1])+":"+string(argv[2]);
   }
	
	cout<<"host is: "<<host<<endl;
	HttpClient httpclient(host);
	waypointclientstub sc = waypointclientstub(httpclient);
	cout<< "Connecting to host "<<host<<endl;
	SampleStudentClient cm("Danielle Panfili Waypoint Browser", &sc);
   	return (Fl::run());
}

