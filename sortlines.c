/* Iain Weisburg */
/* I was having memory allocation errors, 
so I switched to using dynamic allocation 
and could not use aray notation for lineptr */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qSort(char *lineptr[], int left, int right);

/* sort input lines */
/*
Test:
A day never passes when I dont miss the 
Bus and I really just dont get why I
Can never seem to make it any
Day of the week, because I always try to go 
Every day on time but 
For some reason I never 
Get there with my 
Horrible time management skills.

Scrambled:
A day never passes when I dont miss the 
Horrible time management skills.
Every day on time but 
Day of the week, because I always try to go 
Can never seem to make it any
Bus and I really just dont get why I
For some reason I never 
Get there with my 
*/

int main(void)
{
  char *lineptr[MAXLINES];
  int nlines; /* number of input lines read */
  printf("Type some lines of text:\n");
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
  {
    qSort(lineptr, 0, nlines-1);
    printf("Your line sorted:\n");
    writelines(lineptr, nlines);
    return 0;
  }
  else
  {
    printf("error: input too big to sort\n"); 
    return -1;
  }
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
  int i, x=4, nlines=0;
  char c, *ptr = (char*) malloc(x * sizeof(char));

  for (i=0; (c=getchar()) != EOF && i < MAXLEN * maxlines - 1; i++) { 
    ptr = realloc(ptr, x++ * sizeof(char));
    if (ptr == NULL)
        return -1;
    *(ptr+i) = c;
  } 
  i-=2;
  for (nlines = 0; i >= 0 && nlines < maxlines; i--) 
    if (*(ptr+i) == '\n' || *(ptr+i) == '\0') {
      if (lineptr == NULL)
        return -1;
      lineptr[nlines++] = ptr + (i+1);
      *(ptr+i) = '\0';
    }
  lineptr[nlines++] = ptr;

  return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
  printf("\n");
  while (nlines > 0)
    printf("%s\n",lineptr[--nlines]);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
  char *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

/* qSort: sort lineptr[left]...lineptr[right] into increasing order */
void qSort(char *lineptr[], int left, int right)
{
  int i, last;
  /* do nothing if array contains fewer than two elements */
  if (left >= right) return;
    swap(lineptr, left, (left + right)/2); /* move partition elem */
    last = left; /* to lineptr[0] */
    for (i = left + 1; i <= right; i++) /* partition */
      if (strcmp(lineptr[i], lineptr[left]) > 0)
        swap(lineptr, ++last, i);
    swap(lineptr, left, last);
    qSort(lineptr, left, last-1);
    qSort(lineptr, last+1, right); /* restore partition elem */
}