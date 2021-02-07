#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main()
{
	srand(time(NULL));
	int i=0;
	int j=0;
	int num=0;
	int A[10][10];
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++){
			if(i==j){
				A[i][j]=0;
			}
			if(i<j){
				num=rand()%100;
				A[i][j]=num;
				A[j][i]=num;
			}
			
			
		}
	}
	for(int i=0;i<10;i++){
		cout<<i<<",";
	}
	cout<<"\n"<<"\n";
	for(int i=0;i<10;i++)
	{
		cout<<"{";
		for(int j=0;j<10;j++)
		{
			cout<<A[i][j]<<",";
		}
		cout<<"}"<<","<<"\n";
	}

	return 0;
}
