package com.example.javafx_rects;

import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Rectangle2D;
import javafx.scene.Scene;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Screen;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

import java.io.IOException;
import java.util.Random;

public class HelloApplication extends Application {

    Pane pane;
    Scene scene;
    Rectangle[] rects = new Rectangle[1000];
    Random r = new Random();
    Rectangle2D screenBounds = Screen.getPrimary().getBounds();
    private final int WIDTH = (int) (screenBounds.getWidth() * 0.8);
    private final int HEIGHT = (int) (screenBounds.getHeight() * 0.8);


    @Override
    public void start(Stage stage) throws IOException {
        stage.setTitle("framework");
        // --- start: not fullscreen; otherwise just:
        // stage.setFullScreen(true);
        stage.initStyle(StageStyle.UNDECORATED);
        stage.setX(0);
        stage.setY(0);
        // --- end: comment out for fullscreen
        pane = new Pane();
        scene = new Scene(pane, WIDTH, HEIGHT);
        BackgroundFill backgroundFill = new BackgroundFill(Color.BLACK, CornerRadii.EMPTY, Insets.EMPTY);
        Background background = new Background(backgroundFill);
        pane.setBackground(background);

        pane.setOnMousePressed(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                onClick();
            }
        });

        pane.setOnMouseReleased(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                onRelease();
            }
        });

        stage.setScene(scene);
        stage.show();
    }

    private void onClick() {
        for(int i = 0; i < 999; i++) {
            int w = r.nextInt(WIDTH - 400);
            int h = r.nextInt(HEIGHT);
            int x = r.nextInt(400, WIDTH - w);
            int y = r.nextInt(HEIGHT - h);
            float red = r.nextFloat();
            float green = r.nextFloat();
            float blue = r.nextFloat();
            float alpha = 1;
            Rectangle rect = new Rectangle(x, y, w, h);
            rect.setFill(new Color(red, green, blue, alpha));
            rects[i] = rect;
            pane.getChildren().add(rect);
        }
        Rectangle whiteRect = new Rectangle(0, 0, 300, 300);
        whiteRect.setFill(Color.WHITE);
        rects[999] = whiteRect;
        pane.getChildren().add(whiteRect);
    }

    private void onRelease() {
        pane.getChildren().removeAll(rects);
    }

    public static void main(String[] args) {
        launch();
    }
}