import QtQuick 1.1
import com.meego 1.0
import "Constants.js" as Constants

Item {
    id: root
    // properties
    property alias text: text.text
    property alias running: busyIndicator.running
    // busy indicator
    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: root
        platformStyle: BusyIndicatorStyle { size: "large" }
    }
    Text {
        id: text
        anchors.top: busyIndicator.bottom; anchors.topMargin: 15
        anchors.horizontalCenter: root.horizontalCenter
        font.bold: true; font.family: Constants.Page_Common_Font_Family
        font.pixelSize: Constants.Page_Common_Font_PixelSize
        horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
        text: ""; color: "white"
    }
}
