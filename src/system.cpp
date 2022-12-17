#include "system.h"

using namespace std::chrono_literals;

namespace wsgui {

System::System(QObject *parent) : QObject{parent} {
    connect(&m_systemTimeTimer, &QTimer::timeout, this, &System::updateDateTime);
    m_systemTimeTimer.start(1s);
}

const QDate &System::date() const { return m_date; }

const QTime &System::time() const { return m_time; }

void System::updateDateTime() {
    auto currentDateTime = QDateTime::currentDateTime();
    if (currentDateTime.date() != m_date) {
        m_date = currentDateTime.date();
        emit dateChanged();
    }
    if (currentDateTime.time() != m_time) {
        m_time = currentDateTime.time();
        emit timeChanged();
    }
}

} // namespace wsgui
