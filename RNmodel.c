#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"head.h"
void initialPerson()
{
	for (i = 1; i <= N; i++)
	{
		personNode[i] = (struct person*)malloc(sizeof(struct person));
		personNode[i]->ID = i;
	}
}
void initCurrentNeighbor()
{
	for (i = 1; i <= N; i++)
	{
		personNode[i]->currentNeighbor = NULL;
	}
}

void freeCurrentNeighbor()
{
	for (i = 1; i <= N; i++)
	{
		p = personNode[i]->currentNeighbor;
		while (p)
		{
			s = p->next;
			free(p);
			p = s;
		}
	}
}
int isAlreadyCurrentNeighbor(int ID, int toID) 
{
	p = personNode[ID]->currentNeighbor;
	while (p&&p->ID != toID)
	{
		p = p->next;
	}
	if (!p)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
void becomeNeighbor(int currentbtXiaBiao, int neighborXiaBiao)
{
	if (currentbtXiaBiao != neighborXiaBiao) {
		p = (neighborList *)malloc(sizeof(neighborList));
		p->ID = neighborXiaBiao;
		p->next = personNode[currentbtXiaBiao]->currentNeighbor;
		personNode[currentbtXiaBiao]->currentNeighbor = p;
	}
}

void initBian()
{
	FILE *f;
	errno_t err;
	if ((err = fopen_s(&f, "data.txt", "r")) != 0)
	{
		printf("�޷����ļ�\n");
	}
	for (i = 0; i < B; i++)
	{
		bian[i] = (struct Bian*)malloc(sizeof(struct Bian));
		fscanf_s(f, "%d %d %d", &bian[i]->fromId, &bian[i]->toId, &bian[i]->timeStamp);
	}
	printf("��������\n");
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
void readBian(int fromId, int toId) {
	int flag1 = 0, flag2 = 0;
	int fromIdXiaBiao, toIdXiaBiao;
	for (j = 1; j <= N; j++) {
		if (personNode[j]->ID == fromId) {
			fromIdXiaBiao = j;
			flag1 = 1;
		}
		if (personNode[j]->ID == toId) {
			toIdXiaBiao = j;
			flag2 = 1;
		}
		if (flag1&&flag2)
		{
			if (isAlreadyCurrentNeighbor(fromIdXiaBiao, toIdXiaBiao))
				break;
			else
			{
				becomeNeighbor(fromIdXiaBiao, toIdXiaBiao);
				becomeNeighbor(toIdXiaBiao, fromIdXiaBiao);
				break;
			}
		}
	}
}
void freePersonNode() {
	for (i = 1; i <= N; i++) {
		free(personNode[i]);
	}
}

