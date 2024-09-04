#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
void print_fact_exp(int n) {
	for (int i = n; i > 1; i--)
		printf("%d * ", i);

	printf("1");
}
int main(void) {
	int n;
	printf("Enter a number: ");
	scanf("%d", &n);

	printf("%d! = ", n);
	print_fact_exp(n);
	printf("\n");
}