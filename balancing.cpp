#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

#define INPUT "balancing.in"
#define OUTPUT "balancing.out"


const int maxn = 100;
const int maxm = 10000;
const double eps = 1e-8;


int head[maxn], next[maxm], to[maxm], din[maxn], dout[maxn];
int size = 0;
const double alpha = 0.1;

double a[2][maxn], ain[maxn], aout[maxn];

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
	for(int i = 0; i < n; ++i) {
		a[0][i] = 1;
	}

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
	int b = 0;
    for(int T = 0; T < 10000; T++) {
        for(int i = 0; i < n; ++i) {
    		double t = 0;
    		for(int j = head[i]; j != -1; j = next[j]) {
    			t += a[b][to[j]] / din[i];
    		}
    		//fprintf(stderr, "%lf\n", t);
    		a[b^1][i] = a[b][i] + alpha * (t - a[b][i]);
    	}
    	b ^= 1;
	    
	    /*
	    for(int i = 0; i < n; ++i) {
	    	for(int j = head[i]; j != -1; j = next[j]) {
	    		printf("%d->%d: %lf\n", i + 1, 1 + to[j], a[b][j]); 
	    	}
	    }
	    printf("\n");
        */
    }

        
	       
    
    for(int i = 0; i < n; ++i) {
    	//printf("%lf\n", a[b][i]);
    	ain[i] = aout[i] = 0;
    }

    for(int i = 0; i < n; ++i) {
    	for(int j = head[i]; j != -1; j = next[j]) {
    		printf("%d->%d: %lf\n", i + 1, 1 + to[j], a[b][to[j]]); 
    		ain[to[j]] += a[b][to[j]];
    		aout[i] += a[b][to[j]];
    	}
    }

    for(int i = 0; i < n; ++i) {
    	printf("#%d: %lf in, %lf out ; dif = %lf", 1 + i, ain[i], aout[i], fabs(ain[i] - aout[i]));
    	if(fabs(ain[i] - aout[i]) < eps) printf(" Good!\n");
    	else printf(" BAD!!!\n");
    }
	return 0;
}