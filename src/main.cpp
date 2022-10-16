#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QDebug>
#include <QDir>

void dumpFileTree(const QDir &dir, int indent) {
    const auto fiList = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    for (const auto &fi : fiList) {
        qDebug().noquote().nospace() << QString{indent, ' '} << fi.fileName();
        if (fi.isDir()) {
            dumpFileTree({fi.absoluteFilePath()}, indent + 2);
        }
    }
}

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/WeatherstationGUI/qml/main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.addImportPath(":/WeatherstationGUI/qml");
    engine.load(url);

    return app.exec();
}
