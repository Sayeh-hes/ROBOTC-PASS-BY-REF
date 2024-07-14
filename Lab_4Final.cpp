#include<iostream>
#include<cmath>
#include<fstream>
#include<cmath>
#include<iomanip>

using namespace std;

int main()
{

int stopnum = 0;
bool heavyload = 0;
double xprev = 0;
double yprev = 0;
double x = 0;
double y = 0;
double deltax = 0;
double deltay = 0;
double newdist = 0;
double totdist =0, max_dist = -1e12, min_dist = 1e12;
double totcost = 0;
double tripcost = 0, max_price = -1e12, min_price = 1e12;
const double flatfee = 18;
int tripnum = 0;
double totdistorigin=0;
double totdistall = 0;
double totcostall = 0;



ifstream fin("taxi1.txt");

	if(!fin)
	{
		cout << "Unable to open file";
		system ("PAUSE");
		return (EXIT_FAILURE);
	}

	ofstream fout("report.txt");
	
	fout << fixed << setprecision(2);
		
	fout << "trip#" << setw(9) << "stops" << setw(8) << "over" << setw(12) 
		<< "tripDist" << setw(12) << "tripCost" << setw(13) << "totalDist" << 
		setw(13) << "totalCost" <<endl;
		
  

	while (fin >> stopnum >> heavyload)
	{
		
	tripnum++;
	 
	for (int counter = 1; counter <= stopnum; counter++)
		{

		fin >> x >> y;

		deltax = x - xprev;
		deltay = y - yprev;
		newdist = sqrt((pow(deltax,2)+pow(deltay,2)));
		xprev = x;
		yprev = y;
		totdist += newdist;
		
   		}
		
		
		totdistorigin = totdist+(sqrt((pow(xprev,2)) + (pow(yprev,2))));
		totdistall += totdistorigin;
		
	if (heavyload == 0)
		{
		tripcost = flatfee * stopnum + totdistorigin * 2.75;
		}
	else
		{
		tripcost = (flatfee * stopnum + totdistorigin * 2.75) * 1.2;
    	}

	totcostall += tripcost;	
	
	
	if (tripnum >= 1 && tripnum <= 6|| tripnum % 10 == 6)
		{	
		
		fout << setw(5) << tripnum << setw(9) << stopnum << setw(8) << 
		heavyload << setw(12) << totdistorigin << setw(12) << tripcost << 
		setw(13) << totdistall << setw(13) << totcostall << endl;
	    
		}  
		
	if (tripcost > max_price){// to find most expensive trip
		max_price = tripcost;}
		    
	if (totdistorigin < min_dist){ // to find shortest distance travelled
		min_dist = totdistorigin;}
	
		totdistorigin = 0;
		totdist = 0;
		xprev = 0;
		yprev = 0;	
			
			
			
	if (tripnum==227) {	
	fout << "The length of the shortest trip was " << min_dist << " km" << endl;
	fout << "The most expensive trip was $" << max_price << endl;
	fout << "The total distance traveled was "<< totdistall << " km" << endl;
	fout<< "The total amount collected was $" << totcostall <<endl;
		
	}
	
	
	} 
		


return(EXIT_SUCCESS);
}







