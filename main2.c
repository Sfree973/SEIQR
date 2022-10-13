#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include"head.h"
int main()
{
	srand((unsigned)time(NULL));
	initialPerson();
	initBian();
	dataDrivenModel2();
	dataDrivenModel();
}

void dataDrivenModel() {
	initCurrentNeighbor();
	initialAVERstateandlambdaHead();
	initialAVENestateandlambdaHead();
	initialAVEPostateandlambdaHead();
	initialAVEQustateandlambdaHead();
	initialAVETrstateandlambdaHead();
	T1 = TInfect0;
	while (T1 <= TMax){
		initialRstateandlambdaLianbiao();
		initialNestateandlambdaLianbiao();
		initialPostateandlambdaLianbiao();
		initialQustateandlambdaLianbiao();
		initialTrstateandlambdaLianbiao();
		for (ave = 1; ave <= AVE; ave++) {
			initialAllAgentInfectState();
			initialAllAgentFlag();
			initialAllIsQ();
			infectFractionSeeds();
			startTime = bian[0]->timeStamp;
			int countEvent = 0;
			F = 1;
			Ne = 0;
			Po = 0;
			Qu = 0;
			Tr = 0;
			for (b = 0; (bian[b]->timeStamp <= T1 * 600) && (b < B); b++)
			{
					currentTimeStamp = bian[b]->timeStamp;
					if (startTime <= currentTimeStamp && currentTimeStamp < (startTime + interTime))
					{
						readBian(bian[b]->fromId, bian[b]->toId);
						t = bian[b]->timeStamp / 600.0; 
						countEvent++;
						continue;
					}
					else {
						b = b - 1;
						if (countEvent > 0)
						{
							if (t == 0) {
								T0 = 1;
							}
							else
							{
								T0 = ceil(t);
							}
							updateInfectState();
							epidemicProcess(T0, F);
							freeCurrentNeighbor();
							initCurrentNeighbor();
							initialAllAgentFlag();
							readBian(bian[b]->fromId, bian[b]->toId);
							countEvent = 1;
						}
					}
					startTime =currentTimeStamp;
					F++;
				}
			insertRstateandlambdaDensity(T1, computeRstateDensity(), ave);
			insertNestateandlambdaDensity(T1, computeNestateDensity(Ne), ave);
			insertPostateandlambdaDensity(T1, computePostateDensity(Po), ave);
			insertQustateandlambdaDensity(T1, computeQustateDensity(Qu), ave);
			insertTrstateandlambdaDensity(T1, computeTrstateDensity(Tr), ave);
		}
		insertAVERstateandlambda();
		insertAVENestateandlambda();
		insertAVEPostateandlambda();
		insertAVEQustateandlambda();
		insertAVETrstateandlambda();
		freeRstateandlambdaBiao();
		freeNestateandlambdaBiao();
		freePostateandlambdaBiao();
		freeQustateandlambdaBiao();
		freeTrstateandlambdaBiao();
		AVERstateandlambdaBiaoIntoFile();
		AVENestateandlambdaBiaoIntoFile();	
		AVEPostateandlambdaBiaoIntoFile();	
		AVEQustateandlambdaBiaoIntoFile();
		AVETrstateandlambdaBiaoIntoFile();
		T1 = T1 + TInter;
		printf("新的T生成\n");
	}
	freePersonNode();
	freeAVERstateandlambdaBiao();
	freeAVENestateandlambdaBiao();
	freeAVEPostateandlambdaBiao();
	freeAVEQustateandlambdaBiao();
	freeAVETrstateandlambdaBiao();
}
void AVERstateandlambdaBiaoIntoFile() {
	FILE *f;
	errno_t err;
	if (err = fopen_s(&f, "lambdaandRdensity.txt", "w") != 0) {
		printf("无法打开");
	}
	pppp = AVERstateandlambdaHead->next;
	while (pppp)
	{
		fprintf(f, "%d	%.6f\n", pppp->T, pppp->Rdensity);
		pppp = pppp->next;
	}
	fclose(f);
}

void AVENestateandlambdaBiaoIntoFile() {
	FILE* f1;
	errno_t err;
	if (err = fopen_s(&f1, "lambdaandNedensity.txt", "w") != 0) {
		printf("无法打开");
	}
	ppppp = AVENestateandlambdaHead->next;
	while (ppppp)
	{
		fprintf(f1, "%d	%.6f\n", ppppp->T, ppppp->Nedensity);
		ppppp = ppppp->next;
	}
	fclose(f1);
}

void AVEPostateandlambdaBiaoIntoFile() {
	FILE* f2;
	errno_t err;
	if (err = fopen_s(&f2, "lambdaandPodensity.txt", "w") != 0) {
		printf("无法打开");
	}
	pppppp = AVEPostateandlambdaHead->next;
	while (pppppp)
	{
		fprintf(f2, "%d	%.6f\n", pppppp->T, pppppp->Podensity);
		pppppp = pppppp->next;
	}
	fclose(f2);
}
void AVEQustateandlambdaBiaoIntoFile() {
	FILE* f3;
	errno_t err;
	if (err = fopen_s(&f3, "lambdaandQudensity.txt", "w") != 0) {
		printf("无法打开");
	}
	ppppppp = AVEQustateandlambdaHead->next;
	while (ppppppp)
	{
		fprintf(f3, "%d	%.6f\n", ppppppp->T, ppppppp->Qudensity);
		ppppppp = ppppppp->next;
	}
	fclose(f3);
}

void AVETrstateandlambdaBiaoIntoFile() {
	FILE* f4;
	errno_t err;
	if (err = fopen_s(&f4, "lambdaandTrdensity.txt", "w") != 0) {
		printf("无法打开");
	}
	pppppppp = AVETrstateandlambdaHead->next;
	while (pppppppp)
	{
		fprintf(f4, "%d	%.6f\n", pppppppp->T, pppppppp->Trdensity);
		pppppppp = pppppppp->next;
	}
	fclose(f4);
}