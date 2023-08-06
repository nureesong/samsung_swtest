#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N;
int B[5000];
struct EDGE {
	int n, d;
};
vector<EDGE> A[5000];

// Union-Find
int P[50]; // 부모 브랜드
int C[50]; // 브랜드별 호텔 수

typedef pair<int, int> PAIR;
int X = -1; // brandA 호텔 중 출발지에서 최단거리인 호텔

void PrintBrand() {
	cout << "\n====== B[] ======\n";
	for (int i = 0; i < N; i++) {
		cout << B[i] << " ";
	}
	cout << "\n";
}

void PrintPC() {
	cout << "\n====== P[] ======\n";
	for (int i = 0; i < 5; i++) cout << P[i] << " ";
	cout << "\n====== C[] ======\n";
	for (int i = 0; i < 5; i++) cout << C[i] << " ";
	cout << "\n";
}

void init(int nHotels, int mBrands[]) {
	for (int i = 0; i < 5000; i++) {
		A[i].clear();
		B[i] = 0;
	}
	for (int i = 0; i < 50; i++) {
		P[i] = i;
		C[i] = 0;
	}

	N = nHotels;
	X = -1;
	for (int i = 0; i < N; i++) {
		B[i] = mBrands[i];
		C[B[i]]++;
	}
}

void connect(int hotelA, int hotelB, int distance) {
	A[hotelA].push_back({ hotelB,distance });
	A[hotelB].push_back({ hotelA,distance });
}

int find_root(int n) {
	if (P[n] == n) return n;
	return P[n] = find_root(P[n]);
}

int merge(int hotelA, int hotelB) {
	int brandA = B[hotelA];
	int brandB = B[hotelB];
	int rootA = find_root(brandA);
	int rootB = find_root(brandB);
	if (rootA == rootB) return C[rootA];

	// 브랜드 B에 속하는 모든 호텔의 소속 브랜드를 A로 바꿔야 함 (B배열 갱신 필요)
	// -> 이거 안 하려고 find_root 하는거자나
	P[rootB] = rootA;
	B[hotelB] = brandA;
	C[rootA] += C[rootB];
	C[rootB] = 0;

	//PrintBrand();
	//PrintPC();
	return C[rootA];
}

int Dijkstra(int start, int targetBrand) {
	vector<int> D;
	D.resize(N, 0x7fffffff);
	priority_queue<PAIR> pq; // <-거리, 노드>

	D[start] = 0;
	pq.push({ 0,start });

	while (!pq.empty()) {
		PAIR cur = pq.top(); pq.pop();

		// 최적화: 타겟브랜드 호텔에 최초 방문하는 순간 중단
		// 두번째 다익스트라 때는 X가 아닌 가장 가까운 호텔을 구해야 한다
		int rootBrand = find_root(B[cur.second]);
		if (rootBrand == targetBrand && cur.second != start && cur.second != X) {
			X = cur.second;
			return -cur.first;
		}

		for (EDGE e : A[cur.second]) {
			int nd = -cur.first + e.d;
			if (nd >= D[e.n]) continue;
			D[e.n] = nd;
			pq.push({ -nd,e.n });
		}
	}
	return -1;
}

int move(int mStart, int brandA, int brandB) {
	int a = Dijkstra(mStart, brandA);
	//cout << "\n=================================\n";
	int b = Dijkstra(mStart, brandB);
	//cout << "[MOVE] a = " << a << " b = " << b << "\n";
	return a + b;
}


//////////////////  ***** main.cpp *****  ////////////////////
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int N, int mBrands[]);
extern void connect(int mHotelA, int mHotelB, int mDistance);
extern int merge(int mHotelA, int mHotelB);
extern int move(int mStart, int mBrandA, int mBrandB);

#define MAX_N 5000
#define CMD_INIT 100
#define CMD_CONNECT 200
#define CMD_MERGE 300
#define CMD_MOVE 400

static bool run() {
	int query_num;
	scanf("%d", &query_num);

	int ans;
	bool ok = false;

	for (int q = 0; q < query_num; q++) {
		int query;
		scanf("%d", &query);
		if (query == CMD_INIT) {
			int N;
			int mBrands[MAX_N];
			scanf("%d", &N);
			for (int i = 0; i < N; i++) {
				scanf("%d", &mBrands[i]);
			}
			init(N, mBrands);
			ok = true;
		}
		else if (query == CMD_CONNECT) {
			int mHotelA, mHotelB, mDistance;
			scanf("%d %d %d", &mHotelA, &mHotelB, &mDistance);
			connect(mHotelA, mHotelB, mDistance);
		}
		else if (query == CMD_MERGE) {
			int mHotelA, mHotelB;
			scanf("%d %d", &mHotelA, &mHotelB);
			int ret = merge(mHotelA, mHotelB);
			scanf("%d", &ans);
			//printf("[300] ret = %d ans = %d\n", ret, ans);
			if (ans != ret) ok = false;
		}
		else if (query == CMD_MOVE) {
			int mStart, mBrandA, mBrandB;
			scanf("%d %d %d", &mStart, &mBrandA, &mBrandB);
			int ret = move(mStart, mBrandA, mBrandB);
			scanf("%d", &ans);
			//printf("[400] ret = %d ans = %d\n", ret, ans);
			if (ans != ret) ok = false;
		}
	}
	return ok;
}

int main() {
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);
	int T, MARK;
	scanf("%d %d", &T, &MARK);
	for (int tc = 1; tc <= T; tc++) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}
	return 0;
}
