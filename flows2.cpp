#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define INPUT "balancing.in"
#define OUTPUT "flows2.out"


const double eps = 1e-8;
const int maxn = 202;
/// Note that number of edges should be doubled in case of flows.
const int maxm = 10000;                                          

int head[maxn], next[maxm], to[maxm], din[maxn], dout[maxm], flow[maxm], cap[maxm], h[maxn], ex[maxn], cur_edge[maxn];
int size = 0;
int s, t;
int n, m, N;

queue<int> active_vrtx;

double ain[maxn], aout[maxn];


void add_edge(int q, int w, int c) {
	flow[size] = 0;
	cap[size] = c;
	next[size] = head[q];
	head[q] = size;
	to[size] = w;
	dout[q]++;
	din[w]++;
	size++;
}

void push(int v, int e) {
	if(to[e] != s && to[e] != t && ex[to[e]] == 0) {
		active_vrtx.push(to[e]);
	}
	double val = min(ex[v], cap[e] - flow[e]);
    ex[v] -= val;
	ex[to[e]] += val;
	flow[e] += val;
	flow[e^1] = -flow[e];	
}

void relabel(int v) {                              	
	int u = -1;
	for(int i = head[v]; i != -1; i = next[i]) {	
		if(cap[i] - flow[i] > 0 && (u == -1 || h[u] > h[to[i]])) {
			u = to[i];
		}
	}
	h[v] = h[u] + 1;	
}
	
void discharge(int v) {
	if(head[v] == -1) return;
	while(1) {
		if(cap[cur_edge[v]] > flow[cur_edge[v]] && h[v] == h[to[cur_edge[v]]] + 1) {
			push(v, cur_edge[v]);
		}
		if(ex[v] == 0) break;
		cur_edge[v] = next[cur_edge[v]];
		if(cur_edge[v] == -1) {
			relabel(v);
			cur_edge[v] = head[v];
		}
	}
}


int maxflow() {
	for(int i = 0; i < N; ++i) {
		h[i] = N * (i == s);
		ex[i] = 0;
		cur_edge[i] = head[i];
	}
	for(int i = head[s]; i != -1; i = next[i]) {
		if(ex[to[i]] == 0) active_vrtx.push(to[i]);
		ex[to[i]] += cap[i];
		flow[i] = cap[i];
		flow[i^1] = -flow[i];
	}
	while(!active_vrtx.empty()) {
		discharge(active_vrtx.front());
		active_vrtx.pop();
	}
	return ex[t];	
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
    
    scanf("%d%d", &n, &m);
	s = 2 * n;
	t = 2 * n + 1;
	N = 2 * n + 2;
	memset(head, -1, sizeof head);
	
	for(int i = 0; i < m; ++i) {
		int q, w;
		scanf("%d%d", &q, &w);
		add_edge(q - 1, n + w - 1, m);
		add_edge(n + w - 1, q - 1, 0);
    }

    for(int i = 0; i < n; ++i) {
    	add_edge(s, i, 1);
    	add_edge(i, s, 0);
    	
    	add_edge(i + n, t, 1);
    	add_edge(t, i + n, 0);

    	add_edge(i + n, i, m);
    	add_edge(i, i + n, 0);
    }
	
	/*
	for(int i = 0; i < n; ++i) {
		printf("%d %d\n", din[i], dout[i]);
	}
	*/

	bool good = (maxflow() == n);
    fprintf(stderr, "%d\n", ex[t]);

    if(!good) {
    	fprintf(stderr, "No solution\n");
    	printf("No solution\n");
    }

	for(int i = 0; i < n; ++i) {
		for(int j = head[i]; j != -1; j = next[j]) {
            if((0 == (j&1)) && n <= to[j] && to[j] < 2 * n && (i != to[j] - n)) {
            	ain[to[j] - n] += flow[j];
    			aout[i] += flow[j];
    			printf("%d->%d: %d\n", i + 1, to[j] + 1 - n, flow[j]);
    		}
        }
	}
    

	for(int i = 0; i < n; ++i) {
    	printf("#%d: %lf in, %lf out ; dif = %lf", 1 + i, ain[i], aout[i], fabs(ain[i] - aout[i]));
    	if(fabs(ain[i] - aout[i]) < eps) printf(" Good!\n");
    	else printf(" BAD!!!\n");
    }
		
	return 0;
}