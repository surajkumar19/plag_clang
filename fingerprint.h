
void fingerprinting()
{
    /*this function calculates plagiarism by fingerprinting method, the K-gram used is 4 and the
        prime number used for modulus is 10007*/
    int kgram=4;
    int z=strlen(strings1_1)-(kgram-1);
    int hash1[z];
    int hash2[strlen(strings2_2)-(kgram-1)];
    int i,j;
    //creating hash table one
    for(i=0;strings1_1[i+3]!='\0';i++)
    {
        hash1[i]=(strings1_1[i]*1000+strings1_1[i+1]*100+strings1_1[i+2]*10+strings1_1[i+3])%10007;

    }
    //for(i=0;strings1_1[i+3]!='\0';i++)
   // {
   //     printf("%d \n",hash1[i]);

   // }

   //creating hash table two
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
{   /*This function takes an array and removes duplicates from this array*/

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
