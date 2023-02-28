#pragma once

#include <QObject>
#include <QString>
#include <QVariantMap>

#include "IRosTopicHandlerSend.h"
#include "IRosTopicHandlerReceive.h"
#include "utils.h"
#include "rclcpp/rclcpp.hpp"

namespace topic_handlers{

enum class TopicPermissions{
    ReadOnly,
    WriteOnly,
    ReadWrite
};

template <class MessageType>
class RosTopicHandler: public IRosTopicHandlerSend, public IRosTopicHandlerReceive{
public: 
    RosTopicHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName, const TopicPermissions permissions, const int queueSize): m_topic(topicName){
        if(permissions != TopicPermissions::ReadOnly){
            m_publisher = node->create_publisher<MessageType>(topicName.toStdString(), queueSize);
        }
        if(permissions != TopicPermissions::WriteOnly){
            m_subscriber = node->create_subscription<MessageType>(topicName.toStdString(), 
                queueSize, std::bind(&RosTopicHandler::receiveMsg, this, std::placeholders::_1));
        }
    }
    
    void sendMessage(const QVariantMap& map) override final{
        if(m_publisher != nullptr){
            m_publisher->publish(this->parseMap(map));
        }
        else{
            logger::error(m_topic, "Message can't be sent beacuse of read-only permissions");
        }
    }

    virtual QVariantMap parseMsg(const std::shared_ptr<MessageType> msg) = 0;
    virtual MessageType parseMap(const QVariantMap& map) = 0;

//    static QMap<QString, RosT> m_

protected:
    QString m_topic;
    typename rclcpp::Publisher<MessageType>::SharedPtr m_publisher;
    typename rclcpp::Subscription<MessageType>::SharedPtr m_subscriber;

    void receiveMsg(const std::shared_ptr<MessageType> msg){
        emit IRosTopicHandlerReceive::receive(m_topic, parseMsg(msg));
    }

private:
    RosTopicHandler();
};

}
