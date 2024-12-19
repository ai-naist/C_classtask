// fopen_sÇÉGÉâÅ[èàóùÇ‹Ç≈ä‹ÇﬂÇƒé©çÏä÷êîâª

#include <stdio.h>
#include <stdlib.h>

// test1
FILE *fopen_func(FILE *, const char *, const char *);
// test2
void FileOpen(FILE **, const char *, const char *);

FILE *fp1, *fp2, *fp3;

int main(void)
{
	fp1 = fopen_func(fp1, "test1.csv", "w");

	FileOpen(&fp2, "test2.csv", "w");

	if (fopen_s(&fp3, "test3.csv", "w") != 0)
		exit(EXIT_FAILURE);

	fprintf(fp1, "hello1");
	fprintf(fp2, "hello2");
	fprintf(fp3, "hello3");

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	return 0;
}

// test1
FILE *fopen_func(FILE *fp, const char *FileName, const char *Mode)
{
	if (fopen_s(&fp, FileName, Mode) != 0)
		exit(EXIT_FAILURE);

	return fp;
}

// test2
void FileOpen(FILE **fp, const char *filename, const char *mode)
{
	if (fopen_s(&*fp, filename, mode) != 0)
		exit(EXIT_FAILURE);
}