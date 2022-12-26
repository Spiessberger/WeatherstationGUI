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
    Application(QGuiApplication &app);

  private:
    QGuiApplication &m_app;
    QQmlApplicationEngine m_qmlEngine;
    std::unique_ptr<System> m_system;
    PanomaxImageProvider *m_panomaxImageProvider;
};

} // namespace wsgui

#endif // WSGUI_APPLICATION_H
