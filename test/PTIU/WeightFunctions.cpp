#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <cstdio>                                             //the header files needed
#include <cstdlib>
#include <vector>
#include <iostream>
#include <utility>
#include <map>
#include <iomanip>
#include <algorithm>
#include"..\\cpp.h"
#include "..\\csim.h"
#include "..\\global3.h"
#include "..\\VDefinition.h"
//#include "..\\PTIU\FrameWork.cpp"


using namespace std;



void InsertSort(double a[],int count)//直接插入法实现对数组的从大到小排序
{
        int i=0,j=0;
		double temp=0;
        for(i=1;i<count;i++)   
        {
           temp=a[i];
           j=i-1;
           while(a[j]<temp && j>=0)//从a[i-1]开始找比a[i]大的数，同时把数组元素向后移
           {
             a[j+1]=a[j];
              j--;
           }
           if(j!=(i-1))     
             a[j+1]=temp;
         }
}

double FCFS_Weight(vector <int> selectvec, pair <int, int> vex[2000])//calculate the Weight(WaitingTime in LWF)of each request
{
	struct Request * currentReq;

	TIME WaitingTime=0;

	double waitingtime=0;
	double e=0;
	double ex=0;
	double requestWeight = 0;
    double SumWeight = 0;
    int i=0;
	int cliquesize=selectvec.size();
	
	//double LocalmaxDATASIZE= 1.0;//double LocalmaxDATASIZE; /// global variable 
	//double currentDATASIZE= 1.0;

	double WeightWaitingTime[100];//double WaitingTime[cliquesize];

    for(i=0;i<100;i++)
	{
       WeightWaitingTime[i]=-1;
	}

	vector <int>::iterator itor;       

	currentReq = head->Next;

	i=0;
    while(currentReq != NULL)
	{

		for(itor=selectvec.begin();itor!=selectvec.end();itor++)
		 {

			if(currentReq->ClientID==vex[(*itor)].first+1)
			{
				WaitingTime=clock - currentReq->ArrivalTime;
			
				//currentDATASIZE=currentReq->DataSize;//12.22-current datasize of one request in the chosen clique
				//if(currentDATASIZE>LocalmaxDATASIZE)//12.22-current datasize of one request in the chosen clique
				//LocalmaxDATASIZE=currentDATASIZE;

	            WeightWaitingTime[i]=WaitingTime;
				i++;
			    break;

			}//if(currentReq->ClientID==vex[(*itor)].first+1)
			  
		}	//for(itor=selectvec.begin();itor!=selectvec.end();itor++)
        
		currentReq = currentReq->Next;

	}//while(currentReq != NULL)

    InsertSort( WeightWaitingTime,cliquesize);

	for(i=0;i<cliquesize;i++)
	{

        waitingtime=WeightWaitingTime[i];
		e=cliquesize-i;
		ex=pow(2,e);//double pow(double x, double y)是C的内置函数,计算 x的y次幂
		requestWeight = waitingtime*ex;
        SumWeight=SumWeight+requestWeight;
	}

    return SumWeight;
}//End double FCFS_Weight(...)

double MRF_Weight(vector <int> selectvec, pair <int, int> vex[2000])//calculate the Weight(WaitingTime in LWF)of each request,  and LocalmaxDATASIZE
{
	struct Request * currentReq;
	double requestWeight = 0;
    double MaxWeight = -1.0;

	TIME WaitingTime=0;
	
	int cliquesize=selectvec.size();
	
	//double LocalmaxDATASIZE=1.0;//double LocalmaxDATASIZE;  //12.22-current maximum datasize in the chosen clique
	//double currentDATASIZE=1.0;//12.22-current datasize of one request in the chosen clique

	vector <int>::iterator itor;       
	//struct Decodeset *newdecode,*pre,*p;
	//pair <int, int> decode[800];
	
	/*
	currentReq = head->Next;

    while(currentReq != NULL)
	{

		for(itor=selectvec.begin();itor!=selectvec.end();itor++)
		 {

			if(currentReq->ClientID==vex[(*itor)].first+1)
			{
				
				currentDATASIZE=currentReq->DataSize;//12.22-current datasize of one request in the chosen clique
				if(currentDATASIZE>LocalmaxDATASIZE)//12.22-current datasize of one request in the chosen clique
				{LocalmaxDATASIZE=currentDATASIZE;}//12.22-current maximum datasize in the chosen clique

				break;
			}
			  
		}	
        
		currentReq = currentReq->Next;

	} */
    return cliquesize;
}//End double MRF_Weight(...)



double LWF_Weight(vector <int> selectvec, pair <int, int> vex[2000])//calculate the Weight(WaitingTime in LWF)of each request
{
	struct Request * currentReq;
	double requestWeight = 0;
    double SumWeight = 0;

	TIME WaitingTime=0;

	//double LocalmaxDATASIZE = 1.0;//double LocalmaxDATASIZE;  //12.22-current maximum datasize in the chosen clique
	//double currentDATASIZE = 1.0;//12.22-current datasize of one request in the chosen clique


	vector <int>::iterator itor;       
	//struct Decodeset *newdecode,*pre,*p;
	//pair <int, int> decode[800];

	currentReq = head->Next;

    while(currentReq != NULL)
	{

		for(itor=selectvec.begin();itor!=selectvec.end();itor++)
		 {

			if(currentReq->ClientID==vex[(*itor)].first+1)
			{
				//currentDATASIZE=currentReq->DataSize;//12.22-current datasize of one request in the chosen clique
				//if(currentDATASIZE>LocalmaxDATASIZE)//12.22-current datasize of one request in the chosen clique
				//{LocalmaxDATASIZE=currentDATASIZE;}//12.22-current maximum datasize in the chosen clique

				
				WaitingTime=clock - currentReq->ArrivalTime;
                requestWeight = WaitingTime;
				SumWeight= SumWeight+requestWeight;
				break;
			}
			  
		}	
        
		currentReq = currentReq->Next;

	}
    return SumWeight;
}//End double LWF_Weight

double RW_Weight(vector <int> selectvec, pair <int, int> vex[2000])//calculate the Weight(WaitingTime in LWF)of each request,  and LocalmaxDATASIZE
{
	struct Request * currentReq;
	double requestWeight = 0;
    double MaxWeight = -1.0;

	TIME WaitingTime=0;
	
	int cliquesize=selectvec.size();
	
	//double LocalmaxDATASIZE = 1.0;//double LocalmaxDATASIZE;  //12.22-current maximum datasize in the chosen clique
	//double currentDATASIZE = 1.0;//12.22-current datasize of one request in the chosen clique

	vector <int>::iterator itor;       
	//struct Decodeset *newdecode,*pre,*p;
	//pair <int, int> decode[800];

	currentReq = head->Next;

    while(currentReq != NULL)
	{

		for(itor=selectvec.begin();itor!=selectvec.end();itor++)
		 {

			if(currentReq->ClientID==vex[(*itor)].first+1)
			{
				WaitingTime=clock - currentReq->ArrivalTime;
				
				//currentDATASIZE=currentReq->DataSize;//12.22-current datasize of one request in the chosen clique
				//if(currentDATASIZE>LocalmaxDATASIZE)//12.22-current datasize of one request in the chosen clique
				//{LocalmaxDATASIZE=currentDATASIZE;}//12.22-current maximum datasize in the chosen clique

                requestWeight = WaitingTime;

				//SumWeight= SumWeight+requestWeight;//LWF

				if(MaxWeight<requestWeight)//RxW
					MaxWeight=requestWeight;//RxW


				break;
			}
			  
		}	
        
		currentReq = currentReq->Next;

	}
    return (MaxWeight*cliquesize);
}//End double RW_Weight(...)



double EDF_Weight(vector <int> selectvec, pair <int, int> vex[2000])//calculate the sum of the weight in the maximum clique
{
	struct Request * currentReq;

	TIME Deadline=0;
	double slacktime=0;

	double e=0;
	double ex=0;
	double requestWeight = 0;
    double SumWeight = 0;
    int i=0;
	int cliquesize=selectvec.size();
	
	double LocalmaxDATASIZE = 1.0;//double LocalmaxDATASIZE; 
	double currentDATASIZE = 1.0;

	double weightSlackTime[100];//double weightSlackTime[cliquesize];


	//Request->Deadline = RequestDeadline;

    for(i=0;i<100;i++)
	{
       weightSlackTime[i]=-1;
	}

	vector <int>::iterator itor;       

	currentReq = head->Next;

	i=0;
    while(currentReq != NULL)
	{

		for(itor=selectvec.begin();itor!=selectvec.end();itor++)
		 {

			if(currentReq->ClientID==vex[(*itor)].first+1)
			{
				currentDATASIZE=currentReq->DataSize;//12.22-current datasize of one request in the chosen clique
				if(currentDATASIZE>LocalmaxDATASIZE)//12.22-current datasize of one request in the chosen clique
				LocalmaxDATASIZE=currentDATASIZE;

				Deadline=currentReq->Deadline;//TIME type
				slacktime=Deadline-clock;//double type

	            if(slacktime<=0)
					weightSlackTime[i]=0;
				else
					weightSlackTime[i]=1/slacktime;

				i++;
			    break;

			}//if(currentReq->ClientID==vex[(*itor)].first+1)
			  
		}	//for(itor=selectvec.begin();itor!=selectvec.end();itor++)
        
		currentReq = currentReq->Next;

	}//while(currentReq != NULL)

    InsertSort( weightSlackTime,cliquesize);

	for(i=0;i<cliquesize;i++)
	{

		e=cliquesize-i;
		ex=pow(2,e);//double pow(double x, double y)是C的内置函数,计算 x的y次幂
		requestWeight = weightSlackTime[i]*ex;//weightSlackTime[i]=1/slacktime;
        SumWeight=SumWeight+requestWeight;
	}

    return SumWeight;
}//End double EDF_Weight(...)



double SIN_Weight(vector <int> selectvec, pair <int, int> vex[2000])//calculate the sum of the weight in the maximum clique
{
	struct Request * currentReq;

	TIME Deadline=0;
	double slacktime=0;

	double requestWeight = 0;
    double SumWeight = 0;
    int i=0;
	int cliquesize=selectvec.size();
	
	double LocalmaxDATASIZE = 1.0;//double LocalmaxDATASIZE;  
	double currentDATASIZE=1.0;
	
	vector <int>::iterator itor;       

	currentReq = head->Next;

	i=0;
    while(currentReq != NULL)
	{

		for(itor=selectvec.begin();itor!=selectvec.end();itor++)
		 {

			if(currentReq->ClientID==vex[(*itor)].first+1)
			{
				Deadline=currentReq->Deadline;//TIME type
				slacktime=Deadline-clock;//double type
				
				currentDATASIZE=currentReq->DataSize;//12.22-current datasize of one request in the chosen clique
				
				if(currentDATASIZE>LocalmaxDATASIZE)//12.22-current datasize of one request in the chosen clique
				LocalmaxDATASIZE=currentDATASIZE;
				

	            if(slacktime<=0)
					requestWeight=0;
				else
					requestWeight=1/slacktime;

				if(SumWeight<requestWeight)
					SumWeight=requestWeight;

				i++;
			    break;

			}//if(currentReq->ClientID==vex[(*itor)].first+1)
			  
		}	//for(itor=selectvec.begin();itor!=selectvec.end();itor++)
        
		currentReq = currentReq->Next;

	}//while(currentReq != NULL)

    return (SumWeight*cliquesize);
}//End double SIN_Weight(.....)

double LTSF_Weight(vector <int> selectvec, pair <int, int> vex[2000])//calculate the Weight(WaitingTime in LWF)of each request,  and LocalmaxDATASIZE
{
	struct Request * currentReq;
	double requestWeight = 0;
    double SumWeight = 0;

	TIME WaitingTime=0;

	double LocalmaxDATASIZE = 1.0;//double LocalmaxDATASIZE; /* global variable */ //12.22-current maximum datasize in the chosen clique
	double currentDATASIZE = 1.0;//12.22-current datasize of one request in the chosen clique

	vector <int>::iterator itor;       
	//struct Decodeset *newdecode,*pre,*p;
	//pair <int, int> decode[800];

	currentReq = head->Next;

    while(currentReq != NULL)
	{

		for(itor=selectvec.begin();itor!=selectvec.end();itor++)
		 {

			if(currentReq->ClientID==vex[(*itor)].first+1)
			{
				WaitingTime=clock - currentReq->ArrivalTime;
				currentDATASIZE=currentReq->DataSize;//12.22-current datasize of one request in the chosen clique
				
				if(currentDATASIZE>LocalmaxDATASIZE)//12.22-current datasize of one request in the chosen clique
				LocalmaxDATASIZE=currentDATASIZE;//12.22-current maximum datasize in the chosen clique

                requestWeight = WaitingTime;
				SumWeight= SumWeight+requestWeight;
				break;
			}
			  
		}	
        
		currentReq = currentReq->Next;

	}//End while
    double MaxServiceTime = LocalmaxDATASIZE/(double)BANDWIDTH;

	return (SumWeight/(double)MaxServiceTime);
}//End double LTSF_Weight(...)

double STOBS_Weight(vector <int> selectvec, pair <int, int> vex[2000])//calculate the Weight(WaitingTime in LWF)of each request,  and LocalmaxDATASIZE
{
	struct Request * currentReq;
	double requestWeight = 0;
    
	double SumWeight = 0;
	double maxWaitingTime = 0;//7.5-STOBS

	TIME WaitingTime=0;
	int cliquesize=selectvec.size();

	double LocalmaxDATASIZE = 1.0;//double LocalmaxDATASIZE;  //12.22-current maximum datasize in the chosen clique
	double currentDATASIZE = 1.0;//12.22-current datasize of one request in the chosen clique

	vector <int>::iterator itor;       
	//struct Decodeset *newdecode,*pre,*p;
	//pair <int, int> decode[800];

	currentReq = head->Next;

    while(currentReq != NULL)
	{

		for(itor=selectvec.begin();itor!=selectvec.end();itor++)
		 {

			if(currentReq->ClientID==vex[(*itor)].first+1)
			{
				WaitingTime=clock - currentReq->ArrivalTime;
				currentDATASIZE=currentReq->DataSize;//12.22-current datasize of one request in the chosen clique
				if(currentDATASIZE>LocalmaxDATASIZE)//12.22-current datasize of one request in the chosen clique
				LocalmaxDATASIZE=currentDATASIZE;//12.22-current maximum datasize in the chosen clique

                requestWeight = WaitingTime;

				if(maxWaitingTime<requestWeight)//7.5-STOBS
					maxWaitingTime=requestWeight;//7.5-STOBS

				break;
			}
			  
		}	
        
		currentReq = currentReq->Next;

	}//End while
	SumWeight=maxWaitingTime/(double)LocalmaxDATASIZE;//7.5-STOBS
    
	return (SumWeight*cliquesize);
}//End double STOBS_Weight


double FindingMaxDataSize(vector <int> selectvec, pair <int, int> vex[2000])//calculate the Weight(WaitingTime in LWF)of each request,  and LocalmaxDATASIZE
{
	struct Request * currentReq;
	
	double LocalmaxDATASIZE=1.0;//double LocalmaxDATASIZE;  //12.22-current maximum datasize in the chosen clique
	double currentDATASIZE=1.0;//12.22-current datasize of one request in the chosen clique

	vector <int>::iterator itor;       
	//struct Decodeset *newdecode,*pre,*p;
	//pair <int, int> decode[800];

	currentReq = head->Next;

    while(currentReq != NULL)
	{

		for(itor=selectvec.begin();itor!=selectvec.end();itor++)
		 {

			if(currentReq->ClientID==vex[(*itor)].first+1)
			{
				
				currentDATASIZE=currentReq->DataSize;//12.22-current datasize of one request in the chosen clique
				
				if(currentDATASIZE>LocalmaxDATASIZE)//12.22-current datasize of one request in the chosen clique
				LocalmaxDATASIZE=currentDATASIZE;//12.22-current maximum datasize in the chosen clique

				break;
			}
			  
		}	
        
		currentReq = currentReq->Next;

	}//End while
   

	return LocalmaxDATASIZE;
}//End double LTSF_Weight(...)
