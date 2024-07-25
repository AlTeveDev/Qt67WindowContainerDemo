#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQuickWindow>
#include <QQmlComponent>
#include <QQuickItem>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/WindowInWindow/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);
    QQuickWindow *window = qobject_cast<QQuickWindow>(engine.rootObjects().at(0));
    window.show();

    return app.exec();
}
