#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int attributeCount=10;
int attribute=0;
int population[500][10],mutated[200][10];
int populationsize=0;
int newpopulation=0;
int individual;
int fitness[50];
int fitnessfrequency[50];
int fitnessthreshold;
int fitnessfrequencythreshold;
int dist[10][10]={{0,1,3,5,7,6,3,4,9,11},
                    {1,0,2,4,6,4,3,1,3,7},
                    {3,2,0,8,11,17,4,7,1,2},
                    {5,4,8,0,1,10,14,5,4,13},
                    {7,6,11,1,0,6,8,4,2,2},
                    {6,4,17,10,6,0,15,13,12,4},
                    {3,3,4,14,8,15,0,3,4,5},
                    {4,1,7,5,4,13,3,0,6,2},
                    {9,3,1,4,2,12,4,6,0,7},
                    {11,7,2,13,2,4,5,7,0}};
int iterationCount=300000;
/* Function to swap values at two pointers */
int crossover(int male,int female)
{
    
    for(attribute=0;attribute<attributeCount;attribute++)
    {
        if(attribute==0 || attribute==1)
        {
            mutated[newpopulation][attribute]=population[male][attribute];
        }
        else
        {
            mutated[newpopulation][attribute]=population[female][attribute];
        }
    }
    newpopulation+=1;
    return 0;
}

//calculating fitness of each individua 15x+x^2
int fitnessfunc()
{
    
    for(individual=0;individual<populationsize;individual++)
    {
        int x=0;
        for(attribute=0;attribute<attributeCount;attribute++)
        {
            x+=dist[(population[individual][attribute])][population[individual][(attribute+1)%attributeCount]];
            //x+=population[individual][attribute];
        }    
        fitness[individual]=x;
    }
    
    

    return 0;
}
//setting threshols based on fitness of each individual
int fitnessfrequencyCalc()
{
    int j;

    for(individual=0;individual<populationsize;individual++)
    {

        fitnessfrequency[individual]=0;
        for(j=0;j<populationsize;j++)
        {
            if(fitness[individual]==fitness[j])
            {
                fitnessfrequency[individual]+=1;
            }
        }

    }
}
//setting threshold based on fitness of population
int hightestfreq()
{
    int check=0;
    fitnessthreshold=0;
    fitnessfrequencythreshold=0;
    for(individual=0;individual<populationsize;individual++)
    {
        if(fitnessfrequency[individual]==1)
        {
            check++;
        }
    }
    if(check!=populationsize)
    {
        for(individual=0;individual<populationsize;individual++)
        {
            if(fitnessfrequencythreshold<fitnessfrequency[individual])
            {
                fitnessthreshold=fitness[individual];
                fitnessfrequencythreshold=fitnessfrequency[individual];                
            }
        }
    }
    else
    {
        individual=rand()%populationsize;
        fitnessthreshold=fitness[individual];
    }

}
//removing individual below frequency level
int removeindividual(int individualCurrent)
{
    int i;
    if(individualCurrent<populationsize)
    {
        for(i=individualCurrent;i<populationsize;i++)
        {
        	for(attribute=0;attribute<attributeCount;attribute++)
        	{
        		population[i][attribute]=population[i+1][attribute];
        	}
           
        }
    }
    populationsize-=1;
}
//comparing two individuals
int comparepopulation(int one,int two)
{
	int count=0;
    for(attribute=0;attribute<attributeCount;attribute++)
    {
    	
    	if(population[one][attribute]==population[two][attribute])
    		count++;
    }

    if(count==attributeCount)
    	return 1;

    return 0;
}
void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/* Function to print permutations of string
   This function takes three parameters:
   1. String
   2. Starting index of the string
   3. Ending index of the string. */
void permute(int *a, int l, int r)
{
   int i;
   if (l == r)
   {
        for(attribute=0;attribute<attributeCount;attribute++)
        {
            population[populationsize][attribute]=a[attribute];

            
        }
        populationsize++;
   } 
   else
   {
       for (i = l; i <= r; i++)
       {
          swap((a+l), (a+i));
          permute(a, l+1, r);
          swap((a+l), (a+i)); //backtrack
       }
   }
}
void mutation(int individualCurrent)
{
    for(attribute=0;attribute<attributeCount;attribute++)
    {
        for(int j=attribute+1;j<attributeCount;j++)
        {
            if(population[individualCurrent][attribute]==population[individualCurrent][j])
            {
                population[individualCurrent][j]=(population[individualCurrent][j]+1)%attributeCount;
                attribute=0;
            }
        }
    }
}
/* Driver program to test above functions */
int main()
{
    int a[] = {0,1,2,3,4,5,6,7,8,9};
    permute(a, 0,attributeCount-1);
    
    for(int iteration=0;iteration<iterationCount;iteration++)
    {
	
        //printing the generated population
        /*printf("Generated Poplation iteration %d\n",populationsize);
        printf("=====================================================================\n");
        for(individual=0;individual<populationsize;individual++)
        {
            for(attribute=0;attribute<attributeCount;attribute++)
            {
                printf("%d",population[individual][attribute] );
            }
            printf("\n");
        }
        printf("=====================================================================\n");*/
	
        //calculating the fitness of each individual
        fitnessfunc();
        //calculating the frequency of each fitness
        fitnessfrequencyCalc();
        //calcuting the highest repeating value of fitness and setting a threshold
        hightestfreq();
        //removing population below thrshold
        for(individual=0;individual<populationsize;individual++)
        {
            if(fitness[individual]>fitnessthreshold)
            {
                removeindividual(individual);
            }

        }
	
        //performing crossover over fit population
        int j;
        newpopulation=0;
        for(individual=0;individual<10;individual++)
        {
            for(j=populationsize-10;j<populationsize;j++)
            {
                crossover(individual,j);

            }
        }
	
        //merging the current and the new population
	   
	for(individual=0;individual<newpopulation;individual++)
        {
            for(attribute=0;attribute<attributeCount;attribute++)
            {
                population[individual][attribute]=mutated[individual][attribute];

            }
            populationsize++;
        }
	
	    
        for(individual=0;individual<populationsize;individual++)
        {
            mutation(individual);
        }
        //removing duplicates
        for(individual=0;individual<populationsize;individual++)
        {
            for(j=individual+1;j<populationsize;j++)
            {
                if(comparepopulation(individual,j)==1)
                {
                    
                    removeindividual(j);
                    j--;

                }
            }
        }
    }
        //printing final population
        //printf("Processed Population Serail %d\n",populationsize);
        printf("===========================================================\n");
        for(individual=0;individual<populationsize;individual++)
        {
            for(attribute=0;attribute<attributeCount;attribute++)
            {
                printf("%d",population[individual][attribute] );
            }
            printf("\n");
        }
        printf("===========================================================\n");
        
    return 0;

}
