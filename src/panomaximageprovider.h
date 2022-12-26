#ifndef PANOMAXIMAGEPROVIDER_H
#define PANOMAXIMAGEPROVIDER_H

#include <QNetworkAccessManager>
#include <QQuickImageProvider>
#include <QTimer>

#include "downloadproxy.h"

class PanomaxImageProvider : public QQuickImageProvider {

    Q_PROPERTY(bool liveImageAvailable READ liveImageAvailable NOTIFY liveImageAvailableChanged)
    Q_PROPERTY(size_t liveImageId READ liveImageId NOTIFY liveImageIdChanged)
    Q_PROPERTY(
        DownloadProxy *liveImageDownload READ liveImageDownload NOTIFY liveImageDownloadChanged)

    Q_OBJECT
  public:
    PanomaxImageProvider(const QString &panomaxCamId, std::chrono::seconds liveImageInterval);

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;

    bool liveImageAvailable() const;
    size_t liveImageId() const;

    DownloadProxy *liveImageDownload() const;

  signals:
    void liveImageIdChanged();
    void liveImageAvailableChanged();
    void liveImageDownloadChanged();

  private:
    void downloadLiveImage();
    void downloadFinished(DownloadProxy *download, QNetworkReply *reply);

    size_t m_liveImageId = 0;
    bool m_liveImageAvailable = false;
    QString m_baseUrl;
    QTimer m_liveImageTimer;
    QNetworkAccessManager m_netManager;
    QPixmap m_liveImage;
    std::unique_ptr<DownloadProxy> m_liveImageDownload;
};

#endif // PANOMAXIMAGEPROVIDER_H
