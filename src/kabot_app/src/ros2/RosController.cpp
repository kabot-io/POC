#include "RosController.h"

#include <QCoreApplication>
#include <QtQml>

#include "utils.h"

using namespace topic_handlers;

RosController::RosController(QObject * parent): RosMessagesMirror(parent), m_node(std::make_shared<RosNode>()), m_topicHandlersManager(m_node)
{
    m_nodeExecutorThread = std::make_shared<std::thread>(&RosController::startExec, this);
    m_nodeExecutorThread->detach();
    QObject::connect(&m_topicHandlersManager, &RosTopicHandlersManager::receive, this, &RosController::receive);
}

void RosController::startExec(){
    rclcpp::spin(m_node);
    rclcpp::shutdown();
}

RosController& RosController::getInstance()
{
    static RosController instance;
    return instance;
}

QObject* RosController::getQmlInstance(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return &getInstance();
};

void RosController::sendMessage(const QString& topic, const QVariantMap& params)
{
    m_topicHandlersManager.sendMessage(topic, params);
}

QJsonObject RosController::getTopicsInfo()
{
    QJsonObject topics;
    QMap<QString, QString> activeTopics = m_topicHandlersManager.getActiveTopics();
    QStringList connectedTopics = m_topicHandlersManager.getConnectedTopics();
    for(QMap<QString, QString>::iterator i = activeTopics.begin(); i != activeTopics.end(); ++i){
        QJsonObject topicProperties;
        topicProperties.insert("topic", i.key());
        topicProperties.insert("type", i.value());
        topicProperties.insert("connected", connectedTopics.contains(i.key()));
        topics.insert(i.key(), topicProperties);
    }
    return topics;
}


bool RosController::connectToTopic(const QString& topic){
    return m_topicHandlersManager.connectToTopic(topic);
}

namespace{
void registerTypes(){
    qmlRegisterSingletonType<RosController>("RQml", 1, 0, "Ros", RosController::getQmlInstance);
}
}
Q_COREAPP_STARTUP_FUNCTION(registerTypes);
