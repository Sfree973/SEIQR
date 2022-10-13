#define N 410
#define B 17298
#define AVE 1000 
#define interTime 120.0
#define infectSeeds 0.1 
#define mu 0.05 
#define beta 0.19
#define alpha 0.1
#define delta 1.0 
#define tau 0.07
#define K 0.1
#define AVE2 1 
#define lambdaInfect 0.3
#define C0 1 
#define Cmin 0.1 
#define r 0.4  
#define L0 0   
#define L 7 
#define TInter 1
#define TInfect0  1
#define TMax 48    

typedef struct person {
	int ID;
	struct neighborList *currentNeighbor;
	int infectState;
	int oldinfectState;
	int Flag;
	int IsQ;
}person;
typedef struct Bian {
	int timeStamp;
	int fromId;
	int toId;
	int f;
}Bian;
typedef struct neighborList
{
	int ID;
	struct neighborList *next;
}neighborList;
typedef struct BeSelectedID 
{
	int ID;
	struct BeSelectedID* next;
}BeSelectedID;
typedef struct recordRstateandlambda {
	int T;
	double lambda;
	double Rdensity;
	struct recordRstateandlambda *next;
}recordRstateandlambda;
typedef struct recordNestateandlambda {
	int T;
	double lambda;
	double Nedensity;
	struct recordNestateandlambda *next;
}recordNestateandlambda;
typedef struct recordPostateandlambda {
	int T;
	double lambda;
	double Podensity;
	struct recordPostateandlambda *next;
}recordPostateandlambda;
typedef struct recordQustateandlambda {
	int T;
	double lambda;
	double Qudensity;
	struct recordQustateandlambda *next;
}recordQustateandlambda;
typedef struct recordTrstateandlambda {
	int T;
	double lambda;
	double Trdensity;
	struct recordTrstateandlambda *next;
}recordTrstateandlambda;
int i, ave, j, k, kk, b, dege;
int randNumberID;
int m;
int startTime;
int startTime2;
int interNumber;
int randNumberID, selectRandnumber;
double C, Interval, t;
int F;
int Ne, Po, Qu, Tr;

double randomNumber;
int numberOfInfectNeighbor;
double sumRstateDensity, sumNestateDensity, sumPostateDensity, sumQustateDensity, sumTrstateDensity;
double sumInfectNumber;
double RstateDensity, NestateDensity, PostateDensity, QustateDensity, TrstateDensity;
int ave2;
person *personNode[N+1];
neighborList *p, *q, *s, *pp, *qq, *ss, *p1, *p2;
BeSelectedID *BeSelectedHead, *ppp, *qqq, *sss, *BeSelectedInfectSeedsHead;
recordRstateandlambda *RstateandlambdaHead,  *pppp, *qqqq, *ssss, *AVERstateandlambdaHead;
recordNestateandlambda *NestateandlambdaHead, *ppppp, *qqqqq, *sssss, *AVENestateandlambdaHead;
recordPostateandlambda *PostateandlambdaHead, *pppppp, *qqqqqq, *ssssss, *AVEPostateandlambdaHead;
recordQustateandlambda *QustateandlambdaHead, *ppppppp, *qqqqqqq, *sssssss, *AVEQustateandlambdaHead;
recordTrstateandlambda *TrstateandlambdaHead, *pppppppp, *qqqqqqqq, *ssssssss, *AVETrstateandlambdaHead;
Bian *bian[B];
int  currentTimeStamp, currentTimeStamp2, previousTimeStamp, nextTimeStamp;
int T0, T1, T2;

void initialPerson();
void initCurrentNeighbor();
void freeCurrentNeighbor();
int isAlreadyCurrentNeighbor(int ID, int toID);
void becomeNeighbor(int currentbtXiaBiao, int neighborXiaBiao);
void initBian();
int currentNeighborOfNode(int ID);
void readBian(int fromId, int toId);
void dataDrivenModel();
void freePersonNode();

void initialAllAgentInfectState();
void initialAllAgentFlag();
void initialAllIsQ();
void infectFractionSeeds();
void epidemicProcess(int T0, int F);
void changeInfectState(int ID, int F);
void updateInfectState();
double computeRstateDensity();
double computeNestateDensity(int Ne);
double computePostateDensity(int Po);
double computeQustateDensity(int Qu);
double computeTrstateDensity(int Tr);

void initialRstateandlambdaLianbiao();
void initialNestateandlambdaLianbiao();
void initialPostateandlambdaLianbiao();
void initialQustateandlambdaLianbiao();
void initialTrstateandlambdaLianbiao();
void initialAVERstateandlambdaHead();
void initialAVENestateandlambdaHead();
void initialAVEPostateandlambdaHead();
void initialAVEQustateandlambdaHead();
void initialAVETrstateandlambdaHead();
void insertRstateandlambdaDensity(int lambdaValue, double RDensityValue, int ave);
void insertNestateandlambdaDensity(int lambdaValue, double NeDensityValue, int ave);
void insertPostateandlambdaDensity(int lambdaValue, double PoDensityValue, int ave);
void insertQustateandlambdaDensity(int lambdaValue, double QuDensityValue, int ave);
void insertTrstateandlambdaDensity(int lambdaValue, double TrDensityValue, int ave);
void insertAVERstateandlambda();
void insertAVENestateandlambda();
void insertAVEPostateandlambda();
void insertAVEQustateandlambda();
void insertAVETrstateandlambda();
void freeAVERstateandlambdaBiao();
void freeRstateandlambdaBiao();
void freeAVENestateandlambdaBiao();
void freeNestateandlambdaBiao();
void freeAVEPostateandlambdaBiao();
void freePostateandlambdaBiao();
void freeAVEQustateandlambdaBiao();
void freeQustateandlambdaBiao();
void freeAVETrstateandlambdaBiao();
void freeTrstateandlambdaBiao();
void AVERstateandlambdaBiaoIntoFile();
void AVENestateandlambdaBiaoIntoFile();
void AVEPostateandlambdaBiaoIntoFile();
void AVEQustateandlambdaBiaoIntoFile();
void AVETrstateandlambdaBiaoIntoFile();

void freeBeSelectedInfectSeedsBiao();
int currentNeighborOfNode(int ID);
void dataDrivenModel2();