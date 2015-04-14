#include <cstdlib>
#include <cstdio>
#include <ctime>

const int n = 100;
const int m = 300;

int main() {
	srand(time(NULL));
	printf("%d %d\n", n, m);
	
	for(int i = 0; i < m / 3; ++i) {
		printf("%d %d\n", i + 1, ((i + 1) % n) + 1);
		for(int j = 0; j < 2; ++j) {
        	int l = rand() % n + 1;
			int r = rand() % n + 1;
			while(l == r) r = rand() % n + 1;
			
			printf("%d %d\n", r, l);
    	}
    }
}