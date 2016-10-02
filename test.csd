<CsoundSynthesizer>

<CsOptions>

-odac -d

</CsOptions>
<html>
  <head>
  </head>
  <body bgcolor="lightgrey">
  <script>
  function onGetControlChannelCallback(value) {
    document.getElementById('testChannel').innerHTML = value;
   }
  function getChannelWithPromise(channel) {
    var v = getChannel("testChannel");
    document.getElementById("testChannelPromise").innerHTML = v;
   }
  </script>
   HTML5<->Csound test<br>
   <br>
   <button id="button" onclick='csound.readScore("i 1 0 1")' >Event</button>
   <input type="range" id="slider" oninput='csound.setControlChannel("testChannel",this.value/100.0); '></input><br>
   Get channel from csound with callback: <label id="getchannel"></label> <button onclick='csound.getControlChannel("testChannel", onGetControlChannelCallback)' >Get</button>
   Get channel from csound with promise: <label id="getchannel_promise"></label>
   <button onclick='getChannelWithPromise()'>Get</button>
   <br>
	Csound status: <label id="label">x</label><br>
        testChannel (callback):  <label id="testChannel"></label><br>
        testChannel (promise):  <label id="testChannelPromise"></label><br>
   <br>
  </body>
</html>
<CsInstruments>

sr = 44100
nchnls = 2
0dbfs = 1
ksmps = 32
chn_k "testChannel", 3
chnset 0.5, "testChannel" ; to test chnget in the host

instr 1 
  ifreq= 200+chnget:i("testChannel")*500	
  print ifreq
  out poscil(0.5,ifreq)
endin

; schedule 1,0,0.1, 1

</CsInstruments>
<CsScore>
i 1 0 0.1 ; to hear if Csound is loaded
f 0 3600
</CsScore>
</CsoundSynthesizer>


