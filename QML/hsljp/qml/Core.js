var REITTIOPAS = 'http://api.reittiopas.fi/hsl/prod/';
var USER = 'hsljp';
var PASS = 'hsljp';
var COORDINATES = "4326"; // use WGS84(World Geodetic System) format
var FORMAT = "json";
var TRANSPORT_TYPES = "";
var DETAIL = "limited";
var LOCTYPE = "street|address|poi"
// http get
function _http_get(parameters, success) {
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
        if (req.readyState == XMLHttpRequest.DONE) {
            // debug
            console.log("status: " + req.status);
            try {
                var json = eval(req.responseText);
                success(json);
            }
            catch (error) {
                appWindow.popPage();
                appWindow.showNotifyBanner("server error, please try again");
                console.log("error catched");
            }
        }
    }
    // add default parameters
    parameters.epsg_in = COORDINATES;
    parameters.epsg_out = COORDINATES;
    parameters.user = USER;
    parameters.pass = PASS;
    parameters.format = FORMAT;
    // encode parameters to a query string
    var query = [];
    for(var p in parameters) {
        query.push(p + "=" + parameters[p]);
    }
    console.log( REITTIOPAS + '?' + query.join('&')  );
    req.open("GET", REITTIOPAS + '?' + query.join('&') );
    req.send();
}
// location to address
function location_to_address( latitude, longitude, success ) {
    var parameters = {};
    parameters.request = 'reverse_geocode';
    parameters.coordinate = longitude + ',' + latitude;
    _http_get(parameters, function(json) {
                  success(json);
              } );
}
// address to location
function address_to_location(term, success) {
    var parameters = {};
    parameters.request = 'geocode';
    parameters.key = term;
    parameters.loc_types = LOCTYPE;
    _http_get(parameters, success );
}
// find route
function route(from, to, time, mode, success) {
    var parameters = {};
    parameters.request = 'route';
    parameters.from = from;
    parameters.to = to;
    // TODO may be broken
    parameters.date =  Qt.formatDate( time , 'yyyyMMdd' );
    parameters.time = Qt.formatTime( time, 'hhmm');
    parameters.timetype = mode;
    parameters.show = 5;
    parameters.transport_types = TRANSPORT_TYPES;
    parameters.detail = DETAIL;
    _http_get( parameters, success );
}
