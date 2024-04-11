#include <stdlib.h>
#include <stdio.h>

#define BYTES 10
#define BYTES_EXPOENT 20

#define RANDOM_FILE_NAME "random.bin"
#define RANDOM_CUT_FILE_NAME "random_cut.bin"
#define PA_FILE_NAME "pa.bin"
#define PG_FILE_NAME "pg.bin"
#define FIB_FILE_NAME "fib.bin"
#define LUCAS_FILE_NAME "lucas.bin"


unsigned int power(int number, int expoent)
{
    int i = 0;
    unsigned int r = 1;

    for (i; i < expoent; i++)
    {
        r = r*number;
    }

    return r;
}


void error_log(int error_number, char *file_name)
{
    switch (error_number)
    {
    case 1:
        printf("Atention, the archive %s alredy exist; switch it's name to correctly work", file_name);
        exit(1);
    }
}


int file_alredy_exists(char *file_name)
{
    FILE *fptr = fopen(file_name, "rb");

    if (fptr != NULL)
    {
        fclose(fptr);
        return 1;
    }

    fclose(fptr);
    fptr = fopen(file_name, "wb");
    fclose(fptr);
    return 0;
}


void random_generator(char *file_name, int number_limit)
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


void pa_sequence_generator(char *file_name, int initial, int root)
{
    __int64 n = initial;
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
}


void pg_sequence_generator(char *file_name, int initial, int root)
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
}


void fib()
{
    
}


void lucas()
{

}



int main()
{
    // Verify if each file alredy exist
    error_log(file_alredy_exists(RANDOM_FILE_NAME), RANDOM_FILE_NAME);
    error_log(file_alredy_exists(RANDOM_CUT_FILE_NAME), RANDOM_CUT_FILE_NAME);
    error_log(file_alredy_exists(PA_FILE_NAME), PA_FILE_NAME);

    // Define params to each_sequence
    int pa_initial = 0;
    int pa_root = 10;

    random_generator(RANDOM_FILE_NAME, 256);
    random_generator(RANDOM_CUT_FILE_NAME, 27);
    pa_sequence_generator(PA_FILE_NAME, pa_initial, pa_root);

    return 0;
}