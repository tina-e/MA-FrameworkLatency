import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class JavaSwing_default_fullscreen extends JFrame {
    private Color color;

    public JavaSwing_default_fullscreen() {
        setSize(1920, 1080);
        setTitle("framework");
        //setExtendedState(JFrame.MAXIMIZED_BOTH);
        setUndecorated(true);
        setVisible(true);
        color = new Color(0, 0, 0);
    }

    public void paint(Graphics g) {
	    g.setColor(color);
	    g.fillRect(0, 0, getWidth(), getHeight());
    }

    public void mousePressed(MouseEvent e) {
        color = new Color(255, 255, 255);

	Graphics g = getGraphics();
	if (g != null) {
		g.setColor(color);
		g.fillRect(0, 0, getWidth(), getHeight());
		Toolkit.getDefaultToolkit().sync();
	}
    }

    public void mouseReleased(MouseEvent e) {
        color = new Color(0, 0, 0);

	Graphics g = getGraphics();
	if (g != null) {
		g.setColor(color);
		g.fillRect(0, 0, getWidth(), getHeight());
		Toolkit.getDefaultToolkit().sync();
	}
    }

    public static void main(String[] args) {
        JavaSwing_default_fullscreen window = new JavaSwing_default_fullscreen();
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