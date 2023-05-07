#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include<time.h>
#include<fstream>
#include<string.h>
#define TotalThreads 27


using namespace std;

class User{
	public:
		char name[50];
		int age;
		int pass;
		char score[10];
		User()
		{
		
			age=0;
			pass=0;
		}
		
		int setPass()
		{
			srand(time(NULL));
			int pas=1001+rand()%9990;
			pass=pas;
			cout<<"Your password  : "<<pass;
			return pass;
		}
		char* setName()
		{
			char n[50];
			cout<<"Enter your name : ";
			cin.getline(n,49);
			strcpy(name,n);
			return name;
		}
		int setAge()
		{
			int a;
			cout<<"Enter your age : ";
			cin>>a;
			age=a;
			return age;
		}
		char* Score(int c)
		{
			if(c==1)
			{
				strcpy(score,"Loss");
				return score;
			}
			else if(c==2)
			{
				strcpy(score,"Won");
				return score;
			}
			else if(c==0)
			{
				strcpy(score,"NONE");
				return score;
			}
			
		}
		void setData();
		void SaveUser();
		void showData();
		void showUserData();
		void updateScore(int);
};

void User::setData()
{
	setName();
	setAge();
	setPass();
}

void User::SaveUser()
{
	fstream fout;
	fout.open("UserData.dat", ios::out | ios::binary);
	setData();
	fout.write((char*)this, sizeof(*this));
	fout.close();
}
void User::showData()
{
	cout<<"Name : "<<name;
	cout<<endl<<"Age : "<<age;
	cout<<endl<<"Score : "<<score;
	cout<<endl;
}
void User::showUserData()
{
	fstream fin;
	int p;
	cout<<"Enter your password : ";
	cin>>p;
	fin.open("UserData.dat", ios::in | ios::binary);
	if(!fin)
	{
		cout<<"File not found!";
	}
	else
	{
		fin.read((char*)this , sizeof(*this));
		while(!fin.eof())
		{
			if(p==pass)
			{
				showData();
				break;
			}
			fin.read((char*)this, sizeof(*this));
		}
	}
	fin.close();
}
void User::updateScore(int c)
{
			fstream fin;
			fstream tempfin;
			tempfin.open("Temp.dat", ios::out | ios::binary);
        	fin.open("UserData.dat", ios::in | ios::binary);
        	while(!fin.eof())
        	{
        		fin.read((char*)this, sizeof(*this));
        		Score(c);
        		tempfin.write((char*)this, sizeof(*this));
			}
        	fin.close();
        	tempfin.close();
        	remove("UserData.dat");
        	rename("Temp.dat","UserData.dat");
}
struct Sudoku
{
    int row;
    int col;
    int (*board)[9];
};

int result[TotalThreads] = {0};
int count=0;
void welcome()
{
	cout<<"\n\n\n\n\n\n\t\t\t\tThis Program is Designed by\n\n\n\t\t\t\t\t\tk213355 Talha Shahid\n\n\n\t\t\t\t\t\tk214950 Ali Raza\n\n\n\t\t\t\t\t\tk214539 Hamood Siddique";
	cout<<"\n\n\nPress Enter to continue....";
	getchar();
	system("cls");
}



void *ValidateGridThread(void * attr)
{
    Sudoku *SudokuGrid = (Sudoku *) attr;
    int startRow = SudokuGrid->row;
    int startCol = SudokuGrid->col;
    int seen[10] = {0};
    for (int i = startRow; i < startRow + 3; ++i)
    {
        for (int j = startCol; j < startCol + 3; ++j)
        {
            int val = SudokuGrid->board[i][j];
            if (seen[val] != 0)
            {
                pthread_exit(NULL);
            }
            else
             {
                seen[val] = 1;
        
             }
        }
    }

    result[startRow + startCol/3] = 1; 
    pthread_exit(NULL);
}



void *ValidateRowThread(void *attr)
{
    Sudoku *SudokuGrid = (Sudoku *) attr;
    int row = SudokuGrid->row;

    int seen[10] = {0};
    for (int j = 0; j < 9; j++)
    {
        int val = SudokuGrid->board[row][j];
        if (seen[val] != 0)
        {
            pthread_exit(NULL);
        }
        else
        {
            seen[val] = 1;
        }
    }

   
    result[9 + row] = 1;
    pthread_exit(NULL);
}

void *getDataThread(void*)
{
	User obj;
	obj.SaveUser();
	pthread_exit(NULL);
}

void *updateScoreThread(void* attr)
{
	int num = *((int *)attr);
	User obj;
	obj.updateScore(num);
	pthread_exit(NULL);
}

void *ValidateColsThread(void *attr)
{
    Sudoku *SudokuGrid = (Sudoku *) attr;
    int col = SudokuGrid->col;

    int seen[10] = {0};
    for (int i = 0; i < 9; i++)
    {
        int val = SudokuGrid->board[i][col];
        if (seen[val] != 0)
        {
            pthread_exit(NULL);
        }
        else
        {
            seen[val] = 1;
        }
    }

    
    result[18 + col] = 1;
    pthread_exit(NULL);
 }

void *displayDataThread(void *attr)
{
	User obj;
	obj.showUserData();
	pthread_exit(NULL);
}
 
int check_line(int input[9])
{
    int seen[10] = {0};
    for (int i = 0; i < 9; i++)
    {
        int val = input[i];
        if (seen[val] != 0)
        {
            return 1;
        }
        else
         {
            seen[val] = 1;
        }
    }
    return 0;
}


int ValidateGridThread(int sudoku[9][9])
{
    int temp_row, temp_col;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            temp_row = 3 * i;
            temp_col = 3 * j;
            int seen[10] = {0};

            for(int k=temp_row; k < temp_row+3; k++)
            {
                for(int l=temp_col; l < temp_col+3; l++)
                {
                    int val = sudoku[k][l];
                    if (seen[val] != 0)
                    {
                        return 1;
                    }
                    else
                     {
                        seen[val] = 1;
                    }
                }
            }
        }
    }
    return 0;
}

void *ValidateRangeThread(void* attr)
{
	Sudoku *SudokuGrid = (Sudoku *) attr;
    for (int i = 0; i < 9; i++)
    {
    	for(int j=0; j<9; j++)
    	{
        int val = SudokuGrid->board[i][j];
        if (val == 0)
        {
        	count=1;
            pthread_exit(NULL);
        }        
		}
    }
    pthread_exit(NULL);
}

int ValidateSudoku(int sudoku[9][9])
{
    for (int i=0; i<9; i++)
    {
        if(check_line(sudoku[i]))
        {
            return 1;
        }
        
        int check_col[9];
        for (int j=0; j<9; j++)
        {
            check_col[j] = sudoku[i][j];
		}
        if(check_line(check_col))
        {
            return 1;
        }
        if(ValidateGridThread(sudoku))
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
	welcome();
	pthread_t thread1;
	pthread_create(&thread1, NULL, getDataThread, NULL);
	pthread_join(thread1, NULL);
	
	//only remove comment if you want to play game by your self
	
/*    int sudoku[9][9] =
    {
            {9, 4, 0, 1, 6, 3, 8, 5, 7},
            {5, 3, 6, 0, 8, 7, 9, 4, 1},
            {8, 7, 1, 9, 5, 4, 0, 3, 6},
            {3, 2, 0, 8, 1, 9, 4, 6, 5},
            {1, 5, 4, 3, 2, 6, 7, 9, 8},
            {6, 9, 8, 7, 0, 5, 1, 2, 3},
            {2, 6, 5, 4, 7, 1, 3, 8, 9},
            {7, 8, 9, 6, 0, 2, 5, 1, 4},
            {4, 1, 3, 5, 9, 8, 6, 7, 2}
     };
     
     int solution[9][9]=
     {
            {9, 4, 2, 1, 6, 3, 8, 5, 7},
            {5, 3, 6, 2, 8, 7, 9, 4, 1},
            {8, 7, 1, 9, 5, 4, 2, 3, 6},
            {3, 2, 7, 8, 1, 9, 4, 6, 5},
            {1, 5, 4, 3, 2, 6, 7, 9, 8},
            {6, 9, 8, 7, 4, 5, 1, 2, 3},
            {2, 6, 5, 4, 7, 1, 3, 8, 9},
            {7, 8, 9, 6, 3, 2, 5, 1, 4},
            {4, 1, 3, 5, 9, 8, 6, 7, 2}
     };
     
     cout<<"\n\nSolve this SUDOKU (Replace answered value with 0) : \n\n";
     
     for(int i=0; i<9; i++)
     {
         for(int j=0; j<9; j++)
         {
             
                 cout<<sudoku[i][j]<<" ";
                 
         }
         cout<<endl;
     }
     
     cout<<endl<<endl;
     for(int i=0; i<9; i++)
     {
         for(int j=0; j<9; j++)
         {
             if(sudoku[i][j]==0)
             {
                 cout<<"arr["<<i<<"]["<<j<<"] : ";
                 cin>>sudoku[i][j];
             }
         }
     }
     	*/
     	
     	int sudoku[9][9]=
     {
            {9, 4, 2, 1, 6, 3, 8, 5, 7},
            {5, 3, 6, 2, 8, 7, 9, 4, 1},
            {8, 7, 1, 9, 5, 4, 2, 3, 6},
            {3, 2, 7, 8, 1, 9, 4, 6, 5},
            {1, 5, 4, 3, 2, 6, 7, 9, 8},
            {6, 9, 8, 7, 4, 5, 1, 2, 3},
            {2, 6, 5, 4, 7, 1, 3, 8, 9},
            {7, 8, 9, 6, 3, 2, 5, 1, 4},
            {4, 1, 3, 5, 9, 8, 6, 7, 2}
     };
     	Sudoku *grid = (Sudoku *) malloc(sizeof(Sudoku));
     	grid->board = sudoku;
    	pthread_t thread5;
		pthread_create(&thread5, NULL, ValidateRangeThread, grid);
		pthread_join(thread5,NULL);
		
		if(count==1)
		{
			cout<<"\nInvalid Sudoku Solution! because we can not enter 0 in sudoku\n";
			exit(0);
		}
		
    if(ValidateSudoku(sudoku))
    {
		cout<<"\n\n======***************************************************************************************======\n\n";
    	cout<<"\nThis answer is validated by using single Thread :\n\n";
        cout<<"Sudoku solution is invalid\n";
	}
    else
    {
    	cout<<"\n\n======***************************************************************************************======\n\n";
    	cout<<"\nThis answer is validated by using single Thread : \n\n";
        cout<<"Sudoku solution is valid\n";
	}
	
	
	//MultiThreading starts from here.....

    pthread_t threads[TotalThreads];

    int threadIndex = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i%3 == 0 && j%3 == 0)
            {
                Sudoku *gridData = (Sudoku *) malloc(sizeof(Sudoku));
                gridData->row = i;
                gridData->col = j;
                gridData->board = sudoku;
                pthread_create(&threads[threadIndex++], NULL, ValidateGridThread, gridData);
            }

            if (j == 0)
            {
                Sudoku *rowData = (Sudoku *) malloc(sizeof(Sudoku));
                rowData->row = i;
                rowData->col = j;
                rowData->board = sudoku;
                pthread_create(&threads[threadIndex++], NULL, ValidateRowThread, rowData);
            }

            if (i == 0)
            {
                Sudoku *colData = (Sudoku *) malloc(sizeof(Sudoku));
                colData->row = i;
                colData->col = j;
                colData->board = sudoku;
                pthread_create(&threads[threadIndex++], NULL, ValidateColsThread, colData);
            }
        }
    }

    for (int i = 0; i < TotalThreads; i++)
    {
        pthread_join(threads[i], NULL);
	}

    for (int i = 0; i < TotalThreads; i++)
    {
        if (result[i] == 0)
        {
        	pthread_t thread2;
        	int x=1;
			pthread_create(&thread2, NULL, updateScoreThread, (void*)&x);
			pthread_join(thread2, NULL);
        	cout<<"\n\n======***************************************************************************************======\n\n";
        	cout<<"\nThis answer is validated by using MultiThreads :\n\n";
            cout << "Sudoku solution is invalid" << endl;
  /*
             cout<<endl<<endl<<"\n\nYour solution is this : \n\n";
     
     for(int i=0; i<9; i++)
     {
         for(int j=0; j<9; j++)
         {
             
                 cout<<sudoku[i][j]<<" ";
                 
         }
         cout<<endl;
     }
    
    cout<<endl<<endl<<"\n\nCorrect solution is this : \n\n";
     
     for(int i=0; i<9; i++)
     {
         for(int j=0; j<9; j++)
         {
             
                 cout<<solution[i][j]<<" ";
                 
         }
         cout<<endl;
     }
     */
     
     		int m;
        	cout<<"\nDo you want to see you stats if yes press 1 else press 2 : ";
			cin>>m;
			if(m==1)
			{
				pthread_t thread;
			pthread_create(&thread, NULL, displayDataThread, NULL);
			pthread_join(thread, NULL);
			}
			else
			{
				exit(0);
			}
            return 1;
        }
    }
    cout<<"\n\n======***************************************************************************************======\n\n";
    
    cout<<"\nThis answer is validated by using MultiThreads :\n\n";
    cout << "Sudoku solution is valid" << endl;
    		pthread_t thread2;
        	int x=2;
			pthread_create(&thread2, NULL, updateScoreThread, (void*)&x);
			pthread_join(thread2, NULL);
        	
        	int m;
        	cout<<"\nDo you want to see you stats if yes press 1 else press 2 : ";
			cin>>m;
			if(m==1)
			{
				pthread_t thread;
				pthread_create(&thread, NULL, displayDataThread, NULL);
				pthread_join(thread, NULL);
			}
			else
			{
				exit(0);
			}
}
