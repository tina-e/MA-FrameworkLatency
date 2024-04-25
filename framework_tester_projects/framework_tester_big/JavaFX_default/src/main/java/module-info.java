module com.example.javafx_default {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.javafx_default to javafx.fxml;
    exports com.example.javafx_default;
}