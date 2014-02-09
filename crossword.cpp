#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<fstream>
#include<iterator>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

#define N 5 

bool canbeplaced(char solution[N][N],int i,int j) ;
void printans(char solution[N][N]) ;
void canbeplacedutil(char solution[N][N],int i,int j) ;
void solve(char solution[N][N] ,int j,bool* inuse);
vector<string> words;
bool grid[N][N] ;
int n ;

void canbeplacedutil_verti(char solution[N][N],int i,int j,bool* inuse)
{
		
		int row = j/N ;
	int col = j%N ;
	string wordnew = words[i] ;
	
	for(int z=0;z<wordnew.size();z++)
	{
		solution[row+z][col]=wordnew[z] ;
	
	}
	j++;
		printans(solution) ;
	inuse[i]=true;
	solve(solution,j,inuse) ;
	
}


void canbeplacedutil_hori(char solution[N][N],int i,int j,bool* inuse)
{
		int row =0;
	row = (int)j/N ;
	int col = j%N ;
	string wordnew = words[i] ;
	
	for(int z=0;z<wordnew.size();z++)
	{
		solution[row][col+z]=wordnew[z] ;
		j++;
	}
		printans(solution) ;
	inuse[i]=true;
	solve(solution,j,inuse) ;
	
}

// k ,j 
void canbeplaced(char solution[N][N],int i,int j,bool* inuse)
{
	
		int row(0);
	row = (int) ( j / N ) ;
	int col = (int)(j%N) ;
	string wordnew = words[i] ;
	int len = wordnew.size()  ;
		 	
	if( len <= N-col)
		{	int z =0;
			for( z=0;z<len;z++)
			{
				if(grid[row+z][col]==true && (solution[row+z][col]=='1'))
					continue;
				
				else if( solution[row+z][col]!= wordnew[z]) 
					break;
				
			else 
				break;
				}
	if(z==len)
			canbeplacedutil_hori(solution,i,j,inuse) ;
						
		}
		
		if(len<= N-row)
		{
			int z = 0;
			for( z=0;z<len;z++)
			{
				if(grid[row][col+z]==true && (solution[row][col+z]=='1'))
				continue;
				
				else if(solution[row][col+z]!=wordnew[z])
					break;
					
			else 
				break;
				}
	if(z==len)
			canbeplacedutil_verti(solution,i,j,inuse) ;
		
		}
			
}

int main()
{
	
	cout << "To change grid or the words, edit words.txt and/or grid.txt " << endl ;
	cout << "Test Case" << endl ;

		FILE *fp ;
		fp = fopen("grid.txt","r"); 
		ifstream myfile("words.txt");
		
		copy(istream_iterator<string>(myfile),istream_iterator<string>(),back_inserter(words));
          		
		char solution[N][N] ;
		for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			fscanf(fp, "%d", &grid[i][j]);
		}
		}
	
		fclose(fp);
		n = words.size();
		bool inuse[n];
	
	for(int i=0;i<n;i++)
		inuse[i]=false ;
		
		for(int i=0;i<N;i++)
		{for(int j=0;j<N;j++)
			{ solution[i][j] = '1';
			if(grid[i][j]==false)
			solution[i][j]='0' ;
			}
			}
		
		/*History of words is stored in inuse boolean array
		 * 		 to make changes, that is reject any word we have to change the boolean array
		 * e.g. if the user wants to change the words , he will edit words.txt
		 * if the user wants to change the grid he will change grid.txt
		 * if the user doesnt want to use a particular word , 
		 * we will inuse[word_index]=true
		 * the function will not add it into the crossword
		 */ 
		
	solve(solution,0,inuse) ;		
		 
		
		return 0 ;
}

void printans(char solution[N][N])
{
	for(int m=0;m<N;m++)
	{
		for(int n=0;n<N;n++)
		{
			if(solution[m][n]=='1')
			cout << " " << " "; 
			
			else
			cout << solution[m][n] << " " ; 

			}		
			cout << endl ;
		}
		
		cout << endl << endl  ;
	
}


// i is word_index , j is position in solution matrix
void solve(char solution[N][N] ,int j,bool* inuse)
{
	int row=j/N ;
	int col=j%N ;
	
	while(solution[row][col]!='1')
		{
	j++ ;
		row=j/N ;
	col=j%N ;
	
			}
		/*if you want to place some digit in crossword already then inuse[k]=true ;
		 * canbeplaced(solution,k,0,inuse)
		 * if dont want to place it then at instation only inuse[k]=true 
		 */

			for(int k=0 ; k <(words.size()) ; k++)
				{
					if(!inuse[k])
					{
						canbeplaced(solution,k,j,inuse) ;
								
						}	
						
						
		
				}

}
