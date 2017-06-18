#include<bits/stdc++.h>
#include<omp.h>
#include<time.h>
using namespace std;
const int MAX=1e9+20,THREADS=600;
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
    omp_set_num_threads(THREADS);
    #pragma omp parallel
	{
		set <long long> vp1,vp2;
		#pragma omp for nowait
		for(i=1;i<=r;i++)
	    {
	    	if(n1%i==0)
	    	{
	    		vp1.insert(i);
	    		vp1.insert(n1/i);
	    	}

	    	if(n2%i==0)
	    	{
	    		vp2.insert(i);
	    		vp2.insert(n2/i);
	    	}
	    }
	    #pragma omp critical
    	{
    		v1.insert(vp1.begin(), vp1.end());
    		v2.insert(vp2.begin(), vp2.end());
    	}
	}

	cout<<endl;
	struct timespec end;
	clock_gettime(CLOCK_MONOTONIC,&end);
	double elapsed=(end.tv_sec-begin.tv_sec)+((end.tv_nsec-begin.tv_nsec)/1e9);
	cout<<"Threads: "<<THREADS<<endl;
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
