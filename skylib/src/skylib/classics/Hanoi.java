package skylib.classics;

import java.util.LinkedList;
import java.util.List;

public class Hanoi {
	
	public static void solve(int discs){
		move(discs, "from", "aux", "to");
	}
	
	private static void move(int disk, String from, String aux, String to){
		if (disk == 1)
			System.out.println(from + " -> (" + disk + ") -> " + to);
		else {
			move(disk - 1, from, to, aux);
			System.out.println(from + " -> (" + disk + ") -> " + to);
			move(disk - 1, aux, from, to);
		}
	}
	
	public static void main(String[] args) {
		solve(3);
	}
}
