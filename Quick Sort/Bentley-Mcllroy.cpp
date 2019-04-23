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
	int mid[3];
	int m=0;
	for(int j=1;j<=3;j++){
		int n=(last-first+1)/9;
		index1=m;
		index2=m+n;
		index3=m+2*n;
		m+=3*n;
		
		if(a[index1]>a[index2]){
			if(a[index2]>a[index3])		mid[j]=index2;
			else{
				if(a[index1]>a[index3])	mid[j]=index3;
				else				mid[j]=index1;
			}
		}
		else{
			if(a[index1]>a[index3])	mid[j]=index1;
			else{
				if(a[index3]>a[index2])	mid[j]=index2;
				else				mid[j]=index3;
			}
		}
		
	}
	
	int mid_final;
	if(a[mid[1]]>a[mid[2]]){
		if(a[mid[2]]>a[mid[3]])		mid_final=mid[2];
		else{
			if(a[mid[1]]>a[mid[3]])	mid_final=mid[3];
			else				mid_final=mid[1];
		}
	}
	else{
		if(a[mid[1]]>a[mid[3]])	mid_final=mid[1];
		else{
			if(a[mid[3]]>a[mid[2]])	mid_final=mid[2];
			else				mid_final=mid[3];
		}
	}
	
    int i=first+mid_final;
    int temp3;
    temp3=a[last];
    a[last]=a[i];
    a[i]=temp3;
    return PARTITION(a,first,last);
}
