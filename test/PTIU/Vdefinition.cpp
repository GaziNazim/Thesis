#ifndef VDEFINATION_H
#define VDEFINATION_H


#include <iostream>
#include <vector>

#include"..\\cpp.h"
#include "..\\csim.h"
#include "..\\global3.h"

using namespace std;

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
long DownloadDataItemSize[MaxDBSIZE], DeadlineMissNum, SatisfyNum, BroadcastNum,satisfieditem, TotalEncodedNum; // variable for statistic
long SumOfRequestData, BroadcastDataNum, MissedDataItem, ReceivedNum;
event *broadcast,*done; // pointer for count11er
table *tblend,*tblEncodeNum, *tblResponseTm, *tblStretch; // pointer for table
pair<int,int> decode[800];
int encodedata[20];
double TotalResponseTime, TotalServiceTime, ResponseTimeArray[7];
long ReceivedItemNum[7];
int EncodePacketSize[11];


/// system facilities ///
double ZIPF[MaxDBSIZE]; // simulation database
double Unifm[MaxDBSIZE];
struct Request *head; // request queue
struct ClientCacheitem *cachehead[MaxNUMCLIENT];
struct Decodeset *decodesethead;
struct SelRequest *Thead;

//// global variables ////
long Broadcastitem[10],BroadcastNumber, ClientCacheSize[MaxNUMCLIENT]; // number of active tasks
TIME BeginBstTime; // time indicating when start to broadcast current data object
FILE *fp,*fp1,*fp2,*fp3, *fpResult; // file handle for outputing result
int cnt, temperature[MaxDBSIZE],cnt1,count11[DNMAX], recv[MaxNUMCLIENT][MaxDBSIZE], slots; // count11er for on-goning requests 


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
void ResponseTimeDistribution(int, double); 

double FCFS_Weight(vector <int> selectvec, pair <int, int> vex[2000]);//calculate the sum of the weight of a clique
double MRF_Weight(vector <int> selectvec, pair <int, int> vex[2000]);
double LWF_Weight(vector <int> selectvec, pair <int, int> vex[2000]);
double RW_Weight(vector <int> selectvec, pair <int, int> vex[2000]);
double EDF_Weight(vector <int> selectvec, pair <int, int> vex[2000]);
double SIN_Weight(vector <int> selectvec, pair <int, int> vex[2000]);
double LTSF_Weight(vector <int> selectvec, pair <int, int> vex[2000]);
double STOBS_Weight(vector <int> selectvec, pair <int, int> vex[2000]);

double FindingMaxDataSize(vector <int> selectvec, pair <int, int> vex[2000]);


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
void CalculatingDistribution(int encodeNum);//Added by Ali



/// util routines ////
int	DecDistribution(int i);
int	IncDistribution(int i);
void init_Zipf();
void init_Unif();

///Simulation variables///////////
//double THETA;
//int CACHESIZE;
//int IATM;
//long  DBSIZE;
long DWNSIZEMAX;
double IATM;
//long NUMCLIENT;
#endif