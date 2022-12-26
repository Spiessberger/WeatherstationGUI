#ifndef WSGUI_DATA_MOCKWEATHERDATAPROVIDER_H
#define WSGUI_DATA_MOCKWEATHERDATAPROVIDER_H

#include "weatherdataprovider.h"

#include <QTimer>

namespace wsgui {
namespace data {

class MockWeatherDataProvider : public wsgui::data::WeatherDataProvider {
    Q_OBJECT
  public:
    explicit MockWeatherDataProvider(const QString &unit, double minVal, double maxVal,
                                     QObject *parent = nullptr);

  private:
    double m_minVal;
    double m_maxVal;
    QTimer m_valueUpdateTimer;

    void updateMockValue();
};

} // namespace data
} // namespace wsgui

#endif // WSGUI_DATA_MOCKWEATHERDATAPROVIDER_H
