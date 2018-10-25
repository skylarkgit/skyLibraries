package skylib.classics;

import java.util.Arrays;

public class NQueen {

	public static boolean[][] solve(int n) {
		boolean[][] placement = new boolean[n][n];
		if (solveRow(0, placement))
			return placement;
		return 
			null;
	}

	private static boolean solveRow(int row, boolean[][] placed) {
		int size = placed.length;
		
		if (row == size)
			return true;
		
		for (int column = 0; column < size; column++) {
			
			boolean checked = false;
			
			for (int rowToCheck = 0; rowToCheck < row; rowToCheck++){
				if ((column - (row - rowToCheck) >= 0 && placed[rowToCheck][column - (row - rowToCheck)])
						|| (column + (row - rowToCheck) < size && placed[rowToCheck][column + (row - rowToCheck)])
						|| placed[rowToCheck][column]){
					checked = true;
					break;
				}
			}
			
			placed[row][column] = true;
			
			if (!checked && solveRow(row + 1, placed))
				return true;
			
			placed[row][column] = false;
		}

		return false;
	}
	
	public static void main(String[] args) {
		int size = 5;
		
		for (boolean[] row: solve(size)){
			for (boolean col: row)
				System.out.print((col ? 1 : 0)+" ");
			System.out.println();
		}
	}
	
}
