#include<stdio.h>
#include<stdlib.h>

int l1,h1,l2,h2;
int**m1;
int**m2;
int**res;

int main() {
	scanf("%d %d %d %d",&l1,&h1,&l2,&h2);
	if(h1!=l2){
		fprintf(stderr,"illegal input!\n");
		return -1;
	}
	m1 = (int**)malloc(h1 * sizeof(int*));
	for(int i = 0;i < h1;i++){
		m1[i] = (int*)malloc(l1 * sizeof(int));
		for(int j = 0;j < l1;j++){
			scanf("%d",&m1[i][j]);
		}
	}
	printf("finish1\n");
	m2 = (int**)malloc(h2 * sizeof(int*));
	for(int i = 0;i < h2;i++){
		m2[i] = (int*)malloc(l2 * sizeof(int));
		for(int j = 0;j < l1;j++){
			scanf("%d",&m2[i][j]);
		}
	}
	printf("finish2\n");
    system("pause");
    return 0;
}