#include "mqttweatherdataprovider.h"

namespace wsgui {
namespace data {

MqttWeatherDataProvider::MqttWeatherDataProvider(QObject *parent)
    : wsgui::data::WeatherDataProvider{parent}
{

}

} // namespace data
} // namespace wsgui
