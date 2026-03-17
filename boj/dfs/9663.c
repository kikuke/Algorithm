#include <stdio.h>

enum { MAP_MAX = 15, MAP_MARGIN = 1 };
int check_diag_up[(MAP_MAX + MAP_MARGIN) * 2];
int check_diag_down[(MAP_MAX + MAP_MARGIN) * 2];
int check_diag_col[(MAP_MAX + MAP_MARGIN) * 2];

int get_diag_up(int n, int iRow, int iCol);
int get_diag_down(int n, int iRow, int iCol);
int get_diag_col(int n, int iRow, int iCol);

inline int get_diag_up(int n, int iRow, int iCol)
{
	return (iRow + iCol);
}

inline int get_diag_down(int n, int iRow, int iCol)
{
	return (iRow - iCol) + n;
}

inline int get_diag_col(int n, int iRow, int iCol)
{
	return iCol;
}

int add_queen(int n, int iRow, int iCol)
{
	int _iUp = get_diag_up(n, iRow, iCol);
	int _iDown = get_diag_down(n, iRow, iCol);
	int _iCol = get_diag_col(n, iRow, iCol);
	
	if (check_diag_up[_iUp] || check_diag_down[_iDown] || check_diag_col[_iCol]) {
		return -1;
	}
	
	check_diag_up[_iUp] = 1;
	check_diag_down[_iDown] = 1;
	check_diag_col[_iCol] = 1;
	return 0;
}

void remove_queen(int n, int iRow, int iCol)
{
	int _iUp = get_diag_up(n, iRow, iCol);
	int _iDown = get_diag_down(n, iRow, iCol);
	int _iCol = get_diag_col(n, iRow, iCol);
	
	check_diag_up[_iUp] = 0;
	check_diag_down[_iDown] = 0;
	check_diag_col[_iCol] = 0;
}

int n_queen(int n, int iRow)
{
	int finds = 0;
	
	if (iRow > n) {
		return 1;
	}
	
	for (int iCol = 1; iCol <= n; ++iCol) {
		if (add_queen(n, iRow, iCol) < 0)
			continue;
		
		finds += n_queen(n, iRow + 1);
		remove_queen(n, iRow, iCol);
	}
	return finds;
}

int main(void)
{
    int N;
    scanf("%d", &N);

    printf("%d\n", n_queen(N, 1));
    return 0;
}