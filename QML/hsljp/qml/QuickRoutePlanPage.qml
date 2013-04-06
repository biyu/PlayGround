import QtQuick 1.1
import com.meego 1.0
import "Constants.js" as Constants
import "Database.js" as DB

Page {
    id: quickRoutePlanPage
    orientationLock: PageOrientation.LockPortrait
    tools: commonTools
    // properties
    property string pageName: Constants.QuickRoutePlanPage_Name
    property Item newDestinationSheet: null

    Component.onCompleted: {
        DB.loadFavorites();
        destinationPicker.loadDestinations();
    }

    // page items
    Item {
        id: root
        width: Constants.Page_Width; height: Constants.Page_Height-commonTools.height
        anchors.top:  parent.top
        // start point picker
        StartPointPicker {
            id: startPointPicker
            width: Constants.StartPointPicker_Width; height: Constants.StartPointPicker_Height
            anchors.bottom: destinationPicker.top; anchors.bottomMargin: Constants.StartPointPicker_BottomMargin
            anchors.horizontalCenter: root.horizontalCenter
            onClicked: root.startPointPickerClickedAction()
        }
        // destination picker
        DestinationPicker {
            id: destinationPicker
            width: Constants.DestinationPicker_Width; height: Constants.DestinationPicker_Height
            anchors.centerIn: root
            onIndexChanged: console.log("index: " + index); // debug
        }
        // select button
        SelectButton {
            id: selectButton
            width: Constants.SelectButton_Width; height: Constants.SelectButton_Height
            anchors.top: destinationPicker.bottom; anchors.topMargin: Constants.SelectButton_Anchor_TopMargin
            anchors.horizontalCenter: root.horizontalCenter
            // debug
            onClicked: root.selectButtonOnClickedAction();
            // states
            state: "CreateNew"
            states: [
                State {
                    name: "CreateNew"; when: destinationPicker.currentIndex() == 0
                    PropertyChanges { target: selectButton; text: Constants.SelectButton_Text_New }
                },
                State {
                    name: "FindRoute"; when: destinationPicker.currentIndex() != 0
                    PropertyChanges { target: selectButton; text: Constants.SelectButton_Text_FindRoute }
                }
            ]
        }
        // functions
        function selectButtonOnClickedAction() {
            if(destinationPicker.currentIndex()) {
                if(!locator.isAvalible()) {
                    appWindow.showNotifyBanner("location information not available");
                    console.log("location information not available");
                    return;
                }
                appWindow.showRouteResultPage({ startPointValue: startPointPicker.addressValue,
                                              startPointCoords: startPointPicker.addressCoords,
                                              destinationValue: destinationPicker.currentAddressValue(),
                                              destinationCoords: destinationPicker.currentAddressCoords() });
            }
            else {
                createNewDestination();
            }

            console.log("selectbutton clicked");
        }

        function startPointPickerClickedAction() {
            appWindow.showStartPointSelectPage( { _startPointPicker: startPointPicker,
                                               _destinationPicker: destinationPicker } );
            console.log("start point picker clicked");
        }

        function createNewDestination() {
            newDestinationSheet = appWindow.createNewDestinationSheet(root);
            // show route
            newDestinationSheet.accepted.connect(function () {
                                                     // save favorite if needed
                                                     if(newDestinationSheet.saveFavoriteChecked) {
                                                         if(newDestinationSheet.nickName == "") {
                                                             newDestinationSheet.nickName = newDestinationSheet.selectedAddress;
                                                         }
                                                         DB.addSingleFavorite(newDestinationSheet.nickName,
                                                                              newDestinationSheet.selectedAddress,
                                                                              newDestinationSheet.selectedCoord,
                                                                              // add new destination here
                                                                              function(name, value, coords) {
                                                                                  destinationPicker.addDestination(name, value, coords);
                                                                              });
                                                     }
                                                     // check whether gps info ready or not
                                                     if(!locator.isAvalible()) {
                                                         appWindow.showNotifyBanner("location information not available");
                                                         console.log("location information not available");
                                                         return;
                                                     }
                                                     // show result page
                                                     appWindow.showRouteResultPage({ startPointValue: startPointPicker.addressValue,
                                                                                   startPointCoords: startPointPicker.addressCoords,
                                                                                   destinationValue: newDestinationSheet.selectedAddress,
                                                                                   destinationCoords: newDestinationSheet.selectedCoord });

                                                 });
            newDestinationSheet.open();
        }
    }
}
