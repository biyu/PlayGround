import QtQuick 1.1
import com.meego 1.0
import "Constants.js" as Constants

Item {
    id: root
    // properties
    property alias labelText: label.text
    property real _ratio: 0.7
    property alias checked: switcher.checked
    // name of switch
    Label {
        id: label
        width: root.width*_ratio; height: root.height
        anchors.left: root.left; anchors.leftMargin: Constants.Switcher_Label_LeftMergin
        anchors.verticalCenter: root.verticalCenter
        horizontalAlignment: Text.AlignLeft; verticalAlignment: Text.AlignVCenter
        font.bold: true
        platformStyle: LabelStyle {
            fontFamily: Constants.Page_Common_Font_Family
            fontPixelSize: height*0.3
        }
    }
    Switch {
        id: switcher
        anchors.right: root.right; anchors.rightMargin: Constants.Switcher_Switch_RightMergin
        anchors.verticalCenter: root.verticalCenter
    }
}
