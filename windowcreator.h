#ifndef WINDOWCREATOR_H
#define WINDOWCREATOR_H

#include <QObject>
#include <QQmlEngine>
#include <QQuickWindow>

class WindowCreator : public QObject
{
    Q_OBJECT
    QML_ELEMENT

signals:
    void windowCreated(QQuickWindow *window);
    void error(QString text);

public:
    explicit WindowCreator(QObject *parent = nullptr);
    ~WindowCreator();

    // static WindowCreator *create(QQmlEngine *engine, QJSEngine *scriptEngine);

    Q_INVOKABLE void createWindow();
    Q_INVOKABLE void closeWindow();

private:
    void getWindow(QQmlComponent *component);

    QQmlEngine m_engine;
    QQuickWindow *m_createdWindow = nullptr;
};

#endif // WINDOWCREATOR_H
