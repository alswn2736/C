#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
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

    char origin[80];
    char encoded[80];
    fgetc(stdin);
    printf("Enter a sentence to encode: ");
    gets(origin, 80, stdin);
    encodedSentence(alphabet, origin, encoded);
    printf("original sentence: ");
    printf("%s\n", origin);
    printf("encoded sentence: ");
    printf("%s\n", encoded);

    return 0;
}