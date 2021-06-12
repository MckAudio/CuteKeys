#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "nativeobject.h"
#include "audiohandler.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    NativeObject object;
    engine.rootContext()->setContextProperty("object", dynamic_cast<QObject*>(&object));

    AudioHandler audioHandler;
    engine.rootContext()->setContextProperty("audio", dynamic_cast<QObject*>(&audioHandler));

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    // Audio Handling
    audioHandler.Init();



    int ret = app.exec();

    return ret;
}
