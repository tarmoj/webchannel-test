<CsoundSynthesizer>

<CsOptions>

-odac -d

</CsOptions>

<CsHtml5>

<!DOCTYPE html>
<html>
  <head>
  </head>

  <body bgcolor="lightgrey">
   HTML5<->Csound test<br> 
   <br>
   <button id="button" onclick='csound.readScore("i 1 0 1")' >Event</button>
   <input type="range" id="slider" oninput='csound.setControlChannel("testChannel",this.value/100.0);'></input>
   <br>
	Csound status: <label id="label">x</label><br>
   <br>
  </body>

</html>



</CsHtml5>

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
  out poscil(0.1,ifreq)


endin



; schedule 1,0,0.1, 1



</CsInstruments>

<CsScore>
i 1 0 0.1 ; to hear if Csound is loaded
f 0 3600


</CsScore>

</CsoundSynthesizer>


