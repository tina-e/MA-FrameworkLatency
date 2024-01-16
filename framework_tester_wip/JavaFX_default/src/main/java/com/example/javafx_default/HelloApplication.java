package com.example.javafx_default;

import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.geometry.Rectangle2D;
import javafx.scene.Scene;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.HBox;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.stage.Screen;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

import java.io.IOException;

public class HelloApplication extends Application {

    @Override
    public void start(Stage stage) throws IOException {
        stage.setTitle("framework");
        // --- start: not fullscreen; otherwise just:
        // stage.setFullScreen(true);
        Rectangle2D screenBounds = Screen.getPrimary().getBounds();
        double width = screenBounds.getWidth() * 0.8;
        double height = screenBounds.getHeight() * 0.8;
        stage.initStyle(StageStyle.UNDECORATED);
        stage.setX(0);
        stage.setY(0);
        // --- end: comment out for fullscreen
        HBox hbox = new HBox();
        Scene scene = new Scene(hbox, width, height);
        BackgroundFill backgroundFill = new BackgroundFill(Color.BLACK, CornerRadii.EMPTY, Insets.EMPTY);
        Background background = new Background(backgroundFill);
        hbox.setBackground(background);

        hbox.setOnMousePressed(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                BackgroundFill backgroundFill = new BackgroundFill(Color.WHITE, CornerRadii.EMPTY, Insets.EMPTY);
                Background background = new Background(backgroundFill);
                hbox.setBackground(background);
            }
        });

        hbox.setOnMouseReleased(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                BackgroundFill backgroundFill = new BackgroundFill(Color.BLACK, CornerRadii.EMPTY, Insets.EMPTY);
                Background background = new Background(backgroundFill);
                hbox.setBackground(background);
            }
        });

        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}