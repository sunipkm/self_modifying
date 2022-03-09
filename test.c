#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct __attribute__((packed))
{
    uint32_t ident;
    uint32_t pad;
    uint32_t val;
} protected_var;

volatile static protected_var var = {0xdeadbeef, 0xaaaaaaaa, 100};
char *binName;

void updateVal()
{
    if (binName == NULL)
        return;
    FILE *fp = fopen(binName, "r+b");
    if (fp == NULL)
        return;
    uint32_t v;
    int count = 0;
    bool maybe = false;
    while (1)
    {
        if (feof(fp))
            break;
        fread(&v, 4, 1, fp);
        if (v == 0xdeadbeef)
            maybe = true;
        if (maybe && v == 0xaaaaaaaa)
        {
            // printf("Offset %d\n", 4 * count);
            int nval = var.val + 10 + (rand() % 90);
            // modify value here
            // fseek(fp, (count + 1) * 4, SEEK_SET); // unnecessary
            fwrite(&nval, 4, 1, fp);
            break;
        }
        count++;
    }
    fclose(fp);
}

int main(int argc, char *argv[])
{
    printf("This function updates the value of a static variable stored inside the binary.\n");
    binName = argv[0];
    printf("Value: %d\n", var.val);
    atexit(updateVal);
}
