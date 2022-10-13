#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"head.h"
void dataDrivenModel2() {
	int Q = 1;
	bian[0]->f = Q;
	for (i = 1; i < B; i++) {
		Interval = bian[i]->timeStamp / interTime;
		Q = ceil(Interval);
		bian[i]->f = Q;
	}
}