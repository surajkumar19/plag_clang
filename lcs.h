void lcs()
{
    /*this function calculates longest common string between string one and and two using
       dynamic array and calculates the plagiarism*/

    /*create a matrix to find plagiarism using dynamic array*/
    int a=strlen(strings1_1)+1;
    int b=strlen(strings2_2)+1;
    int matrix[a][b];
    int i,j;
    for(i=0;i<a;i++)
    {
        for (j=0;j<b;j++)
        {
            matrix[i][j]=0;
        }
    }
    char aa;
    char bb;
    //fill the matrix with correspondent values "0" for no match and "diagonally up value + 1" if match
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

    //find max of the matrix
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
}
