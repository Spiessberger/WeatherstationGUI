#ifndef WSGUI_DATA_QMLWEATHERDATA_H
#define WSGUI_DATA_QMLWEATHERDATA_H

#include "weatherdataprovider.h"
#include <QObject>

namespace wsgui {
namespace data {

class QmlWeatherData : public QObject {

    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString unit READ unit NOTIFY unitChanged)
    Q_PROPERTY(QVariant value READ value NOTIFY valueChanged)

    Q_OBJECT
  public:
    explicit QmlWeatherData(QObject *parent = nullptr);

    const QString &type() const;
    void setType(const QString &newType);

    QVariant value() const;
    QString unit() const;

  signals:
    void typeChanged();
    void valueChanged();
    void unitChanged();

  private:
    std::shared_ptr<WeatherDataProvider> m_weatherDataProvider;
    QString m_type;
};

} // namespace data
} // namespace wsgui

#endif // WSGUI_DATA_QMLWEATHERDATA_H
