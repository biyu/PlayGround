import QtQuick 1.1
import com.meego 1.0
import "Constants.js" as Constants
import "Core.js" as Core
import "CoreHelper.js" as Parser
import "RouteResultListLoader.js" as ListLoader

Page {
    id: routeResultPage
    orientationLock: PageOrientation.LockPortrait
    tools: commonTools
    // properties
    property string pageName: Constants.RouteResultPage_Name
    property bool loading: false
    property string startPointValue: ""
    property string destinationValue: ""
    property string startPointCoords: ""
    property string destinationCoords: ""
    // loading start here
    Component.onCompleted: ListLoader.startLoad();
    // route results list
    RouteResultList {
        id: routeResultList
        width: Constants.RouteResultList_Width; height: Constants.RouteResultList_Height
        anchors.top: routeResultPage.top
        visible: !loading
        onHeaderClicked: {
            dialog.open();
            console.log("header clicked")
        }
    }
    // address dialog
    Dialog {
        id: dialog
        content: Text {
            id: text
            width: parent.width; height: parent.height/3
            anchors.centerIn: parent
            font.family: Constants.Page_Common_Font_Family; font.bold: true
            font.pixelSize: Constants.Page_Common_Font_PixelSize
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            color: "white"
            text: "FROM: " + routeResultList.headerStartPointText() + "\n\n"
                  + "TO: " + routeResultList.headerDestinationText()
        }
    }
    // busy indicator
    LoadIndicator {
        id: loadIndicator
        // anchors.centerIn: routeResultPage
        anchors.fill: routeResultPage
        visible: loading; running: loading
    }
    // notification banner
    NotifyBanner {
        id: notifyBanner
    }
    // functions
    function setProcessText(newText) {
        loadIndicator.text = newText;
    }
}

