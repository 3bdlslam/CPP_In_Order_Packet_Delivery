#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <cmath>

#include<iostream>
#include <stdlib.h>
#include <cstddef>
#include <exception>

#include "queue.cpp"

int NumOfBits, windowSize,initSequence;
int maxNum;


int checkArgs(int argn, char** argv);
void reOrder(int a[],int n);
bool isNum(const std::string data);
void swtch(int &x);


int main(int argn, char** argv){


// invalid arguments handling

	int errors = checkArgs(argn,argn);

	if(errors){ std::cout<<'\n';return 0;}




	int* R_Backets=new int[argn];;		// array for the received packet IDs
	int received=0;						// counter for received packet IDs

	st_queue<int> OOO_Backets[2];		// define 2 queues to represent ehe waiting list
										//	(OOO_Backets = Out Of Order Backets)
	int obNum=0; 						// this number will take 0 and 1 value only to accesss OOO_backets[obNum]
										//	(obNum = Object number)
	// at any time one of them stores OOO backets between [expeexted   and  maximum]
	// and thr other will stores OOO backets starts from ( 0 )


	int* D_Backets=new int[argn];		// array for the dropped data
	int dropped=0;						// this will count the dropped Packet IDs


	for(int jj=0;jj<argn;jj++)
	{D_Backets[jj]=-1;}


	int Expected=initSequence;

	for(int i=4,iter;i<argn;i++)	// iterate on the backet IDs
	{
		iter=atoi(argv[i]);			// iter = backet_ID [i-4]

		// check is this Packet id exceeded the window size or not
		if(iter>=Expected+windowSize||((Expected>iter)&&(iter>=Expected+windowSize-maxNum)))
		{
			D_Backets[dropped]=iter;
			dropped++;
		}

		else
		{
			if(iter>=Expected)	// is it reach the maximum and start over
			{
				// check also is this Packet Id is repeated
				// if it's true then it will add the value in dropped Packet IDs else the value will be already enqueued
				int tt=OOO_Backets[obNum].enqueue(iter);
				if(tt==1)
				{
					D_Backets[dropped]=iter;
					dropped++;
				}
			}
			else
			{	// same as above one but for the other queue which store the values less than expected
				//(values should be sent last )
				swtch(obNum);
				if(OOO_Backets[obNum].enqueue(iter)==1)
				{
					D_Backets[dropped]=iter;
					dropped++;
				}
				swtch(obNum);
			}
		}

		//=====================================================================================================================
		if(Expected==iter) 									// if true this Packet ID must be sent and check the waiting list
		{
			if(!OOO_Backets[obNum].isEmpty())
				iter=OOO_Backets[obNum].dequeue();
			int lastin=0;
			while((iter==Expected))							// loop while the expected item in the waiting list
			{
				R_Backets[received]=iter;received++;		// Add itterator to received Packet IDs
				lastin =iter;
				Expected++;									// edit the expected Packet ID
				if((OOO_Backets[obNum].isEmpty()))break;	// if waiting list is embty break the loop
				iter=OOO_Backets[obNum].dequeue();			// else get the next element in waiting list and continue the loop
			}

			if(iter!=lastin)
				OOO_Backets[obNum].enqueue(iter);			// enqueue the Packet ID again if it dosnt the expected Packet ID
		}

		//======================================================================================================================

		if(Expected==maxNum)								// if the ecpected Packet ID = 2^NumOfBits it must be start over and return to 0
		{
			swtch(obNum);									// this function convert (0 to 1) or ( 1 to 0 )
															// using this function will swich to the other object which stores Packet IDs starts from 0
			Expected=0;										// return expected to 0 again
			int lastin=maxNum-1;							// the last Packet ID received is (2^NumOfBits)-1
			if(!OOO_Backets[obNum].isEmpty())
				iter=OOO_Backets[obNum].dequeue();
			while((iter==Expected))							// loop while the expected item in the waiting list
			{
				R_Backets[received]=iter;received++;        // Add itterator to received Packet IDs
				lastin =iter;
				Expected++;									// edit the expected Packet ID
				if((OOO_Backets[obNum].isEmpty()))break;	// if waiting list is embty break the loop
				iter=OOO_Backets[obNum].dequeue();			// else get the next element in waiting list and continue the loop
			}
			if((iter!=lastin))
				OOO_Backets[obNum].enqueue(iter);			// enqueue the Packet ID again if it dosnt the expected Packet ID
		}

	}


	int k;
	for(k=0;(k<argn)&&(D_Backets[k]!=-1);k++);
	//reOrder(D_Backets,k);

	std::cout<<"R";for(int s=0;s<received;s++){std::cout<<' '<<R_Backets[s];}
	//	while(!R_Backets2.isEmpty()){std::cout<<' '<<R_Backets2.dequeue();}

	std::cout<<" E "<<Expected<<' ';

	std::cout<<"W";
	while(!OOO_Backets[obNum].isEmpty()){std::cout<<' '<<OOO_Backets[obNum].dequeue();}
	swtch(obNum);
	while(!OOO_Backets[obNum].isEmpty()){std::cout<<' '<<OOO_Backets[obNum].dequeue();}

	std::cout<<" D";
	for(int i=0;i<k ;i++){std::cout<<' '<<D_Backets[i];}


	return 0;
}




void reOrder(int a[],int n){

	for(int j=0;j<n;j++)
	{
		for(int i=0;i<n;i++)
		{
			if(a[i+1]==-1) return;
			if(a[i]>a[i+1])
				{
					a[i]=a[i]+a[i+1];
					a[i+1]=a[i]-a[i+1];
					a[i]=a[i]-a[i+1];
				}
		}
	}
}

bool isNum(const std::string data){
	int aa;
	int flag=0;
	for(int i=0;i<data.length();i++)
	{	aa=data[i];
		if((data[i]>'9'||data[i]<'0' ))
			if(data[i]=='.')
			{
				if(flag)	return 0;
				flag++;
			}
			else
				return 0;

	}
return 1;
}
void swtch(int &x){
	if(x==1) x=0;
	else if(x==0) x=1;
}



int checkArgs(int argn, char** argv)
{
	bool vbs=true;
	int errors=0;
	if(argn<5)	// check is number of arguments is less than allowed
	{
		std::cout<<"Invalid number of arguments";errors++;
	}
	if(argn>1) // if the num of bit is exist
	{
		// chack if the num of bit argument is number and greater than zero
		if(isNum(argv[1])&&(atoi(argv[1])>0))
		{
			NumOfBits=atoi(argv[1]);
			maxNum=pow(2,NumOfBits);
		}else
		{
			if(errors) std::cout<<' ';
			std::cout<<"Invalid seqNumBits";errors++;
			vbs=false;
		}
	}
	if(argn>2)	// if the window size is exist
	{
		// check window size is it positive integer less than 2^NumOfBits (if NumOfBits is valid)
		if(!isNum(argv[2])  ||  (atoi(argv[2])<=0)  ||  ((atoi(argv[2])>=maxNum)&&vbs))
		{
			if(errors) std::cout<<' ';
			std::cout<<"Invalid winSize";errors++;
		}else
		{
			windowSize=atoi(argv[2]);
		}
	}
	if(argn>3)   // if the initial sequence is exist
	{
		// check initial sequence is it positive integer and less than 2^NumOfBits (if NumOfBits is valid)
		if(!isNum(argv[3])  ||  (atoi(argv[3])<0)  ||  ((atoi(argv[3])>=maxNum)&&vbs))
		{
			if(errors) std::cout<<' ';
			std::cout<<"Invalid initSeq";errors++;
		}else
		{
			initSequence=atoi(argv[3]);
		}
	}
	if((argn>4))	// check if at least one packet ID is provided is exist
	{
		//itterate on all packet is to ensure that it is positive integer and less than 2^NumOfBits (if NumOfBits is valid)
		for(int i=4;i<argn;i++)
			if((!isNum(argv[i]))||(((atoi(argv[i])<0)||(atoi(argv[i])>=maxNum))&&vbs))
				{
					if(errors) std::cout<<' ';
					std::cout<<"Invalid packet ID";
					errors++;break;
				}
	}
	return errors;
}

