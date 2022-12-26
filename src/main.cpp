#include "application.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    wsgui::Application wsgui(app);
    return app.exec();
}
