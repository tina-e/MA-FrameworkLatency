import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Random;

public class JavaSwing_rects extends JFrame {
    private Color color;
    private static final int WIDTH = (int) (1920 * 0.8);
    private static final int HEIGHT = (int) (1200 * 0.8);
    private static final int MIN_X_RECTS = WIDTH / 2;

    public JavaSwing_rects() {
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
        Random r = new Random();
        for (int i = 0; i < 1000; i++) {
            int x = r.nextInt(MIN_X_RECTS, WIDTH);
            int y = r.nextInt(HEIGHT);
            int width = r.nextInt(WIDTH - x);
            int height = r.nextInt(HEIGHT - y);
            int red = r.nextInt(254);
            int green = r.nextInt(255);
            int blue = r.nextInt(255);
            float alpha = 255; //r.nextFloat();
            g.setColor(new Color(red, green, blue));
            g.fillRect(x, y, width, height);
        }
        g.setColor(new Color(255, 255, 255));
        g.fillRect(0, 0, 300, 300);

        Toolkit.getDefaultToolkit().sync();
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
        JavaSwing_rects window = new JavaSwing_rects();
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
