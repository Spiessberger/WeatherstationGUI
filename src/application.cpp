#include "application.h"

#include <QDebug>
#include <QDir>
#include <QFontDatabase>

#include "data/weatherdatamanager.h"

using namespace std::chrono_literals;

static void dumpFileTree(const QDir &dir, int indent) {
    const auto fiList = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    for (const auto &fi : fiList) {
        qDebug().noquote().nospace() << QString{indent, ' '} << fi.fileName();
        if (fi.isDir()) {
            dumpFileTree({fi.absoluteFilePath()}, indent + 2);
        }
    }
}

namespace wsgui {

Application::Application(QGuiApplication &app)
    : m_app(app), m_panomaxImageProvider(new PanomaxImageProvider("683", 10min)),
      m_system(std::make_unique<System>()) {
    const QUrl url("qrc:/main.qml");
    QObject::connect(
        &m_qmlEngine, &QQmlApplicationEngine::objectCreated, &m_app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    m_qmlEngine.addImportPath(":");

    // dumpFileTree({":"}, 0);

    qmlRegisterSingletonInstance<System>("wsgui.System", 1, 0, "System", m_system.get());
    qmlRegisterSingletonInstance<PanomaxImageProvider>(
        "wsgui.PanomaxImageProvider", 1, 0, "PanomaxImageProvider", m_panomaxImageProvider);
    // QML Engine takes ownership of imageprovider
    m_qmlEngine.addImageProvider("panomax", m_panomaxImageProvider);

    wsgui::data::initWeatherDataManager("mqtt_data_providers.json");

    auto fonts = QFontDatabase::applicationFontFamilies(
        QFontDatabase::addApplicationFont(":/Roboto-Regular.ttf"));
    Q_ASSERT(fonts.size() == 1);
    m_app.setFont({fonts.front()});

    m_qmlEngine.load(url);
}

} // namespace wsgui
