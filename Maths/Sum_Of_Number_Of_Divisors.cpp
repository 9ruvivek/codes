/*****************************************************************************************************************************************
	
						     Author  : Vivek Nynaru
   						     Handle  : kevin11 
						     Year    :  2015

******************************************************************************************************************************************/

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
/******************************************************************************************************************************************
      
      Question: Find Sum of multiples of all numbers from 1 to N which are less than N ,Simply, SIGMA(N/i) for i in 1-N

      Reference: https://en.wikipedia.org/wiki/Divisor_summatory_function

      Complexity: O(sqrt(N))

******************************************************************************************************************************************/

ll Sum_Of_Number_Of_Divisors_from_1_to_N(ll N){
	ll sq=sqrt(N);
	ll sum=0;
	for(int i=1;i<=sq;i++)
		sum+=N/i;
	return 2*sum-sq*sq;
}
int main(){
	ll N;
	cout <<  "Enter the value of N: ";
	cin >> N;
	cout << Sum_Of_Number_Of_Divisors_from_1_to_N(N) << "\n";
	return 0;
}

