#include<iostream>
#include<cstdlib>
#include<fstream>
#include<ctime>

using namespace std;
void RAND_QUICKSORT(int [],int ,int );
int PARTITION(int [],int ,int );
int RAND_PARTITION(int [],int,int );

int main()
{
    int size;
    fstream fin,fout;
    srand(time(NULL));
    fin.open("input.txt",ios::in);
    fout.open("output.txt",ios::out);
    
    fin>>size;
    int a[size];
    for(int i=1;i<=size;i++){
        fin>>a[i];
    }

    int first=1,last=size;

    RAND_QUICKSORT(a,first,last);

   for(int i=1;i<=size;i++){
       fout<<a[i]<<' ';
   }
    return 0;
}

void RAND_QUICKSORT(int a[],int first,int last)
{
    int q;
    if(first<last)
    {
     q=RAND_PARTITION(a,first,last);
     RAND_QUICKSORT(a,first,q-1);
     RAND_QUICKSORT(a,q+1,last);
    }
}

int PARTITION(int a[],int first,int last)
{
    int temp1,temp2;
    int x=a[last];
    int i=first-1;
    for(int j=first;j<=last-1;j++){
        if(a[j]<=x){
            i=i+1;
            temp1=a[i];
            a[i]=a[j];
            a[j]=temp1;
        }
    }
    temp2=a[i+1];
    a[i+1]=a[last];
    a[last]=temp2;
    return i+1;
}
  
int RAND_PARTITION(int a[],int first,int last)
{
	int index1,index2,index3;
	index1=rand()%(last-first+1);
	index2=rand()%(last-first+1);
	index3=rand()%(last-first+1);
	
	int mid;
	if(a[index1]>a[index2]){
		if(a[index2]>a[index3])		mid=index2;
		else{
			if(a[index1]>a[index3])	mid=index3;
			else				mid=index1;
		}
	}
	else{
		if(a[index1]>a[index3])	mid=index1;
		else{
			if(a[index3]>a[index2])	mid=index2;
			else				mid=index3;
		}
	}
	
    int i=first+mid;
    int temp3;
    temp3=a[last];
    a[last]=a[i];
    a[i]=temp3;
    return PARTITION(a,first,last);
}
