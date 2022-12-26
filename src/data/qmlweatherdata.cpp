#include "qmlweatherdata.h"

#include "weatherdatamanager.h"

#include <QQmlEngine>

namespace {
void initQml() { qmlRegisterType<wsgui::data::QmlWeatherData>("wsgui.data", 1, 0, "WeatherData"); }

Q_CONSTRUCTOR_FUNCTION(initQml);
} // namespace

namespace wsgui {
namespace data {

QmlWeatherData::QmlWeatherData(QObject *parent) : QObject{parent} {}

QVariant QmlWeatherData::value() const {
    return m_weatherDataProvider != nullptr ? m_weatherDataProvider->value() : QVariant{};
}

QString QmlWeatherData::unit() const {
    return m_weatherDataProvider != nullptr ? m_weatherDataProvider->unit() : QString{};
}

const QString &QmlWeatherData::type() const { return m_type; }

void QmlWeatherData::setType(const QString &newType) {
    if (m_type == newType)
        return;
    m_type = newType;

    std::shared_ptr<WeatherDataProvider> newProvider = weatherDataManager().getProvider(m_type);

    if (newProvider == m_weatherDataProvider) {
        return;
    }

    if (m_weatherDataProvider != nullptr) {
        disconnect(m_weatherDataProvider.get(), &WeatherDataProvider::unitChanged, this,
                   &QmlWeatherData::unitChanged);
        disconnect(m_weatherDataProvider.get(), &WeatherDataProvider::valueChanged, this,
                   &QmlWeatherData::valueChanged);
    }

    m_weatherDataProvider = newProvider;

    if (m_weatherDataProvider != nullptr) {
        connect(m_weatherDataProvider.get(), &WeatherDataProvider::unitChanged, this,
                &QmlWeatherData::unitChanged);
        connect(m_weatherDataProvider.get(), &WeatherDataProvider::valueChanged, this,
                &QmlWeatherData::valueChanged);
    }

    emit valueChanged();
    emit unitChanged();
    emit typeChanged();
}

} // namespace data
} // namespace wsgui
