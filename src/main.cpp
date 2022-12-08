#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QDebug>
#include <QDir>

#include "panomaximageprovider.h"

using namespace std::chrono_literals;

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

    // dumpFileTree({":"}, 0);

    auto panomaxProvider = new PanomaxImageProvider("", 10min);

    qmlRegisterSingletonInstance<PanomaxImageProvider>("WeatherstationGUI", 1, 0,
                                                       "PanomaxImageProvider", panomaxProvider);
    engine.addImageProvider("panomax", panomaxProvider);

    engine.load(url);

    return app.exec();
}
