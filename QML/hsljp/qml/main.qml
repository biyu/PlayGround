import QtQuick 1.1
import com.meego 1.0
import "Constants.js" as Constants

PageStackWindow {
    id: appWindow
    // properties
    property Component routeResultPageComponent: null
    property Component startPointSelectPageComponent: null
    property Item notifyBanner: null
    // setup initial page
    initialPage: QuickRoutePlanPage {
        id: quickRoutePlanPage
    }
    // invert theme
    Component.onCompleted: theme.inverted = true

    ToolBarLayout {
        id: commonTools
        visible: true
        ToolIcon {
            platformIconId: "toolbar-back"; opacity: appWindow.pageStack.currentPage != quickRoutePlanPage ? 1.0 : 0.0
            onClicked: { commonMenu.close(); appWindow.popPage() }
            Behavior on opacity { NumberAnimation { duration: 300 } }
        }
        Text {
            id: name
            anchors.centerIn: commonTools
            font.family: Constants.Page_Common_Font_Family; font.pixelSize: Constants.Page_ToolBar_Font_PixelSize
            font.bold: true
            horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
            text: appWindow.pageStack.currentPage.pageName; color: "white"
        }
        ToolIcon {
            platformIconId: "toolbar-view-menu"
            anchors.right: parent===undefined ? undefined : parent.right
            onClicked: (commonMenu.status == DialogStatus.Closed) ? commonMenu.open() : commonMenu.close()
        }
    }

    Menu {
        id: commonMenu
        visualParent: pageStack
        MenuLayout {
            MenuItem { text: "None" }
        }
    }
    // create locator
    Locator {
        id: locator
        active: true
    }

    // functions
    function pushPage(page, properties) {
        if (page.status == Component.Ready)
            pageStack.push(page, properties);
        else
            console.log("Error loading component:", page.errorString());
    }

    function popPage() {
        pageStack.pop();
    }

    function isCurrentPage(page) {
        return (appWindow.pageStack.currentPage == page);
    }

    function showRouteResultPage(properties) {
        if(routeResultPageComponent == null) {
            routeResultPageComponent = Qt.createComponent("RouteResultPage.qml");
        }
        pushPage(routeResultPageComponent, properties);
        console.log("push RouteResultPage.qml");
    }

    function showStartPointSelectPage(properties) {
        if(startPointSelectPageComponent == null) {
            startPointSelectPageComponent = Qt.createComponent("StartPointSelectPage.qml")
        }
        pushPage(startPointSelectPageComponent, properties);
        console.log("push StartPointSelectPage.qml")
    }

    function createNewDestinationSheet(parent) {
        var newDestinationSheetComponent = Qt.createComponent("NewDestinationSheet.qml");
        var newDestinationSheet = newDestinationSheetComponent.createObject(parent);
        newDestinationSheet.width = Constants.Page_Width;
        newDestinationSheet.height = Constants.Page_Height;
//        newDestinationSheet.parent.visible = false;
        // destroy sheet when closed
        newDestinationSheet.statusChanged.connect(function () {
//                                                      if(newDestinationSheet.status == DialogStatus.Closing) {
//                                                          console.log("sheet closing");
//                                                          newDestinationSheet.parent.visible = true;
//                                                      }
                                                      if(newDestinationSheet.status == DialogStatus.Closed) {
                                                          console.log("sheet closed");
                                                          newDestinationSheet.destroy();
                                                      }
                                                  });
        return newDestinationSheet;
    }

    function showNotifyBanner(text) {
        if(notifyBanner == null) {
            var notifyBannerComponent = Qt.createComponent("NotifyBanner.qml");
            notifyBanner = notifyBannerComponent.createObject(quickRoutePlanPage);
        }
        notifyBanner.showText(text);
    }
}
