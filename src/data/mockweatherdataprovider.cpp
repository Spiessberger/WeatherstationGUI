#include "mockweatherdataprovider.h"

#include <QRandomGenerator>

namespace wsgui {
namespace data {

MockWeatherDataProvider::MockWeatherDataProvider(const QString &unit, double minVal, double maxVal,
                                                 QObject *parent)
    : wsgui::data::WeatherDataProvider(parent), m_minVal(minVal), m_maxVal(maxVal) {
    setValue(QRandomGenerator::global()->bounded(m_maxVal - m_minVal) + m_minVal);
    setUnit(unit);

    connect(&m_valueUpdateTimer, &QTimer::timeout, this, &MockWeatherDataProvider::updateMockValue);
    m_valueUpdateTimer.start(5000);
}

void MockWeatherDataProvider::updateMockValue() {
    double newVal = value().toDouble();
    double randVal = QRandomGenerator::global()->generateDouble() * 2 - 1;

    if (newVal + randVal > m_maxVal || newVal + randVal < m_minVal) {
        newVal -= randVal;
    } else {
        newVal += randVal;
    }

    setValue(newVal);
}

} // namespace data
} // namespace wsgui
