//REII 313 PRACTICAL
//GROUP MEMBERS: N Bhengu (30462533), A Mlambo (27527204), D Mokhasinyane (29875846)
#include <iostream>
#include <math.h>
#include <windows.h>
#include <winuser.h>
#include <algorithm>
#include <cmath>

using namespace std;
//char is used as we will make use of both letters and numbers
char* Info(const char* word);
char aInfo[300];

char* Info(const char* word)
{
//CharToOem is a windows function that translates a string into a OEM- defined set of character set. it also returns a boolean.
CharToOem(word, aInfo);
    return aInfo;
}

int main()
{
//class begin {
//public:
begin:
    //i is for rows
    int i;
    //j is for columns
    int j;
    //NBV is for nonbasic variables & BV is for basic variables
    double A[100][100], B[100][100], C[50], NBV, BV, min, max;
    //d is the last element of the 1st row
	int d;
	int e, F, G, I, J, n, flag, sign, repeat, goal;//flag is a variable that states whether the condition is true or false
//for what the user should do
cout<<Info("Maximization or minimization?(1 is for max & 0 is for min)\n ");
cin>>goal;
cout<<Info("\nHow many variables does the LP problem have?\n");
cin>>F;
cout<<Info("\nHow many conditions are there? (1 or 2)\n");
cin>>G;
//add all variables, free members and the estimated ratio, then add a line for the objective function
	J=F+G+2;
	I=G+1;
// output for the created array
for (i=0; i<I; i++)
    for (j=0;j<J;j++)
    {
      A[i][j]=0;
      B[i][j]=0;
    }
cout<<endl;

cout<<Info("\nInput the free members, use 0 for the objective function\n");
	 for (i=0; i<I; i++)
cin>>A[i][0];
cout<<Info("\nEnter the coefficients(use a space in between) of the LP expressions in each line\n");
	for (i=0; i<I; i++)
       for (j=1;j<=F;j++)
cin>>A[i][j];
    for (j=1; j<=F;j++)
        //A[I+1][j]=1*A[I+1][j];
		A[I-1][j]=-1*A[I-1][j];
	n=F; //n represents the change in the sign of the objective function
//for(i=0; i<I+1; i++)
for (i=0; i<I-1; i++)
{
  n++;
cout<<i+1<<Info("\nIs the condition greater than (use 1) or less than (use 0)?\n");
cin>>sign; //enter then sign (1 or 0) for the condition
    for (j=n;j<=n; j++)
     {
       if (sign==1)
        //A[i][j]=1;
         A[i][j]=-1;
    else
        A[i][j]=1;
    }
}
	for(i=0; i<I; i++)
	{
	    //C[i]=i+F-1;
      C[i]=i+F+1;// refers to the number of basic variables
	}
	if (goal==0)
        goto minimum;
//};
/************************************************************************/
//class Simplex {
//public:
simplex:
//for the solution for the max function
//if (A[I+1][0]<0)
	if (A[I-1][0]<0) {cout<<Info("Maximum Function <0")<<endl;goto end;}
//for the optimal answer
for (i=I-1; i<I; i++)
    //for (j=1; j<J+1;j++)
   for (j=1; j<J-1; j++)
     {
         //if (A[i][j]>0) //if the coefficient is positive, proceed
       if (A[i][j]<0)
        flag=1; // if coefficient is negative,then proceed
    }
	if (flag == 0)
{
//for (j=0; j<I+2; j++)
  //for (i=0; i<I+2;i++)
for (j=0; j<I-2; j++)
   for (i=0; i<I-2; i++)
     {
       if (C[i]>C[i+1])
        {
          NBV=C[i]; C[i]=C[i+1]; C[i+1]=NBV;
          BV=A[i][0]; A[i][0]=A[i+1][0]; A[i+1][0]=BV; //move the basic variables for the next iteration
        }
     }
//for the final solution
cout<<Info("\nThe solution has been found.\n")<<endl<<endl;
cout<<Info("\nThe Maximum function is = ")<<A[I-1][0]<<endl<<endl;
cout<<Info("\nThe Optimum solution is: ")<<endl;
//for (i=0; i<I+1; i++)
    for (i=0; i<I-1; i++)
//cout<<"X"<<C[i]<<"="<<A[i][1]<<endl;
cout<<"X"<<C[i]<<" = "<<A[i][0]<<endl;
    goto end;
}
	max=0;
for (j=1; j<=J-1; j++)
    {
     //if (fabs(A[I-1][j])>max || A[I-1][j]<0)
      if (fabs(A[I-1][j])>max && A[I-1][j]<0) //the fabs function returns the absolute value of the argument(given number)
        {
          max=fabs(A[I-1][j]);
        e=j; //for the number of the resolving column
        }
    }
for (i=0; i<I-1; i++) //for the estimated ratio
    {
      for (j=J-1; j<J; j++)
        {
// working out the conditions of the theory of the simplex method
//if (A[i][e]==0 && A[i][]<0 || A[i][0]<0 &&A[i][0]>0 ||A[i][e]<0)
if (A[i][e]==0 ||A[i][0]<0 &&A[i][e]>0 ||A[i][0]>0 &&A[i][e]<0 ||A[i][0]==0)
    A[i][j]=9999; //let infinity be 9999

else A[i][j]=A[i][0]/A[i][e];
        }
    }
// search for the minimum estimated ratio
min=A[0][J-1];
// take at least the last element of the first row
	d=0;
// write the index of this element and search for the minimum element of the last column
for (i=0; i<I-1; i++)
    {
      if (A[i][J-1]<min)
        {
          min=A[i][J-1];
            d=i; //for the resolving string
        }
    }
	C[d]=e;	// the number of the base variable is already defined,
for (i=0; i<I; i++)
{
  if (i == d) //so that no changes are done to the new array
    {
      for (j=0; j<J-1; j++)
      //B[i][j]=A[i][e]/A[d][j];
        B[i][j]=A[i][j]/A[d][e];
        continue;//to the next iteration
    }
// calculate free members of the new simplex table
    for (j=0; j<1; j++)
  //B[i][j]=A[i][j]-(A[d][0]*A[d][e]/A[i][e]);
    B[i][j]=A[i][j]-(A[d][0]*A[i][e]/A[d][e]);
	}
for (i=0; i<I; i++) //for the coefficients of the variables in the table
{
  if (i==d)
    continue;

for (j=1; j<J-1; j++)
//B[i][j]=A[i][j]-(A[d][0]*A[d][e]/A[i][e]);
    B[i][j]=A[i][j]-(A[i][e]*A[d][j]/A[d][e]);
}
// display:
cout<<Info("A Table")<<endl<<endl;
  for (i=0; i<I; i++)
    for (j=0;j<J;j++)
    {
     cout<<A[i][j]<<" / ";
			if (j==J-1) cout<<endl<<endl;
    }

for (i=0; i<I; i++)
    for (j=0; j<J; j++)
        A[i][j]=0;

flag=0;
	if (B[I-1][0]<0) {cout<<Info("\nThe maximum function is <0")<<endl;goto end;}
	for (i=I-1; i<I; i++)
		for (j=1; j<J-1; j++)
		{
			if (B[i][j]<0) flag=1;
		}
	if (flag == 0)
		{

for (j=0; j<I-2; j++)
   for (i=0; i<I-2; i++)
    {
      if (C[i]>C[i+1])
        {
        //NBV=C[i];C[i]=C[i-1];C[i-1]=NBV;
          NBV=C[i];C[i]=C[i+1];C[i+1]=NBV;
          BV=B[i][0];B[i][0]=B[i+1][0];B[i+1][0]=BV;
        }
    }
cout<<Info("\nThe solution has been found.\n")<<endl<<endl;
cout<<Info("\nThe maximum function is = ")<<B[I-1][0]<<endl<<endl;
cout<<Info("\nThe optimum solution is: ")<<endl;
    for (i=0; i<I-1; i++)
cout<<"X"<<C[i]<<" = "<<B[i][0]<<endl;
    goto end;
		}
max=0;

for (j=1; j<=J-1; j++)
{
  if (fabs(B[I-1][j])>max && B[I-1][j]<0)
    {
      max=fabs(B[I-1][j]);
        e=j;// write the column index
    }
}
for (i=0; i<I-1; i++) //for the calculation of the estimated ratios
 {
    for (j=J-1; j<J; j++)
    {
    //if (B[i][e]==0 && B[i][e]<0 && B[i]<0 || B[i][e]<0 || B[i][0]>0 && B[i][e]<0 || B[i][0]==0) B[i][j]=9999;
      if (B[i][e]==0 || B[i][e]<0 || B[i][0]<0 && B[i][e]>0 ||B[i][0]>0 && B[i][e]<0 || B[i][0]==0) B[i][j]=9999;
      //else B[i][j]=B[i][e]/B[i][0];
        else B[i][j]=B[i][0]/B[i][e];
    }
 }
min=B[0][J-1]; // take at least the last element of the first row
	d=0;
for (i=0; i<I-1; i++) //for searching for the min element in the last column
    {
      if (B[i][J-1]<min)
        {
          min=B[i][J-1];
            d=i;
        }
    }
		C[d]=e;
for (i=0; i<I; i++) //for including the free members into the new array
{
  if (i == d)
    {
      for (j=0; j<J-1; j++)
        A[i][j]=B[i][j]/B[d][e];
        continue;// continue with the next iteration
    }
for (j=0; j<1; j++)
//A[i][j]=B[i][j]-(B[d][0]*B[d][e]/B[i][e]);
    A[i][j]=B[i][j]-(B[d][0]*B[i][e]/B[d][e]);
}
for (i=0; i<I; i++)
{
  if (i==d)
    continue;
for (j=1; j<J-1; j++)
//A[i][j]=B[i][j]-(B[j][e]*B[d][i]/B[d][e]);
    A[i][j]=B[i][j]-(B[i][e]*B[d][j]/B[d][e]);
}
cout<<Info("B Table")<<endl<<endl;
    for (i=0; i<I; i++)
    for (j=0;j<J;j++)
    {
      cout<<B[i][j]<<" / ";
			if (j==J-1) cout<<endl<<endl;
    }
for (i=0; i<I; i++)
    for (j=0; j<J; j++)
        B[i][j]=0;
	goto simplex;
//};
//Function minimization
/***********/
//class minimum {
  //public:
      //double minimum;
minimum:

for (i=I-1; i<I; i++)
  for (j=1; j<J-1; j++)
    {
      if (A[i][j]>0) flag=1;
    }
  if (flag == 0)
    {
      for (j=0; j<I-2; j++)
        for (i=0; i<I-2; i++)
          {
            if (C[i]>C[i+1])
          //if (C[i]>C[i-1])
               {
                //NBV=C[i]; C[i]=C[i-1]; C[i-1]=NBV;
                  NBV=C[i]; C[i]=C[i+1]; C[i+1]=NBV;
             //BV=A[i][0]; A[i][0]=A[i-1][0]; A[i-1][0]=BV;
                  BV=A[i][0]; A[i][0]=A[i+1][0]; A[i+1][0]=BV;
                }
         }
cout<<Info("\nThe solution has been found.\n")<<endl;
cout<<Info("\nThe maximum function is = ")<<A[I-1][0]<<endl<<endl;
cout<<Info("\nThe optimum solution is: ")<<endl;
    for (i=0; i<I-1; i++)
cout<<"X"<<C[i]<<" = "<<A[i][0]<<endl;
        goto end;
    }
//};
max=(A[I-1][1]);
	e=1;

for (j=1; j<=J-1; j++)
    {
      if (A[I-1][j]>max && A[I-1][j]>0)
        {
          max=A[I-1][j];
            e=j;
        }
    }

for (i=0; i<I-1; i++)
    {
      for (j=J-1; j<J; j++)
        {
          if (A[i][e]==0 || A[i][e]<0 || A[i][0]<0 && A[i][e]>0 ||
            A[i][0]>0 && A[i][e]<0 || A[i][0]==0) A[i][j]=9999;
            //else A[i][j]=A[i][e]/A[i][0];
				else A[i][j]=A[i][0]/A[i][e];
        }
    }

min=A[0][J-1];
d=0;

for (i=0; i<I-1; i++)
    {
      if (A[i][J-1]<min)
        {
          min=A[i][J-1];
            d=i;
        }
    }
C[d]=e;

for (i=0; i<I; i++)
{
  if (i == d)
    {
      for (j=0; j<J-1; j++)
      //B[i][j]=A[i][e]/A[j][e];
        B[i][j]=A[i][j]/A[d][e];
            continue;
    }

    for (j=0; j<1; j++)
    B[i][j]=A[i][j]-(A[d][0]*A[i][e]/A[d][e]);
}

for (i=0; i<I; i++)
{
  if (i==d)
    continue;
for (j=1; j<J-1; j++)
    B[i][j]=A[i][j]-(A[i][e]*A[d][j]/A[d][e]);
}
cout<<Info("Table А")<<endl<<endl;
   for (i=0; i<I; i++)
    for (j=0;j<J;j++)
    {
      cout<<A[i][j]<<" / ";
        if (j==J-1) cout<<endl<<endl;
    }
for (i=0; i<I; i++)
    for (j=0; j<J; j++)
        A[i][j]=0;

/*************************/
flag=0;

for (i=I-1; i<I; i++)
  for (j=1; j<J-1; j++)
    {
      if (B[i][j]>0) flag=1;
    }
 if (flag == 0)
    {
      for (j=0; j<I-2; j++)
        for (i=0; i<I-2; i++)
          {
            if (C[i]>C[i+1])
              {
                NBV=C[i];C[i]=C[i+1];C[i+1]=NBV;
                BV=B[i][0];B[i][0]=B[i+1][0];B[i+1][0]=BV;
              }
        }
cout<<Info("\nThe solution has been found.\n")<<endl<<endl;
cout<<Info("\nThe minimum function is = ")<<B[I-1][0]<<endl<<endl;
cout<<Info("\nThe optimum solution is: ")<<endl;
    for (i=0; i<I-1; i++)
cout<<"X"<<C[i]<<" = "<<B[i][0]<<endl;
        goto end;
    }

max=B[I-1][1];
	e=1;

for (j=1; j<=J-1; j++)
    {
      if (B[I-1][j]>max && B[I-1][j]>0)
        {
            max=B[I-1][j];
				e=j;
        }
    }

for (i=0; i<I-1; i++)
{
  for (j=J-1; j<J; j++)
    {
      if (B[i][e]==0 || B[i][e]<0 || B[i][0]<0 && B[i][e]>0 ||
       B[i][0]>0 && B[i][e]<0 || B[i][0]==0) B[i][j]=9999;
       //else B[i][j]=B[i][e]/B[i][0];
				else B[i][j]=B[i][0]/B[i][e];
    }
}
min=B[0][J-1];
	d=0;

for (i=0; i<I-1; i++)
 {
   if (B[i][J-1]<min)
    {
        min=B[i][J-1];
        d=i;
    }
}
	C[d]=e;

for (i=0; i<I; i++)
{
  if (i == d)
    {
      for (j=0; j<J-1; j++)
        //A[i][j]=B[i][e]/B[d][e];
        A[i][j]=B[i][j]/B[d][e];
            continue;
			}
    for (j=0; j<1; j++)
        A[i][j]=B[i][j]-(B[d][0]*B[i][e]/B[d][e]);
	}
	for (i=0; i<I; i++)
	{
		if (i==d)
        continue;
    for (j=1; j<J-1; j++)
  //for (i=1; i<I-1; i++)
        A[i][j]=B[i][j]-(B[i][e]*B[d][j]/B[d][e]);
	}
cout<<Info("B Table")<<endl<<endl;
    for (i=0; i<I; i++)
      for (j=0;j<J;j++)
		{
          cout<<B[i][j]<<" / ";
			if (j==J-1) cout<<endl<<endl;
		}

for (i=0; i<I; i++)
    for (j=0; j<J; j++)
        B[i][j]=0;
goto minimum;

/*******************************/
//class theEnd {
   //public:
end:
cout<<Info("do you want to try again?(1 is yes/0 is no)");
cin>>repeat;
	 if (repeat==1)
        goto begin;
	return 0;
}
//};
