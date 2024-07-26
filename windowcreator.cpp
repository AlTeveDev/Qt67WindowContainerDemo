#include "windowcreator.h"

#include <QQuickItem>

WindowCreator::WindowCreator(QObject *parent)
    : QObject{parent}
{
    qDebug() << "window creator created";
}

WindowCreator::~WindowCreator() {
    qDebug() << "window creator broke";
}

void WindowCreator::createWindow() {
    if (m_createdWindow) m_createdWindow->deleteLater();
    QQmlComponent *component = new QQmlComponent(&m_engine, QUrl(QStringLiteral("qrc:/WindowInWindow/Main.qml")), &m_engine);
    if (component->isLoading()) {
        m_createdComponent = component;
        QObject::connect(component, &QQmlComponent::statusChanged,
                         this, &WindowCreator::getWindow);
    } else getWindow();
}

void WindowCreator::closeWindow() {
    m_createdWindow->deleteLater();
    m_createdWindow = nullptr;
    emit windowChanged();
}

QQuickWindow *WindowCreator::window() {
    return m_createdWindow;
}

void WindowCreator::getWindow() {
    QObject::connect(m_createdComponent, &QQmlComponent::statusChanged,
                     this, &WindowCreator::getWindow);

    if (m_createdComponent->status() == QQmlComponent::Error) {
        emit error(m_createdComponent->errorString());
        m_createdWindow = nullptr;
        emit windowChanged();
        return;
    }

    QObject *object = m_createdComponent->create();
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
