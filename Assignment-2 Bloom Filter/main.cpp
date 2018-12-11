/*
Author M Ravi Kumar
CS18MTECH11028
MTECH CSE IIT HYDERABAD
*/

#include <iostream>
#include <stdint.h>
#include "BloomFilter.hpp"
#include <random>
#include<string>

using namespace std;

int v;
 
 //Generating Random number Uniformly with in range a,b
double generateRndmNum (int a,int b)
{
  //Will be used to obtain a seed for the random number engine
  random_device rd;
   //Standard mersenne_twister_engine seeded with rd()
  mt19937 gen(rd());
  uniform_real_distribution<> dis(a,b);
  //Each call to dis(gen) generates a new random double
  return dis(gen);
}  
//Returns a Random Walk on graph with probability of roulette wheel selection
string generate_rndm_walk(double **arr,int s,int r,int k)
{
  string rndm_walk; 
  //We picking vertex based on roulette wheel selection
  for(int j = 0;j<k;j++) //K Steps in Graph
  {
    double adjprarr[v][2] ={0.00};
    double cum_prob = 0.00;
    /*cout<< "Source  Vertex at particular iteration "<<s<<"\n";*/
    //Scaling probability based on cumulative distribution 
    for(int i=0;i<v;i++){
      if((double)(arr[s][i])!=0.00)
      {
        adjprarr[i][0] =cum_prob;
        adjprarr[i][1] =cum_prob+arr[s][i];
        cum_prob+=arr[s][i];
      }
    }
    /*cout<< "Cumulative Probability of each Vertex adjacent to source\n";
    //Each vertex  cumulative probability range
    //Range 0-0 in case of vertex is not adjacent 
    
     for (int i=0; i<v; i++) { 
           for (int j = 0; j < 2; j++) 
               cout << adjprarr[i][j] << " "; 
           cout << endl; 
       }
    */
    //Generating Random Number Uniformly
    double rndnum = generateRndmNum(0,1);
    /*cout<< "Generated Random Number"<<rndnum;
    cout << endl; */
    // Picking Vertex from adjacent
    int pickver;
    for(int i=0;i<v;i++){
      if (rndnum > adjprarr[i][0] && rndnum <= adjprarr[i][1])
      {
        pickver = i;
        break;
      }
    }
    rndm_walk += to_string(pickver);
    //cout << endl; 
    s = pickver;
    /*cout<< "Picked Vertex "<<pickver<<"\n";*/
  }  
    cout<< "Genrated Ant Run "<<rndm_walk<<"\n";

  return rndm_walk;

}

int main() {
  
  cout << "Enter No of Vertices in Graph!\n";
  cin>>v;
//double grap_adj[v][v];

//pointer to 2D array
	double **grap_adj=new double*[v];
  for(int i=0;i<v;i++)
	{
		grap_adj[i]=new double[v];
	}

  cout << "Enter the Adjacency Matrix Values!\n";
  for(int i=0;i<v;i++)
  {
      for(int j=0;j<v;j++)
    {
        cin>>grap_adj[i][j];
    }
  }
  cout << "Printing Given Matrix!\n";
  for(int i=0;i<v;i++)
  {
      for(int j=0;j<v;j++)
    {
        cout<<grap_adj[i][j];
        cout<<"\t";
    }
    cout<<"\n";
  }
  int k;
  cout << "Enter the No of Steps ant should move from Sourse !\n";
  cin>>k;
  int s;
  cout << "Enter the ant  Source Node !\n";
  cin>>s;
  int r;
  cout << "Enter the No of runs from Source Node !\n";
  cin>>r;
  double f_p; //False postive Value
  cout << "Enter the upper bound of False postive Value !\n";  
  cin>>f_p;
  //Computing Bit array size in Bloom Filter
  int bit_array_sz =  -((r*log(f_p))/pow(log(2),2));
  cout << "Bloom Filter Bit array size is!"<<bit_array_sz<<"\n";  
  //Computing No of HashFunctions in Bloom Filter
  int no_hash_fun = (bit_array_sz/r)*log(2);
  cout << "Bloom Filter No of Hash Functions is!"<<no_hash_fun<<"\n"; 
  //Initializing constructor Values
  BloomFilter bf(bit_array_sz, no_hash_fun);
  string rndm_wlks[r];
  cout << "Genarating Ant Runs !\n";  
  for(int i=0;i<r;i++)
  {
    rndm_wlks[i] = generate_rndm_walk(grap_adj,s,r,k);
    bf.insert((uint8_t*)rndm_wlks[i].c_str(), rndm_wlks[i].size());
  }
  cout <<"Genarated Ant Runs\n";
  for(int i=0;i<r;i++)
    cout <<rndm_wlks[i]<<" ";
  cout<<"\n";
  string test;

  //Query module
  while(1)
  {
    string test;
    cout <<"Enter a Ant Run to check in Bloom Filter or  -1 to exit program \n";
    cin>>test;
    if(test=="-1")
      break;
    else 
      cout<<(bf.probablyContains((uint8_t*)test.c_str(),test.size())?"Yes":"No")<<"\n";
    
 }

}