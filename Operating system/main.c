#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int n, nf;
int array[256000000];  // array
int p[50];  // array
int hit = 0;
int i, j, k;
int pagefaultcount = 0; // initialization with zero
int loop = 0; // initialization with zero

// Assign Integer Value
int assignIntValue(char *value)
{
    int val;
    printf("%s", value);
    scanf("%d", &val);
    printf("\n");
    return val;
}

// Assign Double Value
double assigndDoubleValue(char *value)
{
    double val;
    printf("%s", value);
    scanf("%f", &val);
    printf("\n");
    return val;
}

// Unique Distance Range of  Number

int UniqueDistanceRangeNum(int M, int m)
{
    int randNumber;

    randNumber = rand() % (M - m) + m;

    return randNumber;
}

// Generate Random  Number

double randumNum(double min, double max)
{
    double randNumber;
    double range = (max - min);
    double div = RAND_MAX / range;
    randNumber = min + (rand() / div);

    return randNumber;
}

//  Generate Reference String

void GenerateReferenceString(FILE *RS)
{
    // P = 1048576; //2^20
    // m = 20;
    // e = 10;
    // t = 0.001;
    int P;
    int e;
    int m;
    double t;
    printf("\t\t\t****************************************************************\n\n");
    printf("\t\t\t *** Please Enter the value for generate Reference String ***\n\n");
    printf("\t\t\t****************************************************************\n\n");

    printf("\n Please Enter virtual memory size 'P' : ");
    scanf("%d", &P);
    printf("\n Please Enter size of L 'e' : ");
    scanf("%d", &e);
    printf("\n Please Enter  rate of motion 'm' : ");
    scanf("%d", &m);
    printf("\n Please Enter probability of transition 't' : ");
    scanf("%lf", &t);

    int s = 0;

    int countAllGeneratedNumbers = -1;
    while (countAllGeneratedNumbers < 1000000)
    {
        double r;
        int numToAppend;
        int i;
        for (i = 0; i < m; i++)
        {
            numToAppend = UniqueDistanceRangeNum((s + e), s);
            fprintf(RS, "%d\n", numToAppend);
            countAllGeneratedNumbers++;
        }

        r = randumNum(0.000, 1.000);

        if (r < t)
        {
            s = UniqueDistanceRangeNum((P - e), 0);
        }
        else
        {
            s = (s + 1) % P;
        }
    }
}

// Function for user Input
void getDataFromUser()
{

    FILE *ptr;

    // Opening referenceString file in reading mode
    ptr = fopen("referenceString.txt", "r");

    if (NULL == ptr)
    {
        printf("file can't be opened \n");
    }
    int R;
    printf("\n Please Enter The Range 0 to 4194304 ( 2^22 ) ");  // 2^22 == 4194304 higher value in our Scenario
    scanf("%d", &R);
    for (i = 0; i < R; i++)
    {
        fscanf(ptr, "%d,", &array[i]);
        // printf("%d\n", array[i]);
        n++;
    }
    // close connection
    fclose(ptr);
    printf("\nEnter no of frames:");
    scanf("%d", &nf);
}

// initialization data
void initializedata()
{
    pagefaultcount = 0;
    for (i = 0; i < nf; i++)
        p[i] = 9999;
}

int isHit(int data)
{
    hit = 0;
    for (j = 0; j < nf; j++)
    {
        if (p[j] == data)
        {
            hit = 1;
            break;
        }
    }

    return hit;
}

int getHitIndex(int data)
{
    int hitind;
    for (k = 0; k < nf; k++)
    {
        if (p[k] == data)
        {
            hitind = k;
            break;
        }
    }
    return hitind;
}

// Display Pages

void displayPages()
{
    for (k = 0; k < nf; k++)
    {
        if (p[k] != 9999)
            printf(" %d", p[k]);
    }
}

// display Page Fault Count

void displayPageFaultCount()
{
    printf("\nTotal no of page faults:%d", pagefaultcount);
}

// Fifo Replacement Algorithms

void FifoReplacementAlgorithms()
{
    initializedata(); // call function
    for (i = 0; i < n; i++)
    {
        printf("\nFor %d :", array[i]);

        if (isHit(array[i]) == 0)
        {

            for (k = 0; k < nf - 1; k++)
                p[k] = p[k + 1];

            p[k] = array[i];
            pagefaultcount++;
            displayPages(); // call function
        }
        else
            printf("No page fault");
    }
    displayPageFaultCount(); // call function
}

// Optimal Replacement Algorithms
void optimalReplacementAlgorithms()
{
    initializedata(); // call function
    int near[50];
    for (i = 0; i < n; i++)
    {

        printf("\nFor %d :", array[i]);

        if (isHit(array[i]) == 0)
        {

            for (j = 0; j < nf; j++)
            {
                int pg = p[j];
                int found = 0;
                for (k = i; k < n; k++)
                {
                    if (pg == array[k])
                    {
                        near[j] = k;
                        found = 1;
                        break;
                    }
                    else
                        found = 0;
                }
                if (!found)
                    near[j] = 9999;
            }
            int max = -9999;
            int repeateindex;
            for (j = 0; j < nf; j++)
            {
                if (near[j] > max)
                {
                    max = near[j];
                    repeateindex = j;
                }
            }
            p[repeateindex] = array[i];
            pagefaultcount++;

            displayPages(); // call function
        }
        else
            printf("No page fault");
    }
    displayPageFaultCount(); // call function
}

// LRU Chance ReplacementAlgorithms

void LruChanceReplacementAlgorithms()
{
    initializedata(); // call function

    int least[50];
    for (i = 0; i < n; i++)
    {

        printf("\nFor %d :", array[i]);

        if (isHit(array[i]) == 0)
        {

            for (j = 0; j < nf; j++)
            {
                int pg = p[j];
                int found = 0;
                for (k = i - 1; k >= 0; k--)
                {
                    if (pg == array[k])
                    {
                        least[j] = k;
                        found = 1;
                        break;
                    }
                    else
                        found = 0;
                }
                if (!found)
                    least[j] = -9999;
            }
            int min = 9999;
            int repeateindex;
            for (j = 0; j < nf; j++)
            {
                if (least[j] < min)
                {
                    min = least[j];
                    repeateindex = j;
                }
            }
            p[repeateindex] = array[i];
            pagefaultcount++;

            displayPages();  // call function
        }
        else
            printf("No page fault!");
    }
    displayPageFaultCount();  // call function
}

//Second Chance Replacement Algorithms

void SecondChanceReplacementAlgorithms()
{
    int usedbit[50];
    int victimptr = 0;
    initializedata();  // call function
    for (i = 0; i < nf; i++)
        usedbit[i] = 0;
    for (i = 0; i < n; i++)
    {
        printf("\nFor %d:", array[i]);
        if (isHit(array[i]))
        {
            printf("No page fault!");
            int hitindex = getHitIndex(array[i]);
            if (usedbit[hitindex] == 0)
                usedbit[hitindex] = 1;
        }
        else
        {
            pagefaultcount++;
            if (usedbit[victimptr] == 1)
            {
                do
                {
                    usedbit[victimptr] = 0;
                    victimptr++;
                    if (victimptr == nf)
                        victimptr = 0;
                }
                while (usedbit[victimptr] != 0);
            }
            if (usedbit[victimptr] == 0)
            {
                p[victimptr] = array[i];
                usedbit[victimptr] = 1;
                victimptr++;
            }
            displayPages();  // call function
        }
        if (victimptr == nf)
            victimptr = 0;
    }
    displayPageFaultCount(); // call function
}

void menu()
{

    printf("\t\t\t ****************Page Replacement Algorithms\*******************\n\n");
}
int main()
{
    time_t t;
    srand((unsigned)time(&t));
    int M[10];
    FILE *fp;
    char *filename = "referenceString.txt";
    fp = fopen(filename, "w"); //open file write mode
    if (fp != NULL)
    {
        // printf("File created successfully!\n");
    }
    else
    {
        printf("Failed to create the file.\n");
        return -1;
    }
    fclose(fp);
    fp = fopen(filename, "a");
    GenerateReferenceString(fp);
    fclose(fp);
    printf("\n\n");
    printf("Reference String generated in text File ! \n");
    printf("\n\n");
    menu();// call menu function
    int choice;
    while (1)  // while loop
    {
        printf("\n1.Enter data\n2.FIFO\n3.Optimal\n4.LRU\n5.Second Chance\n6.Exit\nEnter your choice:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            getDataFromUser(); // call function
            break;
        case 2:
            FifoReplacementAlgorithms(); // call function
            break;
        case 3:
            optimalReplacementAlgorithms(); // call function
            break;
        case 4:
            LruChanceReplacementAlgorithms(); // call function
            break;
        case 5:
            SecondChanceReplacementAlgorithms(); // call function
            break;
        default:
            return 0;
            break;
        }
    }
}
