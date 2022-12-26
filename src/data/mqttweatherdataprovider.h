#ifndef WSGUI_DATA_MQTTWEATHERDATAPROVIDER_H
#define WSGUI_DATA_MQTTWEATHERDATAPROVIDER_H

#include "weatherdataprovider.h"

namespace wsgui {
namespace data {

class MqttWeatherDataProvider : public wsgui::data::WeatherDataProvider
{
    Q_OBJECT
public:
    explicit MqttWeatherDataProvider(QObject *parent = nullptr);
};

} // namespace data
} // namespace wsgui

#endif // WSGUI_DATA_MQTTWEATHERDATAPROVIDER_H
