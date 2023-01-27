#include "defns.h"

void InsertionSort(int a[], int len) {
	for (int j = 1; j < len; j++) {
		int key = a[j];
		int i = j - 1;
		while (i >= 0 && a[i] > key) {
			a[i + 1] = a[i];
			i--;
		}
		a[i + 1] = key;
	}
}

void InsertionSortEdge(edges a[], int len) {
	for (int j = 1; j < len; j++) {
		edges key = a[j];
		int i = j - 1;
		while (i >= 0 && a[i].end > key.end) {
			a[i + 1] = a[i];
			i--;
		}
		a[i + 1] = key;
	}
}