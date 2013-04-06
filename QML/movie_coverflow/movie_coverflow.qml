import Qt 4.7

Rectangle {
    id: movieCoverFlow
    width: 800
    height: 480
    color: "black"

    // the movie data can be treated as a list
    ListView {
        id: movieListView
        width: parent.width
        height: parent.height
        // model
        model: testModel
        // delegate
        delegate: testDelegate
        orientation: ListView.Horizontal
        highlight: testHighlight
        preferredHighlightBegin: width/3
        preferredHighlightEnd: width*2/3
        highlightRangeMode: ListView.StrictlyEnforceRange
        highlightFollowsCurrentItem: false
        smooth: true
        spacing: 20
    }

    Component {
        id: testDelegate
        Image {
            id: item
            source: pics
            width: ListView.view.width/3
            height: ListView.view.height/2
            sourceSize.width: width
            sourceSize.height: height
            y: (ListView.view.height-height)/2
            smooth: true
        }

    }

    XmlListModel {
        id: testModel
        source: "http://api.flickr.com/services/feeds/photos_public.gne?tags=albumcover"
        query: "/feed/entry"
        namespaceDeclarations: "declare default element namespace 'http://www.w3.org/2005/Atom';"
        XmlRole { name: "pics"; query: "link[@rel='enclosure']/@href/string()" }
    }
}
