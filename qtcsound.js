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


csound.getControlChannel(channel, function(returnValue) {
        // This callback will be invoked when myMethod has a return value. Keep in mind that
        // the communication is asynchronous, hence the need for this callback.
        console.log(returnValue);
        document.getElementById("getchannel").innerHTML = returnValue; //for testing
        
});

