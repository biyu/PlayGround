.pragma library
// data
var favorites = [];

function loadFavorites() {
    favorites = [];
    var db = openDatabaseSync("HSLJPDB", "1.0", "HSLJP Database", 1000000);
    console.log("load favorites")
    db.transaction( function(tx) {
                       // create the database if it doesn't already exist
                       tx.executeSql('CREATE TABLE IF NOT EXISTS Favorites(name TEXT, value TEXT, coords TEXT)');
                       // show all added favorites
                       var result = tx.executeSql('SELECT * FROM Favorites');
                       // check whether there is favorite data or not
                       if(result.rows.length == 0) {
                           console.log("no favorite data")
                           return;
                       }
                       // push single favorite into favotites
                       for(var i=0; i<result.rows.length; i++) {
                           favorites.push(result.rows.item(i));
                           // debug
                           console.log("name: " + result.rows.item(i).name + " value: " + result.rows.item(i).value + " coords: " + result.rows.item(i).coords)
                       }
                   } )
}

function addSingleFavorite(name, value, coords, listUpdate) {
    var db = openDatabaseSync("HSLJPDB", "1.0", "HSLJP Database", 1000000);
    db.transaction( function(tx) {
                       // Add (another) favorite row
                       tx.executeSql('INSERT INTO Favorites VALUES(?, ?, ?)', [ name, value, coords ]);
                   } )
    // update list after adding favorite
    listUpdate(name, value, coords);
    // reload favorites
    loadFavorites();
    // debug
    console.log("add favorite");
}

function deleteSingleFavorite(name, listUpdate) {
    var db = openDatabaseSync("HSLJPDB", "1.0", "HSLJP Database", 1000000);
    db.transaction( function(tx) {
                       // Add (another) favorite row
                       tx.executeSql('DELETE FROM Favorites WHERE name=?', [name]);
                   } )
    // update list after deleting favorite
    listUpdate();
    // reload favorites
    loadFavorites();
    // debug
    console.log("delete favorite");
}
