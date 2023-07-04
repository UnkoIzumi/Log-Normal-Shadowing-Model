#Formula Distance Log-Normal Shadowing Models

in Log-Normal Shadowing Model after to get shadowing value using library with parameter standard deviation (Sigma), then go to next formula to get Distance. So formula :

<b>Distance = ref_d0 * 10^-(Pt(d) - ((PL(d0) - PL(d)) + Shadowing) / 10 * n)</b>

where:
ref_d0 is the distance reference in 1 meters
Pt(d) is the Power Transmitter in Wifi
Shadowing is the value in log-normal shadowing model calculate
PL(d) is the path loss at distance d,
PL(d0) is the path loss at the reference distance d0,
n is the path loss exponent, and
d and d0 are the distances.

----------------->

<h2>Smoothing RSSI</h2>
 how to get stabilized RSSI value, because to bigger weight, then use formula EMU so alpha is the weight determination for konstan value RSSI :

 <b>smoothedRssi =  alpha * rssi + (1 - alpha) * smoothedRssi;</b>.
