
//Mason Kelly

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

const int maxSize = 10000;
int attack[maxSize][maxSize] = { 0 },
cols[maxSize] = { 0 },
solutionCount = 0;
typedef pair<int, int> pi;


ofstream fout("Nqueen3s.out");

void print1solution(int size)
{
	solutionCount++;
	fout << solutionCount << endl;
	for (int r = 1; r <= size; r++)
	{
		for (int c = 1; c <= size; c++)
			if (cols[r] == c)
				fout << "O";
			else
				fout << ".";
		fout << endl;
	}
	fout << endl << endl;

}


void updateAttack(int r, int c, int change, int size)
{
	int r1, c1;

	// update diagnals
	for (r1 = r - 1, c1 = c - 1; r1 >= 1 && c1 >= 1; r1--, c1--)
		attack[r1][c1] += change;

	for (r1 = r + 1, c1 = c + 1; r1 <= size && c1 <= size; r1++, c1++)
		attack[r1][c1] += change;

	for (r1 = r - 1, c1 = c + 1; r1 >= 1 && c1 <= size; r1--, c1++)
		attack[r1][c1] += change;

	for (r1 = r + 1, c1 = c - 1; r1 <= size && c1 >= 1; r1++, c1--)
		attack[r1][c1] += change;

	// update columns 
	for (r1 = 1, c1 = c; r1 <= size; r1++) // k goes to each row		  
		attack[r1][c1] += change;

	//update rows
	for (r1 = r, c1 = 1; c1 <= size; c1++)
		attack[r1][c1] += change;
}


void findNextQueen(int r, int size)
{
	if (r > size) {
		if (solutionCount < 3) {
			print1solution(size);
		}else{
			cout << solutionCount << " solutions found. see NQueen.out.\n";
			system("pause");
			exit(0);
		}
		// return;
		if (solutionCount > 3)
		{
			cout << solutionCount << " solutions found. see NQueen.out.\n";
			system("pause");
			exit(0);
		}
		return;
	}
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	int value = 10000;
	int tmp = 0;
	for (int c = 1; c <= size; c++)
	{
		if (attack[r][c] == 0) // not under attack
		{
			//code going here
					for (int i = r - 1; i <= r + 1; i++) {
						for (int j = c - 1; j <= c + 1; j++) {
							tmp += attack[i][j];
						}
					}
				
				value = tmp; 
				pq.push(make_pair(value, c));
				tmp = 0;
			
		}
	}
	while (!pq.empty()) {
		pair<int, int> top = pq.top();
		int column = top.second;
		pq.pop();
		cols[r] = column;

		updateAttack(r, column, +1, size);
		findNextQueen(r + 1, size);
		updateAttack(r, column, -1, size);



	}
}
int main()
{
	int size, col;
	cout << "Enter the board size: ";
	cin >> size;
	cout << "Enter column of the first queen:\t";
	cin >> col;

	cols[1] = col; // cols store the column value of each queen in that particular row.
	updateAttack(1, col, +1, size);
	findNextQueen(2, size);

	// return here if we found all the solution
	//cout << solutionCount << " solutions found. see NQueen.out.\n";
	cout << solutionCount << " solutions found. see NQueen.out.\n";
	fout.close();
	return 0;
}
