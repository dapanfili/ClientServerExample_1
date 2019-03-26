import java.io.*;
import java.util.*;
import java.net.URL;

import org.json.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

import java.text.DecimalFormat;

/**
 * Copyright (c) 2015 Tim Lindquist,
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
 * Purpose:
 * A Java class and main method demonstrating an approach to calling
 * JsonRpc methods.
 *
 * This software is meant to run on Debian Wheezy Linux
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist (Tim.Lindquist@asu.edu) CIDSE - Software Engineering,
 *                       IAFSE, ASU at the Polytechnic campus
 * @date    July, 2015
 * 
 * 
 *  @author Danielle Panfili dpanfili@asu.edu
 *         Software Engineering, CIDSE, IAFSE, ASU Poly
 * @version January 2018
 **/
 
 //Java client
public class WaypointJavaClient extends WaypointGUI implements ActionListener, ItemListener 
{
   private static final boolean debugOn = true;
   public String serviceURL;
   public JsonRpcRequestViaHttp server;
   public static int id = 0;
   String selectedWayPoint;
 
   //Set up constructor to take the server url
   public WaypointJavaClient (String serviceURL) {
      
      //Set button action listeners
      super("dpanfili");
      removeWPButt.addActionListener(this);
      addWPButt.addActionListener(this);
      modWPButt.addActionListener(this);
      refreshButt.addActionListener(this);
      saveButt.addActionListener(this);
      distBearButt.addActionListener(this);
      frWps.addItemListener(this);
      toWps.addItemListener(this);
      //initialize gui
      refreshGui();
    
     //Set up serviceURL
     this.serviceURL = serviceURL;
		try 
		{
		    //Connect to server
			this.server = new JsonRpcRequestViaHttp(new URL(serviceURL));
			refreshGui();
			System.out.println();
		} 
		catch (Exception ex) 
		{
			System.out.println("Malformed URL " + ex.getMessage());
		}
    
     //Set up listener for exit
	 this.addWindowListener(new WindowAdapter() {
		 @Override
		 public void windowClosing(WindowEvent e) {
		    debug("you clicked X");
		    System.exit(0);
		 }
	      });
	      setVisible(true);
	}

   //This is how we get our functions to pass items to the server and return what we need
   //Getting JSONObject here that we can manipulate when needed
   private JSONObject callServer(String method, String params){
       //Create Json object for getting server string
      JSONObject jsonObj = new JSONObject();
      jsonObj.put("jsonrpc","2.0");
      jsonObj.put("method",method);
      jsonObj.put("id",++id);
      String almost = jsonObj.toString();
      String toInsert = ",\"params\":[" + params+"]";
      String begin = almost.substring(0,almost.length()-1);
      String end = almost.substring(almost.length()-1);
      String ret = begin + toInsert + end;
      String str = "";
      
      //get a string server call
      try{
        str = server.call(ret);
        }catch(Exception e){}
    //Turn string server call into JSON object    
    InputStream in = new ByteArrayInputStream(str.getBytes());
    JSONObject jObj = new JSONObject(new JSONTokener(in));
    return jObj;
    }
    
    
    //Remove Waypoint server call function
   public void removeWaypoint(String name){
       //for testing
	System.out.println("Name is: "+name);
    callServer("removeWaypoint","\""+name+"\"");
	//System.out.println("Remove" + temp.toString());
	try{
        saveJsonFile();
	    refreshGui();
	}catch (Exception e){System.out.println("Exception");}
}

    //Dist and bear server call function
   public String calcDistAndBear(String name1, String name2){
       //get json object here so we can get the result string later 
         JSONObject jObj = callServer("calcDistAndBear","\""+frWps.getSelectedItem().toString()+"\",\""+toWps.getSelectedItem().toString()+"\"");
      return jObj.getString("result");
   }

    //Get waypoint server call.
    //This is where we use the Waypoint so that when itemStateChange we can use the Waypoint object
   public Waypoint getWaypoint(String name){
       //Create waypoint object
	Waypoint way = new Waypoint("name",0.0,0.0,0.0);
    try{
        //Call server
		JSONObject jObj = callServer("getWaypoint","\"" + name + "\"");
		//Get result as json object
		JSONObject res = jObj.getJSONObject("result");
		System.out.println(res.toString());
		//How we can get the object
		JSONObject jsonWP = res.getJSONObject(name);
		//Get the items inside
		way.name = jsonWP.getString("name");
		way.lat = jsonWP.getDouble("lat");
		way.lon = jsonWP.getDouble("lon");
		way.ele = jsonWP.getDouble("ele");
	}catch(Exception e){System.out.println(e+ "Exception");}
	return way;
}

    //Get list is a vector for updating the gui
   public Vector<String> getList(){
	Vector<String> list = new Vector<String>();
    try{
		JSONObject jo = callServer("getList","[]");
        JSONArray res = jo.getJSONArray("result");
			for(int i = 0; i< res.length(); i++){
				list.add(res.getString(i));
            }
	}catch(Exception ex){
         System.out.println("exception in rpc call to getList: "+ex.getMessage());}	
	return list;
}
//Save JSON file 
   public void saveJsonFile(){
       //call server
    JSONObject jObj = callServer("saveLibrary","");
   }

   /**
    * Get the service information.
    * @return The service information
    */
   public String serviceInfo(){
      return "Service information";
   }

//Debug method
   private void debug(String message) {
      if (debugOn)
         System.out.println("debug: "+message);
   }

   //State Change
 public void itemStateChanged(ItemEvent event) {
       try {
           
       if (event.getStateChange() == ItemEvent.SELECTED) {
         Object comp = event.getSource();
         //Debug that allows you to see which waypoint is selected.
         debug("Selection event generated by " +
                 ((comp == frWps) ? "from " : "to ") + "combobox. " +
                 "Selected waypoint is: " + (String) event.getItem());
         String To = "to waypoint";
         String From = "from waypoint";
         String currentSelection;
         if (comp == frWps) {
            currentSelection = frWps.getSelectedItem().toString();
         } else {
            currentSelection = toWps.getSelectedItem().toString();
         }
         //Set the to and from waypoints to null
         if ((currentSelection == "from waypoint") || (currentSelection == "to waypoint")) {
            latIn.setText("null");
            lonIn.setText("null");
            eleIn.setText("null");
            nameIn.setText("null");
            addrIn.setText("null");
         } else {
            try {
              //Get all the necessary values in 
		String wpName = (String)event.getItem();
		//Call getWaypoint here so we can get the waypoint we are selected on
		Waypoint w = getWaypoint(wpName);
               //System.out.println("Description Changed: "+server.get(currentSelection));
           latIn.setText(Double.toString(w.lat));
	       lonIn.setText(Double.toString(w.lon));
	       eleIn.setText(Double.toString(w.ele));
	       nameIn.setText(w.name);
	       //Set selectedWaypoint to use later on
	       selectedWayPoint = wpName;
	    } catch (Exception e) {
               System.out.println("Error retrieving name from server.");
            }
         }
      }
       } catch (Exception e) {
           e.printStackTrace();
       }
 }
 
 //ActionPerformed
   public void actionPerformed(ActionEvent e) {


      try{
       //Remove 
      if(e.getActionCommand().equals("Remove")) {
         debug("you clicked Remove Waypoint");
         //Call remove waypoint and pass in a selected Waypoint
         removeWaypoint(selectedWayPoint);
	  
	  //Add
      }else if(e.getActionCommand().equals("Add")) {
         debug("you clicked Add Waypoint");
         //Set server string call 
         String str = latIn.getText()+","+lonIn.getText()+","+eleIn.getText()+",\""+nameIn.getText()+"\"";
         //Can call server here rather than a method
	     callServer("addWaypoint",str);
	     //refresh GUI
        try{refreshGui();}catch(Exception ex){};
        
        //Modify
      }else if(e.getActionCommand().equals("Modify")) {
          //Same as add, set server string
         String str = latIn.getText()+","+lonIn.getText()+","+eleIn.getText()+",\""+nameIn.getText()+"\"";
         //Call server
	    callServer("modifyWaypoint",str);
        try{refreshGui();}catch(Exception ex){};
        
        
        //Refresh GUI
      }else if(e.getActionCommand().equals("Refresh GUI")) {
        debug("you clicked Import Json Library");
        refreshGui(); 
        
        //Save Library
      }else if(e.getActionCommand().equals("Save")) {
         debug("you clicked Export Json Library");
         saveJsonFile();
         
         //Get Dist and Bear
      }else if(e.getActionCommand().equals("Distance")) {
         debug("you clicked Distance and Bearing");
         distBearIn.setText(calcDistAndBear(frWps.getSelectedItem().toString(), toWps.getSelectedItem().toString()));
         
      }

      } catch (Exception ex) {
         System.out.println("Could not connect.");
      }

   }
	
//Takes string and turns into json object
public JSONObject stringObj(String str){
	InputStream in = new ByteArrayInputStream(str.getBytes());
	JSONObject jObj = new JSONObject( new JSONTokener(in));
	return jObj;
}


//Function to refresh the GUI with the new library
private void refreshGui() {
    frWps.removeAllItems();
    toWps.removeAllItems();
    //Call server to get list 
        Vector<String> lst = getList();
    	for (int i = 0; i<lst.size(); i++){
    		frWps.addItem(lst.get(i));
    		toWps.addItem(lst.get(i));
    	}

}

   


public static void main(String args[]) {
        try 
        {
        	String url = "http://192.168.2.2:8080/";
        
        	if (args.length > 1) 
        	{
        		url = "http://" + args[0] + ":" + args[1] + "/";
        	}
        
        	WaypointJavaClient wjc = new WaypointJavaClient(url);
        	
        } 
        catch (Exception e) 
        {
        	e.printStackTrace();
        	System.out.println("Oops, you didn't enter the right stuff");
        }
    }
}

