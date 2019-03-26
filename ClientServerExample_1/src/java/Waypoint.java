/*
* This class is the waypoint class the defines what a waypoint is. Only need this constructor in one part of the
* java client
*/

public class Waypoint extends Object {

	private static final long serialVersionUID = 1L;
	public final static int STATUTE = 0;
	public final static int NAUTICAL = 1;
	public final static int KMETER = 2;
	public final static double radiusE = 6371;

	public double lat; // degrees lat in DD.D format (+ north, - south)
	public double lon; // degrees lon in DD.D format (+ east, - west)
	public double ele; // elevation in feet MSL
	public String name; // a name for the waypoint

	public Waypoint(String name, double lon, double lat, double ele) {
		this.lat = lat;
		this.lon = lon;
		this.ele = ele;
		this.name = name;
	}

	

	public Waypoint(String name, String lon, String lat, String ele) {
		this.lat = Double.parseDouble(lat);
		this.lon = Double.parseDouble(lon);
		this.ele = Double.parseDouble(ele);
		this.name = name;
	}

	public Waypoint(Waypoint waypoint) {
		// TODO Auto-generated constructor stub
	}

	public double getLat() {
		return lat;
	}

	public double getLon() {
		return lon;
	}

	public double getEle() {
		return ele;
	}

	public void changeLat(String lat) {
		this.lat = Integer.parseInt(lat);
	}

	public void changeLon(String lon) {
		this.lon = Integer.parseInt(lon);
	}

	public void changeEle(String ele) {
		this.ele = Integer.parseInt(ele);
	}

	public void changeName(String name) {
		this.name = name;
	}

	public String getName() {
		return this.name;
	}
}

	
