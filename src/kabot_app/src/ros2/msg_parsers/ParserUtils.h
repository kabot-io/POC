#pragma once

#include "rclcpp/rclcpp.hpp"

#include <QJsonObject>
#include <QList>
#include <QString>
#include <QVariantMap>
#include <QVector>

#include <algorithm>
#include <array>
#include <functional>
#include <string>
#include <vector>

namespace RosMessageParser{
namespace ParseUtils{

inline QVariant toVariant(const bool msg){ return msg;}
inline QVariant toVariant(const uint8_t msg){ return msg;}
inline QVariant toVariant(const char msg){ return msg;}
inline QVariant toVariant(const float msg){ return msg;}
inline QVariant toVariant(const double msg){ return msg;}
inline QVariant toVariant(const int8_t msg){ return msg;}
inline QVariant toVariant(const int16_t msg){ return msg;}
inline QVariant toVariant(const int32_t msg){ return msg;}
inline QVariant toVariant(const uint32_t msg){ return msg;}
inline QVariant toVariant(const int64_t msg){ return QVariant::fromValue(msg);}
inline QVariant toVariant(const uint64_t msg){ return QVariant::fromValue(msg);}
inline QVariant toVariant(const std::string& msg){ return QString::fromStdString(msg);}
inline QVariant toVariant(const std::u16string& msg){ return QString::fromStdU16String(msg);}
template <class T> QVariant toVariant(const std::vector<T>& msg){ QVariantList list; for(auto& i: msg){ list.append(i);} return list;}
template <class T, std::size_t N> QVariant toVariant(const std::array<T,N>& msg){ return toVariant<T>(std::vector(msg.begin(), msg.end()));}

//Use it when T isn't a basic type
// TODO
//template <class T> QVariant toVariant(const std::vector<T>& msg, const std::function<QVariantMap(const T&)>& vectorElementsParser){
//    QList<QVariant> list;
//    for(int i = 0; i < msg.size(); i++)
//        list.append(vectorElementParser(msg[i]));
//    return list;
//}

inline bool toBool(const QString& name, const QVariantMap& msg){ return msg[name].toBool();}
inline uint8_t toUint8(const QString& name, const QVariantMap& msg){ return msg[name].toUInt();}
inline char toChar(const QString& name, const QVariantMap& msg){ return msg[name].toChar().toLatin1();}
inline float toFloat(const QString& name, const QVariantMap& msg){ return msg[name].toFloat();}
inline double toDouble(const QString& name, const QVariantMap& msg){ return msg[name].toDouble();}
inline int8_t toInt8(const QString& name, const QVariantMap& msg){ return msg[name].toInt();}
inline int16_t toInt16(const QString& name, const QVariantMap& msg){ return msg[name].toInt();}
inline int32_t toInt32(const QString& name, const QVariantMap& msg){ return msg[name].toInt();}
inline uint32_t toUint32(const QString& name, const QVariantMap& msg){ return msg[name].toUInt();}
inline int64_t toInt64(const QString& name, const QVariantMap& msg){ return msg[name].toInt();}
inline uint64_t toUint64(const QString& name, const QVariantMap& msg){ return msg[name].toUInt();}
inline std::string toString(const QString& name, const QVariantMap& msg){ return msg[name].toString().toStdString();}
inline std::u16string toU16string(const QString& name, const QVariantMap& msg){ return msg[name].toString().toStdU16String();}

template <class T, std::size_t  N> std::array<T,N> toArray(const QString& name, const QVariantMap& msg){
    auto qvec = msg[name].value<QVector<T>>();
    std::array<T, N> arr;
    std::copy_n(qvec.begin(), N, arr.begin());
    return arr;
}
template <class T> std::vector<T> toVector(const QString& name, const QVariantMap& msg){
    auto qvec = msg[name].value<QVector<T>>();
    return std::vector<T>(qvec.begin(), qvec.end());
}

//// TODO
//template <class T> std::vector<T> toVector(const QString& name, const QVariantMap& msg, std::function<T(const QVariantMap&)> vectorElementsParser){
//    auto qvec = msg[name].value<QVector<T>>();
//    return std::vector<T>(qvec.begin(), qvec.end());
//}

}
}
