#include "qmldownload.h"

#include <QNetworkReply>
#include <QQmlEngine>

namespace {
void initQml() {
    qmlRegisterUncreatableType<QmlDownload>("WeatherstationGUI", 1, 0, "Download",
                                            "Downloads are created only in C++");
}
Q_CONSTRUCTOR_FUNCTION(initQml);
} // namespace

QmlDownload::QmlDownload(int id, QNetworkReply *networkReply, QObject *parent)
    : QObject{parent}, m_id(id), m_networkReply(networkReply) {
    Q_ASSERT(networkReply != nullptr);
    Q_ASSERT(networkReply->operation() == QNetworkAccessManager::GetOperation);
    connect(networkReply, &QNetworkReply::downloadProgress, this, &QmlDownload::downloadProgress);
    connect(networkReply, &QNetworkReply::finished, this, [=]() {
        if (networkReply->error() == QNetworkReply::NoError) {
            m_status = Status::Finished;
            emit statusChanged();
            emit finished();
        } else {
            m_status = Status::Failed;
            emit statusChanged();
            emit failed();
        }
    });

    if (networkReply->isRunning()) {
        m_status = Status::Downloading;
    }
}

int QmlDownload::id() const { return m_id; }

qreal QmlDownload::progress() const { return m_progress; }

void QmlDownload::abort() {
    if (!m_networkReply.isNull()) {
        m_networkReply->abort();
    }
}

void QmlDownload::downloadProgress(qint64 bytesReceived, qint64 bytesTotal) {
    if (bytesTotal > 0) {
        m_progress = qreal(bytesReceived) / bytesTotal;
        emit progressChanged();
    }
}

QmlDownload::Status QmlDownload::status() const { return m_status; }
