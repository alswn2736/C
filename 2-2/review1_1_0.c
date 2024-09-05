#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
void print_reverse(char* str, int end) {
	printf("%c", str[end]);

	if (end == 0)
		return 0;

	return print_reverse(str, end - 1);		// 순환
}
int main(void) {
	char str[100];

	printf("Enter any string: ");
	scanf("%s", str);

	printf("Reversed String is: ");
	print_reverse(str, strlen(str) - 1);

	return 0;
}