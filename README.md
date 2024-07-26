# Qt67WindowContainerDemo
[Run online](https://altevedev.github.io/Qt67WindowContainerDemo/)

It was created as new modern playground loading method for [QmlCreator (My fork)](https://github.com/pp2e/qmlcreator)

## Why?
* This allows embedding qml components with either window or not window as root component. If root is not window, window for it will be created automatically. Loading components with Loader will create new window if root component is window.
* Also using Loader allows loaded component to modify application outside Loader by calling ```parent.parent.parent``` until it gets element outside Loader. This demo uses new QQmlEngine for loaded components just like [Canonic browser](https://github.com/canonic/canonic), so loaded content will never interact with application that loaded it
