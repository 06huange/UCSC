//nQueens.cpp
//implementation of nQueens solution
#include <iostream>
#include <stack>
#include <cstdlib>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector> 
#include <algorithm>
#include <sstream>
#include <cstring>
#include <cctype>
#include <regex>
using namespace std;
int size = 0;

void printBoard(vector<vector<int>> board){
  cout<<"\n--Printing Board--\n";
  for(int i=0; i<size; i++){
    for (int j=0; j<size; j++){
      cout<<board[i][j]<<" ";
    }
    cout<<"\n";
  }
  cout<<"-------------------\n";
}
int is_Safe(vector<vector<int>> board, int row, int col){ 
  // -1 = already have queen on row, move to next row
  // 0 = safe;
  // 1 = not safe, check next tile
  int tempRow = row;
  int tempCol = col;
  //check row
  for(int i=0; i<size;i++){
    if(board[row][i] == 1){
      return -1;
    }
  }
  //check column
  for(int i=0; i<size;i++){
    if(board[i][col] == 1){
      return 1;
    }
  }
  //check top left diagonal
  while(tempRow != 0 && tempCol != 0){
    tempRow--;
    tempCol--;
    if(board[tempRow][tempCol] == 1){
      return 1;
    }
  }
  
  //reset temp variables
  tempRow = row;
  tempCol = col;
  
  //check top right diagonal
  while(tempRow != 0 && tempCol != size-1){
    tempRow--;
    tempCol++;
    if(board[tempRow][tempCol] == 1){
      return 1;
    }
  }
  
  //reset temp variables
  tempRow = row;
  tempCol = col;
  
  //check bottom left
  while(tempRow != size-1 && tempCol != 0){
    tempRow++;
    tempCol--;
    if(board[tempRow][tempCol] == 1){
      return 1;
    }
  }
  
  //reset temp variables
  tempRow = row;
  tempCol = col;
  
  //check bottom right
  while(tempRow != size-1 && tempCol != size-1){
    tempRow++;
    tempCol++;
    if(board[tempRow][tempCol] == 1){
      return 1;
    }
  }
  return 0;
}

void updateBoard(vector<vector<int>> board, int row, int col){
  //reset row to all 0
  if(col == -1){
    for(int i=0; i<size; i++){
      board[row][i] = 0;
    }
  }
  //place queen
  else{
    for(int i=0; i<size; i++){
      board[row][i] = 0;
    }
    board[row][col] = 1;
  }
}

vector<vector<int>> findSolution(vector<vector<int>> board){ //push [%d,%d] onto the stack if no conflicts
  stack <vector<int>> answer;
  vector<int> pair(2);
  int row = 0;
  int col = 0;
  while(row < size){
    while(col < size && row < size){
      //cout<<"check: row"<<row<<" column:"<<col<<" ";
      if(is_Safe(board, row, col) == 0){
        pair[0] = row;
        pair[1] = col;
        answer.push(pair);
        //cout<<"top of stack: "<<answer.empty()<<"\n";
        board[row][col] = 1;
        //printBoard(board);
        row++;
        col=0;
      }
      //already have queen in row
      else if(is_Safe(board, row, col) == -1 || board[row][col] == 1){
        //cout<<"already have queen in row\n";
        row++;
        col=0;
      }
			//not safe, check next column
      else{
        col++;
      }
    }
    if(answer.empty() == 1){
			return {};
      //no answer
    }
		else if(row >= size){
			return board;
		}
    //cout<<"top of stack: "<<answer.empty()<<"\n";
    vector<int> tempPair = answer.top();
    row = tempPair[0];
    col = tempPair[1];
    answer.pop();
    board[row][col] = 0;
    col++;
    
  }
  //cout<<"--------Stack size when returned: "<<answer.size()<<"\n";
  return board;
}

int main(int argc, char** argv){
  /*
   * 1.Read input file for query
   * 2.Place queens onto the board stack<stack>
   * 3.Search for solutions
   * 4.Print to out file
   */
  
  string str;
  
  if (argc < 3) // must provide two arguments as input
  {
      throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
  }
  
  ifstream in; // stream for input file
  ofstream out; // stream for output file
  
  in.open(argv[1]); // open input file
  out.open(argv[2]); // open output file
  
  int count = 1;
  while(getline(in,str)){
    int length = str.length();
    int start = 0;
    int end = 0;
    //get placement of queens
		vector<vector<int>> solution;
    while(isdigit(str[end])!=0){
      end+=1;
    }
    size = stoi(str.substr(start,end));
    end++;
    start = end;
		bool isLegal = true;
    vector<vector<int>> board(size, vector<int>(size,0));
    
    //cout<<"\nsize: "<<size;
    while(end+1 <= length && isdigit(str[end])!= 0){
      while(isdigit(str[end]) != 0){
        end++;
      }
      int col = stoi(str.substr(start,end)) - 1;
      end++;
      start = end;
      while(isdigit(str[end]) != 0){
        end++;
      }
      int row = stoi(str.substr(start,end)) - 1;
      end++;
      start = end;
			if(is_Safe(board,row,col) != 0){
				isLegal = false;
				break;
			}
			board[row][col] = 1;
    }
    printBoard(board);
		if(isLegal == true){
			solution = findSolution(board);
		}
    if(solution.empty() == 1 || isLegal == false){
      out<<"No solution\n";
    }
    else{
			printBoard(solution);
			for(int i=0; i<size; i++){
				for(int j=0; j<size; j++){
					if(solution[j][i] == 1){
            out<<i+1<<" "<<j+1<<" ";
					}
				}
			}
      out<<"\n";
    }
  }
  in.close();
  out.close();
  
}

