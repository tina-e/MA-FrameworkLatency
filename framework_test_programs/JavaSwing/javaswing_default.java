import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class javaswing_default extends JFrame {
    private Color color;

    public javaswing_default() {
        setSize(1920, 1200);
        setTitle("framework");
        setExtendedState(JFrame.MAXIMIZED_BOTH);
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
        javaswing_default window = new javaswing_default();
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
