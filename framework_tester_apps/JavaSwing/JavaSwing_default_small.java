import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class JavaSwing_default_small extends JFrame {
    private Color color;
    private static final int WIDTH = 100;
    private static final int HEIGHT = 100;

    public JavaSwing_default_small() {
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
        JavaSwing_default_small window = new JavaSwing_default_small();
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