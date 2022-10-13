#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"head.h"
void epidemicProcess(int T0, int F) {
	if (T0 < L0) {
		C = C0;
	}
	else if ((T0 >= L0) && (T0 < L)) {
		C = (C0 - Cmin) * exp(-r * (T0 - L0)) + Cmin;
	}
	else if (T0 >= L) {
		C = (Cmin - C0) * exp(-r * (T0 - L)) + C0;
	}
	for (i = 1; i <= N; i++) {
		changeInfectState(i, F);
	}
}
void updateInfectState() {
	for (i = 1; i <= N; i++) {
		personNode[i]->oldinfectState = personNode[i]->infectState;
	}
}
void changeInfectState(int ID, int F) {
	if (personNode[ID]->oldinfectState == 3) {
		randomNumber = rand() / (double)(RAND_MAX);
		if (randomNumber < alpha) {
			personNode[ID]->infectState = 7; //QI
			if (personNode[ID]->IsQ == 0) {
				personNode[ID]->IsQ = 1;
				Qu = Qu + 1; 
				Tr = Tr + 1; 
			}
			p = personNode[ID]->currentNeighbor;
			while (p)
			{
				if ((personNode[p->ID]->oldinfectState == 1) && (personNode[p->ID]->Flag == 0)) {
					personNode[p->ID]->Flag = 1;
					int count = 0;
					for (dege=0; dege < B; dege++)
					{
						if ((bian[dege]->f == F) && (((p->ID == bian[dege]->toId) && (ID == bian[dege]->fromId)) || ((p->ID == bian[dege]->fromId) && (ID == bian[dege]->toId)))) {
							count = 1;
						}
					}
					for (dege = 0; dege < B; dege++) {
						if ((count == 1) && (bian[dege]->f == F) && (((p->ID == bian[dege]->toId) && (ID == bian[dege]->fromId))|| ((p->ID == bian[dege]->fromId) && (ID == bian[dege]->toId))))
						{
							personNode[p->ID]->infectState = 5; 
							if (personNode[p->ID]->IsQ == 0) {
								personNode[p->ID]->IsQ = 1;
								Po = Po + 1; 
								Qu = Qu + 1; 
							}
						}
					}
					if (personNode[p->ID]->infectState != 5)
					{
						numberOfInfectNeighbor = 0;
						p1 = personNode[p->ID]->currentNeighbor;
						while (p1)
						{
							if ((personNode[p1->ID]->oldinfectState == 3) || (personNode[p1->ID]->oldinfectState == 2)) {
								numberOfInfectNeighbor++;
							}
							p1 = p1->next;
						}
						randomNumber = rand() / (double)(RAND_MAX);
						if (randomNumber < (1 - pow((1 - lambdaInfect * C), numberOfInfectNeighbor))) {
							personNode[p->ID]->infectState = 2;
							if (personNode[p->ID]->IsQ == 0) {
								personNode[p->ID]->IsQ = 1;
								Ne = Ne + 1; 
							}
						}
					}
				}
				else if ((personNode[p->ID]->oldinfectState == 2) && (personNode[p->ID]->Flag == 0)) {
					personNode[p->ID]->Flag = 1;
					int Count = 0;
					for (dege = 0; dege < B; dege++)
					{
						if ((bian[dege]->f == F) && (((p->ID == bian[dege]->toId) && (ID == bian[dege]->fromId)) || ((p->ID == bian[dege]->fromId) && (ID == bian[dege]->toId)))) {
							Count = 1;
						}
					}
					for (dege = 0; dege < B; dege++) {
						if ((Count == 1) && (bian[dege]->f == F) && (((p->ID == bian[dege]->toId) && (ID == bian[dege]->fromId)) || ((p->ID == bian[dege]->fromId) && (ID == bian[dege]->toId))))
						{
							personNode[p->ID]->infectState = 6; 
							if (personNode[p->ID]->IsQ == 0) {
								personNode[p->ID]->IsQ = 1;
								Qu = Qu + 1; 
								Po = Po + 1; 
							}
						}
					}
					if (personNode[p->ID]->infectState != 6)
					{
						randomNumber = rand() / (double)(RAND_MAX);
						if (randomNumber < beta)
						{
							personNode[p->ID]->infectState = 3;
							if (personNode[p->ID]->IsQ == 0) {
								personNode[p->ID]->IsQ = 1;
								Ne = Ne + 1;
							}
						}
						else {
							personNode[p->ID]->infectState = 2;
							if (personNode[p->ID]->IsQ == 0) {
								personNode[p->ID]->IsQ = 1;
								Ne = Ne + 1;
							}
						}
					}
					p1 = personNode[p->ID]->currentNeighbor;
					while (p1) {
						if ((personNode[p1->ID]->oldinfectState == 1) && (personNode[p1->ID]->Flag == 0)) {
							personNode[p1->ID]->Flag = 1;
							numberOfInfectNeighbor = 0;
							p2 = personNode[p1->ID]->currentNeighbor;
							while (p2)
							{
								if ((personNode[p2->ID]->oldinfectState == 3) || (personNode[p2->ID]->oldinfectState == 2)) {
									numberOfInfectNeighbor++;
								}
								p2 = p2->next;
							}
							randomNumber = rand() / (double)(RAND_MAX);
							if (randomNumber < (1 - pow((1 - lambdaInfect * C), numberOfInfectNeighbor))) {
								personNode[p1->ID]->infectState = 2;
							}
						}
						p1 = p1->next;
					}
				}
				p = p->next;
			}
		}
		else {
			randomNumber = rand() / (double)(RAND_MAX);
			if (randomNumber < mu) {
				personNode[ID]->infectState = 4;
			}
			p = personNode[ID]->currentNeighbor;
			while (p)
			{
				if ((personNode[p->ID]->oldinfectState == 1) && (personNode[p->ID]->Flag == 0)) {
					personNode[p->ID]->Flag = 1;
					numberOfInfectNeighbor = 0;
					p1 = personNode[p->ID]->currentNeighbor;
					while (p1)
					{
						if ((personNode[p1->ID]->oldinfectState == 3) || (personNode[p1->ID]->oldinfectState == 2)) {
							numberOfInfectNeighbor++;
						}
						p1 = p1->next;
					}
					randomNumber = rand() / (double)(RAND_MAX);
					if (randomNumber < (1 - pow((1 - lambdaInfect * C), numberOfInfectNeighbor))) {
						personNode[p->ID]->infectState = 2;
					}
				}
				else if ((personNode[p->ID]->oldinfectState == 2) && (personNode[p->ID]->Flag == 0)) {
					personNode[p->ID]->Flag = 1;
					randomNumber = rand() / (double)(RAND_MAX);
					if (randomNumber < beta)
					{
						personNode[p->ID]->infectState = 3;
					}
					p1 = personNode[p->ID]->currentNeighbor;
					while (p1) {
						if ((personNode[p1->ID]->oldinfectState == 1) && (personNode[p1->ID]->Flag == 0)) {
							personNode[p1->ID]->Flag = 1;
							numberOfInfectNeighbor = 0;
							p2 = personNode[p1->ID]->currentNeighbor;
							while (p2)
							{
								if ((personNode[p2->ID]->oldinfectState == 3) || (personNode[p2->ID]->oldinfectState == 2)) {
									numberOfInfectNeighbor++;
								}
								p2 = p2->next;
							}
							randomNumber = rand() / (double)(RAND_MAX);
							if (randomNumber < (1 - pow((1 - lambdaInfect * C), numberOfInfectNeighbor))) {
								personNode[p1->ID]->infectState = 2;
							}
						}
						p1 = p1->next;
					}
				}
				p = p->next;
			}
		}
	}
	else if ((personNode[ID]->oldinfectState == 2) && (personNode[ID]->Flag == 0)) {
		randomNumber = rand() / (double)(RAND_MAX);
		if (randomNumber < beta)
		{
			personNode[ID]->infectState = 3;
		}
		p = personNode[ID]->currentNeighbor;
		while (p)
		{
			if ((personNode[p->ID]->oldinfectState == 1) && (personNode[p->ID]->Flag == 0)) {
				personNode[p->ID]->Flag = 1;
				numberOfInfectNeighbor = 0;
				p1 = personNode[p->ID]->currentNeighbor;
				while (p1)
				{
					if ((personNode[p1->ID]->oldinfectState == 3) || (personNode[p1->ID]->oldinfectState == 2)) {
						numberOfInfectNeighbor++;
					}

					p1 = p1->next;
				}
				randomNumber = rand() / (double)(RAND_MAX);
				if (randomNumber < (1 - pow((1 - lambdaInfect * C), numberOfInfectNeighbor))) {
					personNode[p->ID]->infectState = 2;
				}
			}
			p = p->next;
		}
	}
	else if (personNode[ID]->oldinfectState == 5) {
		randomNumber = rand() / (double)(RAND_MAX);
		if (randomNumber < tau)
		{
			personNode[ID]->infectState = 1;
		}
	}
	else if (personNode[ID]->oldinfectState == 6) {
		randomNumber = rand() / (double)(RAND_MAX);
		if (randomNumber < beta) {
			personNode[ID]->infectState = 7;
		}
		else if ((randomNumber > beta) && (randomNumber < (tau + beta))) {
			personNode[ID]->infectState = 2;
			if (personNode[ID]->IsQ == 0) {
				personNode[ID]->IsQ = 1;
				Ne = Ne + 1;
			}
		}
		else
		{
			personNode[ID]->infectState = 6;
		}
	}
	else if (personNode[ID]->oldinfectState == 7) {
		randomNumber = rand() / (double)(RAND_MAX);
		if (randomNumber < K)
		{
			personNode[ID]->infectState = 4;
		}
	}
}
void initialAllAgentInfectState() {
	for (i = 1; i <= N; i++) {
		personNode[i]->infectState = 1;
	}
}
void initialAllAgentFlag() {
	for (i = 1; i <= N; i++) {
		personNode[i]->Flag = 0;
	}
}
void initialAllIsQ() {
	for (i = 1; i <= N; i++) {
		personNode[i]->IsQ = 0;
	}
}
void infectFractionSeeds() {
	BeSelectedInfectSeedsHead = (struct BeSelectedID*)malloc(sizeof(struct BeSelectedID));
	BeSelectedInfectSeedsHead->next = NULL;
	k = 0;
	while (k < infectSeeds * N)
	{
		selectRandnumber = rand() % N + 1;

		ppp = BeSelectedInfectSeedsHead->next;
		while (ppp && ppp->ID != selectRandnumber)
		{
			ppp = ppp->next;
		}
		if (!ppp) {
			sss = (struct BeSelectedID*)malloc(sizeof(struct BeSelectedID));
			sss->ID = selectRandnumber;
			sss->next = BeSelectedInfectSeedsHead->next;
			BeSelectedInfectSeedsHead->next = sss;
			personNode[selectRandnumber]->infectState = 2;
			k++;
		}
		else
		{
			continue;
		}
	}
	freeBeSelectedInfectSeedsBiao();
}
void freeBeSelectedInfectSeedsBiao() {
	ppp = BeSelectedInfectSeedsHead->next;
	while (ppp)
	{
		qqq = ppp->next;
		free(ppp);
		ppp = qqq;
	}
	free(BeSelectedInfectSeedsHead);
}
double computeRstateDensity() {
	sumInfectNumber = 0;
	for (i = 1; i <= N; i++)
	{
		if (personNode[i]->infectState == 4) {
			sumInfectNumber++;
		}
	}
	RstateDensity = sumInfectNumber / (double)N;
	return RstateDensity;
}
double computeNestateDensity(int Ne) {
	NestateDensity = Ne / (double)N;
	return NestateDensity;
}
double computePostateDensity(int Po) {
	PostateDensity = Po / (double)N;
	return PostateDensity;
}
double computeQustateDensity(int Qu) {
	QustateDensity = Qu / (double)N;
	return QustateDensity;
}
double computeTrstateDensity(int Tr) {
	TrstateDensity = Tr / (double)N;
	return TrstateDensity;
}
void initialRstateandlambdaLianbiao() {
	RstateandlambdaHead = (struct recordRstateandlambda*)malloc(sizeof(struct recordRstateandlambda));
	if (RstateandlambdaHead == NULL) {
		printf("RstateandlambdaHead申请内存失败\n");
	}
	RstateandlambdaHead->next = NULL;
}
void initialAVERstateandlambdaHead() {
	AVERstateandlambdaHead = (struct recordRstateandlambda*)malloc(sizeof(struct recordRstateandlambda));
	AVERstateandlambdaHead->next = NULL;
}
void initialNestateandlambdaLianbiao() {
	NestateandlambdaHead = (struct recordNestateandlambda*)malloc(sizeof(struct recordNestateandlambda));
	if (NestateandlambdaHead == NULL) {
		printf("NestateandlambdaHead申请内存失败\n");
	}
	NestateandlambdaHead->next = NULL;
}
void initialAVENestateandlambdaHead() {
	AVENestateandlambdaHead = (struct recordNestateandlambda*)malloc(sizeof(struct recordNestateandlambda));
	AVENestateandlambdaHead->next = NULL;
}
void initialPostateandlambdaLianbiao() {
	PostateandlambdaHead = (struct recordPostateandlambda*)malloc(sizeof(struct recordPostateandlambda));
	if (PostateandlambdaHead == NULL) {
		printf("PostateandlambdaHead申请内存失败\n");
	}
	PostateandlambdaHead->next = NULL;
}
void initialAVEPostateandlambdaHead() {
	AVEPostateandlambdaHead = (struct recordPostateandlambda*)malloc(sizeof(struct recordPostateandlambda));
	AVEPostateandlambdaHead->next = NULL;
}
void initialQustateandlambdaLianbiao() {
	QustateandlambdaHead = (struct recordQustateandlambda*)malloc(sizeof(struct recordQustateandlambda));
	if (QustateandlambdaHead == NULL) {
		printf("QustateandlambdaHead申请内存失败\n");
	}
	QustateandlambdaHead->next = NULL;
}
void initialAVEQustateandlambdaHead() {
	AVEQustateandlambdaHead = (struct recordQustateandlambda*)malloc(sizeof(struct recordQustateandlambda));
	AVEQustateandlambdaHead->next = NULL;
}
void initialTrstateandlambdaLianbiao() {
	TrstateandlambdaHead = (struct recordTrstateandlambda*)malloc(sizeof(struct recordTrstateandlambda));
	if (TrstateandlambdaHead == NULL) {
		printf("TrstateandlambdaHead申请内存失败\n");
	}
	TrstateandlambdaHead->next = NULL;
}
void initialAVETrstateandlambdaHead() {
	AVETrstateandlambdaHead = (struct recordTrstateandlambda*)malloc(sizeof(struct recordTrstateandlambda));
	AVETrstateandlambdaHead->next = NULL;
}
void insertRstateandlambdaDensity(int TValue, double RDensityValue, int ave) {

	ssss = (struct recordRstateandlambda*)malloc(sizeof(struct recordRstateandlambda));
	ssss->T = TValue;
	ssss->Rdensity = RDensityValue;
	ssss->next = RstateandlambdaHead->next;
	RstateandlambdaHead->next = ssss;
}
void insertNestateandlambdaDensity(int TValue, double NeDensityValue, int ave) {

	sssss = (struct recordNestateandlambda*)malloc(sizeof(struct recordNestateandlambda));
	sssss->T = TValue;
	sssss->Nedensity = NeDensityValue;
	sssss->next = NestateandlambdaHead->next;
	NestateandlambdaHead->next = sssss;
}
void insertPostateandlambdaDensity(int TValue, double PoDensityValue, int ave) {

	ssssss = (struct recordPostateandlambda*)malloc(sizeof(struct recordPostateandlambda));
	ssssss->T = TValue;
	ssssss->Podensity = PoDensityValue;
	ssssss->next = PostateandlambdaHead->next;
	PostateandlambdaHead->next = ssssss;
}
void insertQustateandlambdaDensity(int TValue, double QuDensityValue, int ave) {

	sssssss = (struct recordQustateandlambda*)malloc(sizeof(struct recordQustateandlambda));
	sssssss->T = TValue;
	sssssss->Qudensity = QuDensityValue;
	sssssss->next = QustateandlambdaHead->next;
	QustateandlambdaHead->next = sssssss;
}
void insertTrstateandlambdaDensity(int TValue, double TrDensityValue, int ave) {

	ssssssss = (struct recordTrstateandlambda*)malloc(sizeof(struct recordTrstateandlambda));
	ssssssss->T = TValue;
	ssssssss->Trdensity = TrDensityValue;
	ssssssss->next = TrstateandlambdaHead->next;
	TrstateandlambdaHead->next = ssssssss;
}
void insertAVERstateandlambda() {
	sumRstateDensity = 0;
	pppp = RstateandlambdaHead->next;
	ssss = (struct recordRstateandlambda*)malloc(sizeof(struct recordRstateandlambda));
	ssss->T = pppp->T;
	while (pppp)
	{
		sumRstateDensity += pppp->Rdensity;
		pppp = pppp->next;
	}
	ssss->Rdensity = sumRstateDensity / (double)AVE;
	printf("T取值为%d时,总平均%d后R态感染密度为：%lf\n", ssss->T, AVE, ssss->Rdensity);
	ssss->next = AVERstateandlambdaHead->next;
	AVERstateandlambdaHead->next = ssss;
}
void insertAVENestateandlambda() {
	sumNestateDensity = 0;
	ppppp = NestateandlambdaHead->next;
	sssss = (struct recordNestateandlambda*)malloc(sizeof(struct recordNestateandlambda));
	sssss->T = ppppp->T;
	while (ppppp)
	{
		sumNestateDensity += ppppp->Nedensity;
		ppppp = ppppp->next;
	}
	sssss->Nedensity = sumNestateDensity / (double)AVE;
	printf("T取值为%d时,总平均%d后Ne态感染密度为：%lf\n", sssss->T, AVE, sssss->Nedensity);
	sssss->next = AVENestateandlambdaHead->next;
	AVENestateandlambdaHead->next = sssss;
}
void insertAVEPostateandlambda() {
	sumPostateDensity = 0;
	pppppp = PostateandlambdaHead->next;
	ssssss = (struct recordPostateandlambda*)malloc(sizeof(struct recordPostateandlambda));
	ssssss->T = pppppp->T;
	while (pppppp)
	{
		sumPostateDensity += pppppp->Podensity;
		pppppp = pppppp->next;
	}
	ssssss->Podensity = sumPostateDensity / (double)AVE;
	printf("T取值为%d时,总平均%d后Po态感染密度为：%lf\n", ssssss->T, AVE, ssssss->Podensity);
	ssssss->next = AVEPostateandlambdaHead->next;
	AVEPostateandlambdaHead->next = ssssss;
}
void insertAVEQustateandlambda() {
	sumQustateDensity = 0;
	ppppppp = QustateandlambdaHead->next;
	sssssss = (struct recordQustateandlambda*)malloc(sizeof(struct recordQustateandlambda));
	sssssss->T = ppppppp->T;
	while (ppppppp)
	{
		sumQustateDensity += ppppppp->Qudensity;
		ppppppp = ppppppp->next;
	}
	sssssss->Qudensity = sumQustateDensity / (double)AVE;
	printf("T取值为%d时,总平均%d后Qu态感染密度为：%lf\n", sssssss->T, AVE, sssssss->Qudensity);
	sssssss->next = AVEQustateandlambdaHead->next;
	AVEQustateandlambdaHead->next = sssssss;
}
void insertAVETrstateandlambda() {
	sumTrstateDensity = 0;
	pppppppp = TrstateandlambdaHead->next;
	ssssssss = (struct recordTrstateandlambda*)malloc(sizeof(struct recordTrstateandlambda));
	ssssssss->T = pppppppp->T;
	while (pppppppp)
	{
		sumTrstateDensity += pppppppp->Trdensity;
		pppppppp = pppppppp->next;
	}
	ssssssss->Trdensity = sumTrstateDensity / (double)AVE;
	printf("T取值为%d时,总平均%d后Tr态感染密度为：%lf\n", ssssssss->T, AVE, ssssssss->Trdensity);
	ssssssss->next = AVETrstateandlambdaHead->next;
	AVETrstateandlambdaHead->next = ssssssss;
}
void freeAVERstateandlambdaBiao() {
	pppp = AVERstateandlambdaHead->next;
	while (pppp)
	{
		qqqq = pppp->next;
		free(pppp);
		pppp = qqqq;
	}
	free(AVERstateandlambdaHead);
}
void freeAVENestateandlambdaBiao() {
	ppppp = AVENestateandlambdaHead->next;
	while (ppppp)
	{
		qqqqq = ppppp->next;
		free(ppppp);
		ppppp = qqqqq;
	}
	free(AVENestateandlambdaHead);
}
void freeAVEPostateandlambdaBiao() {
	pppppp = AVEPostateandlambdaHead->next;
	while (pppppp)
	{
		qqqqqq = pppppp->next;
		free(pppppp);
		pppppp = qqqqqq;
	}
	free(AVEPostateandlambdaHead);
}
void freeAVEQustateandlambdaBiao() {
	ppppppp = AVEQustateandlambdaHead->next;
	while (ppppppp)
	{
		qqqqqqq = ppppppp->next;
		free(ppppppp);
		ppppppp = qqqqqqq;
	}
	free(AVEQustateandlambdaHead);
}
void freeAVETrstateandlambdaBiao() {
	pppppppp = AVETrstateandlambdaHead->next;
	while (pppppppp)
	{
		qqqqqqqq = pppppppp->next;
		free(pppppppp);
		pppppppp = qqqqqqqq;
	}
	free(AVETrstateandlambdaHead);
}
void freeRstateandlambdaBiao() {
	pppp = RstateandlambdaHead->next;
	while (pppp)
	{
		qqqq = pppp->next;
		free(pppp);
		pppp = qqqq;
	}
	free(RstateandlambdaHead);
}
void freeNestateandlambdaBiao() {
	ppppp = NestateandlambdaHead->next;
	while (ppppp)
	{
		qqqqq = ppppp->next;
		free(ppppp);
		ppppp = qqqqq;
	}
	free(NestateandlambdaHead);
}
void freePostateandlambdaBiao() {
	pppppp = PostateandlambdaHead->next;
	while (pppppp)
	{
		qqqqqq = pppppp->next;
		free(pppppp);
		pppppp = qqqqqq;
	}
	free(PostateandlambdaHead);
}
void freeQustateandlambdaBiao() {
	ppppppp = QustateandlambdaHead->next;
	while (ppppppp)
	{
		qqqqqqq = ppppppp->next;
		free(ppppppp);
		ppppppp = qqqqqqq;
	}
	free(QustateandlambdaHead);
}
void freeTrstateandlambdaBiao() {
	pppppppp = TrstateandlambdaHead->next;
	while (pppppppp)
	{
		qqqqqqqq = pppppppp->next;
		free(pppppppp);
		pppppppp = qqqqqqqq;
	}
	free(TrstateandlambdaHead);
}