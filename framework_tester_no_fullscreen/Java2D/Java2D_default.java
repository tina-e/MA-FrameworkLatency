import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Java2D_default extends JFrame {
    private Color color;
    private static final int WIDTH = 1920;
    private static final int HEIGHT = 1200;

    public Java2D_default() {
        setSize(WIDTH, HEIGHT);
        setTitle("framework");
        // setExtendedState(JFrame.MAXIMIZED_BOTH);
        setUndecorated(true);
        setVisible(true);
        color = new Color(0, 0, 0);
    }

    public void paint(Graphics g) {
        Graphics2D g2d = (Graphics2D) g;
        g2d.setColor(color);
        g2d.fillRect(0, 0, WIDTH, HEIGHT);
    }

    public void mousePressed(MouseEvent e) {
        color = new Color(255, 255, 255);

        Graphics2D g2d = (Graphics2D) getGraphics();
        g2d.setColor(color);
        g2d.fillRect(0, 0, WIDTH, HEIGHT);
	Toolkit.getDefaultToolkit().sync();
    }

    public void mouseReleased(MouseEvent e) {
        color = new Color(0, 0, 0);

        Graphics2D g2d = (Graphics2D) getGraphics();
        g2d.setColor(color);
        g2d.fillRect(0, 0, WIDTH, HEIGHT);
	Toolkit.getDefaultToolkit().sync();
    }

    public static void main(String[] args) {
        Java2D_default window = new Java2D_default();
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
