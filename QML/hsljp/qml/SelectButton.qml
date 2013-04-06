import QtQuick 1.1
import com.meego 1.0
import "Constants.js" as Constants

Item {
    id: root
    // properties
    property alias text: button.text
    // signal
    signal clicked()    // button clicked
    // components
    Button {
        // button
        id: button
        width: root.width; height: root.height; anchors.centerIn: root
        text: Constants.SelectButton_Text_New
        onClicked: root.clicked()
        platformStyle: ButtonStyle {
            fontFamily: Constants.SelectButton_Font_Family
            fontPixelSize: Constants.SelectButton_Font_PixelSize
        }
    }
    // functions
    function changeButtonText(text) {
        button.text = text;
    }
}
