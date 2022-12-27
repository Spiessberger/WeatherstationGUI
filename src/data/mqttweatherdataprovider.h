#ifndef WSGUI_DATA_MQTTWEATHERDATAPROVIDER_H
#define WSGUI_DATA_MQTTWEATHERDATAPROVIDER_H

#include "weatherdataprovider.h"

#include <QMqttClient>
#include <QPointer>

namespace wsgui {
namespace data {

class MqttWeatherDataProvider : public wsgui::data::WeatherDataProvider {
    Q_OBJECT
  public:
    explicit MqttWeatherDataProvider(const QString &unit, const QString &topic,
                                     std::shared_ptr<QMqttClient> mqttClient,
                                     QObject *parent = nullptr);

  private:
    void subscribeTopic();
    void messageReceived(const QMqttMessage &msg);

    QString m_topic;
    std::shared_ptr<QMqttClient> m_mqttClient;
    QPointer<QMqttSubscription> m_sub;
};

} // namespace data
} // namespace wsgui

#endif // WSGUI_DATA_MQTTWEATHERDATAPROVIDER_H
