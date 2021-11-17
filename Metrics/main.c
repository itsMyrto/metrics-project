#include <stdio.h>
#include <string.h>

void makeArray(int A[],int elements[],int size)
{
  int i;

  for(i=0;i<size;i++)
  {
    if(elements[i]==0)
      break;
    A[elements[i]-1]=elements[i];
  }

  for(i=0;i<49;i++)
  {
    if(A[i]==0)
      A[i]=i+1;
  }
  return;
}

void sumArray(int B[],int elements[],int size)
{
  int i;

  for(i=0;i<size;i++)
  {
    if(elements[i]==0)
      break;
    B[elements[i]-1]++;
  }

  return;
}

void bubbleshort(int A[],int B[])
{
  int i,j,temp,temp2;
  for(i=1;i<49;i++)
  {
    for(j=48;j>=i;j--)
    {
      if(B[j]>B[j-1] || (B[j]==B[j-1] && A[j]<A[j-1]))
      {
        temp=B[j];
        B[j]=B[j-1];
        B[j-1]=temp;
        temp2=A[j];
        A[j]=A[j-1];
        A[j-1]=temp2;
      }
    }
  }

  return;
}

void bubbleshortFloat(int A[],float B[])
{
  int i,j,temp;
  float temp2;
  for(i=1;i<49;i++)
  {
    for(j=48;j>=i;j--)
    {
      if(B[j]>B[j-1] || (B[j]==B[j-1] && A[j]<A[j-1]))
      {
        temp2=B[j];
        B[j]=B[j-1];
        B[j-1]=temp2;
        temp=A[j];
        A[j]=A[j-1];
        A[j-1]=temp;
      }
    }
  }

  return;
}

void printArray(int A[],int number)
{
  int i;
  for(i=0;i<number;i++)
    printf("%d ",A[i]);
}

void dn(int elements[],int B[],int C[],int D[],int size)
{
  int i,num,lines;
  lines=1;
  num=1;
  for(i=0;i<size;i++)
  {
    if(elements[i]==0)
      break;
    if(D[elements[i]-1]==0)
    {
      C[elements[i]-1]=lines-1;
      D[elements[i]-1]=1;
    }
    num++;
    if(num==8)
    {
      lines++;
      num=1;
    }
  }
  
  for(i=0;i<49;i++)
  {
    if(B[i]==0)
      C[i]=size/7;
  }
  return;
}

void sum2Array(int B[],int C[],int G[])
{
  int i;

  for(i=0;i<49;i++)
    G[i]=B[i]+C[i];
}


int main()
{
  FILE *fp;
  int number,metric,variable,B[49]={0},A[49]={0},i,j,k,C[49]={0},max=0,D[49]={0},G[49]={0},n;
  char namefile[50]="";
  float rdn[49]={0};

  scanf("%d %d",&number,&metric);

  fscanf(stdin, "%s", namefile);

  fp=fopen(namefile,"r");

  if(number<=0 || number>=50 || metric<=-1 || metric>=4)
  {
    printf("Wrong Input!");
    return 1;
  }
  if(fp==NULL)
  {
    printf("File Error!");
    return 1;
  }

  k = '\0';
  j = '\n';

  while (k=fgetc(fp), k!= EOF)
  {
    if (k=='\n' && j!= '\n')
      max++;
    j = k;
  }
  if (j!='\n')
    max++;

  int elements[max*7];

  for(i=0;i<max*7;i++)
    elements[i]=0;

  fp=fopen(namefile,"r");

  i=0;
  while (1)
  {
    n=fscanf(fp, "%d", &variable);
    if(n==EOF) 
      break;
    elements[i]=variable;
    i++;
  }

  if(metric==0)
  {
    makeArray(A,elements,max*7);
    sumArray(B,elements,max*7);
    bubbleshort(A,B);
    printArray(A,number);
  }

  if(metric==1)
  {
    makeArray(A,elements,max*7);
    sumArray(B,elements,max*7);
    dn(elements,B,C,D,max*7);
    bubbleshort(A,C);
    printArray(A,number);
  }
  
  if(metric==2)
  {
    makeArray(A,elements,max*7);
    sumArray(B,elements,max*7);
    dn(elements,B,C,D,max*7);
    sum2Array(B,C,G);
    bubbleshort(A,G);
    printArray(A,number);
    
  }

  if(metric==3)
  {
    makeArray(A,elements,max*7);
    sumArray(B,elements,max*7);
    dn(elements,B,C,D,max*7);
    k=0;
    
    for(i=0;i<max*7;i++)
    {
        if(elements[i]==0)
            break;
        else
            k++;
    }
    
    for(i=0;i<49;i++)
    {
      if(B[i]!=0)
        rdn[i]=C[i]-((k/7)/(1.0*B[i]));
    }
    bubbleshortFloat(A,rdn);
    printArray(A,number);
  }
  fclose(fp);

  return 0;

}