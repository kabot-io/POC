#pragma once

#include <QBuffer>
#include <QByteArray>
#include <QEventLoop>
#include <QImage>
#include <QThread>
#include <QtWebSockets/QWebSocket>
#include <QtWebSockets/QWebSocketServer>
#include <memory>

#include "RosTopicHandler.h"
#include "SensorMsgsParsers.h"

//https://docs.ros2.org/foxy/api/sensor_msgs/msg/Image.html

namespace topic_handlers{

class ImageHandler: public RosTopicHandler<sensor_msgs::msg::Image>{
    Q_OBJECT

public:
    ImageHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName)
        : RosTopicHandler(node, topicName, TopicPermissions::ReadOnly, 10)
        , server("", QWebSocketServer::NonSecureMode)
    {
        qRegisterMetaType<QAbstractSocket::SocketState>();
        server.listen(QHostAddress::Any, 0);
        QObject::connect(&server, &QWebSocketServer::newConnection, [&](){
            client = server.nextPendingConnection();
        });
        QObject::connect(this, &ImageHandler::publishImage, this, &ImageHandler::onPublishImage);
    }

    QVariantMap parseMsg(const sensor_msgs::msg::Image::SharedPtr msg) final override{
        auto map = RosMessageParser::Image::toVariantMap(*msg);
        map.insert("data", server.serverUrl());
        if((client != nullptr) && client->isValid()){
            QImage::Format format;
            if(msg->encoding == "rgb8" || msg->encoding == "bgr8" ){
                format = QImage::Format_RGB888;
            }
            else{
                logger::error("ImageHandler" , QString("Image format not supported: %1").arg(msg->encoding.c_str()));
                return map;
            }

            QImage source_image(msg->data.data(), msg->width, msg->height, format);
            if (msg->encoding == "bgr8"){
              source_image = source_image.rgbSwapped();
            }
            emit publishImage(source_image);
        }
        return map;
    }

    sensor_msgs::msg::Image parseMap(const QVariantMap& map) final override{
        return RosMessageParser::Image::toMessage(map);
    }

signals:
    void publishImage(QImage image);

private slots:
    void onPublishImage(QImage image){
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");
        client->sendTextMessage("data:image/png;base64," + QString::fromLatin1(byteArray.toBase64().data()));
    }

private:
    QWebSocketServer server;
    QWebSocket *client = nullptr;
};

}
