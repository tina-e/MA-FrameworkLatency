module com.example.javafx_rects {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.javafx_rects to javafx.fxml;
    exports com.example.javafx_rects;
}