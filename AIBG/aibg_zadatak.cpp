#include <iostream>
#include <vector>
#include <stdlib.h> 
#include <istream>
#include <string>
#include <sstream>
using namespace std;


class Solution {
	int N;
	vector<vector<int>> rows;
	vector<vector<int>> cols;

	public:
		Solution(int n, vector<vector<int>> r, vector<vector<int>> c) : N(n) {
			for (int i = 0; i < n; i++) {
				rows.push_back({});
				for (int j = 0; j < r[i].size(); j++) rows[i].push_back(r[i][j]);
				cols.push_back({});
				for (int j = 0; j < c[i].size(); j++) cols[i].push_back(c[i][j]);
			}
		}
		/// <summary>Finds the first non-zero element in vector</summary>
		/// <param name="v">Vector</param>
		/// <returns>index of the first non zero element or -1 if all elements are zero</returns>  
		int indNonZero(vector<int>& v) {
			int j = 0;
			while (j < v.size() && v[j] == 0) j++;
			if (j < v.size()) return j;
			else return -1;
		}
		/// <summary>This method fills canvas row</summary>
		/// <param name="canv">2D vector representing painted segments</param>
		/// <param name="domain">2D vector representing whether a filed can be painted or not</param>
		/// <param name="start">Field at which row starts to be filled</param>
		/// <param name="len">Number of consecutive fields to be filled</param>
		/// <param name="colsCopy">Vector of remaining column-wise constraints</param>
		/// <param name="rSeg">Index of row segment being filled</param>
		/// <returns>Success of operation</returns>  
		bool paintRow(vector<vector<int>> canv, vector<vector<bool>> domain, pair<int, int> start, int len, vector<vector<int>> colsCopy,int rSeg) {
			if (start.second + len >= N+1) return false;
			else {
				for (int i = 0; i < len; i++) {
					if (domain[start.first][start.second + i]) {
						canv[start.first][start.second + i] = 1;
						domain[start.first][start.second + i] = false;
						int j=indNonZero(colsCopy[start.second + i]);
						if (j != -1) {
							colsCopy[start.second + i][j]--;
							if (colsCopy[start.second + i][j] == 0) {
								if (j == colsCopy[start.second + i].size() - 1) {
									for (int p = 1; p < N - start.first; p++) {
										domain[start.first + p][start.second + i] = false;
									}
								}
								else {
									if (start.first + 1 < N) {
										domain[start.first + 1][start.second + i] = false;
									}
								}
								
							}
						}
						
					}
					else {
						return false;
					}
				}
				if (start.second + len < N) {
					if (hasToBe(colsCopy, start.first, start.second + len)) return false;
					else {
						domain[start.first][start.second + len] = false;
					}
				}
				
				//paint(canv);
				if (rows[start.first].size() > rSeg + 1) {
					if (!nextRow(canv, domain, start.first, colsCopy,rSeg+1)) return false;
				}
				for (int i = start.second + len + 1; i < N; i++) {
					if (hasToBe(colsCopy, start.first, i)) return false;
				}
				if (!nextRow(canv, domain, start.first + 1, colsCopy,0)) return false;
			}
			//return true;
		}
		/// <summary>Finds a starting point in the row</summary>
		/// <param name="canv">2D vector representing painted segments</param>
		/// <param name="domain">2D vector representing whether a filed can be painted or not</param>
		/// <param name="r">Index of row</param>
		/// <param name="colsCopy">Vector of remaining column-wise constraints</param>
		/// <param name="rSeg">Index of row segment being filled</param>
		/// <returns>Success of operation</returns>  
		bool nextRow(vector<vector<int>> canv, vector<vector<bool>> domain, int r, vector<vector<int>> colsCopy,int rSeg) {
			if (r == N) {
				paint(canv);
				exit(1);
			}
			int len = rows[r][rSeg];
			
			for (int c = 0; c < N - len+1; c++) {
				if (domain[r][c] == false) {
					continue;
				}
				pair<int, int> start{ r , c };
				bool t = paintRow(canv, domain, start, len, colsCopy,rSeg);
				if (!t && hasToBe(colsCopy, r, c)) return false;
				domain[r][c] = false;
				//if (t) return true;
			}	
			return false;
		}
		/// <summary>This method checks if field has to be painted because of column-wise constraints</summary>
		/// <param name="colsCopy">Vector of remaining column-wise constraints</param>
		/// <param name="r">Index of row</param>
		/// <param name="c">Index of column</param>
		/// <returns>true if field needs to be painted</returns>  
		bool hasToBe(vector<vector<int>>& colsCopy, int r, int c) {
			int j = indNonZero(colsCopy[c]);
			if (j != -1 && cols[c][j] != colsCopy[c][j]) {
				return true;
			}
			else return false;
		}
		/// <summary>This method prints out design</summary>
		/// <param name="canv">2D vector representing painted segments</param>
		/// <returns>Success of operation</returns>  
		bool paint(vector<vector<int>>& canv) {
			cout.flush();
			cout << "Jedno resenje problema je:\n";
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					cout << canv[i][j];
				}
				cout << '\n';
			}
			return true;
		}
		/// <summary>Main method that starts the solving process</summary>
		/// <returns>Success of operation</returns>  
		bool learnToPaint() {
			vector<vector<int>> canv(N, vector<int>(N, 0));
			vector<vector<bool>> domain(N, vector<bool>(N, true));
			bool success= nextRow(canv, domain, 0, cols, 0);
			if (!success) {
				cout << "Problem ne moze da se resi.";
			}
			return success;
		}

};

int main() {
	//za N=5
//vector<vector<int>> rows = { {3}, {4}, {4}, {4}, {5} };
//vector<vector<int>> cols = { {2, 1}, {5}, {5}, {5}, {2} };

//za N=10
//vector<vector<int>> rows = { {2}, {4}, {4}, {6}, {8}, {9}, {9}, {6}, {6}, {4} };
//vector<vector<int>> cols = { {3}, {5}, {6}, {6}, {7}, {8}, {7}, {7}, {6}, {3} };

//za N=7
//vector<vector<int>> rows = { {3,1}, {6}, {5}, {4}, {2,1,1}, {5}, {5} };
//vector<vector<int>> cols = { {1,3}, {2,3}, {3,2}, {7}, {3,2}, {5}, {2}};
	
	cout.flush();
	vector<vector<int>> rows, cols;

	int N;
	//cout << "Canvas size N:\n";
	cin >> N;
	string S;
	//cout << "Row constraints:\n";
	for (int i = 0; i < N; i++) {
		cin >> S;
		int ind1 = S.find('[');
		int p = 0; int ind2 = 0;
		rows.push_back(vector<int>());
		while (ind2 != string::npos) {
			ind2 = S.find(',', ind2 + 1);
			if (ind2 != string::npos)
			{
				int new_elem = stoi(S.substr(ind1 + 1, ind2 - ind1));
				rows[i].push_back(new_elem);
				ind1 = ind2;
			}
		}
		ind2 = S.find(']');
		rows[i].push_back(stoi(S.substr(ind1 + 1, ind2 - ind1)));
	}
	//cout << "Column constraints:\n";
	for (int i = 0; i < N; i++) {
		cin >> S;
		int ind1 = S.find('[');
		int p = 0; int ind2 = 0;
		cols.push_back(vector<int>());
		while (ind2 != string::npos) {
			ind2 = S.find(',', ind2 + 1);
			if (ind2 != string::npos)
			{
				int new_elem = stoi(S.substr(ind1 + 1, ind2 - ind1));
				cols[i].push_back(new_elem);
				ind1 = ind2;
			}
		}
		ind2 = S.find(']');
		cols[i].push_back(stoi(S.substr(ind1 + 1, ind2 - ind1)));
	}

	Solution s1{ N,rows,cols };

	cout.flush();
	s1.learnToPaint();
	
}






