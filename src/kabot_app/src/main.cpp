#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWidgets/QApplication>

#include "ros2/RosController.h"

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication::setAttribute(Qt::AA_ShareOpenGLContexts, true);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QObject::connect(&engine, &QQmlEngine::warnings, [](const QList<QQmlError> &warnings){
        for(auto& warning : warnings){
            logger::warning("QML", warning.toString());
        }
    });

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.addImportPath("qrc:/");
    engine.addImportPath("qrc:/qml");

    engine.load(url);

    return app.exec();
}
