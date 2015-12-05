/**********************************************************************************************************************************
	
						     Author  : Vivek Nynaru
   						     Handle  : kevin11 
						     Year    :  2015

**********************************************************************************************************************************/

#include<bits/stdc++.h>
using namespace std;
typedef long double LD;
/******************************************************************************************************************************************
      
      Question: Find area of intersection of two circles

******************************************************************************************************************************************/
LD Area(LD X1,LD Y1,LD R1,LD X2,LD Y2,LD R2)
{
	// Add area of two sectors and remove area of triangle formed by centers and point of intersections
	LD d=sqrt((X2-X1)*(X2-X1)+(Y2-Y1)*(Y2-Y1));
	if(R1<R2)
		swap(R1,R2);
	if(R1+R2<=d) // disjoint
		return 0;
	else if(R1-R2>=d) // subset
		return M_PI*R2*R2;
	else
	{
		LD anglea=acos((((d*d+R1*R1-R2*R2)/2)/R1)/d);
		LD angleb=acos((((d*d+R2*R2-R1*R1)/2)/R2)/d);
		return R1*R1*(anglea-sin(anglea)*cos(anglea))+R2*R2*(angleb-sin(angleb)*cos(angleb));
	}
}
int main()
{
	long double X1,Y1,R1,X2,Y2,R2;
	cin >> X1 >> Y1 >> R1;	
	cin >> X2 >> Y2 >> R2;
	cout << setprecision(10) << Area(X1,Y1,R1,X2,Y2,R2) << "\n";
	return 0;
}

