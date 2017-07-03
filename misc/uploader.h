#ifndef UPLOADER_H
#define UPLOADER_H


#include <QtCore>
#include <QtNetwork>
#include <QDebug>

// upload des des fichier au serveur (pas finit) 

class Uploader: public QObject
{
    Q_OBJECT

public:

    Uploader(QObject *p = 0);
    void start(const QString &file);
 
public slots:

    void uploadProgress(qint64 bytesSent, qint64 bytesTotal); 
    void uploadDone();

private:
    QNetworkAccessManager nam;
    QFile *data;
    QNetworkReply *reply;
};

#endif
