import QtCharts 2.12
import QtQml 2.12
import QtQuick 2.12
import QtQuick.Controls.Material 2.12

import RQml 1.0
import RQml.Utils 1.0
import RQml.Layout 1.0

RItem{
    id: root
    topic: "/imu"

    Timer {
        property int amountOfData: 0 //So we know when we need to start
        property int timeline: 0 // Start of the timeline
        id: refreshTimer
        interval: 100
        running: !root.isDefaultValue
        repeat: true
        onTriggered: {
            timeline++;
            series1.append(timeline, Ros.mirror[root.topic]["linear_acceleration"]["x"]);
            series2.append(timeline, Ros.mirror[root.topic]["linear_acceleration"]["y"]);
            series3.append(timeline, Ros.mirror[root.topic]["linear_acceleration"]["z"]);
            if(amountOfData > axisX.max){
                axisX.min++;
                axisX.max++;
            }else{
                amountOfData++; //This else is just to stop incrementing the variable unnecessarily
            }
            //remove all data points that are not visible anymore
            if (timeline > 100){
                series1.remove(1);
                series2.remove(1);
                series3.remove(1);
            }
        }
    }

    ChartView {
        id: chart
        title: "IMU: linear acceleration"

        anchors.fill: parent
        antialiasing: true

        ValueAxis {
            id: axisX
            min: 0
            max: 10
            tickCount: 5
        }

        ValueAxis {
            id: axisY1
            min: -10
            max: 10
        }

        ValueAxis {
            id: axisY2
            min: -10
            max: 10
        }

        ValueAxis {
            id: axisY3
            min: -10
            max: 10
        }

        SplineSeries {
            id: series1
            name: "x"
            axisX: axisX
            axisY: axisY1
        }

        SplineSeries {
            id: series2
            name: "y"
            axisX: axisX
            axisY: axisY2
        }

        SplineSeries {
            id: series3
            name: "z"
            axisX: axisX
            axisY: axisY3
        }
    }
}
