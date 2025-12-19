/*
--------------------------------------------------
Project: a4q2
File:    myrecord.c
Author:  Nadeem Hassan
Version: 2025-10-06
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "myrecord.h"
#include "mysort.h"

GRADE grade(float score) {
	GRADE r = { "F" };
	int p = (int) round(score);
	char g[14][5] = { "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+",
			"D", "D-", "F" };
	int b[] = { 100, 90, 85, 80, 77, 73, 70, 67, 63, 60, 57, 53, 50, 0 };
	int i = 0, n = sizeof(b) / sizeof(float);
	for (i = 0; i < n; i++) {
		if (score >= b[i + 1])
			break;
	}
	strcpy(r.letter_grade, g[i]);
	return r;
}

int import_data(FILE *fp, RECORD *dataset) {
	int count = 0;
	char line[100];
	while (fgets(line, sizeof(line), fp)) {
		char *token = strtok(line, ",");
		if (token) {
			strcpy(dataset[count].name, token);
			token = strtok(NULL, ",");
			if (token) {
				dataset[count].score = atof(token);
				count++;
			}
		}
	}
	return count;
}

STATS process_data(RECORD *dataset, int count) {
	STATS stats = { count, 0, 0, 0 };
	if (count == 0)
		return stats;

	float sum = 0, sum_sq = 0;
	float *scores[count];
	for (int i = 0; i < count; i++) {
		sum += dataset[i].score;
		sum_sq += dataset[i].score * dataset[i].score;
		scores[i] = &dataset[i].score;
	}
	stats.mean = sum / count;
	stats.stddev = sqrt((sum_sq / count) - (stats.mean * stats.mean));

	quick_sort(scores, 0, count - 1);
	if (count % 2 == 0)
		stats.median = (*scores[count / 2 - 1] + *scores[count / 2]) / 2;
	else
		stats.median = *scores[count / 2];
	return stats;
}


int report_data(FILE *fp, RECORD *dataset, STATS stats) {
	fprintf(fp,
			"Stats:value\nCount: %d\nMean: %.2f\nStddev: %.2f\nMedian: %.2f\n\n",
			stats.count, stats.mean, stats.stddev, stats.median);
	fprintf(fp, "name:score,grade\n");
	for (int i = stats.count - 1; i >= 0; i--) {
		fprintf(fp, "%s:%.1f,%s\n", dataset[i].name, dataset[i].score,
				grade(dataset[i].score).letter_grade);
	}

	return 1;
}
