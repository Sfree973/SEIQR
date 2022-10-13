#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"head.h"
int main()
{
	srand((unsigned)time(NULL));
	initialPersonNode();
	printf("一阶平均活跃度为%lf，二阶平均活跃度为%lf\n", aveActive1, aveActive2);
	lambdaInfect = lambdaInfect0;
	initialAVERstateandlambdaHead();
	while (lambdaInfect <= lambdaMax) {
		initialRstateandlambdaLianbiao();
		for (ave = 1; ave <= AVE; ave++) {
			initialCurrentNeighbor();
			initialAllAgentInfectState();
			infectFractionSeeds();
			epidemicProcess();
			insertRstateandlambdaDensity(lambdaInfect, computeRstateDensity(), ave);
		}
		insertAVERstateandlambda();
		freeRstateandlambdaBiao();
		AVERstateandlambdaBiaoIntoFile();
		lambdaInfect = lambdaInfect + lambdaInter;
		printf("新的lambdaInfect生成\n");
	}
	freePersonNode();
	freeAVERstateandlambdaBiao();
}

void initialRstateandlambdaLianbiao() {
	RstateandlambdaHead = (struct recordRstateandlambda*)malloc(sizeof(struct recordRstateandlambda));
	if (RstateandlambdaHead == NULL) {
		printf("RstateandlambdaHead申请内存失败\n");
	}
	RstateandlambdaHead->next = NULL;
}
void initialDstateandlambdaLianbiao() {
	DstateandlambdaHead = (struct recordDstateandlambda*)malloc(sizeof(struct recordDstateandlambda));
	if (DstateandlambdaHead == NULL) {
		printf("DstateandlambdaHead申请内存失败\n");
	}
	DstateandlambdaHead->next = NULL;
}
void initialAVERstateandlambdaHead() {
	AVERstateandlambdaHead = (struct recordRstateandlambda*)malloc(sizeof(struct recordRstateandlambda));
	AVERstateandlambdaHead->next = NULL;
}

void initialAVEDstateandlambdaHead() {
	AVEDstateandlambdaHead = (struct recordDstateandlambda*)malloc(sizeof(struct recordDstateandlambda));
	AVEDstateandlambdaHead->next = NULL;
}

void insertRstateandlambdaDensity(double lambdaValue, double RdensityValue, int ave) {

	ssss = (struct recordRstateandlambda*)malloc(sizeof(struct recordRstateandlambda));
	ssss->lambda = lambdaValue;
	ssss->Rdensity = RdensityValue;
	printf("--------------第%d次结束,lambda值为：%lf,阈值为%lf，R密度为%lf\n", ave, lambdaValue,lambdac, RdensityValue);
	ssss->next = RstateandlambdaHead->next;
	RstateandlambdaHead->next = ssss;

}
void insertDstateandlambdaDensity(double lambdaValue, double DdensityValue, int ave) {

	sssss = (struct recordDstateandlambda*)malloc(sizeof(struct recordDstateandlambda));
	sssss->lambda = lambdaValue;
	sssss->Ddensity = DdensityValue;
	printf("--------------第%d次结束,lambda值为：%lf,阈值为%lf，D密度为%lf\n", ave, lambdaValue, lambdac, DdensityValue);
	sssss->next = DstateandlambdaHead->next;
	DstateandlambdaHead->next = sssss;

}
void insertAVERstateandlambda() {

	sumRstateDensity = 0;
	pppp = RstateandlambdaHead->next;

	ssss = (struct recordRstateandlambda*)malloc(sizeof(struct recordRstateandlambda));
	ssss->lambda = pppp->lambda;

	while (pppp)
	{
		sumRstateDensity += pppp->Rdensity;
		pppp = pppp->next;
	}
	ssss->Rdensity = sumRstateDensity / (double)AVE;
	printf("lambda取值为%lf时，总平均%d后R态感染密度为：%lf\n", ssss->lambda,  AVE, ssss->Rdensity);
	ssss->next = AVERstateandlambdaHead->next;
	AVERstateandlambdaHead->next = ssss;
}

void insertAVEDstateandlambda() {

	sumDstateDensity = 0;
	ppppp = DstateandlambdaHead->next;

	sssss = (struct recordDstateandlambda*)malloc(sizeof(struct recordDstateandlambda));
	sssss->lambda = ppppp->lambda;

	while (ppppp)
	{
		sumDstateDensity += ppppp->Ddensity;
		ppppp = ppppp->next;
	}
	sssss->Ddensity = sumDstateDensity / (double)AVE;
	printf("lambda取值为%lf时,总平均%d后D态感染密度为：%lf\n", sssss->lambda,  AVE, sssss->Ddensity);
	sssss->next = AVEDstateandlambdaHead->next;
	AVEDstateandlambdaHead->next = sssss;
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
void freeDstateandlambdaBiao() {
	ppppp = DstateandlambdaHead->next;
	while (ppppp)
	{
		qqqqq = ppppp->next;
		free(ppppp);
		ppppp = qqqqq;
	}
	free(DstateandlambdaHead);
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
void freeAVEDstateandlambdaBiao() {
	ppppp = AVEDstateandlambdaHead->next;
	while (ppppp)
	{
		qqqqq = ppppp->next;
		free(ppppp);
		ppppp = qqqqq;
	}
	free(AVEDstateandlambdaHead);
}
void AVERstateandlambdaBiaoIntoFile() {
	FILE* f;
	errno_t err;
	if (err = fopen_s(&f, "lambdaandRdensity.txt", "w") != 0) {
		printf("无法打开");
	}
	pppp = AVERstateandlambdaHead->next;
	while (pppp)
	{
		fprintf(f, "%lf	%lf\n", pppp->lambda, pppp->Rdensity);
		pppp = pppp->next;
	}

	fclose(f);
}
void AVEDstateandlambdaBiaoIntoFile() {
	FILE* f;
	errno_t err;
	if (err = fopen_s(&f, "lambdaandDdensity.txt", "w") != 0) {
		printf("无法打开");
	}
	ppppp = AVEDstateandlambdaHead->next;
	while (ppppp)
	{
		fprintf(f, "%lf	%lf\n", ppppp->lambda,  ppppp->Ddensity);
		ppppp = ppppp->next;
	}
	fclose(f);
}