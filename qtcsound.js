// qtcound.js - necessary functionality to use html5/javascript from CsoundQt or other Qt based program



var csound ;


window.addEventListener('load', initialize_qt, false);

// Initialise connection to QT C++
function initialize_qt() {
        console.log("INIT");
        if (typeof qt != 'undefined') new QWebChannel(qt.webChannelTransport, function(channel) {
                csound = channel.objects.csound; // use something like  QWebchannel::registerObject("csound", &cs) ; in C++ where cs is the object handling Csound encessary methods
        } );
}


// this way functions could be wrapped to check if Csound is loaded OK, but it may be also skipped
function scoreEvent(event) {
    if (typeof csound !== 'undefined') {
        csound.scoreEvent(event);
    }
}

function setControlChannel(channel, value) {
    console.log("Channel "+channel+" value: "+ value);
    if (typeof csound !== 'undefined') {
        csound.setChannel(channel, value) ;
    }
}

