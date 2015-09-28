//Name: Nishesh Shukla
//Project: Graph.cpp
//Thanks to Jorel Akers, Guillermo Rodriguez, and Samuel Hoffman (LA) for helping me out with this lab

#include "graph.h"
using namespace std;

// default constructor at work here; pretty cute!
graph::graph()
{//already done
}	

// destructor is easy, we just clear our vertex vector and our edge map
graph::~graph()
{
	//use the clear function to remove the vectors
	vertices.clear();
	edges.clear();
}	

// add a vertex to the graph by adding it to the vector
void graph::add_vertex(const vertex& v) 
{
	vertices.push_back(v);//pushback command allows the addition to the end
}

// add an edge to the graph as long as it's under the distance limit
void graph::add_edge(vertex* v, vertex* u, double limit)
{
	double T = great_circle_distance(*v, *u);
	if( T < limit && T>0){
		edges[v].push_back(u);
		cout << "Distance for: " << v->get_city_name() << " & " << u->get_city_name() << endl; // print out
		}
	else{} // do nothing
}
// compute distance from one lat/long to another as the crow flies
double graph::great_circle_distance(const vertex& v, const vertex& u) const
{
	double PI = 3.1415926535897932;
	double lat1, lat2, long1, long2, dist;

	lat1 = ((double) v.get_latitude_degrees()) + (((double) v.get_latitude_minutes()) / 60.0);
	lat1 *= PI/180.0;
	long1 = ((double) v.get_longitude_degrees()) + (((double) v.get_longitude_minutes()) / 60.0);
	long1 *= PI/180.0;
	lat2 = ((double) u.get_latitude_degrees()) + (((double) u.get_latitude_minutes()) / 60.0);
	lat2 *= PI/180.0;
	long2 = ((double) u.get_longitude_degrees()) + (((double) u.get_longitude_minutes()) / 60.0);
	long2 *= PI/180.0;

	// from http://www.meridianworlddata.com/Distance-Calculation.asp
	// result in km
	dist = 6378.7 * acos((sin(lat1) * sin(lat2)) + (cos(lat1) * cos(lat2) * cos(long2 - long1)));

	return dist;
}
// read in 120 cities and their latitude/longitude
// cities within limit km of each other are connected by edges
void init_graph_from_file(graph& g, const string& filename, double limit)
{
	string line;
	string city_name;
	int lat1, lat2, long1, long2;
	//char compass_dir;
	ifstream file_to_read;
	string ladir;
	string lgdir;
	
	// open the data file of cities
	open_for_read(file_to_read, filename);
		while(getline(file_to_read,line)){
		//breaking each imported line into sections where information is taken from
		int Sep1 = line.find(":"); 
		int Sep2 = line.find(" ",Sep1 + 2); // adding two each time to the previous one to equal to the current one, basically (n-1)+2.
		int Sep3 = line.find(" ",Sep2 + 2);
		int Sep4 = line.find(" ",Sep3 + 2);
		int Sep5 = line.find(" ",Sep4 + 2);
		int Sep6 = line.find(" ",Sep5 + 2);
		int size1 = Sep2-(Sep1 + 2); // Sep1 ends at the semicolon; the next character is white space and the next character afte rthat is where it should start. If only one is added, it will take the whitespace after that one as well. 
		int size2 = Sep3-(Sep2 + 1);
		int size4 = Sep5-(Sep4 + 1);
		int size5 = Sep6-(Sep5 + 1);
		city_name = line.substr(0,Sep1); 
		
		lat1 = stoi(line.substr(Sep1 + 2, size1)); //same story
		lat2 = stoi(line.substr(Sep2 + 1, size2));
		long1 = stoi(line.substr(Sep4 + 1, size4));
		long2 = stoi(line.substr(Sep5 + 1, size5));
		ladir = line.substr(Sep3 + 1,1); //vector direction of latitude
		lgdir = line.substr(Sep6 + 1,1); //vector direction of longitude
		
		if (ladir == "W"){ //opposite if lattidude vector direction is west
			lat1 = -lat1;
			lat2 = -lat2;
			cout << lat1 << " "<< lat2 << endl;
		}
		if(lgdir == "S"){ //opposite if longitude vector direction is south
			long1 = -long1;
			long2 = -long2;
			cout << long1 << " " << long2 << endl;
		}
		vertex city(city_name,lat1,lat2,long1,long2); //new vertez = new city
		g.add_vertex(city);//addition of the vertex to the graph graph.
		}// end of the while statement
		
	// now we are done with our file
	file_to_read.close();
	//add the edges 
	for(unsigned int i = 0; i < g.vertices.size(); ++i){
		for(unsigned int k = 0; k < g.vertices.size(); ++k){ // start a loop through all the vertecies
			if (i != 120){	
			g.add_edge(&g.vertices[i], &g.vertices[k], limit); //create edges for them
			}
		}
	}
}
// function defined by Michael Main for input data
void open_for_read(ifstream& f, string filename)
{
	f.open(filename);
	if (f.fail())
	{
		cerr << "Could not open input file." << endl;
		exit(0);
	}
}
// function defined by Michael Main for input data
bool is_more_stuff_there(ifstream& f)
{
	return (f && (f.peek() != EOF));
}





