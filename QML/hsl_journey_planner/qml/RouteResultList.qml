import QtQuick 1.1
import com.meego 1.0
import "Constants.js" as Constants

Item {
    id: root
    // signals
    signal headerClicked()
    // header
    Item {
        id: header
        width: Constants.RouteResultList_Header_Width
        height: Constants.RouteResultList_Header_Height
        anchors.top: root.top; anchors.left: root.left; anchors.right: root.right
        // properties
        property string startPointText: ""
        property string destinationText: ""
        Button {
            id: headerBackground
            width: header.width; height:  header.height
            anchors.fill: header
            onClicked: root.headerClicked()
        }
        Row {
            id: headerRow
            width: header.width*0.9; height: header.height*0.9
            anchors.centerIn: header
            Text {
                id: startPointButton
                width: headerRow.width*3/7; height: headerRow.height
                font.family: Constants.Page_Common_Font_Family
                font.pixelSize: Constants.RouteResultList_Header_Text_Font_PixelSize
                font.bold: true
                horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                color: Constants.RouteResultList_Header_Text_Color; elide: Text.ElideRight
                text: header.startPointText
            }
            Text {
                id: headerText
                width: headerRow.width/7; height: headerRow.height
                font.family: Constants.Page_Common_Font_Family
                font.pixelSize: Constants.RouteResultList_Header_Text_Font_PixelSize
                horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                color: Constants.RouteResultList_Header_Text_Color
                text: Constants.RouteResultList_Header_Text_Delimeter
            }
            Text {
                id: destinationButton
                width: headerRow.width*3/7; height: headerRow.height
                font.family: Constants.Page_Common_Font_Family
                font.pixelSize: Constants.RouteResultList_Header_Text_Font_PixelSize
                font.bold: true
                horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                color: Constants.RouteResultList_Header_Text_Color; elide: Text.ElideRight
                text: header.destinationText
            }
        }
    }
    // list view
    ListView {
        id: listView
        width: root.width; height: root.height
        anchors.top: header.bottom; anchors.topMargin: Constants.RouteResultList_List_TopMargin
        highlightRangeMode: ListView.StrictlyEnforceRange
        maximumFlickVelocity: Constants.Page_Common_ListView_MaximumFlickVelocity
        orientation: ListView.Vertical; currentIndex: 0
        spacing: 10; clip: true
        delegate: Rectangle {
            id: background
            width: Constants.RouteResultList_Delegate_Width; height: Constants.RouteResultList_Delegate_Height
            color: "transparent"
            // splite one line into two parts
            Column {
                width: background.width; height:  background.height
                spacing: 5
                // first line for displaying routes
                Row {
                    id: firstLine
                    width: parent.width; height: parent.height*0.6
                    spacing: 5
                    // time for first point
                    Column {
                        width: firstLine.width/5; height: firstLine.height
                        Text {
                            id:startTime
                            width: parent.width; height: parent.height*0.4
                            font.family: Constants.Page_Common_Font_Family
                            font.pixelSize: height; font.bold: true; font.letterSpacing: -2
                            verticalAlignment: Text.AlignVCenter
                            color: Constants.Page_Common_Text_Color
                            text: pointRepeater.model.get(0).leg.first.time
                        }
                        Text {
                            id: endTime
                            width: parent.width; height: parent.height*0.6
                            font.family: Constants.Page_Common_Font_Family
                            font.pixelSize: height; font.bold: true; font.letterSpacing: -2
                            horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                            color: Constants.Page_Common_Text_Color
                            text: pointRepeater.model.get(0).leg.last.time;
                        }
                    }
                    // route points
                    Repeater {
                        id: pointRepeater
                        width: firstLine.width*4/5; height: firstLine.height
                        model: points
                        // each point
                        Column {
                            width: firstLine.height*0.6; height:firstLine.height
                            spacing: 3
                            Image {
                                id: symbolImage
                                width: parent.width; height: parent.height*0.6
                                smooth: true
                                source: {
                                    if(leg.type == "walk") return Constants.RouteResultList_Delegate_ImageSource_Walk;
                                    if(leg.type == "bus") return Constants.RouteResultList_Delegate_ImageSource_Bus;
                                    if(leg.type == "metro") return Constants.RouteResultList_Delegate_ImageSource_Metro;
                                    if(leg.type == "tram") return Constants.RouteResultList_Delegate_ImageSource_Tram;
                                    if(leg.type == "train") return Constants.RouteResultList_Delegate_ImageSource_Train;
                                }
                            }
                            Text {
                                width: parent.width; height: parent.height*0.4
                                font.family: Constants.Page_Common_Font_Family
                                font.bold: leg.type == "walk" ? false : true; font.letterSpacing: -2
                                font.pixelSize: {
                                    if(text.length <= 3) return height*0.9;
                                    else if(text.length < 5) return height*0.7;
                                    else return height*0.6;
                                }
                                horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                                color: Constants.Page_Common_Text_Color; elide: Text.ElideRight
                                text: {
                                    if(leg.type == "walk") return leg.length;
                                    if(leg.type == "bus") return leg.code;
                                    if(leg.type == "metro") return "M";
                                    if(leg.type == "tram") return leg.code;
                                    if(leg.type == "train") return leg.code;
                                }
                            }
                        }
                    }
                }
                // second line for displaying route info
                Row {
                    id: secondLine
                    width: parent.width; height: parent.height*0.4
                    spacing: 10
                    Text {
                        height: parent.height
                        font.family: Constants.Page_Common_Font_Family
                        font.pixelSize: height*0.5; font.bold: true
                        verticalAlignment: Text.AlignVCenter
                        color: Constants.Page_Common_Text_Color
                        text: "Walk: " + briefInfo.walking + " km"
                    }
                    Text {
                        height: parent.height
                        font.family: Constants.Page_Common_Font_Family
                        font.pixelSize: height*0.5; font.bold: true
                        verticalAlignment: Text.AlignVCenter
                        color: Constants.Page_Common_Text_Color
                        text: "Duration: " + briefInfo.duration + " mins"
                    }
                    Text {
                        height: parent.height
                        font.family: Constants.Page_Common_Font_Family
                        font.pixelSize: height*0.5; font.bold: true
                        verticalAlignment: Text.AlignVCenter
                        color: Constants.Page_Common_Text_Color
                        text: "Arrival: " + briefInfo.arrival
                    }
                }
            }
        }
        model: ListModel {id: listModel}
    }
    // functions
    function setHeaderText(startPoint, destination) {
        header.startPointText = startPoint;
        header.destinationText = destination;
    }

    function headerStartPointText() {
        return header.startPointText;
    }

    function headerDestinationText() {
        return header.destinationText;
    }

    function addSingleRouteInfo(points, briefInfo) {
        listView.model.append( { "points": points, "briefInfo": briefInfo } );
    }
}
