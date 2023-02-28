#pragma once

#include <memory>
#include <thread>

#include <QJsonObject>
#include <QQmlApplicationEngine>

#include "RosMessagesMirror.h"
#include "RosNode.h"
#include "topic_handlers/RosTopicHandlersManager.h"

#include "rclcpp/rclcpp.hpp"

class RosController: public RosMessagesMirror
{
    Q_OBJECT

public:
    static RosController& getInstance();
    static QObject* getQmlInstance(QQmlEngine* engine, QJSEngine* scriptEngine);
    
    Q_INVOKABLE bool connectToTopic(const QString& topic);
    Q_INVOKABLE void sendMessage(const QString& topic, const QVariantMap& params);

    Q_INVOKABLE QJsonObject getTopicsInfo();

private:
    explicit RosController(QObject *parent = nullptr);

    void startExec();
    std::shared_ptr<RosNode> m_node;
    std::shared_ptr<std::thread> m_nodeExecutorThread;
    topic_handlers::RosTopicHandlersManager m_topicHandlersManager;
};
