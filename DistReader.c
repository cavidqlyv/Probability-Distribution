#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum //Enum For Distribution
{
    Normal=1,
    Binomial=2,
    StudentT=3,
    ChiSquare=4,
    TDist=5
} distType;

//Check file opening
FILE *OpenFile(char *filename) 
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Problem couldnt open the file\n\n");
        exit(1);
    }
    return fp;
}

//Calculation for finding position of numberOfTrials in the binomial CSV file
int numberOfTrials(int userInput){
    int col = 3;
    int n = 5;
    int x = userInput / 5;
     for (int i = 1; i < x; i++)
     {
             col = col + (n + 1);
             n+=5;
     }
     return col;
}


//:D
int checkProbFloat(int prob){if(prob==25){return 2;}else if(prob>=75){return (prob+=25)/10;}else if(prob>=25){return (prob+=15)/10;}else{return prob/10;}}


//Normal Dist 
void extractDataNormal(FILE *fp, int n, int m)
{
    char str[1000], *token; //str for string line, token for 1 cell
    int i = 0, j = 0; // i for column row and j for row
    do
    {
        i = 0; //set row counter to zero on every line begining
        fscanf(fp, "%s", str);
        j++; //increase the column counter
        token = strtok(str, ";");
        while (token != NULL) // we go next token(cell) if token is empty
        {
            token = strtok(NULL, ";");
            i++;//increase the row counter
            if (i == n && j == m) //overlap  of  values
            {
                printf("RESULT IS:%s\n\n\n", token);// print of the Normal Dist value
            }
        }
    } while (fgetc(fp) != EOF); //while it's not the end of the file, go next line
}

//Binomial
void extractDataBinomial(FILE *fp, int x, int p, int userInput) 
{
    char str[1000], *token;
    int i = 0, j = 0;
    x = numberOfTrials(userInput)+x; // finding the right row by just adding position of numbersoftrials to number of successes 
    do
    {
        fscanf(fp, "%s", str);
        j++;
        i = 0;
        token = strtok(str, ";");
        while (token!=NULL)
        {
                token = strtok(NULL, ";");

                if (j == x && i == p-3)
                {
                        printf("RESULT IS:%s\n\n\n", token);
                        break;
                        break;
                }
                i++;
               
        }
    } while (fgetc(fp) != EOF);
}

//StudentT
void extractDataStudentT(FILE *fp, int n, int m)
{
    char str[1000], *token;
    int p=0, i = -1, j = -1;
    float val;
    do
    {
        i = 0;
        fscanf(fp, "%s", str);
        j++;
        token = strtok(str, ";");
        while (token != NULL)
        {
            if (atof(token)*1000==n && j==0) // Used for find the position of the column if token is equal to the given n on line 1. We save this pos in p variable.
            {
                p=i;
            }
            
            token = strtok(NULL, ";");
            i++;
            if (i == p && j == m)  // used column position (p) for find result
            {
                printf("RESULT IS:%s\n\n\n", token);
            }
        }
    } while (fgetc(fp) != EOF);
}

//CHI-Square
void extractDataChi(FILE *fp, int n, int m)
{
    char str[1000], *token;
    int p=0, i = -1, j = -1;
    float val;
    do
    {
        i = 0;
        fscanf(fp, "%s", str);
        j++;
        token = strtok(str, ";");
        while (token != NULL)
        {
            if (atof(token)*1000==n && j==0)
            {
                p=i;
            }
            
            token = strtok(NULL, ";");
            i++;
            if (i == p && j == m)
            {
                //val = atof(token);
                printf("RESULT IS:%s\n\n\n", token);
            }
        }
    } while (fgetc(fp) != EOF);
}

//T dist
void extractDataTdist(FILE *fp, int n, int m)
{
    char str[1000], *token;
    int i = -1, j = -1;
    float val;
    do
    {
        i = 0;
        fscanf(fp, "%s", str);
        j++;
        token = strtok(str, ";");
        while (token != NULL)
        {
            
            token = strtok(NULL, ";");
            i++;
            if (i == n && j == m)
            {
                printf("RESULT IS:%s\n\n\n", token);
            }
        }
    } while (fgetc(fp) != EOF);
}




void SelectDistType()
{
       

    distType choise; //enum for distribution selection
  
    while (1)
    {
        printf("Please select Probability Distribution type:\n1:Normal distribution\n\n2:Binomial distribution\n\n3:Student's t distribution\n\n4:Chi-square distribution\n\n5:F-distribution\n\n0:Exit\n\n");
        int ch;
        scanf("%d", &choise);

        char *path[30];
        printf("Please write file Name:"); // Get File name from user
        scanf("%s", path);
        printf("path is :%s\n", path);
        FILE *ptrf = OpenFile(path); // open file

        int line = 0, col = 0; // all temp variables are stored at here
        int c, x, n, p, new;
        float prob, z, f;
        switch (choise)
        {
        case Normal: // Normal Distribution
            printf("This program will give you the result of N(0,1)\n");
            printf("Give us a float number with 2 digits after the comma, ex 1.22\n");
            scanf("%f", &z);
            new = z * 100;
            printf("new=%d\n", new);
            col = new % 10;
            line = new / 10;
            printf("For line %d, col %d, the result will be\n", line, col);
            extractDataNormal(ptrf, col + 1, line + 2);
            break;

        case Binomial: //Binomial Distribution
            printf("This program will give you the result of Binomial distribution from given csv file\n");
            printf("Give us number of trials [5,10,15,20,25]\n");
            scanf("%d", &n);
            printf("Number of successes\n");
            scanf("%d", &x);
            printf("Give us a Probability of success on a single trial\n");
            scanf("%f", &prob);

            p = prob * 100;

            extractDataBinomial(ptrf, x, checkProbFloat(p) + 2, n);
            break;

        case StudentT: //Student's t Distribution
            printf("This program will give you the result of Student's t-distribution from csv file\n");
            printf("Give us a float number, ex 1.99\n After the comma must be [0.9 ; 0.95 ; 0.975 ; 0.99 ; 0.995 ; 0.999]\n");
            scanf("%f", &z);
            new = z * 1000;
            col = new % 1000;
            line = new / 1000;
            f = col / 1000;
            printf("For line %d, col %f, the result will be\n", line, f);
            extractDataStudentT(ptrf, col, line);
            break;

        case ChiSquare: // Chi-Square Distribution
            printf("This program will give you the result of Chi-square form csv file\n");
            printf("Give us a float number, ex 1.995\n After the comma must be [0.995 ; 0.99 ; 0.975 ; 0.95 ; 0.9 ; 0.1 ; 0.05 ; 0.025 ; 0.01]\n");
            scanf("%f", &z);
            new = z * 1000;   //1.995 1995
            col = new % 1000; //
            line = new / 1000;
            f = col / 1000;
            printf("For line %d, col %f, the result will be\n", line, f);
            extractDataChi(ptrf, col, line);

            break;

        case TDist: // T Distribution
            printf("This program will give you the result of Student's t-distribution from csv file\n");
            printf("Give us row number in the range of [1-30]\n");
            scanf("%d", &line);

            printf("Give col number in the range of [1-10]\n");
            scanf("%d", &col);
            printf("For line %d, col %d, the result will be\n", line, col);
            extractDataTdist(ptrf, col, line);
            break;
        default:
            printf("Distribution not found\n");
            exit(1);
            break;
        }

    }
}

int main() // use filepath at the startup. ex ./DistReader normal.csv
{

    SelectDistType();

    return 0;
}