#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <string>

#define MAX 9999
//#define DEBUG

// records a single movement
// side is either left or right, meaning taking from the leftmost or the rightmost integer
// num is the # of integers to take
struct move {
	std::string side = "";
	int num = NULL;
	void print() {
		if (num != NULL && side != "")
			std::cout << side << " " << num << std::endl;
	}
};

int* arr;	// the array of integers
int** map;	// a 2-d array to store known answers
move** move_map;

int solve_dp(int start, int end)
{
	int ans = -MAX;	// the return value;
	move best_move;	// record the best move
	if (start == end - 1)	
	{
		ans = arr[start];	// return the element if there is only one
	}
	else if (start == end)
	{
		ans = 0;	// return 0 when no elements are left
	}
	else 
	{
		// get the sum of all numbers
		int sum = 0;
		for (int i = start; i < end; i++) sum += arr[i];

		// now try all possible moves from the left
		for (int i = start + 1; i <= end; i++) {
			// when taking (i - start) elements from the left, the result is sum - solve_dp(i, end)
			// solve_dp(i, end) means the max points the opponent can take away if plays optimally
			// solve_dp(i, end) might already been computed, so check from map first
			int res = map[i][end];
			if (res == -MAX) {
				int f = solve_dp(i, end);
				map[i][end] = f;
				res = f;
			}
			res = sum - res;
#ifdef DEBUG
			std::cout << "[loop1]Computed: (" << start << ", " << end << "): " << "[" << i << ", " << end << "] = " << map[i][end]
				<< "; sum = " << sum << "; result = " << res << ";" << std::endl;
#endif
			if (res > ans)	// update the answer
			{
				ans = res;
				best_move.side = "left";
				best_move.num = i - start;
			}
		}

		// try all possible moves starting from the right
		for (int i = end - 1; i >= start; i--) {
			int res = map[start][i];
			if (res == -MAX) {
				int f = solve_dp(start, i);
				map[start][i] = f;
				res = f;
			}
			res = sum - res;
#ifdef DEBUG
			std::cout << "[loop2]Computed: (" << start << ", " << end << "): " << "[" << i << ", " << end << "] = " << map[start][i]
				<< "; sum = " << sum << "; result = " << res << ";" << std::endl;
#endif
			if (res > ans)
			{
				ans = res;
				best_move.side = "right";
				best_move.num = end - i;
			}
		}
	}

	// save ans to map and return it
	map[start][end] = ans;
	move_map[start][end] = best_move;
	return ans;
}


int main() {
	int n;			// size of array

	// read n and array from file
	std::ifstream ifile("input.txt");
	ifile >> n;
	arr = new int[n];
	for (int i = 0; i < n; i++) ifile >> arr[i];

	// create a map that stores known solutions to sub-problems
	// map(a, b) means the max points the first player can get from the sub-array arr[a] to arr[b - 1]
	// so map(0, n) is the final answer
	map = new int* [n + 1];
	for (int i = 0; i <= n; i++) map[i] = new int[n + 1];
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			map[i][j] = -MAX;	// at start, no solutions are known
	
	// create a map of moves that records the optimal move at each scenario
	move_map = new move * [n + 1];
	for (int i = 0; i <= n; i++) move_map[i] = new move[n + 1];

	// print the result
	std::cout << "The maximum point the first player can get is : " << solve_dp(0, n) << std::endl;
	
	// additional printouts
	std::cout << "The original array was: ";
	for (int i = 0; i < n; i++) std::cout << arr[i] << " ";
	std::cout << std::endl;
	int st = 0;
	int ed = n;
	std::string prefix[] = { "Your turn:\t\t", "Opponent's turn:\t" };
	int turn = 0;
	while (st < ed)
	{
		std::cout << prefix[turn];

		// Handle the last move specially
		if (st == ed - 1) {
			std::cout << "take the last integer" << std::endl;
			break;
		}

		// print out the current optimal move
		move temp = move_map[st][ed];
		temp.print();

		// change st and ed
		if (temp.side == "left") st += temp.num;
		else ed -= temp.num;
		turn = 1 - turn;
	}
	
#ifdef DEBUG
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++)
			std::cout << map[i][j] << " ";
		std::cout << std::endl;
	}
#endif
	
	// deallocate memory
	delete[] arr;
	for (int i = 0; i < n + 1; i++) {
		delete[] map[i];
		delete[] move_map[i];
	}
	delete[] map;
	delete[] move_map;
	return 0;
}