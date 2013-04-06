import QtQuick 1.1
import com.nokia.extras 1.0
// import "Constants.js" as Constants

InfoBanner {
    id: infoBanner
    timerEnabled: true
    text: ""
    // functions
    function showText(mText) {
        text = mText;
        infoBanner.show();
    }
}
