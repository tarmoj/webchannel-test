<CsoundSynthesizer>

<CsOptions>

-odac -d

</CsOptions>

<CsHtml5>

<!DOCTYPE html>

<html>

<head>

<style type="text/css">

button.bigbutton { width: 50px; height : 30px; } 

</style>

</head>

<body>

<h1> My html</h1>

<button class="bigbutton" onclick='csound.readScore("i 1 0 1 1")'">NEXT</button><br><br><br>

<button class="bigbutton" onclick='csound.readScore("i 1 0 0.1 -1")'>Previous</button>

</body>

</html>

</CsHtml5>

<CsInstruments>



sr = 44100

nchnls = 2

0dbfs = 1

ksmps = 32

chn_k "testChannel", 3
chnset 0.5, "testChannel"



instr 1 ; send 1 for NEXT and  -1 for previous

  ivalue = p4

  print ivalue
  ifreq= 200+chnget:i("testChannel")*500	
  out poscil(0.1,ifreq)

  ;OSCsend 1, "192.168.1.201",7077,"/android","i", ivalue

endin



; schedule 1,0,0.1, 1



</CsInstruments>

<CsScore>
i 1 0 0.5
f 0 3600


</CsScore>

</CsoundSynthesizer>



<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>100</x>
 <y>100</y>
 <width>320</width>
 <height>240</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="nobackground">
  <r>255</r>
  <g>255</g>
  <b>255</b>
 </bgcolor>
</bsbPanel>
<bsbPresets>
</bsbPresets>
