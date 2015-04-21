#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define INPUT "balancing.in"
#define OUTPUT "gauss.out"

const double eps = 1e-8;
const int maxn = 100;
const int maxm = 10000;

int head[maxn], next[maxm], to[maxm], din[maxn], dout[maxn];
int size = 0;
bool bound[maxn];
const double alpha = 0.01;

double a[maxn], ain[maxn], aout[maxn], c[maxn][maxn];

int p[maxn];

void add_edge(int q, int w) {
	next[size] = head[q];
	head[q] = size;
	to[size] = w;
	dout[q]++;
	din[w]++;
	size++;
}


int main(int argc, char *argv[])  {
	if(argc > 1) {
    	freopen(argv[1], "r", stdin);
    } else {
    	freopen(INPUT, "r", stdin);
    }
    
    if(argc > 2) {
    	freopen(argv[2], "w", stdout);
    } else {
    	freopen(OUTPUT, "w", stdout);
    }
    
    int n, m;
	scanf("%d%d", &n, &m);
	memset(head, -1, sizeof head);
	
	for(int i = 0; i < m; ++i) {
		int q, w;
		scanf("%d%d", &q, &w);
		add_edge(q - 1, w - 1);
	}
	/*
	for(int i = 0; i < n; ++i) {
		printf("%d %d\n", din[i], dout[i]);
	}
	*/

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) c[i][j] = 0;

		for(int j = head[i]; j != -1; j = next[j]) {
			c[i][to[j]] += 1;
		}

		c[i][i] = -din[i];
	}

	bool good = false;
	memset(bound, 0, sizeof bound);

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; ++j) 
			printf("%lf%c", c[i][j], " \n"[j == n - 1]);

	for(int k = 0; k < n; ++k) {
		int pos = k;
		for(int i = k; i < n; ++i) {
			if(fabs(c[i][k]) >fabs(c[pos][k])) {
				pos = i;
			}
		}

		//fprintf(stderr, "%lf\n", c[pos][k]);

		if(fabs(c[pos][k]) < eps) {
			good = true;
			continue;
		}
		
		bound[k] = true;

		for(int i = k; i < n; ++i) {
			//swap(c[pos][i], c[k][i]);
			double u = c[pos][i];
			c[pos][i] = c[k][i];
			c[k][i] = u;
		}

		for(int i = k + 1; i < n; ++i) {
			double d = c[i][k] / c[k][k];
			for(int j = k; j < n; ++j) {
				c[i][j] -= d * c[k][j];
			}
		}             
	}

	/*
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; ++j) 
			printf("%lf%c", c[i][j], " \n"[j == n - 1]);
	*/

	if(!good) {
		fprintf(stderr, "No solution!!!");
	}

	for(int i = n - 1; i >= 0; --i) {
		if(!bound[i]) {
			a[i] = 1;
		} else {
			a[i] = 0;
			for(int j = i + 1; j < n; ++j) {
				a[i] -= c[i][j] * a[j];
			}
			a[i] /= c[i][i];
		}
	}     

    
    for(int i = 0; i < n; ++i) {
    	ain[i] = aout[i] = 0;
    }

    for(int i = 0; i < n; ++i) {
    	for(int j = head[i]; j != -1; j = next[j]) {
    		printf("%d->%d: %lf\n", i + 1, 1 + to[j], a[to[j]]); 
    		ain[to[j]] += a[to[j]];
    		aout[i] += a[to[j]];
    	}
    }

    for(int i = 0; i < n; ++i) {
    	printf("#%d: %lf in, %lf out ; dif = %lf", 1 + i, ain[i], aout[i], fabs(ain[i] - aout[i]));
    	if(fabs(ain[i] - aout[i]) < eps) printf(" Good!\n");
    	else printf(" BAD!!!\n");
    }
	return 0;
}