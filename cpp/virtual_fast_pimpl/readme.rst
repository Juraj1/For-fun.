Building version A:
cmake -DOS_A=ON -DOS_B=OFF .  && make

Building version B:
cmake -DOS_A=OFF -DOS_B=ON . && make
