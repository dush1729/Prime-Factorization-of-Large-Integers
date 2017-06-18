#include<bits/stdc++.h>
#include<time.h>
using namespace std;
const int MAX=1e9+20;
long long i,n1,n2,r;
set <long long> v1,v2,cd;
void PrintPF(long long n, set <long long> &v)
{
	cout<<n<<" = ";
	for(auto i=++v.begin();i!=v.end();i++)
	{
		while(n%*i==0)
		{
			if(n==*i) cout<<*i;
			else cout<<*i<<" * ";
			n/=*i;
		}
	}
	cout<<endl;
}
int main()
{
    cout<<"Enter number 1: "; cin>>n1;
    cout<<"Enter number 2: "; cin>>n2;
    r=max(sqrtl(n1),sqrtl(n2));

    struct timespec begin;
    clock_gettime(CLOCK_MONOTONIC, &begin);
	for(i=1;i<=r;i++)
    {
    	if(n1%i==0)
    	{
    		v1.insert(i);
    		v1.insert(n1/i);
    	}

    	if(n2%i==0)
    	{
    		v2.insert(i);
    		v2.insert(n2/i);
    	}
    }

	cout<<endl;
	struct timespec end;
	clock_gettime(CLOCK_MONOTONIC,&end);
	double elapsed=(end.tv_sec-begin.tv_sec)+((end.tv_nsec-begin.tv_nsec)/1e9);
	cout<<"Time elapsed: "<<elapsed<<endl<<endl;

	PrintPF(n1,v1);
	cout<<"Divisors of "<<n1<<": ";
    for(auto i:v1) cout<<i<<" "; cout<<endl;
    cout<<"Number of divisors: "<<v1.size()<<endl<<endl;

	PrintPF(n2,v2);
    cout<<"Divisors of "<<n2<<": ";
    for(auto i:v2) cout<<i<<" "; cout<<endl;
	cout<<"Number of divisors: "<<v2.size()<<endl<<endl;

    for(auto i:v1) if(v2.find(i)!=v2.end()) cd.insert(i);
    cout<<"Common Divisors: ";
    for(auto i:cd) cout<<i<<" ";cout<<endl;
    cout<<"GCD("<<n1<<","<<n2<<") = "<<*--cd.end()<<endl<<endl;
}
