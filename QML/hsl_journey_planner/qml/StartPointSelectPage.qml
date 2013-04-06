import QtQuick 1.1
import com.meego 1.0
import "Constants.js" as Constants
import "Database.js" as DB

Page {
    id: startPointSelectPage
    orientationLock: PageOrientation.LockPortrait
    tools: commonTools
    // properties
    property string pageName: Constants.StartPointSelectPage_Name
    property Item _startPointPicker: null
    property Item _destinationPicker: null
    property Item newDestinationSheet: null
    // titel
    Rectangle {
        id: title
        width: Constants.StartPointSelectPage_Button_Width; height: Constants.StartPointSelectPage_TopMargin/2
        anchors.top: parent.top; anchors.topMargin: Constants.StartPointSelectPage_TopMargin/2;
        anchors.horizontalCenter: parent.horizontalCenter
        color: "gray"; radius: 10
        Text {
            id: text
            anchors.fill: parent
            font.family: Constants.Page_Common_Font_Family; font.bold: true
            font.pixelSize: Constants.Page_Common_Font_PixelSize
            horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere; color: "white"
            text: Constants.StartPointSelectPage_Title_Text
        }
    }
    // flickable
    Flickable {
        id: flickable
        width: buttonColumn.paintWidth(); height: Constants.Page_Height*3/4
        anchors.top: title.bottom; anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        contentWidth: buttonColumn.paintWidth(); contentHeight: buttonColumn.paintHeight()
        flickableDirection: Flickable.VerticalFlick; clip: true
        Component.onCompleted: buttonColumn.loadFavorites();
        // button columns
        ButtonColumn {
            id: buttonColumn
            anchors.fill: parent
            exclusive: false
            Repeater {
                id: repeater
                delegate: Button {
                    width: Constants.StartPointSelectPage_Button_Width
                    height: Constants.StartPointSelectPage_Button_Height
                    text: name
                    onClicked: buttonColumn.buttonClickedAction(name, value, coords);
                }
                model: ListModel {
                    id: listModel
                }
            }
            // functions
            function loadFavorites() {
                repeater.model.append({"name": "[Current Location]", "value": "Current Location", "coords": ""});
                repeater.model.append({"name": "[Enter a New Address]", "value": "Enter a New Address", "coords": ""});
                for(var i=0; i<DB.favorites.length; i++) {
                    repeater.model.append(DB.favorites[i]);
                }
                console.log("load origins; favorites: " + DB.favorites.length);
            }
            function buttonClickedAction(name, value, coords) {
                if(value == "Enter a New Address") {
                    newDestinationSheet = appWindow.createNewDestinationSheet(startPointSelectPage);
                    newDestinationSheet.accepted.connect( function () {
                                                             if(newDestinationSheet.nickName == "") {
                                                                 newDestinationSheet.nickName = newDestinationSheet.selectedAddress;
                                                             }
                                                             if(newDestinationSheet.saveFavoriteChecked) {
                                                                 DB.addSingleFavorite(newDestinationSheet.nickName,
                                                                                      newDestinationSheet.selectedAddress,
                                                                                      newDestinationSheet.selectedCoord,
                                                                                      // add new destination here
                                                                                      function(name, value, coords) {
                                                                                          _destinationPicker.addDestination(name, value, coords);
                                                                                      });
                                                             }
                                                             _startPointPicker.setAddressInfo(newDestinationSheet.nickName,
                                                                                              newDestinationSheet.selectedAddress,
                                                                                              newDestinationSheet.selectedCoord);
                                                             appWindow.popPage();
                                                         } )
                    newDestinationSheet.open();
                }
                else {
                    _startPointPicker.setAddressInfo(name, value, coords);
                    appWindow.popPage();
                }
            }
            function paintWidth() {
                return Constants.StartPointSelectPage_Button_Width;
            }
            function paintHeight() {
                return Constants.StartPointSelectPage_Button_Height*repeater.count;
            }
        }
    }
}
