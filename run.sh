#files=("run29_1" "run30_1" "run31_1" "run32_1" "run33_1" "run34_1")
#for filename in ${files[*]}
#do
#  root -q -l "signalSearch_noCut.C(\"$filename\")" > "$filename".log
#  printf "%s\n" $filename
#done

#files=("signal_run20_1" "signal_run21_1" "signal_run22_1" "signal_run23_1" "signal_run24_1" "signal_run25_1" "signal_run26_1" "signal_run27_1" "signal_run28_1" "signal_run29_1" "signal_run30_1" "signal_run31_1" "signal_run32_1" "signal_run33_1" "signal_run34_1" "signal_run35_1" "signal_run36_1" "signal_run37_1" "signal_run38_1")
files=("signal_run29_1" "signal_run30_1" "signal_run31_1" "signal_run32_1" "signal_run33_1" "signal_run34_1")
for filename in ${files[*]}
do
  root -q -l "signalSelection.C(\"$filename\")" > "$filename".log
  printf "%s\n" $filename
done
