#pragma once

#include <memory>

#include <QObject>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QTimer>

#include "topic_handlers/AllTopicHandlers.h"
#include "rclcpp/rclcpp.hpp"

namespace topic_handlers{

class RosTopicHandlersManager: public QObject{
    Q_OBJECT
public:
    RosTopicHandlersManager(std::shared_ptr<rclcpp::Node> node);
    void sendMessage(const QString& topic, const QVariantMap& params);
    bool connectToTopic(const QString& topic);

    QMap<QString, QString> getActiveTopics() const;
    QStringList getConnectedTopics() const;

signals:
    void receive(const QString& topic, const QVariantMap& params);
    void connectedToTopic(const QString& topic);

private slots:
    void tryToConnect();

private:
    QMap<QString, std::shared_ptr<IRosTopicHandlerSend>> m_topicHandlers;
    std::shared_ptr<rclcpp::Node> m_node;

    QStringList m_topicsToConnect;
    QStringList m_connectedTopics;
    QTimer m_topicsAutoconnectTimer;
};

}
