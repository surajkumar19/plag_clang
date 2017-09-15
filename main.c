#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include<math.h>
#include <dirent.h>
char file[10][100]={'\0'};
char name[20][20];
int fcount=0;

static void scan_dir(const char *dir);

float bagofwordsplag[40]={'\0'};
float lcsplag[40]={'\0'};
float fingerplag[40]={'\0'};
int mcount=0;

void main()
{
    scan_dir("C:\\Users\\suraj kumar\\Desktop\\msit\\4.cspp2\\c\\project\\plag_final_0\\New folder");
    int i,j;
    for(i=0;i<fcount;i++)
    {
        printf("%s\n",file[i]);
    }
    for (i=0;i<fcount;i++)
    {

        for (j=0;j<fcount;j++)
        {
            openfile(file[i],file[j]);
        }


    }
    printmatrix();

}

static void scan_dir(const char *dir)
{
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
    		//strcpy(file[ff],dir);
	    	strcat(file[ff],entry->d_name);
	    	strcpy(name[ff],entry->d_name);
	    	//printf("%s\n",file[ff]);
	    	ff+=1;
    	}
    	c+=1;
    }
    closedir(d);
}




void openfile(char f1[],char f2[])
{
    char strings1[10][10]={'\0'};
    char strings2[10][10]={'\0'};
    char strings1_1[50]={'\0'};
    char strings2_2[50]={'\0'};
    int freq1[10]={'\0'};
    int freq2[10]={'\0'};

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
    int i=0, j=0,p=0;
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
            strings2[i][j]=ch;

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
    int k=0;
    /*frequency of words in file1 */
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            if(strcmp(strings1[i],strings1[j])){}
            else{
                freq1[k]+=1;
                if(i!=j)
                {
                   memset(strings1[j],0,strlen(strings1[j]));
                }

            }

        }
        k++;
    }
    k=0;
    /*frequency of words in file1 */
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            if(strcmp(strings2[i],strings2[j])){}
            else{
                    //if(strings2[j]!=0){}
                freq2[k]+=1;
                if(i!=j)
                {
                   memset(strings2[j],0,strlen(strings2[j]));
                }

            }

        }
        k++;
    }

    int sum=0;
    for(i=0;strings1[i][0]!=0;i++)
    {
        for(j=0;strings2[j][0]!=0;j++)
        {
            if(strcmp(strings1[i],strings2[j])){}
            else{
                sum+=freq1[i]*freq2[j];
            }
        }
    }

    float sqrt1=0,sqrt2=0;
    for(i=0;strings1[i][0]!=0;i++)
    {
        sqrt1+=freq1[i]*freq1[i];
    }
    sqrt1=sqrt (sqrt1);
    for(i=0;strings2[i][0]!=0;i++)
    {
        sqrt2+=freq2[i]*freq2[i];
    }
    sqrt2=sqrt (sqrt2);
    bagofwordsplag[mcount]=((float)sum/(sqrt1*sqrt2))*100;
    //printf("plag(bag of words) = %.2f %%\n",((float)sum/(sqrt1*sqrt2))*100);




    /*lcs plagarism starts from here*/
    int a=strlen(strings1_1)+1;
    int b=strlen(strings2_2)+1;
    int matrix[a][b];
    for(i=0;i<a;i++)
    {
        for (j=0;j<b;j++)
        {
            matrix[i][j]=0;
        }
    }
    char aa;
    char bb;
    for(j=1;j<b;j++)
    {
        for (i=1;i<a;i++)
        {
            aa=strings1_1[i-1];
            bb=strings2_2[j-1];
            if(strings1_1[i-1]==strings2_2[j-1])
            {
                matrix[i][j]=(matrix[i-1][j-1])+1;


            }

        }
    }


    int max=0;
    for(j=0;j<b;j++)
    {
        for (i=0;i<a;i++)
        {
            if (max<matrix[i][j])
            {
                max=matrix[i][j];
            }
        }

    }
    lcsplag[mcount]=(((float)max*2)/(a+b-2))*100;
    //printf("plag(lcs) = %.2f %%\n",(((float)max*2)/(a+b-2))*100);

    /*plag detection fingerprinting     */
    int kgram=4;
    int z=strlen(strings1_1)-(kgram-1);
    int hash1[z];
    int hash2[strlen(strings2_2)-(kgram-1)];

    for(i=0;strings1_1[i+3]!='\0';i++)
    {
        hash1[i]=(strings1_1[i]*1000+strings1_1[i+1]*100+strings1_1[i+2]*10+strings1_1[i+3])%10007;

    }
    //for(i=0;strings1_1[i+3]!='\0';i++)
   // {
   //     printf("%d \n",hash1[i]);

   // }
    for(i=0;strings2_2[i+3]!='\0';i++)
    {
        hash2[i]=(strings2_2[i]*1000+strings2_2[i+1]*100+strings2_2[i+2]*10+strings2_2[i+3])%10007;
    }
    removes(hash1,z);
    //for(i=0;strings1_1[i+3]!='\0';i++)
    //{
    //    printf("%d \n",hash1[i]);

    //}
    int hashcount=0;
    for (i=0;i<z;i++)
    {
        for(j=0;j<strlen(strings2_2)-(kgram-1);j++)
        {
            if(hash1[i]==hash2[j])
            {
                hashcount++;
            }
        }
    }

    fingerplag[mcount]=((2*hashcount)/(z+strlen(strings2_2)-(kgram-1)))*100;
    mcount++;
    //printf("plag = %.2f",((float)(2*hashcount)/(float)(z+strlen(strings2_2)-(kgram-1)))*100);



}

void removes(int a[],int z)
{

    int b[z];
    int i,j,flag=0,k=0;
    for(i=0;i<z;i++)
    {
        b[i]='\0';
    }
    for(i=0;i<z;i++)
    {
        flag=0;
        for(j=0;j<z;j++)
        {
            if(b[j]==a[i])
            {
                flag=1;
            }
        }
        if(flag==0)
        {
            //printf("%d    %d\n",a[i],b[k]);
            b[k]=a[i];
            k++;
        }
    }
    for(i=0;i<z;i++)
    {
        a[i]=b[i];
    }



}

void printmatrix()
{
    printf("plagarism detector using bag of words.\n");
       printf("\n");
    int i,j,k=0;
    printf("           ");
    for(i=0;i<fcount;i++)
    {
        printf("%s  ",file[i]);
    }
    printf("\n");
    for (i=0;i<fcount;i++)
    {
        printf("%s  ",file[i]);
        for (j=0;j<fcount;j++)
        {
            printf("%*.2f     ",6,bagofwordsplag[k]);
            k++;
        }
        printf("\n");

    }
    printf("\n\n");

      printf("plagarism detector using LCS.\n");
         printf("\n");
    k=0;
    printf("           ");
    for(i=0;i<fcount;i++)
    {
        printf("%s  ",file[i]);
    }
    printf("\n");
    for (i=0;i<fcount;i++)
    {
        printf("%s  ",file[i]);
        for (j=0;j<fcount;j++)
        {
            printf("%*.2f     ",6,lcsplag[k]);
            k++;
        }
        printf("\n");

    }
    printf("\n\n");
    k=0;

      printf("plagarism detector using FingerPrinting.\n");
         printf("\n");
    printf("           ");
    for(i=0;i<fcount;i++)
    {
        printf("%s  ",file[i]);
    }
    printf("\n");
    for (i=0;i<fcount;i++)
    {
        printf("%s  ",file[i]);
        for (j=0;j<fcount;j++)
        {
            printf("%*.2f     ",6,fingerplag[k]);
            k++;
        }
        printf("\n");

    }
    printf("\n\n");


}


