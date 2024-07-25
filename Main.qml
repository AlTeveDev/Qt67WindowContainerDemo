import QtQuick
import QtQuick.Controls
import WindowInWindow

Window {
    id: rootWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    WindowCreator {
        id: windowCreator

        onWindowCreated: (window) => {
            container.window = window;
        }
    }

    Rectangle {
        anchors.fill: parent
        color: Qt.hsla(Math.random(), 0.5, 0.5, 1)
        border.color: "black"
        border.width: 2
    }

    Text {
        text: "Qt 6.7 WindowContainer demo"
    }

    Row {
        anchors.right: parent.right
        Button {
            text: "Create"
            onClicked: windowCreator.createWindow()
        }

        Button {
            text: "Close"
            onClicked: windowCreator.closeWindow()
        }
    }

    WindowContainer {
        id: container
        anchors.fill: parent
        anchors.margins: 30
    }

    Text {
        anchors.bottom: parent.bottom
        text: "Every \"Window\" is QQuickWindow in it's own QQmlEngine"
    }
}
