import QtQuick 1.1
import com.meego 1.0
import com.nokia.extras 1.0
import "Constants.js" as Constants

Item {
    id: root
    // properties
    property string addressValue: "Current Location"
    property string addressCoords: ""
    property alias addressName: addressText.text
    //signal
    signal clicked()
    // components
    Button {
        // button
        id: button
        width: root.width; height: root.height
        anchors.centerIn: root
        platformStyle: ButtonStyle {
            fontFamily: Constants.SelectButton_Font_Family
            fontPixelSize: Constants.SelectButton_Font_PixelSize
        }
        onClicked: root.clicked()
    }
    // prefix text
    Text {
        id: prefixText
        width: Constants.StartPointPicker_Prefix_Text_Width
        height: Constants.StartPointPicker_Prefix_Text_Height
        anchors.left: root.left; anchors.leftMargin: Constants.StartPointPicker_Prefix_Text_LeftMargin
        anchors.verticalCenter: root.verticalCenter
        font.family: Constants.Page_Common_Font_Family
        font.pixelSize: Constants.StartPointPicker_Font_PixelSize
        font.bold: true;
        horizontalAlignment: Text.AlignLeft; verticalAlignment: Text.AlignVCenter
        text: Constants.StartPointPicker_Prefix_Text; color: "white"
    }
    // start point text
    Text {
        id: addressText
        width: Constants.StartPointPicker_Address_Text_Width
        height: Constants.StartPointPicker_Address_Text_Height
        anchors.left: prefixText.right; anchors.leftMargin: 10
        anchors.verticalCenter: root.verticalCenter
        font.family: Constants.Page_Common_Font_Family
        font.pixelSize: Constants.StartPointPicker_Font_PixelSize
        horizontalAlignment: Text.AlignLeft; verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
        text: Constants.StartPointPicker_Default_Text; color: "white"
    }
    // more indicator
    MoreIndicator {
        id: moreIndicator
        width: Constants.StartPointPicker_MoreIndicator_Width
        height: Constants.StartPointPicker_MoreIndicator_Height
        anchors.left: addressText.right; anchors.right: root.right; anchors.verticalCenter: root.verticalCenter
    }
    // functions
    function setAddressName(name) {
        addressName = name;
    }
    function setAddressValue(value) {
        addressValue = value;
    }
    function setAddressCoords(coords) {
        addressCoords = coords;
    }
    function setAddressInfo(name, value, coords) {
        addressName = name;
        addressValue = value;
        addressCoords = coords;
    }
}
