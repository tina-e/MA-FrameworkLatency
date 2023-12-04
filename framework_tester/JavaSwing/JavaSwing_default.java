import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class JavaSwing_default extends JFrame {
    private Color color;
    private static final int WIDTH = (int) (1920 * 0.8);
    private static final int HEIGHT = (int) (1200 * 0.8);

    public JavaSwing_default() {
        setSize(WIDTH, HEIGHT);
        setTitle("framework");
        setUndecorated(true);
        setVisible(true);
        color = new Color(0, 0, 0);
    }

    public void paint(Graphics g) {
	    g.setColor(color);
	    g.fillRect(0, 0, WIDTH, HEIGHT);
    }

    public void mousePressed(MouseEvent e) {
        color = new Color(255, 255, 255);

	Graphics g = getGraphics();
	if (g != null) {
		g.setColor(color);
		g.fillRect(0, 0, WIDTH, HEIGHT);
		Toolkit.getDefaultToolkit().sync();
	}
    }

    public void mouseReleased(MouseEvent e) {
        color = new Color(0, 0, 0);

	Graphics g = getGraphics();
	if (g != null) {
		g.setColor(color);
		g.fillRect(0, 0, WIDTH, HEIGHT);
		Toolkit.getDefaultToolkit().sync();
	}
    }

    public static void main(String[] args) {
        JavaSwing_default window = new JavaSwing_default();
        window.addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent e) {
                window.mousePressed(e);
            }

            public void mouseReleased(MouseEvent e) {
                window.mouseReleased(e);
            }
        });
    }
}
