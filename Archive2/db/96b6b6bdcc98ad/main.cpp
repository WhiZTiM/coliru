#include <stdio.h>
int main() {
char s1[32];
char* s2="Ciao";
char* s3="pippo";
int age=24;
snprintf (s1,21, "%s %s ho %d anniiusfhv", s2, s3, age);
// Scrivo su s1 attraverso la sprintf
// Ora s1 contiene la stringa "Ciao pippo ho 24 anni"
printf("%s",s1);
return 0;
}