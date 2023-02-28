import Qt3D.Core 2.0
import Qt3D.Extras 2.12
import Qt3D.Input 2.0
import Qt3D.Render 2.12

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Scene3D 2.0


// Dla przyszlych pokolen
// Ariadna jest ustawiona przeciwnie do osi Z ktora przechodzi przez jej prawa gasienice
// Os X wychodzi przez jej prawy bok
// Os Y wychodzi do gory
// Kamera zawsze patrzy w punkt 0,0,0

Item{
    id: root

    function moveCameraTo(x, y, z, animationDurationMs){
        cameraAnimationX.stop()
        cameraAnimationY.stop()
        cameraAnimationZ.stop()

        cameraAnimationX.from = camera.xPosition
        cameraAnimationX.to = x
        cameraAnimationX.duration = animationDurationMs

        cameraAnimationY.from = camera.yPosition
        cameraAnimationY.to = y
        cameraAnimationY.duration = animationDurationMs

        cameraAnimationZ.from = camera.zPosition
        cameraAnimationZ.to = z
        cameraAnimationZ.duration = animationDurationMs

        cameraAnimationX.start()
        cameraAnimationY.start()
        cameraAnimationZ.start()
    }

    Rectangle {
        id: scene
        anchors.fill: parent
        color: "transparent"

        Scene3D {
            id: scene3d
            anchors.fill: parent
            focus: true

            Entity {
                id: sceneRoot

                Camera {
                    id: camera

                    property int xPosition: 0
                    property int yPosition: 0
                    property int zPosition: 0

                    projectionType: CameraLens.PerspectiveProjection
                    fieldOfView: 45
                    nearPlane : 0.1
                    farPlane : 1000.0
                    position: Qt.vector3d( xPosition, yPosition, zPosition )
                    upVector: Qt.vector3d( 0.0, 0.0, 0.0 )
                    viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
                }

                components: [
                    RenderSettings {
                        id: renderSettings
                        activeFrameGraph: ForwardRenderer {
                            camera: camera
                            clearColor: "transparent"
                        }
                    },
                    InputSettings {}
                ]

                Entity {
                    id: ariadnaEntity
                    components: [
                        Mesh{
                            source: "qrc:/images/saper.obj"
                        },
                        PhongMaterial {
                            ambient:  "grey"

                            shininess: 1.0
                            diffuse:  "white"
                            specular: "yellow"
                        }
                    ]
                }
            }
        }
    }

    NumberAnimation {
        id: cameraAnimationX
        target: camera
        property: "xPosition"
        easing.type: Easing.InOutQuad
    }

    NumberAnimation {
        id: cameraAnimationY
        target: camera
        property: "yPosition"
        easing.type: Easing.InOutQuad
    }

    NumberAnimation {
        id: cameraAnimationZ
        target: camera
        property: "zPosition"
        easing.type: Easing.InOutQuad
    }
}
