#include "heap.h"

void PercDown(float* h, int i, int len) {
	float x = h[i];
	int parent, child;
	for (parent = i; (parent * 2) <= len; parent = child) {
		child = parent * 2;
		if ((child != len) && (h[child] < h[child + 1])) {
			child++;
		}
		if (x >= h[child]) {
			break;
		}
		else {
			h[parent] = h[child];
		}
	}
	h[parent] = x;

}

void BuildHeap(float* h, int count)
{
	int i;
	for (i = count / 2; i > 0; i--) {
		PercDown(h, i, count);
	}
}
