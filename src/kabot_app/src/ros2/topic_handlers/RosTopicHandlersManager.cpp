#include "RosTopicHandlersManager.h"

#include <map>
#include <string>
#include <vector>

#include "utils.h"

using namespace topic_handlers;

constexpr auto CLASS_NAME = "RosTopicHandlersManager";

RosTopicHandlersManager::RosTopicHandlersManager(std::shared_ptr<rclcpp::Node> node): m_node(node)
{
    QObject::connect(&m_topicsAutoconnectTimer, &QTimer::timeout, this, &RosTopicHandlersManager::tryToConnect);
    m_topicsAutoconnectTimer.start(1000);
}

void RosTopicHandlersManager::sendMessage(const QString& topic, const QVariantMap& params){
    if(not m_topicHandlers.contains(topic)){
        return;
    }

    m_topicHandlers[topic]->sendMessage(params);
}

bool RosTopicHandlersManager::connectToTopic(const QString& topic){
    if(m_topicHandlers.contains(topic)){
        return true;
    }

    auto topicsTypesMap = getActiveTopics();
    if(not topicsTypesMap.contains(topic)){
        if(not m_topicsToConnect.contains(topic)){
            m_topicsToConnect.push_back(topic);
        }
        return false;
    }
    m_topicsToConnect.removeOne(topic);
    auto handler = getHandlerForTopic(m_node, topic, topicsTypesMap[topic]);
    if(handler.first == nullptr){
        return false;
    }

    m_topicHandlers.insert(topic, handler.first);
    QObject::connect(handler.second.get(), &IRosTopicHandlerReceive::receive, this, &RosTopicHandlersManager::receive);
    logger::info(CLASS_NAME, QString("Connected to topic %1").arg(topic));
    m_connectedTopics.append(topic);
    emit connectedToTopic(topic);
    return true;
}

QMap<QString, QString> RosTopicHandlersManager::getActiveTopics() const{
    auto topics = m_node->get_topic_names_and_types();
    QMap<QString, QString> activeTopicsList;
    for(auto& [name, type]: topics){
        activeTopicsList.insert(QString::fromStdString(name), QString::fromStdString(type.front()));
        if(type.size() != 1){
            logger::warning("RosTopicHandlersManager",
                QString("Multiple types in topic %1. Will be parsed using %2 topic handler.")
                    .arg(QString::fromStdString(name), QString::fromStdString(type.front())));
        }
    }
    return activeTopicsList;
}

QStringList RosTopicHandlersManager::getConnectedTopics() const
{
    return m_connectedTopics;
}

void RosTopicHandlersManager::tryToConnect(){
    for ( const auto& topic : m_topicsToConnect ){
        connectToTopic(topic);
    }
}
