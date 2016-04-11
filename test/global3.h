/* default settings, do not change */


//#define NRPC 300// number of arrivals to be simulated
#define NRPC 400 // 400 number of arrivals to be simulated

#define DNMIN 1
#define DNMAX 1
#define BANDWIDTH 1.0
//#define TH 10

#define DWNSIZEMIN 1



#define MaxDBSIZE 2000
#define MaxNUMCLIENT 600

////Simulation variables//////////
#define THETA 0.6 // 0.6
#define CACHESIZE  60
//#define IATM 20// mean of inter-arrival time distribution
#define DBSIZE 1000
//#define DWNSIZEMAX 30 //30 //10
#define NUMCLIENT 100 //300

#define CYCLE 1
#define LMIN  120.0            
#define LMAX 200.0
#define BETA 0.8
#define DELTA 1.0
#define SELECTP 60


/* default settings, do not change */


//#define NUMCLIENT 300
//#define CATEGORY "NUMCLIENT"
//#define OUTFILE "..\\ExpResult\\%s\\%s_%d.out"
//#define RESPONSEFILE "..\\ExpResult\\%s\\%s.txt"
//#define STARVFILE "..\\ExpResult\\%s\\%s.txt"
//#define PRODUCTFILE "..\\ExpResult\\%s\\%s.txt"
//#define SAVBANDWIDTHFILE "..\\ExpResult\\%s\\%s.txt"
//#define EFFICIENCYFILE	"..\\ExpResult\\%s\\%s.txt"
//#define FORMAT_OUTFILE sprintf(outfile, OUTFILE, CATEGORY, MODULE_NAME, (int)NUMCLIENT)
//#define FORMAT_RESPONSEFILE sprintf(responsetimefile,RESPONSEFILE,CATEGORY,"AvgResponeTime")
//#define FORMAT_STARVFILE sprintf(starvfile,STARVFILE,CATEGORY,"starvationratio")
//#define FORMAT_SAVBANDWIDTHFILE sprintf(savebandwidthfile,SAVBANDWIDTHFILE,CATEGORY,"savebandwidth")
//#define FORMAT_PRODUCTFILE sprintf(productfile,PRODUCTFILE,CATEGORY,"productivity")




//// for DBSIZE
//#define DBSIZE 1400
//#define CATEGORY "DBSIZE"
//#define OUTFILE "..\\ExpResult\\%s\\%s_%d.out"
//#define RESPONSEFILE "..\\ExpResult\\%s\\%s.txt"
//#define STARVFILE "..\\ExpResult\\%s\\%s.txt"
//#define PRODUCTFILE "..\\ExpResult\\%s\\%s.txt"
//#define SAVBANDWIDTHFILE "..\\ExpResult\\%s\\%s.txt"
//#define EFFICIENCYFILE	"..\\ExpResult\\%s\\%s.txt"
//#define FORMAT_OUTFILE sprintf(outfile, OUTFILE, CATEGORY, MODULE_NAME, (int)DBSIZE)
//#define FORMAT_RESPONSEFILE sprintf(responsetimefile,RESPONSEFILE,CATEGORY,"AvgResponeTime")
//#define FORMAT_SAVBANDWIDTHFILE sprintf(savebandwidthfile,SAVBANDWIDTHFILE,CATEGORY,"savebandwidth")
//#define FORMAT_PRODUCTFILE sprintf(productfile,PRODUCTFILE,CATEGORY,"productivity")
////for cache size
//#define CACHESIZE 60
//#define CATEGORY "CacheSize"

//#define MODULE_NAME "FCFS"
//#define MODULE_NAME "MRF"
//#define MODULE_NAME "LWF"
//#define MODULE_NAME "RW"
//#define MODULE_NAME "EDF"
//#define MODULE_NAME "SIN"
#define MODULE_NAME "LTSF_TH"
//#define MODULE_NAME "STOBS_TH"


//#define CATEGORY "ChangingTHETA"
//#define CATEGORY "ChangingCacheSize"
//#define CATEGORY "ChangingArrivalRate"
//#define CATEGORY "ChangingDBSIZE"
#define CATEGORY "ChangingItemSize"
//#define CATEGORY "ChangingNumofClient"

#define OUTFILE "..\\ExpResult\\%s\\%s_%s.out"
#define RESULTFILE "..\\ExpResult\\%s\\%s_%s.txt"
#define RESPONSEFILE "..\\ExpResult\\%s\\%s_%s.txt"
#define STARVFILE "..\\ExpResult\\%s\\%s.txt"
#define PRODUCTFILE "..\\ExpResult\\%s\\%s_%s.txt"
#define SAVBANDWIDTHFILE "..\\ExpResult\\%s\\%s_%s.txt"
#define EFFICIENCYFILE	"..\\ExpResult\\%s\\%s.txt"
#define FORMAT_OUTFILE sprintf(outfile, OUTFILE, CATEGORY, MODULE_NAME, "DefaultFile")
#define FORMAT_RESPONSEFILE sprintf(responsetimefile,RESPONSEFILE,CATEGORY, MODULE_NAME, "ResponseTimeFile")
#define FORMAT_SAVBANDWIDTHFILE sprintf(savebandwidthfile,SAVBANDWIDTHFILE,CATEGORY,MODULE_NAME, "EncdLngthDstrn")
#define FORMAT_PRODUCTFILE sprintf(productfile,PRODUCTFILE,CATEGORY,MODULE_NAME, "productivity")
#define FORMAT_TOTALRESULT sprintf(resultfile, RESULTFILE, CATEGORY, MODULE_NAME, "CompleteResult")

// for DataRange
//#define DNMIN 1
//#define DNMAX 1
//#define CATEGORY "DataRange"
//#define MISSRATIOFILE "..\\ExpResult\\%s\\%s.txt"
//#define STARVFILE "..\\ExpResult\\%s\\%s.txt"
//#define PRODUCTFILE "..\\ExpResult\\%s\\%s.txt"
//#define SAVBANDWIDTHFILE "..\\ExpResult\\%s\\%s.txt"
//#define OUTFILE "..\\ExpResult\\%s\\%s_%d-%d.out"
//#define EFFICIENCYFILE	"..\\ExpResult\\%s\\%s.txt"
//#define FORMAT_OUTFILE sprintf(outfile, OUTFILE, CATEGORY, MODULE_NAME, (int)DNMIN, (int)DNMAX)
//#define FORMAT_RESPONSEFILE sprintf(responsetimefile,RESPONSEFILE,CATEGORY,"AvgResponeTime")
//#define FORMAT_SAVBANDWIDTHFILE sprintf(savebandwidthfile,SAVBANDWIDTHFILE,CATEGORY,"savebandwidth")
//#define FORMAT_PRODUCTFILE sprintf(productfile,PRODUCTFILE,CATEGORY,"productivity")





//// //for Zipf
//#define CATEGORY "Zipf"
//#define THETA 0.0
//#define BETA 0.0
//#define RESPONSEFILE "..\\ExpResult\\%s\\%s.txt"
//#define STARVFILE "..\\ExpResult\\%s\\%s.txt"
//#define PRODUCTFILE "..\\ExpResult\\%s\\%s.txt"
//#define SAVBANDWIDTHFILE "..\\ExpResult\\%s\\%s.txt"
//#define EFFICIENCYFILE	"..\\ExpResult\\%s\\%s.txt"
//#define OUTFILE "..\\ExpResult\\%s\\%s_%d.out"
//#define FORMAT_OUTFILE sprintf(outfile, OUTFILE, CATEGORY,MODULE_NAME,( int)(10*BETA))
//#define FORMAT_RESPONSEFILE sprintf(responsetimefile,RESPONSEFILE,CATEGORY,"AvgResponeTime")
//#define FORMAT_SAVBANDWIDTHFILE sprintf(savebandwidthfile,SAVBANDWIDTHFILE,CATEGORY,"savebandwidth")///
//#define FORMAT_PRODUCTFILE sprintf(productfile,PRODUCTFILE,CATEGORY,"productivity")



//#define SELECTP 400
//#define CATEGORY "SelectPoint"
//#define OUTFILE "..\\ExpResult\\%s\\%s_%d.out"
//#define RESPONSEFILE "..\\ExpResult\\%s\\%s.txt"
//#define STARVFILE "..\\ExpResult\\%s\\%s.txt"
//#define PRODUCTFILE "..\\ExpResult\\%s\\%s.txt"
//#define SAVBANDWIDTHFILE "..\\ExpResult\\%s\\%s.txt"
//#define EFFICIENCYFILE	"..\\ExpResult\\%s\\%s.txt"
//#define FORMAT_OUTFILE sprintf(outfile, OUTFILE, CATEGORY, MODULE_NAME, (int)SELECTP)
//#define FORMAT_RESPONSEFILE sprintf(responsetimefile,RESPONSEFILE,CATEGORY,"AvgResponeTime")
//#define FORMAT_SAVBANDWIDTHFILE sprintf(savebandwidthfile,SAVBANDWIDTHFILE,CATEGORY,"savebandwidth")
//#define FORMAT_PRODUCTFILE sprintf(productfile,PRODUCTFILE,CATEGORY,"productivity")
