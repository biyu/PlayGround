function startLoad() {
    // loading start, run busy indicator
    routeResultPage.loading = true;
    if(startPointValue == "Current Location") {
        loadStartPointValue();
        // debug
        console.log("location address ...");
    }
    else {
        showList();
    }
}
function showList() {
    routeResultPage.setProcessText("loading route ...");
    // show header with start point and destination
    showHeader();
    // load list
    Core.route(routeResultPage.startPointCoords, routeResultPage.destinationCoords,
               new Date(), 'departure', loadRouteData);
    // debug
    console.log("show list now");
}
function showHeader() {
    routeResultList.setHeaderText(routeResultPage.startPointValue, routeResultPage.destinationValue)
    console.log(startPointValue + " , " + destinationValue);
}
function loadStartPointValue() {
    routeResultPage.setProcessText("locating address ...");
    var longitude = locator.getCurrentPosition().longitude;
    var latitude = locator.getCurrentPosition().latitude;
    // get address based on location
    Core.location_to_address(latitude, longitude, function(response) {
                                 routeResultPage.startPointValue = response[0].name;
                                 routeResultPage.startPointCoords = response[0].coords;
                                 // now show list
                                 showList();
                                 // debug
                                 console.log("startPointAddress:" + routeResultPage.startPointValue);
                             } );
}
function loadRouteData(response) {
    // for initial release, only handle one route (the best one
    for( var index in response ) {
        var route = response[index][0];
        // route brief info
        var briefInfo = {};
        var walking = 0;
        // array for points of single route
        var points = [];
        for( var leg in route.legs ) {
            leg = route.legs[leg];
            leg = Parser.decode( leg )
            points.push( {"leg": leg} );
            if(leg.type == 'walk') {
                walking += parseFloat(leg.length);
            }
        }
        // add points of single route into list
        briefInfo.duration = route.duration/60;
        briefInfo.arrival = points[points.length-1].leg.last.time;
        briefInfo.walking = walking.toFixed(1);
        routeResultList.addSingleRouteInfo(points, briefInfo);
    }
    routeResultPage.loading = false;
    console.log("Loading Complete");
}
