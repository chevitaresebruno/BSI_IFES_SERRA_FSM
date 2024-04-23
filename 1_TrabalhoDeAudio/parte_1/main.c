#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Files Size
#define BYTES 10
#define BYTES_EXPOENT 20

// Files Name
#define RANDOM_FILE_NAME "random.bin"
#define RANDOM_CUT_FILE_NAME "random_cut.bin"
#define PA_FILE_NAME "pa.bin"
#define PG_FILE_NAME "pg.bin"
#define FIB_FILE_NAME "fib.bin"
#define LUCAS_FILE_NAME "lucas.bin"
#define PRIMO_FILE_NAME "primo.bin"

// Define params to each sequence
#define PA_INITIAL 0
#define PA_ROOT 10
#define PG_INITIAL 1
#define PG_ROOT 5
#define LUCAS_FIRST 2
#define LUCAS_SECOND 1


unsigned int power(const int number, const int expoent)
{
    int i = 0;
    unsigned int r = 1;

    for (i; i < expoent; i++)
    {
        r = r*number;
    }

    return r;
}


int file_alredy_exists(const char *file_name)
{
    FILE *fptr = fopen(file_name, "rb");

    if (fptr != NULL)
    {
        fclose(fptr);
        printf("Atention, the archive %s alredy exist; switch it's name to correctly work", file_name);
        return 1;
    }

    fclose(fptr);
    fptr = fopen(file_name, "wb");
    fclose(fptr);
    return 0;
}


int is_primo(const int n)
{
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}


void random_generator(const char *file_name, const int number_limit)
{
    unsigned int sf = BYTES*power(2, BYTES_EXPOENT);  // sf is "stop flag"
    unsigned int i = 0;
    unsigned char c;

    FILE *fptr = fopen(file_name, "ab");
    
    srand(time(NULL));

    for (i; i<sf; i++)
    {
        c = rand() % number_limit;

        fwrite(&c, sizeof(char), 1, fptr);
    }

    fclose(fptr);
}


void pa_sequence_generator(const char *file_name, const int initial, const float root)
{
    double n = initial;
    unsigned char c;
    unsigned int sf = BYTES*power(2, BYTES_EXPOENT);
    int i = 0;

    FILE *fptr = fopen(file_name, "ab");

    for (i; i < sf; i++)
    {
        n += root;
        c = abs(c)%256;
        fwrite(&c, sizeof(char), 1, fptr);
    }

    fclose(fptr);
}


void pg_sequence_generator(const char *file_name, const int initial, const int root)
{
    __int64 n = initial;
    unsigned char c;
    unsigned int sf = BYTES*power(2, BYTES_EXPOENT);
    int i = 0;

    FILE *fptr = fopen(file_name, "ab");

    for (i; i < sf; i++)
    {
        n = n*root;
        c = abs(c)%256;
        fwrite(&c, sizeof(char), 1, fptr);
    }
    
    fclose(fptr);
}


void lucas_sequence_generator(const char *file_name, const int first, const int second)
{
    unsigned  __int64 n;
    unsigned __int64 n1 = first;
    unsigned __int64 n2 = second;
    
    unsigned char c;
    unsigned int sf = BYTES*power(2, BYTES_EXPOENT);
    int i = 0;

    FILE *fptr = fopen(file_name, "ab");

    for (i; i < sf; i++)
    {
        n = n1+n2;
        n2 = n1;
        n1 = n;

        c = n%256;
        fwrite(&c, sizeof(char), 1, fptr);
    }
    
    fclose(fptr);
}


void fib_sequence_generator(const char *file_name)
{
    lucas_sequence_generator(file_name, 0, 1);
}


void primo_sequence_generator(const char * file_name) {
    unsigned int sf = BYTES*power(2, BYTES_EXPOENT);  // sf is "stop flag"
    unsigned int i = 0;
    unsigned char c;
    unsigned int n = 1;

    FILE *fptr = fopen(file_name, "ab");

    for (i; i<sf; i++)
    {
        while (! is_primo(n))
        {
            n++;
        }

        c = n % 256;

        fwrite(&c, sizeof(char), 1, fptr);
    }

    fclose(fptr);
}


int main()
{
    // Verify if each file alredy exist
    file_alredy_exists(RANDOM_FILE_NAME);
    file_alredy_exists(RANDOM_CUT_FILE_NAME);
    file_alredy_exists(PA_FILE_NAME);
    file_alredy_exists(PG_FILE_NAME);
    file_alredy_exists(LUCAS_FILE_NAME);
    file_alredy_exists(FIB_FILE_NAME);
    file_alredy_exists(PRIMO_FILE_NAME);

    random_generator(RANDOM_FILE_NAME, 256);
    random_generator(RANDOM_CUT_FILE_NAME, 27);
    pa_sequence_generator(PA_FILE_NAME, PA_INITIAL, PA_ROOT);
    pg_sequence_generator(PG_FILE_NAME, PG_INITIAL, PG_ROOT);
    lucas_sequence_generator(LUCAS_FILE_NAME, LUCAS_FIRST, LUCAS_SECOND);
    fib_sequence_generator(FIB_FILE_NAME);
    primo_sequence_generator(PRIMO_FILE_NAME);

    return 0;
}