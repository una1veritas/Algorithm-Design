import java.awt.*;
public class test {
	public static void main(String argv[]) {
		System.out.println("Hi.");
		
		String s = "THIS IS A PEN.";
		System.out.println(s.hashCode());
		Point p = new Point(2,3);
		System.out.println(p.hashCode());
	}
}
