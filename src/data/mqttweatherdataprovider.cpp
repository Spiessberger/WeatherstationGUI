#include "mqttweatherdataprovider.h"

namespace wsgui {
namespace data {

MqttWeatherDataProvider::MqttWeatherDataProvider(const QString &unit, const QString &topic,
                                                 std::shared_ptr<QMqttClient> mqttClient,
                                                 QObject *parent)
    : wsgui::data::WeatherDataProvider{parent}, m_topic(topic), m_mqttClient(mqttClient) {
    setUnit(unit);
    subscribeTopic();
    connect(mqttClient.get(), &QMqttClient::connected, this,
            &MqttWeatherDataProvider::subscribeTopic);
}

void MqttWeatherDataProvider::subscribeTopic() {
    if (m_topic.isEmpty() || m_mqttClient == nullptr ||
        m_mqttClient->state() != QMqttClient::Connected) {
        return;
    }

    auto subscription = m_mqttClient->subscribe(m_topic);
    if (m_sub != subscription && subscription != nullptr) {
        m_sub = subscription;
        connect(m_sub, &QMqttSubscription::messageReceived, this,
                &MqttWeatherDataProvider::messageReceived);
    }
}

void MqttWeatherDataProvider::messageReceived(const QMqttMessage &msg) {
    bool ok = false;
    double value = msg.payload().toDouble(&ok);
    if (ok) {
        setValue(value);
    } else {
        setValue(msg.payload());
    }
}

} // namespace data
} // namespace wsgui
