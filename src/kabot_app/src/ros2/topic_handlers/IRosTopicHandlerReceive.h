#pragma once

#include <QObject>
#include <QString>
#include <QVariantMap>

namespace topic_handlers{

class IRosTopicHandlerReceive : public QObject
{
Q_OBJECT

public:
    explicit IRosTopicHandlerReceive(QObject *parent = nullptr);
    virtual ~IRosTopicHandlerReceive() = default;

signals:
    void receive(const QString& topic, const QVariantMap& params);
};

}
