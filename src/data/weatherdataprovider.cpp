#include "weatherdataprovider.h"

namespace wsgui {
namespace data {

WeatherDataProvider::WeatherDataProvider(QObject *parent) : QObject{parent} {}

const QString &WeatherDataProvider::unit() const { return m_unit; }

void WeatherDataProvider::setUnit(const QString &newUnit) {
    if (m_unit == newUnit)
        return;
    m_unit = newUnit;
    emit unitChanged();
}

const QVariant &WeatherDataProvider::value() const { return m_value; }

void WeatherDataProvider::setValue(const QVariant &newValue) {
    if (m_value == newValue)
        return;
    m_value = newValue;
    emit valueChanged();
}

} // namespace data
} // namespace wsgui
