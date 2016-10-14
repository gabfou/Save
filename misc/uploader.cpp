#include "uploader.h"

#include <QtCore>
#include <QtNetwork>
#include <QDebug>

Uploader::Uploader(QObject *p): QObject(p)
{
}

void Uploader::start(const QString &file)
{
    QUrl url("ftp://ftp-etudemurano.alwaysdata.net/home/etudemurano/www/" + file);
    url.setUserName("etudemurano");
    url.setPassword("t4x5akda");

    data = new QFile(file, this);
    if (data->open(QIODevice::ReadOnly))
    {
        reply = nam.put(QNetworkRequest(url), data);
        connect(reply, SIGNAL(uploadProgress(qint64, qint64)), SLOT(uploadProgress(qint64, qint64)));
       connect(reply, SIGNAL(finished()), SLOT(uploadDone()));
    }
    else
        qDebug() << "Oops";
}

void Uploader::uploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    qDebug() << "Uploaded" << bytesSent << "of" << bytesTotal;
}

void Uploader::uploadDone()
{
    qDebug() << "Finished" << reply->error();
    data->deleteLater();
    reply->deleteLater();
}
