/**********************************************************************************************************************************
	
						     Author  : Vivek Nynaru
   						     Handle  : kevin11 
						     Year    :  2015

**********************************************************************************************************************************/

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double LD;

/******************************************************************************************************************************************
      
      Question: Find Median of the data at every step

      Complexity: Can be Considered to be atmost O(sqrt(N)) + Time to precompute phisum till a fixed limit(using normal way)

******************************************************************************************************************************************/

priority_queue < ll , vector < ll > , greater < ll > > minheap;
priority_queue < ll , vector < ll > , less < ll > > maxheap;
LD median;         // stores median
ll n,val,lc,rc; // lc->left count, rc->right count

// minheap is used to store data greater than median at current stage
// maxheap is used to store data lesser than median at current stage
int main()
{
	cin >> n;
	for(int i=1;i<=n;i++)
	{
		cin >> val;
                // when data is read check if it is lesser than median, if so push it into maxheap else into minheap
		if((LD)val<=median)
		{
			maxheap.push(val);
			lc++;
		}
		else
		{
			minheap.push(val);
			rc++;
		}
		// Balancing heap such that difference in size of heaps is atmost 1
		if(rc-lc==2)
		{
			maxheap.push(minheap.top()); // This just removes the smallest element is right side and pushes it into left side
			minheap.pop();
			lc++;rc--;
		}
		else if(lc-rc==2)
		{
			minheap.push(maxheap.top());
			maxheap.pop();
			lc--;rc++;
		}
		// Updating the median
		if(lc==rc)
			median=((minheap.top()+maxheap.top())*1.0)/2.0;
		else if(lc>rc)
			median=maxheap.top()*1.0;
		else
			median=minheap.top()*1.0;
		cout << median << "\n";
	}
	return 0;
}

