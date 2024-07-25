#include "windowcreator.h"

#include <QQuickItem>
#include <QQmlComponent>

WindowCreator::WindowCreator(QObject *parent)
    : QObject{parent}
{
    qDebug() << "window creator created";
}

WindowCreator::~WindowCreator() {
    qDebug() << "window creator broke";
}

// WindowCreator *WindowCreator::create(QQmlEngine *engine, QJSEngine *scriptEngine) {
//     Q_UNUSED(engine)
//     Q_UNUSED(scriptEngine)

//     return new WindowCreator(engine);
// }

void WindowCreator::getWindow(QQmlComponent *component) {
    if (component->status() == QQmlComponent::Error) {
        emit error(component->errorString());
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
        emit windowCreated(m_createdWindow);
        return;
    }
    emit windowCreated(m_createdWindow);
}

void WindowCreator::createWindow() {
    if (m_createdWindow) delete m_createdWindow;
    QQmlComponent *component = new QQmlComponent(&m_engine, QUrl(QStringLiteral("qrc:/WindowInWindow/Main.qml")), &m_engine);
    if (component->isLoading())
        QObject::connect(component, &QQmlComponent::statusChanged,
                         [=] () {getWindow(component);});
    else getWindow(component);
}

void WindowCreator::closeWindow() {
    delete m_createdWindow;
    m_createdWindow = nullptr;
}
