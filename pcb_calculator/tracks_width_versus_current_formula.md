If you specify the maximum current, then the trace widths will be calculated to suit.

If you specify one of the trace widths, the maximum current it can handle will be calculated. The width for the other trace to also handle this current will then be calculated.

The controlling value is shown in bold.

The calculations are valid for currents up to 35A (external) or 17.5A (internal), temperature rises up to 100 deg C, and widths of up to 400mil (10mm).

The formula, from IPC 2221, is
<center>__I = K * dT<sup>0.44</sup> * (W*H)<sup>0.725</sup>__</center>
where:  
__I__ = maximum current in amps  
__dt__ = temperature rise above ambient in deg C  
__W,H__ = width and thickness in mils  
__K__ = 0.024 for internal traces or 0.048 for external traces
