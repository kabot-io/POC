#include "RosMessagesMirror.h"

RosMessagesMirror::RosMessagesMirror(QObject *parent): QObject(parent)
{
}

QJsonObject RosMessagesMirror::getRosMirror() const
{
    return m_rosMirror;
}

QJsonObject RosMessagesMirror::getLatestMessage() const
{
    return m_latestRosMessage;
}

void RosMessagesMirror::receive(const QString &topic, const QVariantMap &params)
{
    m_rosMirror.insert(topic, QJsonObject::fromVariantMap(params));
    m_latestRosMessage = QJsonObject{{topic, QJsonObject::fromVariantMap(params)}};

    emit rosMirrorChanged();
    emit latestMessageChanged(m_latestRosMessage);
}
