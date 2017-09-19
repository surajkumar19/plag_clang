#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include<math.h>
#include <dirent.h>


#include "global.h"
#include "bagofwords.h"
#include "lcs.h"
#include "fingerprint.h"


void main()
{
    char path[100]={'\0'};
    scanf("%[^\n]s",&path);     //directory path
    scan_dir(path);
    int i,j;
    for(i=0;i<fcount;i++)
    {
        //printf("%s\n",file[i]);
    }
    for (i=0;i<fcount;i++)
    {

        for (j=0;j<fcount;j++)
        {
            openfile(file[i],file[j]);
            bagofwords();
            lcs();
            fingerprinting();
        }


    }
    printmatrix();

}

static void scan_dir(const char *dir)
{
    /*This function takes a path and stores all the file names from that directory to the
        an array called files.*/
    struct dirent * entry;
    DIR *d = opendir( dir );
    int c=0,ff=0;
   	if (d == 0)
   	{
	    perror("opendir");
	    return;
    }
    while ((entry = readdir(d)) != 0)
    {
        if(c>1)
    	{
    		fcount+=1;
    		strcpy(file[ff],dir);
    		strcat(file[ff],"\\");
            strcat(file[ff],entry->d_name);
	    	strcpy(name[ff],entry->d_name);
	    	printf("%s\n",name[ff]);
	    	ff+=1;
    	}
    	c+=1;
    }
    closedir(d);
}


void openfile(char f1[],char f2[])
{
    /*this function takes two file names as input and reads the data in the files
     and stores it in strings declared globally. */
    int i,j;

    // making strings empty
    for(i=0;i<10;i++){
        for(j=0;j<10;j++)
        {
            strings1[i][j]='\0';
            strings2[i][j]='\0';
        }
    }
    for(j=0;j<50;j++)
        {
            strings1_1[j]='\0';
            strings2_2[j]='\0';
        }

    ;



    FILE *fptr;
    char ch;

   /*  open the file1 for reading */
    fptr = fopen(f1, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    ch = fgetc(fptr);
    i=0;
     j=0;
     int p=0;
    while (ch != EOF)
    {

        if(ch!=' ')
        {
            if (ch>64 && ch<91)
            {
                ch=ch+32;
            }
            strings1_1[p]=ch;
            p++;
            strings1[i][j]=ch;

        }

        j++;
        ch = fgetc(fptr);
        if(ch==' ')
        {
            i++;
            j=0;
            ch = fgetc(fptr);
        }
    }
    fclose(fptr);



   /*  open the file2 for reading */
    fptr = fopen(f2, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    ch = fgetc(fptr);
    i=0;
    j=0;
    p=0;
    while (ch != EOF)
    {
        if(ch!=' ')
        {
            if (ch>64 && ch<91)
            {
                ch=ch+32;
            }
            strings2_2[p]=ch;
            p++;
            if (ch>='a' || ch<='z')
            {
                strings2[i][j]=ch;
            }


        }

        j++;
        ch = fgetc(fptr);
        if(ch==' ')
        {
            i++;
            j=0;
            ch = fgetc(fptr);
        }
    }
    fclose(fptr);
}


void printmatrix()
{
    /*this prints a matrix of all files and the plagiarized values between files*/
    printf("------------------------------------------------------");
    printf("\n      plagarism detector using bag of words.\n");
       printf("\n");
    int i,j,k=0;
    printf("           ");
    for(i=0;i<fcount;i++)
    {
        printf("%s  ",name[i]);
    }
    printf("\n");
    for (i=0;i<fcount;i++)
    {
        printf("%s  ",name[i]);
        for (j=0;j<fcount;j++)
        {
            printf("%*.2f     ",6,bagofwordsplag[k]);
            k++;
        }
        printf("\n");

    }
    printf("\n\n");

 printf("------------------------------------------------------\n");
    printf("      plagarism detector using LCS.\n");
    printf("\n");
    k=0;
    printf("           ");
    for(i=0;i<fcount;i++)
    {
        printf("%s  ",name[i]);
    }
    printf("\n");
    for (i=0;i<fcount;i++)
    {
        printf("%s  ",name[i]);
        for (j=0;j<fcount;j++)
        {
            printf("%*.2f     ",6,lcsplag[k]);
            k++;
        }
        printf("\n");

    }
    printf("\n\n");
    k=0;


 printf("------------------------------------------------------\n");
    printf("      plagarism detector using FingerPrinting.\n");
    printf("\n");
    printf("           ");
    for(i=0;i<fcount;i++)
    {
        printf("%s  ",name[i]);
    }
    printf("\n");
    for (i=0;i<fcount;i++)
    {
        printf("%s  ",name[i]);
        for (j=0;j<fcount;j++)
        {
            printf("%*.2f     ",6,fingerplag[k]);
            k++;
        }
        printf("\n");

    }
    printf("\n\n");
 printf("------------------------------------------------------\n");

}


