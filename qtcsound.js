// qtcound.js - necessary functionality to use html5/javascript from CsoundQt or other Qt based program

// See https://medium.com/@bluepnume/learn-about-promises-before-you-start-using-async-await-eb148164a9c8#.22714eqie.

window.addEventListener('load', initialize_qt, false);

var channel;
var csound;

// Initialise connection to QT C++
function initialize_qt() {
    console.log("INIT");
    if (typeof qt !== 'undefined') {
        // Use something like  QWebchannel::registerObject("csound", &cs) ; in C++ where cs is the object exposing Csound methods.
        channel = new QWebChannel(qt.webChannelTransport, function(channel) {
            csound = channel.objects.csound;
            csound.test("INIT");
        });
    }
}



// This way functions could be wrapped to check if Csound is loaded OK, but it may be also skipped.

function scoreEvent(event) {
    if (typeof csound !== 'undefined') {
        csound.scoreEvent(event);
    }
}

// Here, 'returning: undefined' is printed before 'resolved: value' is printed.
// In order to force getChannel to wait, either it will have to loop until channelValue is not undefined,
// or we will have to wait for ECMAScript 7 to arrive, with 'async' and 'await'.
// The upshot is, promises do nothing more the existing callback option for async functions in
// QWebChannel; and with ECMAScript 7, promises will not be necessary (actually will be
// implicitly created by declaring 'async' -- and 'await' will wait for 'then.'

function getChannel(channel_name){
    var channelValue;
    var promise = new Promise(function(resolve, reject) {
        csound.getControlChannel(channel_name, function(value) {
            resolve(value);
        });
    });
    channel_value = promise.then(
        function(value) {
            channelValue = value;
            csound.test('resolved: ' + channelValue);
            return value;
        },
        function(value) {
            console.log('Error in getChannel');
        }
    );
    csound.test('returning: ' + channelValue)
    return channelValue;
}


