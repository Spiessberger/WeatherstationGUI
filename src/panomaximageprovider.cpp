#include "panomaximageprovider.h"

#include <QNetworkReply>

PanomaxImageProvider::PanomaxImageProvider(const QString &panomaxCamId,
                                           std::chrono::seconds liveImageInterval)
    : QQuickImageProvider(QQuickImageProvider::Pixmap),
      m_baseUrl("https://live-image.panomax.com/cams/" + panomaxCamId + "/") {

    Q_ASSERT(QSslSocket::supportsSsl());
    connect(&m_liveImageTimer, &QTimer::timeout, this, &PanomaxImageProvider::downloadLiveImage);

    m_liveImageTimer.setInterval(liveImageInterval);
    downloadLiveImage();
    m_liveImageTimer.start();
}

QPixmap PanomaxImageProvider::requestPixmap(const QString &id, QSize *size,
                                            const QSize &requestedSize) {
    Q_UNUSED(requestedSize)

    bool ok = false;
    size_t imageId = id.toUInt(&ok);

    if (!ok) {
        return {};
    }

    if (imageId == m_liveImageId) {
        *size = m_liveImage.size();
        return m_liveImage;
    }

    return {};
}

void PanomaxImageProvider::downloadLiveImage() {
    auto reply = m_netManager.get(QNetworkRequest(QUrl(m_baseUrl + "recent_default.jpg")));

    m_liveImageDownload = std::make_unique<QmlDownload>(++m_id, reply, this);
    emit liveImageDownloadChanged();
    connect(reply, &QNetworkReply::finished, this,
            [=]() { downloadFinished(m_liveImageDownload.get(), reply); });
}

void PanomaxImageProvider::downloadFinished(QmlDownload *download, QNetworkReply *reply) {
    qDebug() << __func__ << reply;

    if (reply->error() == QNetworkReply::NoError) {
        m_liveImage.loadFromData(reply->readAll());
        m_liveImageId = download->id();
        emit liveImageIdChanged();

    } else {
        qDebug() << "error downloading image:" << reply->errorString();
    }

    reply->deleteLater();
}

size_t PanomaxImageProvider::liveImageId() const { return m_liveImageId; }

QmlDownload *PanomaxImageProvider::liveImageDownload() const { return m_liveImageDownload.get(); }
