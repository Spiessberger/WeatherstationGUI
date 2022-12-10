#include "downloadproxy.h"

#include <QNetworkReply>
#include <QQmlEngine>

namespace {
void initQml() {
    qmlRegisterUncreatableType<DownloadProxy>(
        "WeatherstationGUI", 1, 0, "Download",
        "Download is just a Proxy Class abstracting Dowbloads from C++ in QML");
}
Q_CONSTRUCTOR_FUNCTION(initQml);
} // namespace

DownloadProxy::DownloadProxy(int id, QNetworkReply *networkReply, QObject *parent)
    : QObject{parent}, m_id(id), m_networkReply(networkReply) {
    Q_ASSERT(networkReply != nullptr);
    Q_ASSERT(networkReply->operation() == QNetworkAccessManager::GetOperation);
    connect(networkReply, &QNetworkReply::downloadProgress, this, &DownloadProxy::downloadProgress);
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

int DownloadProxy::id() const { return m_id; }

qreal DownloadProxy::progress() const { return m_progress; }

void DownloadProxy::abort() {
    if (!m_networkReply.isNull()) {
        m_networkReply->abort();
    }
}

void DownloadProxy::downloadProgress(qint64 bytesReceived, qint64 bytesTotal) {
    if (bytesTotal > 0) {
        m_progress = qreal(bytesReceived) / bytesTotal;
        emit progressChanged();
    }
}

DownloadProxy::Status DownloadProxy::status() const { return m_status; }
