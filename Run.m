% This is a script meant to build, and also run tests for audio files
% This matlab script should be run in commandline
%
% STEP 1 - Load the latest GNU to run the software.
% STEP 2 - make changes in make file suitable for platform
% STEP 3 - give make command to build the software
%
%


%STEP 1
%we check the platfrom. Defaults to unix
LINUX = 0;
WIN = 1;
MAC = 2;

platform = LINUX;
if ispc == 1
    platform = WIN;
elseif isunix == 1
    platform = LINUX;
end

if platform == LINUX
    system('module load GNU/8.2.0-2.31.1');
    system('cp makefiles/makefile.defs.linux.barren ./makefile.defs')
elseif platform == WIN
    system('cp makefiles/makefile.defs.mingw64 ./makefile.defs')
end

system('make -j32 all')
