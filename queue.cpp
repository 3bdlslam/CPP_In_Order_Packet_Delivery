#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <cmath>

#include<iostream>
#include <stdlib.h>
#include <cstddef>
#include <exception>

template <class QDT >
class st_queue {
	private:
		QDT *queueData;
		int rear, front,full,empty,queueSize;
		bool flipover;

	public:
		st_queue();
		st_queue(int n);
		bool enqueue(QDT elem);
		QDT dequeue();
		bool isEmpty();
		bool isFull();
		bool print();

};


template<class QDT>
st_queue<QDT>::st_queue()
{
	try
	{
		queueData=new QDT[100];
	}
	catch(std::bad_alloc& e)
	{
		std::cerr<<e.what()<<'\n';
	}
	rear=-1; front=0;full=0;empty=1;queueSize=100;flipover=false;
}

template<class QDT>
st_queue<QDT>::st_queue(int n)
{
	try
	{
		queueData=new QDT[n];
	}
	catch(std::bad_alloc& e)
	{
		std::cerr<<e.what()<<'\n';
	}
	rear=-1; front=-1;full=0;empty=1;queueSize=n;flipover=false;
}

template<class QDT>
bool st_queue<QDT>::enqueue(QDT elem){
	if(full==1)
	{
		std::cerr<<"you are trying to enQueue to a full Queue\n";
		return 2;
	}
	else
	{


	// find the position of the element to insert
		int insPos=front;
		for(int f=0;queueData[insPos]<elem && (insPos<rear||(flipover&&!f));insPos++)
		{
			if(insPos==queueSize-1)
			{
				f=1;insPos=-1;
			}
			if(queueData[insPos]==elem){	return 1;	}

		}

	// handle the in should be inserted @ the end of the queue	and repeated element
		if((empty==0)&&(queueData[insPos]==elem))
		{
			return 1;
			//std::cerr<<"the element is repeated";
		}
		else if(empty==0&&queueData[insPos]<elem) 
		{
			if(insPos==queueSize-1)
				{insPos=0;}
			else
				{insPos++;}
		}

	// increment rear  and check is it flipped over
		if(rear==queueSize-1)
			{rear=0;flipover=1;}
		else
			{rear++;}

	//check is it become full
		if(rear+1==front||(rear==queueSize-1&&front==0)){full=1;}

	//check is it was empty
		if(rear==front){empty=0;}

	// insert the element and shift the others
		QDT temp;
		for(int i=insPos, f=0;(i<=rear||(flipover&&!f));i++){

			temp=queueData[i];
			queueData[i]=elem;
			elem=temp;
			if(i==queueSize-1){
				f=1;i=-1;
			}

		}
		elem=queueData[insPos];
	}

	return 0;
}

template<class QDT>
QDT st_queue<QDT>::dequeue()
{
	QDT ret_val;
	if(empty==1)
	{
		//std::cerr<<"you are trying to deQueue from empty Queue\n";
	}
	else{
		ret_val=queueData[front];



		// check if it was full to update class info
		if(front-1==rear||(front==0&&rear==queueSize-1)){full=0;}

		//increment front and check flipover
		if(front==queueSize-1){front=0;flipover=0;}
		else{front++;}

		// check if it becomes empty to update class info
		if(front==(rear+1)){empty=1;}
	}

	return ret_val;
}

template<class QDT>
bool st_queue<QDT>::isEmpty()
{
	return empty;
}

template<class QDT>
bool st_queue<QDT>::isFull()
{
	return full;
}

template<class QDT>
bool st_queue<QDT>::print()
{
	if(empty==1){std::cout<<"empty Queue print\n";}
	else
	{
		std::cout<<"queue :";
		for(int i=front,f=0;(i<=rear)||(flipover&&(!f));i++)
		{
			std::cout<<queueData[i]<<"\t";
			if(i==queueSize-1){f=1;i=-1;}

		}
		std::cout<<"\n";
	}
	return empty;
}
