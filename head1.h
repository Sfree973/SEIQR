#define N 10000	
#define m 6	
#define gamma 2.1	
#define lBound 0.01		
#define uBound 1	
#define AVE 1000
#define step 10000

#define infectSeeds 0.01	
#define mu 0.01	
#define beta 0.19 
#define alpha 0.1 
#define delta 0.36 
#define tau 0.07 
#define K 0.05 
#define C 1 

#define lambdaInter 0.02
#define lambdaInfect0  0
#define lambdaMax 1      
typedef struct person {
	int ID;
	double active;
	struct neighborList *currentNeighbor;
	int activeState;
	int oldinfectState;
	int infectState;
	int Flag;
}person;

typedef struct neighborList
{
	int ID;
	struct neighborList *next;
}neighborList;
typedef struct BeSelectedID 
{
	int ID;
	struct BeSelectedID *next;
}BeSelectedID;

typedef struct recordRstateandlambda {
	double lambda;
	double Rdensity;
	double lambdac;
	struct recordRstateandlambda* next;
}recordRstateandlambda;
typedef struct recordDstateandlambda {
	double lambda;
	double Ddensity;
	double lambdac;
	struct recordDstateandlambda* next;
}recordDstateandlambda;
struct person *personNode[N];
neighborList *p, *q, *s, *Head, *pp, *qq, *ss, *temp, *p1, *p2;
BeSelectedID *BeSelectedHead, *ppp, *qqq, *sss,*BeSelectedInfectSeedsHead;
recordRstateandlambda* RstateandlambdaHead, * s1, * pppp, * qqqq, * ssss, * AVERstateandlambdaHead;
recordDstateandlambda* DstateandlambdaHead, * s3, * ppppp, * qqqqq, * sssss, * AVEDstateandlambdaHead;
int kk;
int i, k,t,ave;
double randomNumber, active, aveActive1, aveActive2, lambdac;
double sumRstateDensity, sumDstateDensity;
int  randNumberID, selectRandnumber;
int  numberOfCurrentNeighb;
double sumInfectNumber;
int numOfActiveState;
int infectNumber;
double RstateDensity, DstateDensity;
int integerPart; 
double decimalPart;
double sumActive;
int numberOfInfectNeighbor;
int immuNumber;
double lambdaInfect;

void initialPersonNode();
void initialCurrentNeighbor(); 
void initialBeSelectedID();
void computeAveActive();
void fireAllAgent();
void selectNodeToContact(int ID, int numberOfContact);
int isAlreadyCurrentNeighbor(int ID, int ppID);
void becomeNeighbor(int ID1, int ID2);
void freePersonNode();
void freeCurrentNeighbor();
void freeBeselectedIDandHead();
									  
void initialAllAgentFlag();
void epidemicProcess();
void infectFractionSeeds();
void initialAllAgentInfectState();
void updateInfectState();
void changeInfectState(int ID);
void freeBeSelectedInfectSeedsBiao();
double computeRstateDensity();
double computeDstateDensity();

void initialRstateandlambdaLianbiao();
void initialDstateandlambdaLianbiao();

void insertRstateandlambdaDensity(double lambdaValue, double RdensityValue, int ave);
void insertDstateandlambdaDensity(double lambdaValue, double DdensityValue, int ave);

void freeRstateandlambdaBiao();
void freeDstateandlambdaBiao();

void initialAVERstateandlambdaHead();
void initialAVEDstateandlambdaHead();

void insertAVERstateandlambda();
void insertAVEDstateandlambda();

void AVERstateandlambdaBiaoIntoFile();
void AVEDstateandlambdaBiaoIntoFile();

void freeAVERstateandlambdaBiao();
void freeAVEDstateandlambdaBiao();


int currentNeighborOfNode(int ID);
