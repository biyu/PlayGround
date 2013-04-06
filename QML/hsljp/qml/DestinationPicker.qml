import QtQuick 1.1
import com.meego 1.0
import QtMultimediaKit 1.1
import "Constants.js" as Constants
import "Database.js" as DB

Item {
    id: root
    clip: true
    // signal
    signal indexChanged(int index)
    // load destinations when item ready
    Component.onCompleted: {
        listView.currentIndexChanged.connect(listView.indexChangeActions);
    }

    // components

    // sound effect
    SoundEffect {
        id: scrollSoundEffect
        source: Constants.DestinationPicker_Soundeffect_Filename
    }
    // background
    Rectangle {
        id: background
        width: root.width; height: root.height; radius: 20; anchors.fill: root
        gradient: Gradient {
            GradientStop { position: 0.0; color: "black" }
            GradientStop { position: 0.5; color: "white" }
            GradientStop { position: 0.5; color: "white" }
            GradientStop { position: 1.0; color: "black" }
        }
    }
    // destination list
    ListView {
        // list view
        id: listView
        width: root.width; height: root.height; anchors.fill: root
        highlightRangeMode: ListView.StrictlyEnforceRange
        preferredHighlightBegin: Constants.DestinationPicker_Delegate_Highlight_Begin
        preferredHighlightEnd: Constants.DestinationPicker_Delegate_Highlight_End
        maximumFlickVelocity: Constants.Page_Common_ListView_MaximumFlickVelocity
        orientation: ListView.Vertical; currentIndex: 0
        highlight: Item {
            // highlight item
            id: listHighlightRoot
            width: Constants.DestinationPicker_Delegate_Highlight_Width
            height: Constants.DestinationPicker_Delegate_Highlight_Height
            opacity: Constants.DestinationPicker_Delegate_Highlight_Opacity
            Rectangle {
                id: listHighlightRect
                width: listHighlightRoot.width; height: listHighlightRoot.height
                border.width: Constants.DestinationPicker_Delegate_Highlight_Border_Width
                border.color: "black"
                color: "grey"
            }
        }
        // list delegate
        delegate: Item {
            // delegate item
            id: listDelegateRoot
            width: Constants.DestinationPicker_Delegate_Width
            height: Constants.DestinationPicker_Delegate_Height
            // delegate background
            Rectangle {
                id: listDelegateBG
                width: listDelegateRoot.width; height: listDelegateRoot.height; anchors.centerIn: listDelegateRoot
                color: "lightblue"; opacity: 0.0
            }
            // text
            Text {
                // delegate text
                id: listDelegateText
                width: listDelegateRoot.width-10; height: listDelegateRoot.height; anchors.centerIn: listDelegateRoot
                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
                font.family: Constants.DestinationPicker_Delegate_Font_Family
                font.pixelSize: Constants.DestinationPicker_Delegate_Font_PixelSize
                font.bold: index == 0 ? false : true
                font.wordSpacing: Constants.DestinationPicker_Delegate_Font_WordSpace
                smooth: true; elide: Text.ElideRight
                text: name
            }
            NumberAnimation {
                // delegate background animation
                id: listDelegateBGAnimation
                target: listDelegateBG; property: "opacity"
                to: 0.0; duration: 500
            }
            // connect current index change signal to actions
            Connections {
                target: listView
                onCurrentIndexChanged: {
                    listDelegateBGAnimation.start()
                }
            }
            MouseArea {
                // delegate mouse area
                anchors.fill: listDelegateRoot
                onPressed: listView.currentIndex != index ? listDelegateBG.opacity = 1.0 : listDelegateBG.opacity = 0.0
                onReleased: listView.currentIndex = index
                onPressAndHold: contextMenu.open()
            }
            ContextMenu {
                id: contextMenu
                MenuLayout {
                    MenuItem {
                        text: "Delete"
                        onClicked: {
                            DB.deleteSingleFavorite(name, function() {
                                                        listView.model.remove(index);
                                                    })
                        }
                    }
                }
            }
        }
        model: ListModel {
            // list model
            id: listModel
        }
        // functions
        function indexChangeActions() {
            // emit signal
            root.indexChanged(listView.currentIndex);
            // play scroll effect
            scrollSoundEffect.play();
        }
    }
    // functions
    function loadDestinations() {
        listView.model.append({"name": "[Define New Destination]", "value": "", "coords": ""});
        // load favorites
        for(var i=0; i<DB.favorites.length; i++) {
            listView.model.append(DB.favorites[i]);
        }
    }
    function currentIndex() {
        return listView.currentIndex;
    }
    function currentAddressValue() {
        return listView.model.get(listView.currentIndex).value;
    }
    function currentAddressCoords() {
        return listView.model.get(listView.currentIndex).coords;
    }
    function addDestination(name, value, coords) {
        listView.model.append({"name": name, "value": value, "coords": coords});
    }
}
