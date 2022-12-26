#ifndef DOWNLOADPROXY_H
#define DOWNLOADPROXY_H

#include <QObject>
#include <QQmlEngine>

class QNetworkReply;

class DownloadProxy : public QObject {
    Q_PROPERTY(size_t id READ id CONSTANT)
    Q_PROPERTY(qreal progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)

    Q_OBJECT
  public:
    enum Status { None, Downloading, Finished, Failed };
    Q_ENUM(Status)

    explicit DownloadProxy(QNetworkReply *networkReply, QObject *parent = nullptr);

    size_t id() const;
    qreal progress() const;
    Status status() const;

    Q_INVOKABLE
    void abort();

  private:
    static size_t s_id;
    size_t m_id;
    qreal m_progress = 0.0;
    Status m_status = Status::None;
    QPointer<QNetworkReply> m_networkReply;

    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

  signals:
    void progressChanged();
    void finished();
    void failed();
    void statusChanged();
};

#endif // DOWNLOADPROXY_H
