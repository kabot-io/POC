#pragma once

#include <QVariantMap>

namespace topic_handlers{

class IRosTopicHandlerSend{
public:
    virtual void sendMessage(const QVariantMap& params) = 0;
};

}
