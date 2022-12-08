#ifndef QMLDOWNLOAD_H
#define QMLDOWNLOAD_H

#include <QObject>
#include <QQmlEngine>

class QNetworkReply;

class QmlDownload : public QObject {
    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(qreal progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)

    Q_OBJECT
  public:
    enum Status { None, Downloading, Finished, Failed };
    Q_ENUM(Status)

    explicit QmlDownload(int id, QNetworkReply *networkReply, QObject *parent = nullptr);

    int id() const;
    qreal progress() const;
    Status status() const;

    Q_INVOKABLE
    void abort();

  private:
    int m_id;
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

#endif // QMLDOWNLOAD_H
