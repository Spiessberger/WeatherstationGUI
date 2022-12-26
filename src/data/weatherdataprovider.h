#ifndef WSGUI_DATA_WEATHERDATAPROVIDER_H
#define WSGUI_DATA_WEATHERDATAPROVIDER_H

#include <QObject>
#include <QVariant>

namespace wsgui {
namespace data {

class WeatherDataProvider : public QObject {

    Q_OBJECT
  public:
    explicit WeatherDataProvider(QObject *parent = nullptr);
    virtual ~WeatherDataProvider() = default;

    const QString &unit() const;
    void setUnit(const QString &newUnit);

    const QVariant &value() const;
    void setValue(const QVariant &newValue);

  private:
    QString m_unit;
    QVariant m_value;

  signals:
    void unitChanged();
    void valueChanged();
};

} // namespace data
} // namespace wsgui

#endif // WSGUI_DATA_WEATHERDATAPROVIDER_H
