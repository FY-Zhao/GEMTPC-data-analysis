# GEMTPC-data-analysis
Analysis script for GEMTPC measurement data. It's based on CERN ROOT framework 
It includes three part:
1. convert text data to Tree file, which will be more compact;
2. Search peaks over the 2D distribution for ADC in "channel" and "time" direction, recording messeges in a user-defined class "Signal";
3. Carry out analysis according to these signals.
