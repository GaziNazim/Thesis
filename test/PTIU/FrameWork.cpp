
//#include "stdafx.h"
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
//#include "..\\WeightFunctions.cpp"

//#define _TRACE_ // comment this line to avoid outputing trace information

using namespace std;
double AverageDataItemSize;
double TH;

/*
struct Request
{
	long ClientID;
	long Requestcount;
	TIME ArrivalTime;
	TIME Deadline;
	int	DataNum; // how many data objects are requested
	double DataSize;
	int	DataSet[DNMAX][2]; // DataSet[i][0] - request data number, DataSet[i][1] - received flag
	int UnservNum;
	double Priority;
	struct Request *Next;
};

struct ClientCacheitem 
{
  	long DataID; //cache data item;
  	//TIME BroadcastTime; // the broadcast time of data item
  	//TIME Expiretime; // the deadline of data item 
  	struct ClientCacheitem * Next;
};


struct Decodeset
{
	pair <int, int>decode[800];
	struct Decodeset *Next;
}; 


/// statistic facilities ///
double maxDATASIZE;
long DownloadDataItemSize[DBSIZE], DeadlineMissNum, SatisfyNum, BroadcastNum,satisfieditem, TotalEncodedNum; // variable for statistic
long SumOfRequestData, BroadcastDataNum, MissedDataItem, ReceivedNum;
event *broadcast,*done; // pointer for count11er
table *tblend,*tblEncodeNum, *tblResponseTm, *tblStretch; // pointer for table
pair<int,int> decode[800];
int encodedata[20];
double TotalResponseTime, TotalServiceTime;
double THETA;


/// system facilities ///
double ZIPF[DBSIZE]; // simulation database
double Unifm[DBSIZE];
struct Request *head; // request queue
struct ClientCacheitem *cachehead[NUMCLIENT];
struct Decodeset *decodesethead;
struct SelRequest *Thead;

//// global variables ////
long Broadcastitem[10],BroadcastNumber, ClientCacheSize[NUMCLIENT]; // number of active tasks
TIME BeginBstTime; // time indicating when start to broadcast current data object
FILE *fp,*fp1,*fp2,*fp3, *fpResult; // file handle for outputing result
int cnt, temperature[DBSIZE],cnt1,count11[DNMAX], recv[NUMCLIENT][DBSIZE], slots; // count11er for on-goning requests 


//// system routines ////
void Request(long ClientID, long Requestcount);
void client(long ClientID);
void server();
void init_queue();
void init_clientcache();
void init_decodeset() ;
void init_broadcastset();

///// scheduling rountines /////
int EncodeNum(pair <int, int >decode[800]);
void Generateclientcache(long ClientID);
int Generatecache(long ClientID, int DataID);
int AdditionalCacheGeneration(long ClientID,int m);
void EDF_EnterQueue(long ClientID, long Requestcount, TIME ArrivalTime, TIME RequestDeadline,
					int DataNum, int Item[DNMAX][2],int Unserved);
void EDF_DeleteQueueByClientID(long ClientID, long Requestcount);
void ChooseData();

double SIN_Weight(vector <int> selectvec, pair <int, int> vex[2000]);//calculate the sum of the weight in the maximum clique

void InsertSort(double a[],int count);//直接插入法实现对数组的排序

 void GenerateBroadcastset();
 void Encode(long selectedRecv,int Dataset[DNMAX],  struct Decodeset *location);
void maxclique(int k, int select[DNMAX], pair <int, int> vex[2000],struct Decodeset *location);
void GeneratedecodeQ(vector <int> selectvec, struct Decodeset *location,  pair <int, int> vex[2000], int i);
void FinalBrodcast(long DataID ,pair <int, int> decode[800],int k);
void VisualUpdateData(pair <int, int> decode[800] );
void UpdateData(pair <int, int> decode[800]);
void UpdateCache(pair <int, int> decode[800] );
void GenerateDecodeset(int encode[20],int encodeNum, pair <int, int> predecode[800]);
void Updateremain(pair <int, int> decode[800], pair <int, int> decode2[800]);




/// util routines ////
int	DecDistribution(int i);
int	IncDistribution(int i);
void init_Zipf();
void init_Unif();
//void printNewRequest(Request *newRequest);
//void printRequestQueue();
*/

void sim()
{
	int i,j;
	double sum;
	int temp;
	double tbldeadlinemissrate=0;
	set_output_file(fp);
	set_trace_file(fp);
	set_error_file(fp);
	set_model_name("ADC-realtime");

	maxDATASIZE = 1.0;
	DeadlineMissNum = 0;
	SatisfyNum = 0;
	BroadcastNum = 0;
	SumOfRequestData = 0;
	BroadcastDataNum = 0;
	MissedDataItem = 0;
	ReceivedNum = 0;
	satisfieditem=0;
	TotalEncodedNum = 0;
	TotalResponseTime = 0.0;
	TotalServiceTime = 0.0;
	
	sum = 0.0;
	temp = 0;
	/* initialize event */
	broadcast = new event("broadcast");
	done = new event("done");

	/* initialize table */
	tblend =new table("deadline miss ratio");
	tblEncodeNum= new table ("encode number");
	tblResponseTm = new table ("Response Time");
	tblStretch = new table ("Stretch");
	create("sim");
	reseed(NIL, 1);
	
	tblend->confidence();
	tblend->run_length(0.05,0.95,10000);
	tblEncodeNum->confidence();
	tblResponseTm->confidence();
	tblStretch->confidence();
	
	init_queue(); // initialize request queue
	init_Zipf(); // initialize database
	init_Unif();
	init_clientcache(); //initialize client cache
	 init_decodeset(); 

	cnt = NRPC * NUMCLIENT;	// initialize cnt
	for (i = 0; i < DBSIZE; i++)
	{

		temperature[i]=0;
	}
	for(i=0;i<DNMAX;i++)
	{
	     count11[i]=0;
	}
	for(i=0;i<NUMCLIENT;i++) //initailize cache size
	{
		for(j=0;j<DBSIZE;j++)
			{
                 		recv[i][j]=-1;
					
			}
		
	}
	
	for(i=0;i<=10;i++)
	EncodePacketSize[i]=0; //initialize EncodePacketSize
	
	for(i=0;i<7;i++)
	{
		ResponseTimeArray[i] = 0.0;
		ReceivedItemNum[i] = 0;
	}
	
	/* random item size distribution */
	double TotalItemSize = 0.0;
	
	for (i=0; i<DBSIZE;i++)
	{
	DownloadDataItemSize[i]=DWNSIZEMIN + uniform(0.0, 1.0)*(DWNSIZEMAX-DWNSIZEMIN+1);
	TotalItemSize += DownloadDataItemSize[i];
	}
	AverageDataItemSize = TotalItemSize/(double)DBSIZE;

	TH =(double)DWNSIZEMAX / 3 ;


	server();

	for(i = 1; i <= NUMCLIENT; i++)
	{
		client(i); // initiate process cust		
	}
      


       done->wait();	// wait until all done
      /* converged.wait();*/
	tbldeadlinemissrate =tblend->mean();
	double DeadlineMissRate = DeadlineMissNum /(double)(DeadlineMissNum + SatisfyNum);
	double tblAvgEncodedLength = tblEncodeNum->mean();
	double AvgEncodedLength = TotalEncodedNum/(double)BroadcastNum;
	double AvgResponseTime = TotalResponseTime/(double)SatisfyNum;
	double tblAvgResponseTime = tblResponseTm->mean();
	double AvgStretch = TotalResponseTime/TotalServiceTime;
	double tblAvgStretch = tblStretch->mean();
	double AvgProductivity =  SatisfyNum/(double)BroadcastNum;
	double SavedBandwidth = (satisfieditem- BroadcastNum) * 1.0 / satisfieditem;

	fprintf(fp, "The environment parameters are as bellows:\n");
	fprintf(fp, "\n");
	fprintf(fp, "IATM= %d; DBSIZE = %d ; NUMCLIENT = %d ; THETA = %.2f,CACHESIZE=%d, BstCycle= %d \n", IATM, DBSIZE, NUMCLIENT, THETA,CACHESIZE, CYCLE);
	fprintf(fp, "DNMIN = %d ; DNMAX = %d; LMIN = %.2f ; LMAX = %.2f\n",
		     DNMIN, DNMAX, LMIN, LMAX);
	fprintf(fp, "The Current Time is : %.2f, the Broacast Number is : %d\n", clock, BroadcastNum);
	fprintf(fp, "\n");

	report(); // print report of csim
	//fprintf(fp1,"%f\n", tbldeadlinemissrate);
	for(i=1;i<7;i++)
	//fprintf(fp1, "%f\t", ResponseTimeArray[i]/ReceivedItemNum[i]);
	//fprintf(fp1, "%d\n", DWNSIZEMAX);
	
	for(i=0;i<=10;i++)
	//fprintf(fp2,"%f\t", EncodePacketSize[i]/(double)BroadcastNum);
	//fprintf(fp2,"%d\n", DWNSIZEMAX);


	//fprintf(fp2,"%f\n",(satisfieditem- BroadcastNum) * 1.0 / satisfieditem);
	//fprintf(fp3,"%f\n",SatisfyNum*1.0/BroadcastNum);
	fprintf(fp, "Deadline Missed Number = %d;\n", DeadlineMissNum);
	fprintf(fp, "Deadline Satisfied Number = %d;\n", SatisfyNum);
	fprintf(fp, "Deadline Miss Rate = %.3f;\n", DeadlineMissNum * 1.0 / (DeadlineMissNum + SatisfyNum));
	fprintf(fp,"average productivity per broadcast = %.4f\n", SatisfyNum*1.0/BroadcastNum);
	fprintf(fp, "Request Data Item Number = %d;\n", SumOfRequestData);
	fprintf(fp, "Broadcast Data Item Number = %d;\n", BroadcastNum);
	
	fprintf(fpResult,"%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%d\n", tbldeadlinemissrate, DeadlineMissRate, tblAvgResponseTime, AvgResponseTime, tblAvgStretch, AvgStretch, tblAvgEncodedLength, AvgEncodedLength, AvgProductivity, SavedBandwidth, DWNSIZEMAX);
	
	
	printf("simulation over!");
}

void server()
{
	struct Decodeset *currentbroadcast; 
	int i,j, encodeNum;
	create("server");

	//printf("server started!\n");
	i=0;
	while (cnt>0)
	{
		
		if(decodesethead->Next==NULL)
		{
			hold(expntl(0.01));
			ChooseData();
		}
		else
		{
			if(i==0)
			{
				currentbroadcast=decodesethead->Next;
			}
			if(currentbroadcast!=NULL)
			{
				
				encodeNum=0;
				encodeNum=EncodeNum(currentbroadcast->decode);
				tblEncodeNum->record(encodeNum);
				TotalEncodedNum += encodeNum;
				CalculatingDistribution(encodeNum);
				BeginBstTime=clock;
				BroadcastNum++;
				i++;
				for(j=0;j<800;j++)
				{
					decode[j]=make_pair(0,0);
				}


				GenerateDecodeset(encodedata,encodeNum,currentbroadcast->decode);
				UpdateData(decode);
				currentbroadcast=currentbroadcast->Next;

				//Change for finding max data size in a clique

				double mds=0;
				for(int x=0;x<20;x++)
				{
					if( encodedata[x] >= 0 && mds < DownloadDataItemSize[encodedata[x]]){
						mds = DownloadDataItemSize[encodedata[x]];
					}
				}

				//hold(1.0); // hold service time
				hold(mds/(double)BANDWIDTH);

				//cout<<maxDATASIZE;
				broadcast->set(); 
			}
			else
			{
				i=0;
				init_broadcastset();
			}
		}

	}
}

int EncodeNum(pair <int, int> decode[800] )
{
	int Number,i, j,DataID,repeatFlag;
	for(i=0;i<20;i++)
	{
		encodedata[i]=-1;

	}
	Number=0;
	
	for(i=0;i<800;i++)
	{
		if(decode[i].first!=0)
		{
			DataID=decode[i].second;
			repeatFlag=0;
			if(encodedata[0]==-1)
			{
				encodedata[0]=DataID;
				Number++;
			}
				
			for(j=0;j<Number;j++)
			{
				if(DataID==encodedata[j]) // a repeated one 
				{
					repeatFlag=1;
					break;

				}

			}
			if(repeatFlag==0)
			{
				encodedata[Number++]=DataID;

			}
		}
		else
			break;

	}
	return Number;
}



void CalculatingDistribution(int encodeNum)
{
if(encodeNum == 0)
	EncodePacketSize[0]++;
else if(encodeNum == 1)
	EncodePacketSize[1]++;
else if(encodeNum == 2)
	EncodePacketSize[2]++;
else if(encodeNum == 3)
	EncodePacketSize[3]++;
else if(encodeNum == 4)
	EncodePacketSize[4]++;
else if(encodeNum == 5)
	EncodePacketSize[5]++;
else if(encodeNum == 6)
	EncodePacketSize[6]++;
else if(encodeNum == 7)
	EncodePacketSize[7]++;
else if(encodeNum == 8)
	EncodePacketSize[8]++;
else if(encodeNum == 9)
	EncodePacketSize[9]++;
else 
	EncodePacketSize[10]++;
}//End void CalculatingDistribution(int encodeNum);



void client(long ClientID)
{
	TIME	arrivalTime, requestDeadline, relativeDeadline, ResponseTime, Clock_Time;
	long		reqDataID,result;
	int		i, j, m, n, notSatisfy, dataNum, acceptedNum,NPMR, temp,UnservedNum,Requestcount, stremstatus;
	int		dataSet[DNMAX][2];
	double	tempProb, tempProb1,f, Stretch, ServiceTime;
	int		repeatFlag,cachesize;
	int      incacheFlag,s,availablecacheNum;
	struct  ClientCacheitem*CurrentItem, *pre,*p,*newdata; 
	struct  Request  * CurrentRequest;

	    create("request"); // required create statement
	    /*printf("%d request  of client %d started!\n", ClientID,Requestcount);*/
	for(s=1;s<=NRPC;s++)
	{
		IATM = 100/AverageDataItemSize;//20
		f=1.0/IATM;
		hold(expntl(f));
		NPMR=0;
		notSatisfy = 1;
		Requestcount=s;
		arrivalTime = clock; // time of request
		//dataNum = (int)(uniform(DNMIN*1.0, DNMAX*1.0)/1);
		tempProb1 = uniform(DNMIN*1.0, DNMAX*1.0);
		temp=(int)tempProb1;
		tempProb1=tempProb1-temp;
		if(tempProb1>0.5)
			dataNum=temp+1;
		else
			dataNum=temp;
		 //relativeDeadline = (1 + uniform(LMIN, LMAX))/ BANDWIDTH;
		
		//relativeDeadline = (1 + uniform(LMIN, LMAX)) * uniform(DNMIN, DNMAX)*1.0;
		//requestDeadline = clock + relativeDeadline;
		
		UnservedNum=dataNum;
		for(j=0;j<DBSIZE;j++)
		{
                recv[ClientID-1][j]=-1;
		}
		m = 0;
		/*Generateclientcache(ClientID);*/
		while (m < dataNum)
		{
			repeatFlag = 0;
			incacheFlag=0;
			Clock_Time = clock;
			tempProb = uniform(0.0, 1.0);

			/* choose a data object based on zipf distribution */
			for (j = 0; j < DBSIZE; j++)
			{
				if (j == 0 && tempProb <= ZIPF[j])
				{
					reqDataID = j;
					break;
				}
 
				if (tempProb <= ZIPF[j] && tempProb > ZIPF[j-1]) 
				{
					reqDataID = j;
					break;
				}
			}
			
					dataSet[m][0] = reqDataID;
					dataSet[m][1] = 0;
					m++;
	
		}//End while
		
		stremstatus = stream_state(NIL);

		relativeDeadline = (1 + uniform(LMIN, LMAX)) * (DownloadDataItemSize[dataSet[0][0]]/(double)BANDWIDTH);
		requestDeadline = clock + relativeDeadline;
		
		
		UnservedNum=dataNum;
		cachehead[ClientID-1]->Next=NULL; // initial cache, generate new cache content.
		m=0;
		for(i=0;i<dataNum;i++)
		{
			if(dataSet[i][1]==0)
			{
				Generatecache(ClientID, dataSet[i][0]);
				m++;
			}
				
			else
			{
				newdata=(struct ClientCacheitem *)malloc(sizeof(struct ClientCacheitem));
				newdata->DataID=dataSet[i][0];	
				repeatFlag=0;
				pre=cachehead[ClientID-1];
				p=cachehead[ClientID-1]->Next;
				while(p!=NULL)
	   			{
					if(dataSet[i][0]==p->DataID)
					{	
			   			repeatFlag=1;
			   			break;
					}
					pre=pre->Next;
					p=p->Next;
	   			}	
			
			/* ok, a fresh one, add it into cache! */
				if (repeatFlag == 0)
				{
					newdata=(struct ClientCacheitem *)malloc(sizeof(struct ClientCacheitem));
					newdata->DataID=dataSet[i][0];
					pre=cachehead[ClientID-1];
					p=cachehead[ClientID-1]->Next;
					while(p!=NULL)
	    			{

						pre=pre->Next;
						p=p->Next;
	    			}
	   				pre->Next=newdata;
	  				newdata->Next=NULL;	
					m++;
					recv[ClientID-1][dataSet[i][0]]=1;
				}
				
			}
		
		}
		AdditionalCacheGeneration(ClientID, m);
		SumOfRequestData += UnservedNum;	
		/*printf("client %d --> send request No.%d\n", ClientID, Requestcount);*/
	
		EDF_EnterQueue(ClientID,Requestcount, arrivalTime, requestDeadline, dataNum, dataSet, UnservedNum);
		acceptedNum = 0;

		/* listen to the broadcast channel util satisfied */
		while (notSatisfy)
		{
			broadcast->wait();
			/*
			result = broadcast->timed_wait(relativeDeadline);
			
			if (result == TIMED_OUT) //timeout, miss the deadline
			{
				notSatisfy = 0;
				CurrentRequest=head->Next;
				while(CurrentRequest!=NULL)
				{

					if(CurrentRequest->ClientID==ClientID&&CurrentRequest->Requestcount==Requestcount)
					{
						for(j=0;j<CurrentRequest->DataNum;j++)
						{
							if(CurrentRequest->DataSet[j][1]==0)
							{
					 			temperature[dataSet[j][0]]-=1;
								recv[ClientID-1][dataSet[j][0]]=-1;
								NPMR++;
							 }

						}
						
						break;
						
					}	
				CurrentRequest=CurrentRequest->Next;
				}
				EDF_DeleteQueueByClientID(ClientID,Requestcount);
				cachehead[ClientID-1]->Next=NULL;
				DeadlineMissNum++;
				if(--cnt == 0) done->set(); // if last arrival, signal
				
			} */
		  // else
		   //{
			CurrentRequest=head->Next;
			while(CurrentRequest!=NULL)
			{

				if(CurrentRequest->ClientID==ClientID&&CurrentRequest->Requestcount==Requestcount)
				{

					if(CurrentRequest->UnservNum==0)
					{
						notSatisfy = 0;
						ResponseTime = clock-arrivalTime;
						ResponseTimeDistribution(dataSet[0][0], ResponseTime);
						TotalResponseTime += ResponseTime;
						ServiceTime = DownloadDataItemSize[dataSet[0][0]]/(double)BANDWIDTH;
						TotalServiceTime += ServiceTime;

						Stretch = ResponseTime/(double)ServiceTime;
						satisfieditem=satisfieditem+dataNum;
						EDF_DeleteQueueByClientID(ClientID,Requestcount);
						cachehead[ClientID-1]->Next=NULL;
						SatisfyNum++;
						//printf("client %d --> request No.%d satisfied!\n", ClientID, Requestcount);
						/*tblStretch->record((clock - arrivalTime) /dataNum);*/
						//tblServeTime->record(clock - fbroadcast); // record sevince  time
						tblResponseTm->record(ResponseTime);
						tblStretch->record(Stretch);
						tblend->record(DeadlineMissNum * 1.0 / (DeadlineMissNum + SatisfyNum));
						
						if(--cnt == 0)   
						{
							printf("count is zero!\n");
							done->set(); // if last arrival, signal

						}

					}
					/*else
					{
						relativeDeadline = requestDeadline - clock;

					} */
					break;

				}
				CurrentRequest=CurrentRequest->Next;
			}
		//}//End else
	   }//End while (notSatisfy)

	}
}//End void Client()

void ResponseTimeDistribution(int ReceivedItem, double ResponseTime)
{
if(ReceivedItem < 100)
{
ResponseTimeArray[1] += ResponseTime;
ReceivedItemNum[1]++;
}
if(ReceivedItem < 200)
{
ResponseTimeArray[2] += ResponseTime;
ReceivedItemNum[2]++;
}
if(ReceivedItem < 400)
{
ResponseTimeArray[3] += ResponseTime;
ReceivedItemNum[3]++;
}
if(ReceivedItem < 600)
{
ResponseTimeArray[4] += ResponseTime;
ReceivedItemNum[4]++;
}
if(ReceivedItem < 800)
{
ResponseTimeArray[5] += ResponseTime;
ReceivedItemNum[5]++;
}
if(ReceivedItem < 1000)
{
ResponseTimeArray[6] += ResponseTime;
ReceivedItemNum[6]++;
}
}//End void ResponseTimeDistribution(int, double ResponseTime)


void Generateclientcache(long ClientID) // initialize a head pointor of client cache queue, real cached data starts from  cachehead->Next
{
	int j,m, repeatFlag;
	double tempProb;
	long cachedID,reqDataID;
	struct ClientCacheitem *newdata,*pre,*p;
		m = 0;
		while (m < CACHESIZE)
		{
			repeatFlag = 0;
			
			tempProb = uniform(0.0, 1.0);

			/* choose a data object based on zipf distribution */
			for (j = 0; j < DBSIZE; j++)
			{
				if (j == 0 && tempProb <= Unifm[j])
				{
					reqDataID = j;
					break;
				}
 
				if (tempProb <= Unifm[j] && tempProb > Unifm[j-1]) 
				{
					reqDataID = j;
					break;
				}
			}

			/* check whether it is in the client's cache*/
			pre=cachehead[ClientID-1];
			p=cachehead[ClientID-1]->Next;
			while(p!=NULL)
	   		 {
                    		cachedID= p->DataID;
				if(reqDataID==cachedID)
				{
			   		repeatFlag=1;
			   		break;
				}
				pre=pre->Next;
				p=p->Next;
	   		}
			
			/* ok, a fresh one, add it into cache! */
			if (repeatFlag == 0)
			{
					newdata=(struct ClientCacheitem *)malloc(sizeof(struct ClientCacheitem));
					newdata->DataID=reqDataID;
					pre=cachehead[ClientID-1];
					p=cachehead[ClientID-1]->Next;
					while(p!=NULL)
	    				{

						pre=pre->Next;
						p=p->Next;
	    				}
	   				pre->Next=newdata;
	  				newdata->Next=NULL;
					m++;
				
			}
		}
}



int Generatecache(long ClientID, int DataID)
{
	struct  ClientCacheitem*pre,*p,*newitem; 
	int i,m,repeatFlag; //the initial number of data items in a client's cache
	int Dataset[2];
	double temp;
	/*temp=uniform(0,1);
	
	if(DataID%2==0)
	{
		if(DataID==0)
		{
			Dataset[0]=DataID+1;
			Dataset[1]=DataID+2;
		}

		if(temp<=0.5)
		{
			Dataset[0]=DataID-1;
			Dataset[1]=DataID-2;
		}
		else
		{
			Dataset[0]=DataID+1;
			Dataset[1]=DataID+2;

		}

	}
	else
	{
		Dataset[0]=DataID-1;
		Dataset[1]=DataID+1;

	}*/

	Dataset[0]=DataID-1;
	Dataset[1]=DataID+1;	

	for(i=0;i<2;i++)
	{
		if(Dataset[i]>=0&&Dataset[i]<=DBSIZE-1)
		{
			repeatFlag=0;
			pre=cachehead[ClientID-1];
			p=cachehead[ClientID-1]->Next;
			m=0;
			while(p!=NULL)
			{
				if(p->DataID==Dataset[i])
				{
					repeatFlag=1;
					//break;
				}
				pre=pre->Next;
				p=p->Next;
				m++;
			}
			
			if(repeatFlag==0)
			{
				if(m<CACHESIZE)
				{
					newitem= (struct ClientCacheitem *)malloc(sizeof(struct ClientCacheitem));
					newitem->DataID=Dataset[i];
					pre->Next=newitem;
					newitem->Next=NULL;
					m++;
					recv[ClientID-1][Dataset[i]]=1;

				}
			}
			
		}
		else
			continue;
		
	}
	return m;
}


int AdditionalCacheGeneration(long ClientID,int m)
{
	int j,repeatFlag;
	double tempProb;
	long cachedID,reqDataID;
	struct ClientCacheitem  *newdata,*pre,*p;

	while (m < CACHESIZE)
	{
			repeatFlag = 0;
			
			tempProb = uniform(0.0, 1.0);

			/* choose a data object based on zipf distribution */
			for (j = 0; j < DBSIZE; j++)
			{
				if (j == 0 && tempProb <= Unifm[j])
				{
					reqDataID = j;
					break;
				}
 
				if (tempProb <= Unifm[j] && tempProb > Unifm[j-1]) 
				{
					reqDataID = j;
					break;
				}
			}

			/* check whether it is in the client's cache*/
			pre=cachehead[ClientID-1];
			p=cachehead[ClientID-1]->Next;
			while(p!=NULL)
	   		 {
                    		cachedID= p->DataID;
				if(reqDataID==cachedID)
				{
			   		repeatFlag=1;
			   		break;
				}
				pre=pre->Next;
				p=p->Next;
	   		}
			
			/* ok, a fresh one, add it into cache! */
			if (repeatFlag == 0)
			{
					newdata=(struct ClientCacheitem *)malloc(sizeof(struct ClientCacheitem));
					newdata->DataID=reqDataID;
					pre=cachehead[ClientID-1];
					p=cachehead[ClientID-1]->Next;
					while(p!=NULL)
	    				{

						pre=pre->Next;
						p=p->Next;
	    				}
	   				pre->Next=newdata;
	  				newdata->Next=NULL;
					recv[ClientID-1][reqDataID]=1;
					m++;
				
			}
		}
return m;
}
void init_queue()
{
	/* initialize a head pointor of request queue, real request starts from head->next */
	int i;
	struct Request * newRequest;

	newRequest = (struct Request *)malloc(sizeof(struct Request));

	newRequest->ClientID = -1;
	newRequest->Requestcount = -1;
	newRequest->ArrivalTime = -1;
	newRequest->Deadline = -1;
	newRequest->DataNum = -1;
	newRequest->DataSize = -1.0;

	for (i = 0; i < DNMAX; i++)
	{
		newRequest->DataSet[i][0] = -1;
		newRequest->DataSet[i][1] = -1;
	}
	newRequest->UnservNum=-1;
	newRequest->Priority=-1;
	newRequest->Next = NULL;

	head = newRequest;
}

void init_clientcache() // initialize a head pointor of client cache queue, real cached data starts from  cachehead->Next
{
	int i;
	struct ClientCacheitem * newitem[MaxNUMCLIENT];

	for(i=0;i<NUMCLIENT;i++)
	{
		newitem[i]= (struct ClientCacheitem *)malloc(sizeof(struct ClientCacheitem));
		newitem[i]->DataID=-1;
		newitem[i]->Next=NULL;
		cachehead[i]=newitem[i];
	}

}

void init_decodeset()  // initialize  a head pointor of decode request queue. 
{
   struct Decodeset* newRequest;
   int i;
  
   newRequest= (struct Decodeset*)malloc(sizeof(struct Decodeset));
   for(i=0;i<800;i++)
   {
	newRequest->decode[i]=make_pair(-1,-1);

   }
   newRequest->Next=NULL;
   decodesethead=newRequest;
   

}


void init_broadcastset()
{

	decodesethead->Next=NULL;

}

void EDF_EnterQueue(long ClientID, long Requestcount, TIME ArrivalTime, TIME RequestDeadline,
					int DataNum, int Item[DNMAX][2], int Unserved)
{
	struct Request *pre,*p;
	int	   i;
	struct Request *newRequest;

	newRequest=(struct Request *)malloc(sizeof(struct Request));
	newRequest->ClientID = ClientID;
	newRequest->Requestcount = Requestcount;
	newRequest->ArrivalTime = ArrivalTime;
	newRequest->Deadline = RequestDeadline;
	newRequest->DataNum = DataNum;
	newRequest->UnservNum=Unserved;
	newRequest->DataSize = DownloadDataItemSize[Item[0][0]];

	
	for (i = 0; i < DataNum; i++)
			{
				newRequest->DataSet[i][0] = Item[i][0];
				newRequest->DataSet[i][1] = Item[i][1];

				if(Item[i][1]==0)
				{
				temperature[Item[i][0]]+=1;
				recv[ClientID-1][Item[i][0]]=0;

				}
			}
	pre = head;
	p = head->Next;
while (p != NULL)
	{

		if (p->Deadline != -1 && p->Deadline > RequestDeadline)
		{
			
			newRequest->Next = p;
			pre->Next = newRequest;

			/*printNewRequest(newRequest);
			printRequestQueue();*/
			return;
		}

		pre = pre->Next;
		p = p->Next;
	}

	newRequest->Next = NULL;
	pre->Next = newRequest;

	/*printNewRequest(newRequest);
	printRequestQueue();*/
}

void EDF_DeleteQueueByClientID(long ClientID,long Requestcount)
{
	struct Request *q, *pre;

	pre = head;
	q = head->Next;

	while (q != NULL)
	{
		if ((q->ClientID == ClientID)&&(q->Requestcount== Requestcount))
		{
			pre->Next = q->Next;
			free(q);
			return;
		}
		q = q->Next;
		pre = pre->Next;
	}
}

void ChooseData()
{
	struct Request * currentReq;
	struct Request * selectedRequest;
	long tempDataID = 0;
	double requestPriority = 0;
	double Pri ,MaxPri; // LT is the slack time of a request, TEMP is the popularity of a request, STARVA is the factor cause starvation.
	int dataMaxTemperature = 0; // number of unsatisfied requests in the request list
	long TEMPER, selectedRev,selectedDataID,cliquesize;
	TIME WaitingTime;	
	int k,t;
	int s=0;
	int i,j,p,DataID, select;
	pair <int, int> vex[3000], subvex[3000];
	int G[1000][1000];
	vector <int> vec;
	vector <int>::iterator itor;    
	pair <int, int> decode[800];
	//selected request's location in recv[]
	selectedRev=-1;
	selectedRequest=NULL;
	currentReq = head->Next;
	MaxPri=-1;
	selectedDataID = -1;

	// generate vetex
	k=0;
	t=0;
	for(i=0;i<NUMCLIENT;i++)
	{                                     // r is the number of request
		for(j=0;j<DBSIZE;j++)
		{                                  // m is the number of items                            
			if(recv[i][j]==0)
			{                                 // If request i wants item j, then there exists a vertex v_{ij} in G
					
				vex[k++] = make_pair (i,j);   
							// Put all vertices to a array vex
			}//if                                              // recv[i][j]=0, request i wants item j
		}//for                                                 // recv[i][j]=1, request i has item j
	}//for


	//selected request's location in recv[]

	currentReq = head->Next;
	while(currentReq != NULL)
	{
		
		Pri=0;
		WaitingTime=-1;
//8.8 Deadline
		if (currentReq->UnservNum != 0)
		//if ((currentReq->UnservNum != 0)&&((currentReq->Deadline-clock)>1.0))//if current request is not served， and its relative-deadline is larger than 1 (service time)
		{
				
				WaitingTime=clock - currentReq->ArrivalTime;
				selectedRev=currentReq->ClientID-1;
				DataID=currentReq->DataSet[0][0];
				for(i=0;i<k;i++)
				{
					if(vex[i].first==selectedRev&&vex[i].second==DataID)
					{
						p=i;
						break;
					}
				}

		for(i=0;i<t;i++)
		{
			subvex[i]=make_pair(0,0);
			for(j=0;j<t;j++)
			{
					G[i][j]=0;
			}

		}


		/// Changes for Thershold

		//find the vertices that connected to the selected vertex
		select=p;
		t=0;
		int ll=vex[select].first;                                   // the first subscript fo vertex (request id), client ll
		int lr=vex[select].second;
		double DS1 = DownloadDataItemSize[lr];
		subvex[t++]=make_pair (vex[select].first,vex[select].second); 
		for(int j=0;j<k;j++){
			int rl=vex[j].first;                           // request rl
			int rr=vex[j].second;// item rr, client rl wants item rr
			double DS2 = DownloadDataItemSize[rr];
			if(ll!=rl)
			{
				if(lr!=rr){
					
					//fprintf(fp," %d  %.2f\n", lr, x1);
					//fprintf(fp," %d  %.2f\n", rr, x3);
					if((recv[ll][rr]==1&&recv[rl][lr]==1) && ((DS2-DS1) < TH) ) //change for TH  
						subvex[t++]=make_pair (vex[j].first,vex[j].second); // request ll wants item lr, it has item rr; request rl wants item rr, it has item lr
						                           // (v_{ll,lr}, v_{rl,rr}) is an edge
				}
				else if(lr==rr){
					if(recv[ll][lr]==0&&recv[rl][rr]==0)       // request ll wants item lr, request rl wants item rr, (rr=lr)
						subvex[t++]=make_pair (vex[j].first,vex[j].second);                          // (v_{ll,lr}, v_{rl,rr}) is an edge
				}
			}
			
			}//for


		// generate graph G according to the selected vertex
		for(i=0;i<t;i++){                                 
		int ll=subvex[i].first;                                   // the first subscript fo vertex (request id), client ll
		int lr=subvex[i].second;                                  // the first subscript fo vertex (item id), packet lr
		for(int j=0;j<t;j++){
			if(i==j)
				G[i][j]=0;                                     
			else{
				int rl=subvex[j].first;                           // request rl
				int rr=subvex[j].second;                          // item rr, client rl wants item rr
				G[i][j]=0;
				if(lr!=rr){
					if(recv[ll][rr]==1&&recv[rl][lr]==1)       // request ll wants item lr, it has item rr; request rl wants item rr, it has item lr
						G[i][j]=1;                             // (v_{ll,lr}, v_{rl,rr}) is an edge
				}
				else if(lr==rr){                               
					if(recv[ll][lr]==0&&recv[rl][rr]==0)       // request ll wants item lr, request rl wants item rr, (rr=lr)
						G[i][j]=1;                             // (v_{ll,lr}, v_{rl,rr}) is an edge
				}
			}//else
		}//for
	}//for
		

	// find the maximum clique of the selected vertex

	DataID=subvex[0].second;	
	select=0;
	vec.push_back(0);   // put the selected vertex in the vector
	
 		int times=1;
		while(times>0){
		int tag;
		int maxm=0;
		int sj=-1;
		int may=0;
		for( j=0;j<t;j++){
			tag=0;
			if(G[select][j]==1){
				if(find(vec.begin(),vec.end(),j)!=vec.end()) //
					continue;
				int ttag=0;
				for(itor=vec.begin();itor!=vec.end();itor++){
							if(G[j][(*itor)]!=1){               // If a new vertex does not connect to all the vertices in the queue, discard this new vertex            
								ttag=1;
								break;
							}//if
						}//for
				if(ttag==1)
					continue;
				may=0;
				for(int r=0;r<t;r++){                                        // find the neighbor of j
					if(G[j][r]==1){
						if(find(vec.begin(),vec.end(),r)!=vec.end())
							continue;
						 tag=0;
						for(itor=vec.begin();itor!=vec.end();itor++){
							if(G[r][(*itor)]!=1){                          // If a new vertex does not connect to all the vertices in the queue, discard this new vertex
								tag=1;
								break;
							}//if
						}//for
						if(tag==0){                                        //If a new vertex connects to all the vertices in the queue, this new vertex is added to the queue
							may++;
						}//if
					}//if
				}//for
				if(may>=maxm){
					sj=j;
					maxm=may;
				}//if
			}//if
			
		}//for		
		if(sj!=-1)
		vec.push_back(sj);
		times=maxm;
		select=sj;
	    }//while
	cliquesize=vec.size();

	
     //Pri=SIN_Weight(vec,subvex)*cliquesize;//Original implementation of SIN
	
	//Pri = FCFS_Weight(vec,subvex); //FCFS implementation
	//Pri = MRF_Weight(vec,subvex);//MRF implementation	  
	 //Pri=LWF_Weight(vec,subvex); //LWF implementation
	//Pri=RW_Weight(vec,subvex); //RW implementation
	//Pri=EDF_Weight(vec,subvex); //EDF implementation
	//Pri = SIN_Weight(vec,subvex);	//SIN implementation
	//Pri = LTSF_Weight(vec,subvex); //LTSF implementation 
	Pri = STOBS_Weight(vec,subvex); //STOBS implementation

	if(Pri>MaxPri)
	  {
		MaxPri=Pri;
		for(i=0;i<cliquesize;i++)
		{
			decode[i]=make_pair(0,0);
		}
		 s=0;
	 	for(itor=vec.begin();itor!=vec.end();itor++)
	  	{
			decode[s++]=make_pair(subvex[(*itor)].first+1,subvex[(*itor)].second);
			  
		}
		selectedDataID=subvex[0].second;
	  }	
	  vec.clear();
				
	}//end if (currentReq->UnservNum != 0) //if current request is not served
				
	  currentReq = currentReq->Next;	

	}// while

	FinalBrodcast(selectedDataID,decode,s);
}
	
/*
double SIN_Weight(vector <int> selectvec, pair <int, int> vex[2000])//calculate the sum of the weight in the maximum clique
{
	struct Request * currentReq;

	TIME Deadline=0;
	double slacktime=0;

	double requestWeight = 0;
    double SumWeight = 0;
    int i=0;
	int cliquesize=selectvec.size();
	
	maxDATASIZE=1;//int maxDATASIZE; /// global variable 
	double currentDATASIZE=1;
	
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
				
				if(currentDATASIZE>maxDATASIZE)//12.22-current datasize of one request in the chosen clique
				maxDATASIZE=currentDATASIZE;
				

	            if(slacktime==0)
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

    return SumWeight;
}

*/

/*

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
} */

void FinalBrodcast(long DataID ,pair <int, int> decode[800],int k)
{
    struct Request * currentReq;
     struct Decodeset *newdecode,*pre,*p;
	pair <int, int> decode1[800];
	int i,sum,j;
	sum=0;
	
////Changed by Ali///////////
	//if(decode[0].first == 0)
	if(DataID == -1)
		{
		decodesethead->Next = NULL;
		return;
		}
//////////////////////////////////////

	currentReq=head->Next;
        while(currentReq!=NULL)
        {
		for (i = 0; i < currentReq->DataNum; i++)
		{

			if(currentReq->DataSet[i][0]==DataID&&currentReq->DataSet[i][1]==0)
			{
				decode1[sum++]=make_pair(currentReq->ClientID,DataID);	 
                            break;

			}


		}
	
		currentReq=currentReq->Next;
       }

     if(k>=sum)
     	{
           newdecode=(struct Decodeset*)malloc(sizeof(struct Decodeset));
	    for(j=0;j<800;j++)
	    {
		newdecode->decode[j]=make_pair(0,0);	
	     }
 		for(j=0;j<k;j++)
 		{
			newdecode->decode[j]=decode[j];
		}

		pre=decodesethead;
		pre->Next=newdecode;
		newdecode->Next=NULL;
		UpdateCache(newdecode->decode);


	 }
	 else
	 {
		
		newdecode=(struct Decodeset*)malloc(sizeof(struct Decodeset));
	    for(j=0;j<800;j++)
	    {
		newdecode->decode[j]=make_pair(0,0);	
	     }
 		for(j=0;j<sum;j++)
 		{
			newdecode->decode[j]=decode1[j];
		}
		pre=decodesethead;
		pre->Next=newdecode;
		newdecode->Next=NULL;
		UpdateCache(newdecode->decode);
	 }
}


//void VisualUpdateData(pair <int, int> decode[500] )
//{
//	struct SelRequest * currentReq, *p;
//	struct ClientCacheitem *currentitem;
//	struct DecodeRequest * currdecodeReq;
//	int i ,j= 0 ;
//	long ClientID, DataID;
//
//	
//	for(j=0;j<100;j++)
//	{
//		if(decode[j].first!=0)
//		{
//			ClientID=decode[j].first;
//			DataID=decode[j].second;
//			currentReq = Thead->Next;
//			while (currentReq!= NULL)
//			{
//				 if(ClientID==currentReq->ClientID)//the request status need to be updated
//                 		{
//
//					for (i = 0; i < currentReq->DataNum; i++)
//					{
//
//						if (currentReq->DataSet[i][0] ==DataID&&currentReq->DataSet[i][1]==0)
//						{
//							currentReq->DataSet[i][1] = 1; //tag the request as served	
//							faketemperature[DataID]--;
//							currentReq->UnservNum-=1;
//							break;
//						}
//
//		        		}
//
//			
//                 	       }
//				
//					 if(currentReq->UnservNum==0)
//					 {
//							p=currentReq;
//							currentReq=currentReq->Next;
//						 DeleteTQueueByClientID(p->ClientID,p->Requestcount);
//					 }
//					 else
//							 currentReq=currentReq->Next;
//                     }
//		}
//		else
//		{
//			break;
//		}
//				
//	}
//		
// }
//	    
//void DeleteTQueueByClientID(long ClientID,long Requestcount)
//{
//	struct SelRequest *q, *pre;
//
//	pre = Thead;
//	q = Thead->Next;
//
//	while (q != NULL)
//	{
//		if ((q->ClientID == ClientID)&&(q->Requestcount== Requestcount))
//		{
//			pre->Next = q->Next;
//			free(q);
//			return;
//		}
//		q = q->Next;
//		pre = pre->Next;
//	}
//}

void UpdateCache(pair <int, int> decode[800] )
{
    
  struct DecodeRequest * curdecodeReq;
  struct ClientCacheitem*  newcacheitem, *pre, *p;
  long cachedID,ClientID, DataID;

  int flag,j;
  
  for(j=0;j<800;j++)
{
	if(decode[j].first!=0)
	{
		ClientID=decode[j].first;
		DataID=decode[j].second;
	  	 newcacheitem=(struct ClientCacheitem*)malloc(sizeof(struct ClientCacheitem));
	    	newcacheitem->DataID=DataID;
	    	pre=cachehead[ClientID-1];
           	p=pre->Next;
	    	while(p!=NULL)
	    	{
			pre=pre->Next;
			p=p->Next;
	    	}
	   	pre->Next=newcacheitem;
	  	newcacheitem->Next=NULL;
	}
		
	//}   
	else
	{
		break;
	}
  }
    
}





void UpdateData(pair <int, int> decode[800] )
{
	struct Request * currentReq;
	struct ClientCacheitem *currentitem;
	struct DecodeRequest * currdecodeReq;
	int i ,j= 0 ;
	long ClientID, DataID;

	currentReq = head->Next;
	
	
	for(j=0;j<800;j++)
	{
		if(decode[j].first!=0)
		{
			ClientID=decode[j].first;
			DataID=decode[j].second;
			
			currentReq = head->Next;
			while (currentReq != NULL )
			{
				 if(ClientID==currentReq->ClientID)//the request status need to be updated
                 		{

					for (i = 0; i < currentReq->DataNum; i++)
					{

						if (currentReq->DataSet[i][0] ==DataID&&currentReq->DataSet[i][1]==0)
						{
							currentReq->DataSet[i][1] = 1; //tag the request as served	
							temperature[DataID]--;
							recv[ClientID-1][DataID]=1;
							currentReq->UnservNum-=1;
							break;
						}

		        		}

			
                 	       }
			     currentReq=currentReq->Next;
                     }
		}
		else
		{
			break;
		}
				
	}
		
 }


void Updateremain(pair <int, int> decode[800], pair <int, int> decode2[800])
{
     struct DecodeRequest * curdecodeReq;
  struct ClientCacheitem*  newcacheitem, *pre, *p;
  long cachedID,ClientID, DataID;
  int i,j,flag;
  for(i=0;i<800;i++)
  {
	if(decode[i].first!=0)
	{
		flag=0;
		for(j=0;j<800;j++)
		{
			if(decode[i].first==decode2[j].first&&decode[i].second==decode2[j].second&&decode2[j].first!=-1) //if the content is same 
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			
			ClientID=decode[i].first;
			DataID=decode[i].second;
		newcacheitem=(struct ClientCacheitem*)malloc(sizeof(struct ClientCacheitem));
	    	newcacheitem->DataID=DataID;
	    	pre=cachehead[ClientID-1];
           	p=pre->Next;
	    	while(p!=NULL)
	    	{
			pre=pre->Next;
			p=p->Next;
	    	}
	   	pre->Next=newcacheitem;
	  	newcacheitem->Next=NULL;
  		}	
	}
	else
	{
		break;
	}	
	
}
}


void GenerateDecodeset(int encode[20],int encodeNum, pair <int, int> predecode[800])
{
	int rl,ll,t,i,j;
	struct Request * currentReq;

	if(encodeNum==1)
	{
		t=0;
		currentReq=head->Next;
		while(currentReq!=NULL)
		{
			for(i=0;i<currentReq->DataNum;i++)
			{
				if(currentReq->DataSet[i][0]==encode[0]&&currentReq->DataSet[i][1]==0)
				{
						decode[t++]=make_pair(currentReq->ClientID,encode[0]);
						break;
				}
			}
			currentReq=currentReq->Next;
		}
	
	
	}
	if(encodeNum==2)
	{
	
		ll=encode[0];
		rl=encode[1];
		currentReq=head->Next;
		t=0;
		while(currentReq!=NULL)
		{
			if(recv[currentReq->ClientID-1][ll]==1&&recv[currentReq->ClientID-1][rl]==0) // ll is in the cache and rl is required 
			{	
				for(i=0;i<currentReq->DataNum;i++)
				{
					if(currentReq->DataSet[i][0]==rl&&currentReq->DataSet[i][1]==0)
					{
						decode[t++]=make_pair(currentReq->ClientID,rl);
						break;
					}
				}
									
			}
			if(recv[currentReq->ClientID-1][ll]==0&&recv[currentReq->ClientID-1][rl]==1) // rl is in the cache and ll is required
			{
				for(i=0;i<currentReq->DataNum;i++)
				{
					if(currentReq->DataSet[i][0]==ll&&currentReq->DataSet[i][1]==0)
					{
						decode[t++]=make_pair(currentReq->ClientID,ll);
						break;
					}
				}
										
			}
			currentReq=currentReq->Next;

	  }
  }
	if(encodeNum>2)
	{
		t=0;
		for(j=0;j<800;j++)
		{		
			if(predecode[j].first!=0)
			{
				decode[t++]=make_pair(predecode[j].first,predecode[j].second);
			}
		}

	}

}

void init_Zipf()
{
	int i; 
	double sum;

	sum = 0.0; 
	for (i =0 ; i < DBSIZE; i++)
	{
		if (i == 0)
			sum = sum + 1.0;
		else
			sum = sum + 1.0 / pow((double) i + 1.0, THETA);
	}

	for (i = 0; i < DBSIZE; i++)
	{
		if (i == 0)
			ZIPF[i] = 1.0 / sum;
		else
			ZIPF[i] = ZIPF[i-1] + 1.0 / (pow((double) i + 1.0 , THETA) * sum);
	}
}

void init_Unif()
{
	int i; 
	double sum;

	sum = 0.0; 
	for (i =0 ; i < DBSIZE; i++)
	{
		if (i == 0)
			sum = sum + 1.0;
		else
			sum = sum + 1.0 / pow((double) i + 1.0, BETA);
	}

	for (i = 0; i < DBSIZE; i++)
	{
		if (i == 0)
			Unifm[i] = 1.0 / sum;
		else
			Unifm[i] = Unifm[i-1] + 1.0 / (pow((double) i + 1.0 , BETA) * sum);
	}
}



void main(int argc, char* argv[])
{
	char trace[255];
	char outfile[255];
	char resultfile[255];
	char responsetimefile[255];
	char starvfile[255];
	char savebandwidthfile[255];
	char productfile[255];
	char efficiency[255];
	FORMAT_OUTFILE;
	FORMAT_RESPONSEFILE;
	FORMAT_SAVBANDWIDTHFILE;
	FORMAT_PRODUCTFILE;
	FORMAT_TOTALRESULT;

	//FORMAT_BSTFILE;
	//FORMAT_ARVRFILE;
	fp = fopen(outfile, "a");
	fp1=fopen(responsetimefile, "a");
	fp2=fopen(savebandwidthfile,"a");
	fp3=fopen(productfile,"a");
	fpResult = fopen(resultfile,"a");

#ifdef _TRACE_	
	FORMAT_TRACEFILE;
	requestList = fopen(trace, "w");
#endif
	//THETA = (atof)(argv[1]);
	CACHESIZE = (atoi)(argv[1]);
	//IATM = (atoi)(argv[1]);
	//DBSIZE = (atoi)(argv[1]);
	//DWNSIZEMAX = (atoi)(argv[1]);
	//NUMCLIENT = (atoi)(argv[1]);

	sim();
	fclose(fp);
	//fclose(fp1);
#ifdef _TRACE_
	fclose(requestList);
	getchar(); // pause for viewing output :)
#endif
}






