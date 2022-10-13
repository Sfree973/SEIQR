#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"head.h"

void initialPersonNode() {
	printf("--------------------------节点初始化开始--------------------------\n");
	FILE *f;
	errno_t err;
	if ((err = fopen_s(&f, "activeFile2.txt", "r")) != 0)
	{
	printf("无法打开文件\n");
	}
	
	for (i = 0; i < N; i++)
	{
		personNode[i] = (struct person*)malloc(sizeof(person));
		personNode[i]->ID = i;
		fscanf_s(f, "%lf", &personNode[i]->active);
	}
	printf("--------------------------已完成活跃度分配--------------------------\n");	
	printf("--------------------------节点初始化结束----------------------------\n");
	fclose(f);
}
void computeAveActive() {
	sumActive = 0;
	aveActive2 = 0;
	for (i = 0; i < N; i++) {
		sumActive += personNode[i]->active;
	    aveActive2 = aveActive2+(personNode[i]->active * personNode[i]->active) / (double)N;
	}
	aveActive1 = sumActive / (double)N;
	lambdac = (mu + alpha - alpha * mu - alpha * delta * mu - alpha * alpha * delta + alpha * alpha * delta * mu) / (m * (aveActive1 + (double)sqrt(aveActive2))* (1 - alpha * delta) * (1 - alpha * delta));
}

void fireAllAgent() {
	numOfActiveState = 0;
	for (i = 0; i < N; i++)
	{
		randomNumber = rand() / (double)(RAND_MAX);
		if (randomNumber < personNode[i]->active) {
			personNode[i]->activeState = 1;
			numOfActiveState++;
		}
		else
		{
			personNode[i]->activeState = 0;
		}
	}
}

void initialCurrentNeighbor()
{
	for (i = 0; i < N; i++)
	{
		personNode[i]->currentNeighbor = NULL;
	}
}

void initialBeSelectedID() {
	BeSelectedHead = (struct BeSelectedID *)malloc(sizeof(struct BeSelectedID));
	BeSelectedHead->next = NULL;
}

int isAlreadyCurrentNeighbor(int ID, int ppID) {

	p = personNode[ID]->currentNeighbor;
	while (p && p->ID != ppID)
	{
		p = p->next;
	}
	if (!p) {
		return 0;
	}
	else
	{
		return 1;
	}
}
void becomeNeighbor(int ID1, int ID2) {
	p = (neighborList *)malloc(sizeof(neighborList));
	p->ID = ID2;
	p->next = personNode[ID1]->currentNeighbor;
	personNode[ID1]->currentNeighbor = p;
	p = (struct neighborList *)malloc(sizeof(neighborList));
	p->ID = ID1;
	p->next = personNode[ID2]->currentNeighbor;
	personNode[ID2]->currentNeighbor = p;
}
void freeBeselectedIDandHead() {
	ppp = BeSelectedHead->next;
	while (ppp)
	{
		sss = ppp->next;
		free(ppp);
		ppp = sss;
	}

	free(BeSelectedHead);
}
void freeCurrentNeighbor() {
	for (i = 0; i < N; i++) {
		p = personNode[i]->currentNeighbor;
		while (p)
		{
			s = p->next;
			free(p);
			p = s;
		}
	}
}
void selectNodeToContact(int ID, int numberOfContact) {

	initialBeSelectedID();
	k = 0;
	while (k < numberOfContact)
	{
		randNumberID = rand() % N;
		if (ID == randNumberID) {
			continue;
		}
		if (isAlreadyCurrentNeighbor(ID, randNumberID)) {
			continue;
		}
		else
		{
			ppp = BeSelectedHead->next;
			while (ppp && ppp->ID != randNumberID)
			{
				ppp = ppp->next;
			}
			if (!ppp) {
				sss = (struct BeSelectedID *)malloc(sizeof(struct BeSelectedID));
				sss->ID = randNumberID;
				sss->next = BeSelectedHead->next;
				BeSelectedHead->next = sss;
				k++;
			}
			else
			{
				continue;
			}
		}

	}
	ppp = BeSelectedHead->next;
	while (ppp)
	{
		becomeNeighbor(ID, ppp->ID);
		ppp = ppp->next;
	}

	freeBeselectedIDandHead();
}

void freePersonNode() {
	for (i = 0; i < N; i++) {
		free(personNode[i]);
	}
}
void writeGraphAfterImmunization() {
	FILE* f;
	errno_t err;
	if (err = fopen_s(&f, "GraphAfterImmuization.txt", "w") != 0) {
		printf("写入失败");
	}
	for (i = 0; i < N; i++) {
		fprintf(f, "%d	%lf	%d\n", i, personNode[i]->active, personNode[i]->infectState);
	}
	fclose(f);
}

int currentNeighborOfNode(int ID) {

	kk = 0;

	p = personNode[ID]->currentNeighbor;
	while (p)
	{
		kk++;
		p = p->next;
	}
	return kk;
}