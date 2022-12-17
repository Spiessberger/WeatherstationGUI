#ifndef WSGUI_SYSTEM_H
#define WSGUI_SYSTEM_H

#include <QDate>
#include <QObject>
#include <QTime>
#include <QTimer>

namespace wsgui {

class System : public QObject {
    Q_PROPERTY(QDate date READ date NOTIFY dateChanged)
    Q_PROPERTY(QTime time READ time NOTIFY timeChanged)

    Q_OBJECT
  public:
    explicit System(QObject *parent = nullptr);

    const QDate &date() const;
    const QTime &time() const;

  private:
    QDate m_date;
    QTime m_time;

    QTimer m_systemTimeTimer;

    void updateDateTime();

  signals:
    void dateChanged();
    void timeChanged();
};

} // namespace wsgui

#endif // WSGUI_SYSTEM_H
