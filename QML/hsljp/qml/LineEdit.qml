import QtQuick 1.1
import com.meego 1.0
import "Constants.js" as Constants

Item {
    id: root
    // properties
    property alias labelText: label.text
    property alias labelColor: label.color
    property alias text: textField.text
    property real _ratio: 0.3
    property bool isActiveFocus: textField.activeFocus
    // signals
    signal textChanged()
    // text input field
    TextField {
        id: textField
        width: root.width; height: root.height
        anchors.top: root.top
        inputMethodHints: Qt.ImhNoPredictiveText
        platformStyle: TextFieldStyle {
            paddingLeft: label.width
        }
        onTextChanged: root.textChanged()
    }
    // text label
    Label {
        id: label
        width: root.width*_ratio; height: root.height
        anchors.left: textField.left; anchors.top: textField.top
        anchors.leftMargin: Constants.LineEdit_Label_LeftMargin
        horizontalAlignment: Text.AlignLeft; verticalAlignment: Text.AlignVCenter
        font.bold: true
        platformStyle: LabelStyle {
            textColor: "black"
            fontFamily: Constants.Page_Common_Font_Family
            fontPixelSize: height*_ratio //Constants.Page_Common_Font_PixelSize
        }
    }
}
