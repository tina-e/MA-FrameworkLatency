#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view = QQuickView();
    const QUrl url(u"qrc:/Qt6_quick_default/Main.qml"_qs);
    view.setSource(url);

    auto test = view.graphicsApi();


    view.showFullScreen();


    /*QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);*/

    return app.exec();
}


