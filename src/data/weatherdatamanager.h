#ifndef WEATHERDATAMANAGER_H
#define WEATHERDATAMANAGER_H

#include <QMqttClient>
#include <QObject>

#include "weatherdataprovider.h"

namespace wsgui {
namespace data {

class WeatherDataManager;

WeatherDataManager &weatherDataManager();
void initWeatherDataManager(const QString &configFile);

class WeatherDataManager : public QObject {
    Q_OBJECT
  public:
    explicit WeatherDataManager(const QString &configFile, QObject *parent = nullptr);

    std::shared_ptr<WeatherDataProvider> getProvider(const QString &providerId);

  private:
    bool parseConfig(const QString &configFile);

    std::shared_ptr<QMqttClient> m_mqttClient;
    std::unordered_map<QString, std::shared_ptr<WeatherDataProvider>> m_dataProviders;
};

} // namespace data
} // namespace wsgui

#endif // WEATHERDATAMANAGER_H
