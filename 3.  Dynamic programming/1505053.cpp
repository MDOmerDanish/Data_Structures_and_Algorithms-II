#include<stdio.h>
//#include<limits.h>
#include<iostream>

using namespace std;

// Matrix Ai has dimension p[i-1] x p[i] for i = 1..n

void PRINT_OPTIMAL(int **s, int i, int j){
   // cout<<"reached here\n";

   // cout<<s[i][j]<<endl;
    if (i == j)
      printf("%c",i+'A'-1);
    else {
        printf("(");
        PRINT_OPTIMAL(s,i,s[i][j]);
        PRINT_OPTIMAL(s,s[i][j]+1,j);
        printf(")");
    }
    return ;
}

int Matrix_mul(int p[], int n)
{
    int m[n][n];
    int **s;
    s = new int*[n];
    for(int i=0; i<n; i++) s[i] = new int[n] ;

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            s[i][j] = 0;
        }
    }

    int i, j, k, L, q;

    for (i=1; i<n; i++)
        m[i][i] = 0;    //number of multiplications are 0(zero) when there is only one matrix

    //Here L is chain length. It varies from length 2 to length n.
    for (L=2; L<n; L++)
    {
        for (i=1; i<n-L+1; i++)
        {
            j = i+L-1;
            m[i][j] = INT_MAX;  //assigning to maximum value

            for (k=i; k<=j-1; k++)
            {
                q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;    //if number of multiplications found less that number will be updated.
                    s[i][j] = k;
                }
            }
        }
    }
    //printf("Minimum number of calculations is %d \n",m[1][n-1]);
    PRINT_OPTIMAL(s,1,n-1);
    printf("\n\n");

    return m[1][n-1];   //returning the final answer which is M[1][n]

}

int main()
{
    int n,i;
    printf("Enter number of matrices\n");
    cin>>n;

    int arr[n+1];
    int m,k;
    //cout<<n<<endl;
    for(int i=0; i<n;i++ ){
        cin>>m>>k;
        arr[i] = m;
    }
    arr[n] = k ;
    //cout<<"All input taken";


    printf("Minimum number of calculations is %d \n", Matrix_mul(arr, n+1));


    return 0;
}
