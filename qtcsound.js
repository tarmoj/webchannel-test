// qtcound.js - necessary functionality to use html5/javascript from CsoundQt or other Qt based program



var csound ;
var currentChannel= null, currentValue = null;

window.addEventListener('load', initialize_qt, false);



// Initialise connection to QT C++
function initialize_qt() {
        console.log("INIT");
        if (typeof qt != 'undefined') new QWebChannel(qt.webChannelTransport, function(channel) {
                csound = channel.objects.csound; // use something like  QWebchannel::registerObject("csound", &cs) ; in C++ where cs is the object handling Csound encessary methods
                csound.test("INIT");

                // seems that the signal connections should be connected here

                csound.newChannelValue.connect( function(channelName, value) { // a signal from csound getControlChanel
                            currentChannel=channelName; currentValue=value;
                            alert("New value! " + value);
                            csound.test("from newChannelValue"+value);

                 });

        } );
}


// this way functions could be wrapped to check if Csound is loaded OK, but it may be also skipped
function scoreEvent(event) {
    if (typeof csound !== 'undefined') {
        csound.scoreEvent(event);
    }
}


function getChannel(channel){  // with promise
    var channelValue;
    var promise = new Promise(function(fulfill, reject) {

            csound.getControlChannel(channel, function(ret) {
                    //alert("INNER "+ret);
                    fulfill(ret);
                });
        });
    promise.then(function(value) {
        alert("THEN "+value)
        channelValue = value; // How on earth to get getChannel to return the value?
    },  function(value) {
            console.log('Error in getChannel');
        }
    );
}


function getChannel2(channel){
     csound.getControlChannel(channel);
//    csound.getControlChannel(channel, function(ret){
//        currentChannel = channel;
//        currentValue = ret; // the value is received correctyl here.
//        alert("INNER"+currentValue);  // the value is received correctyl here.
//    });

    // wait until value is set
    var start = new Date().getTime();
    var timeOut = 1000; // TODO sr/ksmps*4 for any case
    var now = start;
    while (now < start + timeOut) {  // && currentValue===null
         now = new Date().getTime();
    }

    alert("GOT VALUE"+currentValue); // does not work... sinse gets evaluated before async call returns
    currentValue = null; currentChannel = null;
    return currentValue;

}

function getChannel3(channel){
    csound.getControlChannel(channel);
    // wait until value is set

    var start = new Date().getTime();
    var timeOut = 1000; // TODO sr/ksmps*4 for any case
    var now = start;
    while (now < start + timeOut) {  // && currentValue===null
         now = new Date().getTime();
    }

    var v = csound.lastChannelValue;
    //alert("VALUE: "+v);
    return v;
}



