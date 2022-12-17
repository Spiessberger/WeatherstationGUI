#ifndef WSGUI_APPLICATION_H
#define WSGUI_APPLICATION_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "panomaximageprovider.h"
#include "system.h"

namespace wsgui {

class Application : public QObject {
    Q_OBJECT
  public:
    Application(int argc, char *argv[]);
    int exec();

  private:
    QGuiApplication m_app;
    QQmlApplicationEngine m_qmlEngine;
    std::unique_ptr<PanomaxImageProvider> m_panomaxImageProvider;
    std::unique_ptr<System> m_system;
};

} // namespace wsgui

#endif // WSGUI_APPLICATION_H
