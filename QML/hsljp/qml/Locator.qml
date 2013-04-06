import QtQuick 1.1
import com.meego 1.0
import QtMobility.location 1.2

PositionSource {
    id: positionSource
    updateInterval: 0
    // functions
    function getCurrentPosition() {
        var coordinate = { "latitude": 0.0, "longitude": 0.0 };
        // update current position
        coordinate.latitude = position.coordinate.latitude;
        coordinate.longitude = position.coordinate.longitude;
        return coordinate;
    }
    function setActiveStatus(status) {
        active = status
    }
    function isAvalible() {
        return !(isNaN(position.coordinate.latitude) || isNaN(position.coordinate.longitude));
    }
}
