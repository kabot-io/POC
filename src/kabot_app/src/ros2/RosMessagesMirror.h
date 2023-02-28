#pragma once

#include <QObject>
#include <QJsonObject>

class RosMessagesMirror: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonObject mirror READ getRosMirror NOTIFY rosMirrorChanged);
    Q_PROPERTY(QJsonObject latestMessage READ getLatestMessage NOTIFY latestMessageChanged);

public:
    RosMessagesMirror(QObject *parent);
    QJsonObject getRosMirror() const;
    QJsonObject getLatestMessage() const;

signals:
    void rosMirrorChanged();
    void latestMessageChanged(const QJsonObject& message);

protected slots:
    void receive(const QString& topic, const QVariantMap& params);

private:
    QJsonObject m_rosMirror;
    QJsonObject m_latestRosMessage;

};

