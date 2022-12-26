#ifndef WSGUI_DATA_I2CWEATHERDATAPROVIDER_H
#define WSGUI_DATA_I2CWEATHERDATAPROVIDER_H

#include "weatherdataprovider.h"

namespace wsgui {
namespace data {

class I2CWeatherDataProvider : public wsgui::data::WeatherDataProvider {
    Q_OBJECT
  public:
    explicit I2CWeatherDataProvider(QObject *parent = nullptr);
};

} // namespace data
} // namespace wsgui

#endif // WSGUI_DATA_I2CWEATHERDATAPROVIDER_H
