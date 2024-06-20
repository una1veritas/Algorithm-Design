import java.awt.*;

public class AWTHello {
	public static void main(String[] args) {
		Dialog d = new Dialog(((Window) null), "Hello world!");
		d.setBounds(0, 0, 180, 70);
		d.add(new Label("Hello world!"));
		d.setVisible(true);
	}
}