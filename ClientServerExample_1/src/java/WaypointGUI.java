import javax.swing.*;
import java.awt.*;

import java.awt.event.*;
import java.util.*;

/**
 * Copyright (c) 2018 Tim Lindquist,
 * Software Engineering,
 * Arizona State University at the Polytechnic campus
 * <p>
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation version 2
 * of the License.
 * <p>
 * This program is distributed in the hope that it will be useful,
 * but without any warranty or fitness for a particular purpose.
 * 
 * Please review the GNU General Public License at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 * see also: https://www.gnu.org/licenses/gpl-faq.html
 * so you are aware of the terms and your rights with regard to this software.
 * Or, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,USA
 * <p>
 * Purpose: Java client UI for Waypoint management.
 * This class creates Gui components for a UI to manage waypoints.
 * This software is meant to run on Ser321 development environment (and MacOS)
 * <p>
 * Ser321 Principles of Distributed Software Systems
 * @see <a href="http://pooh.poly.asu.edu/Ser321">http://pooh.poly.asu.edu/Ser321</a>
 * @see <a href="../../JavaWaypointGUI.png">JavaWaypointGUI.png</a>
 * @author Tim Lindquist (Tim.Lindquist@asu.edu) CIDSE - Software Engineering
 *                       Ira Fulton Schools of Engineering, ASU Polytechnic
 * file    WaypointGUI.java
 * date    January, 2018
 * license See above
 **/
public class WaypointGUI extends JFrame {

   /**
    * frWps is the JComboBox in the upper left of the waypoint browser.
    */
   protected JComboBox frWps;

   /**
    * toWps is the JComboBox just above the Distance and Bearing JButton
    * in the waypoint browser.
    */
   protected JComboBox toWps;

   /**
    * latIn is the JTextField labeled lat in the waypoint browser.
    */
   protected JTextField latIn;

   /**
    * lonIn is the JTextField labeled lon in the waypoint browser.
    */
   protected JTextField lonIn;

   /**
    * eleIn is the JTextField labeled ele in the waypoint browser.
    */
   protected JTextField eleIn;

   /**
    * nameIn is the JTextField labeled name in the waypoint browser.
    */
   protected JTextField nameIn;

   /**
    * distBearIn is the JTextField to the right of the Distance and Bearing
    * button in the waypoint browser. The field is for displaying the
    * distance and bearing between from and to waypoints.
    */
   protected JTextField distBearIn;

   /**
    * addrIn is the JTextArea to the right of addr label. Its for entering
    * and displaying a waypoint's address.
    */
   protected JTextArea addrIn;

   /**
    * removeWPButt is the JButton just below the to waypoint drop-down.
    * When the user clicks Remove Waypoint, the waypoint named in the 
    * nameIn JTextField should be removed from the server.
    */
   protected JButton removeWPButt;

   /**
    * addWPButt is the JButton labeled Add Waypoint.
    * When the user clicks Add Waypoint, the current values of the fields on
    * the right of the GUI are used to create and register a new waypoint
    * with the server
    */
   protected JButton addWPButt;

   /**
    * modWPButt is the JButton labeled Modify Waypoint
    * When the user clicks Modify Waypoint, the fields on the right side
    * of the GUI are used modify an existing waypoint. The name of a Waypoint
    * cannot be modified.
    */
   protected JButton modWPButt;

   /**
    * importButt is the JButton labeled Import Json Library.
    * When the user clicks this button, the app (re)initializes
    * the library from a json file.
    */
   protected JButton refreshButt;

   /**
    * exportButt is the JButton labeled Export Json Library.
    * When the user clicks this button, the app generates json file
    * of al library waypoints, thereby persisting the library to disk.
    */
   protected JButton saveButt;

   /**
    * distBearButt is the JButton bottom button.
    * When the user clicks Distance and Bearing, the direction and distance 
    * between the from waypoint and the to waypoint should be displayed
    * in the distBearIn text field.
    */
   protected JButton distBearButt;

   private JLabel latLab, lonLab, eleLab, nameLab, addrLab, fromLab, toLab;

   public WaypointGUI(String title) {
      super("Waypoint Browser for User: "+title);
      Toolkit tk = Toolkit.getDefaultToolkit();
      getContentPane().setLayout(null);
      setSize(500,350);
      frWps = new JComboBox();
      frWps.setBounds(50,10,160,25);
      getContentPane().add(frWps);
      frWps.addItem("from waypoint");
      frWps.setSelectedIndex(0);
      fromLab = new JLabel("from");
      fromLab.setBounds(10, 10, 40, 25);
      getContentPane().add(fromLab);

      toWps = new JComboBox();
      toWps.setBounds(50,45,160,25);
      getContentPane().add(toWps);
      toWps.addItem("to waypoint");
      toWps.setSelectedIndex(0);
      toLab = new JLabel("to");
      toLab.setBounds(10, 45, 40, 25);
      getContentPane().add(toLab);

      removeWPButt = new JButton("Remove Waypoint");
      removeWPButt.setBounds(20, 80, 175, 25);
      removeWPButt.setActionCommand("Remove");
      getContentPane().add(removeWPButt);

      addWPButt = new JButton("Add Waypoint");
      addWPButt.setBounds(40, 115, 135, 25);
      addWPButt.setActionCommand("Add");
      getContentPane().add(addWPButt);

      modWPButt = new JButton("Modify Waypoint");
      modWPButt.setBounds(20, 150, 155, 25);
      modWPButt.setActionCommand("Modify");
      getContentPane().add(modWPButt);

      refreshButt = new JButton("Refresh GUI");
      refreshButt.setBounds(20, 185, 180, 25);
      refreshButt.setActionCommand("Refresh");
      getContentPane().add(refreshButt);

      saveButt = new JButton("Save Library");
      saveButt.setBounds(20, 220, 180, 25);
      saveButt.setActionCommand("Save");
      getContentPane().add(saveButt);

      distBearButt = new JButton("Distance & Bearing");
      distBearButt.setBounds(20, 260, 180, 25);
      distBearButt.setActionCommand("Distance");
      getContentPane().add(distBearButt);

      latIn = new JTextField("lat");
      latIn.setBounds(250, 10, 230, 25);
      getContentPane().add(latIn);
      latLab = new JLabel("lat");
      latLab.setBounds(225, 10, 25, 25);
      getContentPane().add(latLab);

      lonIn = new JTextField("lon");
      lonIn.setBounds(250, 45, 230, 25);
      getContentPane().add(lonIn);
      lonLab = new JLabel("lon");
      lonLab.setBounds(225, 45, 25, 25);
      getContentPane().add(lonLab);

      eleIn = new JTextField("ele");
      eleIn.setBounds(250, 80, 230, 25);
      getContentPane().add(eleIn);
      eleLab = new JLabel("ele");
      eleLab.setBounds(225, 80, 25, 25);
      getContentPane().add(eleLab);

      nameIn = new JTextField("name");
      nameIn.setBounds(250, 115, 230, 25);
      getContentPane().add(nameIn);
      nameLab = new JLabel("name");
      nameLab.setBounds(200, 115, 45, 25);
      getContentPane().add(nameLab);

      addrIn = new JTextArea("addr");
      addrIn.setBounds(250, 150, 230, 70);
      getContentPane().add(addrIn);
      addrLab = new JLabel("addr");
      addrLab.setBounds(210, 150, 35, 25);
      getContentPane().add(addrLab);

      distBearIn = new JTextField("dist/bearing");
      distBearIn.setBounds(225, 260, 255, 25);
      getContentPane().add(distBearIn);

      setVisible(true);
   }
}


