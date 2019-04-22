#include<iostream>
#include<fstream>
#include<queue>
#include<string.h>
using namespace std;

typedef struct{
	int freq;
	int left;
	int right;
	int word;
}Node;

Node node[700];

struct cmp{
	bool operator()(const int& i,const int&j)
	{
		return node[i].freq > node[j].freq;
	}
};
int code2[256];
int code[256][256];
void encode(Node N,int level);

void tree(){
	priority_queue<int, vector<int>, cmp> pq;
	
	//��Ҧ���(�r��)��ipriority queue
	for(int i=0;i<256;i++){
		if(node[i].freq>0){
			pq.push(i);
		}
	} 
	//�E�X N-1 ���N�|�o����
	int c=0;	//optimal code tree ���v��
	for(int i=0;pq.size()>=2;i++){
		int a=pq.top();			//Ū��priority_queue�̤W�������A�����R���������C
		pq.pop();				//�qpriority_queue�̤W�����X�����A�ñqpriority_queue�R���������C
		int b=pq.top();
		pq.pop();
		node[256+i].freq=node[a].freq+node[b].freq;
		node[256+i].left=a;
		node[256+i].right=b;
		pq.push(256+i);				// ��s�`�I��ipriority queue 
	} 
	for(int i=0;i<256;i++){			//��l�� code 
		for(int j=0;j<256;j++){
			code[i][j]=-1;
		}
	} 
	node[510]=node[pq.top()];		//�̰����@�Ӹ`�I 
	encode(node[510],0); 
}

void encode(Node N,int level){
	if(N.left==-1 && N.right==-1){		//���𸭤F	
		for(int i=0;i<level;i++){
			code[N.word][i]=code2[i];
		}
		return;
	}
	
	code2[level]=0;
	if(N.left != -1)	encode(node[N.left],level+1);
	
	code2[level]=1;
	if(N.right != -1)	encode(node[N.right],level+1);
	
	return;
}

int main(){
	
	int digit=0;		//�s�X�ᦳ�X���
	ifstream file;
	ofstream file2;
	
	string filename="input.txt";
	file.open(filename.c_str(),ios::binary); 
	
	unsigned char temp;
	
	for(int i=0;i<700;i++){		//��l�� 
		node[i].left=-1;
		node[i].right=-1;
		node[i].freq=0;
		node[i].word=i;			
	}
	while(file.read((char*)&temp,1)){	//�@��Ū�@�Ӧr 
		node[temp].freq++;
		node[temp].left=-1;
		node[temp].right=-1;
		node[temp].word=temp;	//���� node ���s�X 
	}
	
	tree();
	file.close();
	
	file.open(filename.c_str(), ios::binary);
	
	queue<char> que;
	
	unsigned char temp2=0;
	while(file.read((char*)&temp, 1)){	//Ū��@�Ӧr�A�s�� temp 
		int a = 0;						 
        while(code[temp][a] != -1)	//�Q�s�X�L�F 
        {
            temp2 = temp2 << 1;
            temp2 = temp2 | code[temp][a];
            digit++;
            a++;
            if(digit == 8) 
            {
            	que.push(temp2);
                digit=0;
                temp2=0;
            }
        }
	}
	que.push(temp2); 
    file.close();
    
	
	string filename2="output.txt";
	file2.open(filename2.c_str(),ios::binary);
	
	unsigned char num;
	int deindex=510;
	while(!que.empty()){
		num=que.front();
		que.pop();
		int looptime=8;
		if(que.empty()){
			looptime=digit;
			num = num << (8-digit);
		}
		for(int i=0;i<looptime;i++){
			int nowbit=(num&128)>>7;
			num=num<<1;
			if(nowbit==1){
				deindex=node[deindex].right;
				if(node[deindex].right==-1 && node[deindex].left==-1){
					file2.write((char*)&node[deindex].word,1);
					deindex=510;
				}
			}
			else if(nowbit==0){
				deindex=node[deindex].left;
				if(node[deindex].right==-1 && node[deindex].left==-1){
					file2.write((char*)&node[deindex].word,1);
					deindex=510;
				}
				
			}
			
		}
		
		
	}
	
	
	
	
	
	
	
	
	file2.close();
}










