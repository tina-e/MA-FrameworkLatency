import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class JavaSwing_image_fullscreen extends JFrame {
    private static final int WIDTH = 1920;
    private static final int HEIGHT = 1080;

    private Color color;
    private Image image;
    private boolean pressed = false;

    public JavaSwing_image_fullscreen() {
        setSize(WIDTH, HEIGHT);
        setTitle("framework");
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setVisible(true);
        color = new Color(0, 0, 0);
        image = Toolkit.getDefaultToolkit().getImage("noise.png");
    }

    public void paint(Graphics g) {
        if (pressed)
        {
            g.drawImage(image, 0, 0, this);
        }
        else
        {
            g.setColor(color);
            g.fillRect(0, 0, getWidth(), getHeight());
        }
    }

    public void mousePressed(MouseEvent e) {
        pressed = true;
        Graphics g = getGraphics();
        if (g != null) {
            g.drawImage(image, 0, 0, this);
            Toolkit.getDefaultToolkit().sync();
        }
    }

    public void mouseReleased(MouseEvent e) {
        pressed = false;
        color = new Color(0, 0, 0);

        Graphics g = getGraphics();
        if (g != null) {
            g.setColor(color);
            g.fillRect(0, 0, getWidth(), getHeight());
            Toolkit.getDefaultToolkit().sync();
        }
    }

    public static void main(String[] args) {
        JavaSwing_image_fullscreen window = new JavaSwing_image_fullscreen();
        window.addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent e) {
                window.mousePressed(e);
            }

            public void mouseReleased(MouseEvent e) {
                window.mouseReleased(e);
            }
        });
        GraphicsEnvironment graphics = GraphicsEnvironment.getLocalGraphicsEnvironment();
        GraphicsDevice device = graphics.getDefaultScreenDevice();
        device.setFullScreenWindow(window);
    }
}
