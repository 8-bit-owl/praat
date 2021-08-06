%system('./praat_barren testPRAATscript.psc testAUDIOfile.wav')

tmppraatwav_psc='testPRAATscript.psc';
tmppraatwav='testAUDIOfile';
if ispc == 1
	commstring = ['praatcon ' tmppraatwav_psc ' ' tmppraatwav '.wav'];
elseif isunix == 1
	commstring = ['./praat_barren ' tmppraatwav_psc ' ' tmppraatwav '.wav'];
end
[s, w] = system(commstring,'-echo');
