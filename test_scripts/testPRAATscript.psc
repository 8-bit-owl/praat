form Voice_analysis
   text name ''
endform
Read from file... 'name$'
name$ = selected$("Sound")

To Pitch (cc)... 0 60 15 no 0.03 0.25 0.01 0.35 0.14 300
select Sound 'name$'
To PointProcess (periodic, cc)... 60 300

select PointProcess 'name$'
plus Pitch 'name$'
plus Sound 'name$'
voiceReport$ = Voice report... 0 0 60 300 1.3 1.6 0.03 0.25

jitter = extractNumber (voiceReport$, "Jitter (local): ")
jitter_abs = extractNumber (voiceReport$, "Jitter (local, absolute): ")
jitter_rap = extractNumber (voiceReport$, "Jitter (rap): ")
jitter_ppq5 = extractNumber (voiceReport$, "Jitter (ppq5): ")
jitter_ddp = extractNumber (voiceReport$, "Jitter (ddp): ")

shimmer = extractNumber (voiceReport$, "Shimmer (local): ")
shimmer_db = extractNumber (voiceReport$, "Shimmer (local, dB): ")
shimmer_apq3 = extractNumber (voiceReport$, "Shimmer (apq3): ")
shimmer_apq5 = extractNumber (voiceReport$, "Shimmer (apq5): ")
shimmer_apq11 = extractNumber (voiceReport$, "Shimmer (apq11): ")
shimmer_dda = extractNumber (voiceReport$, "Shimmer (dda): ")

nhr = extractNumber (voiceReport$, "Mean noise-to-harmonics ratio: ")
hnr = extractNumber (voiceReport$, "Mean harmonics-to-noise ratio: ")

filedelete testPRAATscript.txt
fileappend testPRAATscript.txt 'jitter:8''newline$'
fileappend testPRAATscript.txt 'jitter_abs:8''newline$'
fileappend testPRAATscript.txt 'jitter_rap:8''newline$'
fileappend testPRAATscript.txt 'jitter_ppq5:8''newline$'
fileappend testPRAATscript.txt 'jitter_ddp:8''newline$'
fileappend testPRAATscript.txt 'shimmer:8''newline$'
fileappend testPRAATscript.txt 'shimmer_db:8''newline$'
fileappend testPRAATscript.txt 'shimmer_apq3:8''newline$'
fileappend testPRAATscript.txt 'shimmer_apq5:8''newline$'
fileappend testPRAATscript.txt 'shimmer_apq11:8''newline$'
fileappend testPRAATscript.txt 'shimmer_dda:8''newline$'
fileappend testPRAATscript.txt 'nhr:8''newline$'
fileappend testPRAATscript.txt 'hnr:8''newline$'