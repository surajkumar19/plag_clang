void bagofwords()
{
    /*this file calculates the plagarism between above two red files*/
    int freq1[10]={'\0'};
    int freq2[10]={'\0'};
    int i,j,k=0;
    /*calculating the frequency of words in file1 */
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
    /*frequency of words in file2 */
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
    //multiply the frequency of two files
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
    //calculating and inserting plagiarized value into an array
    bagofwordsplag[mcount]=((float)sum/(sqrt1*sqrt2))*100;
    //printf("plag(bag of words) = %.2f %%\n",((float)sum/(sqrt1*sqrt2))*100);

}
