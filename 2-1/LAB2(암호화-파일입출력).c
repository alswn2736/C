#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
void encoded(int distance, char a[]) {
	for (int i = 0; i < 26; i++) {
		a[i] = 'A' + distance + i;
		if (a[i] > 'Z')
			a[i] -= 26;
		//printf("%c", a[i]);
	}
}
void encodedSentence(char a[], char o[], char e[]) {
	int i;
	for (i = 0; o[i] != '\0'; i++) {
		if (o[i] >= 'A' && o[i] <= 'Z')
			e[i] = a[o[i] - 'A'];

		else
			e[i] = o[i];
	}
	e[i] = '\0';
}
int main(void) {
	int distance;
	char alphabet[26];
	FILE* fp1;
	FILE* fp2;
	printf("Enter a distance for encodeing: ");
	scanf("%d", &distance);

	printf("----------------------------------------------------\n");
	printf("alphabet: \t");

	for (int i = 'A'; i <= 'Z'; i++)
		printf("%c", i);

	printf("\nencoded: \t");
	encoded(distance, alphabet);
	for (int i = 0; i < 26; i++)
		printf("%c", alphabet[i]);
	
	printf("\n\n");

	if ((fp1 = fopen("original.txt", "r")) == NULL) {
		printf("파일 오픈 에러1");
		exit(1);
	}

	if ((fp2 = fopen("encoded.txt", "w")) == NULL) {
		printf("파일 오픈 에러2");
		exit(1);
	}

	char origin[80];
	char encoded[80];

	while (fgets(origin, sizeof(origin), fp1) != NULL) {
		encodedSentence(alphabet, origin, encoded);
		fputs(encoded, fp2);
	}
	fclose(fp1);
	fclose(fp2);

	return 0;
}