import QtQuick 1.1
import com.meego 1.0
import "Constants.js" as Constants
import "Core.js" as Core

Sheet {
    id: sheet
    // properties
    property string selectedAddress: ""
    property string selectedCoord: ""
    property string nickName
    property bool saveFavoriteChecked
    // debug
    onSelectedAddressChanged: console.log("selectedName: " + selectedAddress)
    onSelectedCoordChanged: console.log("selectedCoord: " + selectedCoord)
    onSaveFavoriteCheckedChanged: console.log("saveFavoriteChecked: " + saveFavoriteChecked)
    // disable "find route" button at beginning
    Component.onCompleted: { disableButton(1) }
    acceptButtonText: "Find Route"
    rejectButtonText: "Cancel"
    content: Item {
        id: contents
        anchors.fill: parent; anchors.leftMargin: 10; anchors.topMargin: 10
        // block mouse event passing to parent page
        MouseArea {
            anchors.fill: parent
        }
        Column {
            id: column
            anchors.fill: parent
            spacing: 10
            move: Transition {
                reversible: true
                NumberAnimation {
                    properties: "y,opacity"
                    easing.type: Easing.OutQuad
                    duration: 200
                }
            }
            // destination input
            LineEdit {
                id: destLineEdit
                width: parent.width; height: parent.height/11
                labelText: "Destination: "
                onTextChanged: input(text)
                // functions
                function input(text) {
                    if( text.length > 2) {
                        Core.address_to_location( text, function(response) {
                                                     contents.showAddressSuggestion(destLineEdit, response)
                                                 } )
                        listView.show();
                        sheet.enableButton(1);
                    }
                    else {
                        listView.hideAndClear();
                        sheet.disableButton(1);
                    }
                }
            }
            // location name suggestion list
            ListView {
                id: listView
                width: parent.width; height: parent.height*4/11 //Math.min(parent.height*4/11, parent.height/22*count)
                opacity: 0.0; clip: true
                delegate: Rectangle {
                    id: itemRoot
                    width: listView.width; height: listView.height/8
                    color: "transparent"
                    Text {
                        id: itemText
                        anchors.fill: parent
                        font.family: Constants.Page_Common_Font_Family
                        font.pixelSize: Constants.Page_Common_Font_PixelSize
                        font.bold: true; horizontalAlignment: Text.AlignLeft; verticalAlignment: Text.AlignVCenter
                        color: Constants.Page_Common_Text_Color; elide: Text.ElideRight
                        text: name
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: itemRoot.color = "lightblue"
                        onReleased: {
                            itemRoot.color = "transparent";
                            clickTarget.text = itemText.text;
                            sheet.setValues(name, coord);
                            listView.hideAndClear();
                        }
                        onCanceled: itemRoot.color = "transparent"
                    }
                }
                model: listModel
                // functions
                function show() {
                    listView.opacity = 1.0;
                }
                function hideAndClear() {
                    listView.opacity = 0.0;
                    listView.model.clear();
                }
            }
            // nick name input
            LineEdit {
                id: nickNameLineEdit
                width: parent.width; height: parent.height/11
                labelText: "NickName: "
                opacity: switcher.checked ? 1.0 : 0.0
            }
            // save switch
            Switcher {
                id: switcher
                width: parent.width; height: parent.height/11
                labelText: "Save Destination As Favorite"
            }
            Binding {
                target: sheet
                property: "nickName"
                value: nickNameLineEdit.text
            }
            Binding {
                target: sheet
                property: "saveFavoriteChecked"
                value: switcher.checked
            }
        }
        // list model
        ListModel {
            id: listModel
        }
        // functions
        function showAddressSuggestion(target, response) {
            console.log("searching place")
            listModel.clear();
            for( var location in response ) {
                location = response[location]
                listModel.append( {
                                 name: location.name,
                                 city: location.city,
                                 coord: location.coords,
                                 clickTarget: target
            } );
            }
            // automatically update selection; always choose first one
            if(listModel.count>0) {
                sheet.setValues(listModel.get(0).name, listModel.get(0).coord);
            }
        }
    }
    // functions
    function enableButton(index) {
        buttons[index].enabled = true
    }
    function disableButton(index) {
        buttons[index].enabled = false
    }
    function setValues(name, coord) {
        selectedAddress = name;
        selectedCoord = coord;
    }
}
