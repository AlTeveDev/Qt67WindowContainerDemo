#include "windowcreator.h"

#include <QQuickItem>

WindowCreator::WindowCreator(QObject *parent)
    : QObject{parent}
{
    qDebug() << "window creator created";
}

WindowCreator::~WindowCreator() {
    if (m_createdWindow) m_createdWindow->deleteLater();
    qDebug() << "window creator broke";
}

void WindowCreator::createWindow() {
    if (m_createdWindow) m_createdWindow->deleteLater();
    m_createdWindow = nullptr; // for safety
    QQmlComponent *component = new QQmlComponent(&m_engine, QUrl(QStringLiteral("qrc:/WindowInWindow/Main.qml")), &m_engine);
    if (component->isLoading())
        QObject::connect(component, &QQmlComponent::statusChanged,
                         [=] () {getWindow(component);});
    else
        getWindow(component);
}

void WindowCreator::closeWindow() {
    if (!m_createdWindow) return;
    m_createdWindow->deleteLater();
    m_createdWindow = nullptr;
    emit windowChanged();
}

QQuickWindow *WindowCreator::window() {
    return m_createdWindow;
}

void WindowCreator::getWindow(QQmlComponent *component) {
    if (component->status() == QQmlComponent::Error) {
        emit error(component->errorString());
        m_createdWindow = nullptr;
        emit windowChanged();
        return;
    }

    QObject *object = component->create();
    m_createdWindow = qobject_cast<QQuickWindow*>(object);
    if (!m_createdWindow) {
        QQuickItem *item = qobject_cast<QQuickItem*>(object);
        qDebug() << "Creato windo";
        m_createdWindow = new QQuickWindow();
        item->setParentItem(m_createdWindow->contentItem());
        m_createdWindow->show();
    }
    emit windowChanged();
}
