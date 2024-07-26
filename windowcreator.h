#ifndef WINDOWCREATOR_H
#define WINDOWCREATOR_H

#include <QObject>
#include <QQmlEngine>
#include <QQuickWindow>
#include <QQmlComponent>

class WindowCreator : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QQuickWindow* window READ window NOTIFY windowChanged)

signals:
    void windowChanged();
    void error(QString text);

public:
    explicit WindowCreator(QObject *parent = nullptr);
    ~WindowCreator();

    QQuickWindow *window();

    Q_INVOKABLE void createWindow();
    Q_INVOKABLE void closeWindow();

private:
    void getWindow();

    QQmlEngine m_engine;
    QQmlComponent *m_createdComponent = nullptr;
    QQuickWindow *m_createdWindow = nullptr;
};

#endif // WINDOWCREATOR_H
