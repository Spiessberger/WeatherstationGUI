#include "weatherdatamanager.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "mockweatherdataprovider.h"

namespace wsgui {
namespace data {

static std::unique_ptr<WeatherDataManager> s_weatherDataManager;

void initWeatherDataManager(const QString &configFile) {
    Q_ASSERT(s_weatherDataManager == nullptr);
    s_weatherDataManager = std::make_unique<WeatherDataManager>(configFile);
}

WeatherDataManager &weatherDataManager() {
    Q_ASSERT(s_weatherDataManager != nullptr);
    return *s_weatherDataManager;
}

WeatherDataManager::WeatherDataManager(const QString &configFile, QObject *parent) {
    parseConfig(configFile);
}

std::shared_ptr<WeatherDataProvider> WeatherDataManager::getProvider(const QString &providerId) {
    auto iter = m_dataProviders.find(providerId);
    if (iter != m_dataProviders.end()) {
        return iter->second;
    }
    qWarning() << "no weather data provider found with id" << providerId;
    return nullptr;
}

bool WeatherDataManager::parseConfig(const QString &configFile) {
    QFile config{configFile};
    if (!config.exists()) {
        qWarning() << "no config for weather data providers found at" << configFile;
        return false;
    }
    if (!config.open(QIODevice::ReadOnly)) {
        qWarning() << "error opening weater data provider config file for reading:"
                   << config.errorString();
        return false;
    }

    QJsonParseError error;
    auto jsonDoc = QJsonDocument::fromJson(config.readAll(), &error);

    if (jsonDoc.isNull()) {
        qWarning() << "error parsing weater data provider config file:" << error.errorString();
        return false;
    }

    for (const auto &providerValRef : jsonDoc.array()) {
        auto providerObj = providerValRef.toObject();

        QStringList missingFields;
        for (const auto &field : QStringList{"id", "providerType", "providerInfo"}) {
            if (!providerObj.contains(field)) {
                missingFields.append(field);
            }
        }
        if (!missingFields.isEmpty()) {
            qWarning() << "weather data provider config file missing field(s):"
                       << missingFields.join(", ");
            qWarning() << "Context:"
                       << qPrintable(QJsonDocument{providerObj}.toJson(QJsonDocument::Indented));
            return false;
        }

        QString id = providerObj["id"].toString();
        QString providerType = providerObj["providerType"].toString();
        QString unit = providerObj["unit"].toString();
        QJsonObject providerInfo = providerObj["providerInfo"].toObject();

        std::shared_ptr<WeatherDataProvider> provider;

        if (providerType == "MOCK") {
            provider = std::make_shared<MockWeatherDataProvider>(
                unit, providerInfo["minVal"].toDouble(0), providerInfo["maxVal"].toDouble(0));
        } else if (providerType == "I2C") {
        } else if (providerType == "MQTT") {
        } else {
            qWarning() << "unknown weather data provider type:" << providerType;
        }

        if (provider != nullptr) {
            m_dataProviders.insert({id, provider});
        }
    }

    return true;
}

} // namespace data
} // namespace wsgui
